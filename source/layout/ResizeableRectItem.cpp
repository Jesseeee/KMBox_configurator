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

ResizeableRectItem::ResizeableRectItem(QGraphicsItem *parent)
	: QGraphicsRectItem(parent)
{
	setFlags(ItemIsSelectable | ItemIsMovable | ItemSendsGeometryChanges);
	setCursor(Qt::SizeAllCursor);
}

void ResizeableRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QGraphicsRectItem::paint(painter, option, widget);
	// TODO To fix the trailing squares left behind we need to restrict the squares to inside the rectangle
	// As we can't move the bounding rect outside the square as that would mess up redrawing
	// QRectF currentrect = this->rect();
	// painter->setPen(QPen(Qt::black, 1));
	// painter->drawRect(currentrect);
	const qreal	   handleSize  = 8;
	const qreal	   handleSpace = 2;
	QRectF		   rect		   = boundingRect();
	QPointF		   topLeft	   = rect.topLeft() + QPointF(4, 4);
	QPointF		   topRight	   = rect.topRight() + QPointF(-4, 4);
	QPointF		   bottomLeft  = rect.bottomLeft() + QPointF(4, -4);
	QPointF		   bottomRight = rect.bottomRight() + QPointF(-4, -4);
	QPointF		   midTop	   = rect.topLeft() + QPointF(rect.width() / 2, 4);
	QPointF		   midBottom   = rect.bottomLeft() + QPointF(rect.width() / 2, -4);
	QPointF		   midLeft	   = rect.topLeft() + QPointF(4, rect.height() / 2);
	QPointF		   midRight	   = rect.topRight() + QPointF(-4, rect.height() / 2);
	QList<QPointF> anchorList;
	anchorList << topLeft << topRight << bottomLeft << bottomRight << midTop << midBottom << midLeft << midRight;
	QRectF handleRect;
	handleRect.setSize(QSizeF(handleSize, handleSize));
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
		QRectF	rect  = this->rect();
		QPointF delta = event->pos() - event->lastPos();
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
	QRectF	rect		= this->rect();
	QPointF topLeft		= rect.topLeft() + QPointF(4, 4);
	QPointF topRight	= rect.topRight() + QPointF(-4, 4);
	QPointF bottomLeft	= rect.bottomLeft() + QPointF(4, -4);
	QPointF bottomRight = rect.bottomRight() + QPointF(-4, -4);
	QPointF midTop		= rect.topLeft() + QPointF(rect.width() / 2, 4);
	QPointF midBottom	= rect.bottomLeft() + QPointF(rect.width() / 2, -4);
	QPointF midLeft		= rect.topLeft() + QPointF(4, rect.height() / 2);
	QPointF midRight	= rect.topRight() + QPointF(-4, rect.height() / 2);

	if ((topLeft - point).manhattanLength() <= 8)
		return HandleAnchor::TopLeft;
	if ((topRight - point).manhattanLength() <= 8)
		return HandleAnchor::TopRight;
	if ((bottomLeft - point).manhattanLength() <= 8)
		return HandleAnchor::BottomLeft;
	if ((bottomRight - point).manhattanLength() <= 8)
		return HandleAnchor::BottomRight;
	if ((midTop - point).manhattanLength() <= 8)
		return HandleAnchor::Top;
	if ((midBottom - point).manhattanLength() <= 8)
		return HandleAnchor::Bottom;
	if ((midLeft - point).manhattanLength() <= 8)
		return HandleAnchor::Left;
	if ((midRight - point).manhattanLength() <= 8)
		return HandleAnchor::Right;

	return HandleAnchor::None;
}
