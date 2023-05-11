/**
 * @file ResizeableRectItem.cpp
 *
 * @brief TODO
 *
 * &copy; Copyright 2023 ScioTeq bv. All rights reserved.
 * +-------------------------------------------------------------------------------------------+
 * |                             Export Control Information                                    |
 * +--------+-------------+-------------------------------------+----------->-------------------+
 * | Origin |   Country   |     Jurisdiction & Control List     |     Authorization number     |
 * +--------+-------------+-------------------------------------+------------------------------+
 * |    X   |   Belgium   |                 n/a                 |              n/a             |
 * |        |             +-------------------------------------+------------------------------+
 * |        |             |  Export control marking is not applicable to Belgian regulations.  |
 * +--------+-------------+--------------------------------------------------------------------+
 *
 * <H3>Purpose</H3>
 * - <!--purpose-->
 *
 * <H3>Notes</H3>
 * - <!--notes-->
 *
 * <H3>Author</H3>
 * - May 07, 2023 ; jesvan
 */

#include "ResizeableRectItem.hpp"

static const int32_t	 HANDLE_RECT_SIZE	  = 20;
static constexpr int32_t HANDLE_RECT_HALFSIZE = HANDLE_RECT_SIZE / 2;

ResizeableRectItem::ResizeableRectItem(QGraphicsItem *parent)
	: QGraphicsRectItem(parent)
{
	setFlags(ItemIsSelectable | ItemIsMovable | ItemSendsGeometryChanges);
	setCursor(Qt::SizeAllCursor);
}

void ResizeableRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QGraphicsRectItem::paint(painter, option, widget);
	QRectF		   rect		   = boundingRect();
	QPointF		   topLeft	   = rect.topLeft() + QPointF(HANDLE_RECT_HALFSIZE, HANDLE_RECT_HALFSIZE);
	QPointF		   topRight	   = rect.topRight() + QPointF(-HANDLE_RECT_HALFSIZE, HANDLE_RECT_HALFSIZE);
	QPointF		   bottomLeft  = rect.bottomLeft() + QPointF(HANDLE_RECT_HALFSIZE, -HANDLE_RECT_HALFSIZE);
	QPointF		   bottomRight = rect.bottomRight() + QPointF(-HANDLE_RECT_HALFSIZE, -HANDLE_RECT_HALFSIZE);
	QPointF		   midTop	   = rect.topLeft() + QPointF(rect.width() / 2, HANDLE_RECT_HALFSIZE);
	QPointF		   midBottom   = rect.bottomLeft() + QPointF(rect.width() / 2, -HANDLE_RECT_HALFSIZE);
	QPointF		   midLeft	   = rect.topLeft() + QPointF(HANDLE_RECT_HALFSIZE, rect.height() / 2);
	QPointF		   midRight	   = rect.topRight() + QPointF(-HANDLE_RECT_HALFSIZE, rect.height() / 2);
	QList<QPointF> anchorList;
	anchorList << topLeft << topRight << bottomLeft << bottomRight << midTop << midBottom << midLeft << midRight;
	QRectF handleRect;
	handleRect.setSize(QSizeF(HANDLE_RECT_SIZE, HANDLE_RECT_SIZE));
	for (const QPointF &location : anchorList)
	{
		handleRect.moveCenter(location);
		painter->drawRect(handleRect);
	}
}

void ResizeableRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	m_anchor = getHandleAnchor(event->pos());
	QGraphicsRectItem::mousePressEvent(event);
}

void ResizeableRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (m_anchor != HandleAnchor::None)
	{
		QRectF		  rect	= this->rect();
		const QPointF delta = event->pos() - event->lastPos();
		switch (m_anchor)
		{
			case HandleAnchor::TopLeft:
				rect.setTopLeft(rect.topLeft() + delta);
				break;
			case HandleAnchor::Top:
				rect.setTop(rect.y() + delta.y());
				break;
			case HandleAnchor::TopRight:
				rect.setTopRight(rect.topRight() + delta);
				break;
			case HandleAnchor::Right:
				rect.setRight(rect.right() + delta.x());
				break;
			case HandleAnchor::BottomRight:
				rect.setBottomRight(rect.bottomRight() + delta);
				break;
			case HandleAnchor::Bottom:
				rect.setBottom(rect.bottom() + delta.y());
				break;
			case HandleAnchor::BottomLeft:
				rect.setBottomLeft(rect.bottomLeft() + delta);
				break;
			case HandleAnchor::Left:
				rect.setLeft(rect.left() + delta.x());
				break;
			default:
				break;
		}
		setRect(rect);
		for (QGraphicsItem *item : childItems())
		{
			QPointF newPos = boundingRect().center() - item->boundingRect().center();
			item->setPos(newPos);
		}
	}
	else
	{
		QGraphicsRectItem::mouseMoveEvent(event);
	}
}

void ResizeableRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	m_anchor = HandleAnchor::None;
	QGraphicsRectItem::mouseReleaseEvent(event);
}

ResizeableRectItem::HandleAnchor ResizeableRectItem::getHandleAnchor(const QPointF &point) const
{
	QRectF		  rect		  = this->rect();
	const QPointF topLeft	  = rect.topLeft() + QPointF(HANDLE_RECT_HALFSIZE, HANDLE_RECT_HALFSIZE);
	const QPointF topRight	  = rect.topRight() + QPointF(-HANDLE_RECT_HALFSIZE, HANDLE_RECT_HALFSIZE);
	const QPointF bottomLeft  = rect.bottomLeft() + QPointF(HANDLE_RECT_HALFSIZE, -HANDLE_RECT_HALFSIZE);
	const QPointF bottomRight = rect.bottomRight() + QPointF(-HANDLE_RECT_HALFSIZE, -HANDLE_RECT_HALFSIZE);
	const QPointF midTop	  = rect.topLeft() + QPointF(rect.width() / 2, HANDLE_RECT_HALFSIZE);
	const QPointF midBottom	  = rect.bottomLeft() + QPointF(rect.width() / 2, -HANDLE_RECT_HALFSIZE);
	const QPointF midLeft	  = rect.topLeft() + QPointF(HANDLE_RECT_HALFSIZE, rect.height() / 2);
	const QPointF midRight	  = rect.topRight() + QPointF(-HANDLE_RECT_HALFSIZE, rect.height() / 2);

	if ((topLeft - point).manhattanLength() <= HANDLE_RECT_SIZE)
	{
		return HandleAnchor::TopLeft;
	}
	if ((topRight - point).manhattanLength() <= HANDLE_RECT_SIZE)
	{
		return HandleAnchor::TopRight;
	}
	if ((bottomLeft - point).manhattanLength() <= HANDLE_RECT_SIZE)
	{
		return HandleAnchor::BottomLeft;
	}
	if ((bottomRight - point).manhattanLength() <= HANDLE_RECT_SIZE)
	{
		return HandleAnchor::BottomRight;
	}
	if ((midTop - point).manhattanLength() <= HANDLE_RECT_SIZE)
	{
		return HandleAnchor::Top;
	}
	if ((midBottom - point).manhattanLength() <= HANDLE_RECT_SIZE)
	{
		return HandleAnchor::Bottom;
	}
	if ((midLeft - point).manhattanLength() <= HANDLE_RECT_SIZE)
	{
		return HandleAnchor::Left;
	}
	if ((midRight - point).manhattanLength() <= HANDLE_RECT_SIZE)
	{
		return HandleAnchor::Right;
	}

	return HandleAnchor::None;
}
