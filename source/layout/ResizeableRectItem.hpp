#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QMouseEvent>

class ResizableRectItem : public QGraphicsRectItem
{
public:
	ResizableRectItem(QGraphicsItem *parent = nullptr)
		: QGraphicsRectItem(parent)
	{
		setFlags(ItemIsSelectable | ItemIsMovable | ItemSendsGeometryChanges);
		setCursor(Qt::SizeAllCursor);
	}

	enum HandleAnchor
	{
		TopLeft,
		Top,
		TopRight,
		Right,
		BottomRight,
		Bottom,
		BottomLeft,
		Left,
		None
	};

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override
	{
		QGraphicsRectItem::paint(painter, option, widget);
		const qreal handleSize	= 8;
		const qreal handleSpace = 2;
		QRectF		rect		= boundingRect();
		QPointF		tl			= rect.topLeft();
		QPointF		tr			= rect.topRight();
		QPointF		bl			= rect.bottomLeft();
		QPointF		br			= rect.bottomRight();
		QPointF		mt			= rect.topLeft() + QPointF(rect.width() / 2, 0);
		QPointF		mb			= rect.bottomLeft() + QPointF(rect.width() / 2, 0);
		QPointF		ml			= rect.topLeft() + QPointF(0, rect.height() / 2);
		QPointF		mr			= rect.topRight() + QPointF(0, rect.height() / 2);
		QRectF		handleRect;
		handleRect.setSize(QSizeF(handleSize, handleSize));
		handleRect.moveCenter(tl);
		painter->drawRect(handleRect);
		handleRect.moveCenter(tr);
		painter->drawRect(handleRect);
		handleRect.moveCenter(bl);
		painter->drawRect(handleRect);
		handleRect.moveCenter(br);
		painter->drawRect(handleRect);
		handleRect.moveCenter(mt);
		painter->drawRect(handleRect);
		handleRect.moveCenter(mb);
		painter->drawRect(handleRect);
		handleRect.moveCenter(ml);
		painter->drawRect(handleRect);
		handleRect.moveCenter(mr);
		painter->drawRect(handleRect);
	}

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE { m_anchor = getHandleAnchor(event->pos()); }

	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE
	{
		if (m_anchor != None)
		{
			QRectF	rect  = this->rect();
			QPointF delta = event->pos() - event->lastPos();
			switch (m_anchor)
			{
				case TopLeft:
					rect.setTopLeft(rect.topLeft() + delta);
					break;
				case Top:
					rect.setTop(rect.y() + delta.y());
					break;
				case TopRight:
					rect.setTopRight(rect.topRight() + delta);
					break;
				case Right:
					rect.setRight(rect.right() + delta.x());
					break;
				case BottomRight:
					rect.setBottomRight(rect.bottomRight() + delta);
					break;
				case Bottom:
					rect.setBottom(rect.bottom() + delta.y());
					break;
				case BottomLeft:
					rect.setBottomLeft(rect.bottomLeft() + delta);
					break;
				case Left:
					rect.setLeft(rect.left() + delta.x());
					break;
				default:
					break;
			}
			setRect(rect);
		}
	}

	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE
	{
		Q_UNUSED(event)
		m_anchor = None;
	}

private:
	HandleAnchor getHandleAnchor(const QPointF &point) const
	{
		QRectF	rect = this->rect();
		QPointF tl	 = rect.topLeft();
		QPointF tr	 = rect.topRight();
		QPointF bl	 = rect.bottomLeft();
		QPointF br	 = rect.bottomRight();
		QPointF mt	 = rect.topLeft() + QPointF(rect.width() / 2, 0);
		QPointF mb	 = rect.bottomLeft() + QPointF(rect.width() / 2, 0);
		QPointF ml	 = rect.topLeft() + QPointF(0, rect.height() / 2);
		QPointF mr	 = rect.topRight() + QPointF(0, rect.height() / 2);

		if ((tl - point).manhattanLength() <= 4)
			return TopLeft;
		if ((tr - point).manhattanLength() <= 4)
			return TopRight;
		if ((bl - point).manhattanLength() <= 4)
			return BottomLeft;
		if ((br - point).manhattanLength() <= 4)
			return BottomRight;
		if ((mt - point).manhattanLength() <= 4)
			return Top;
		if ((mb - point).manhattanLength() <= 4)
			return Bottom;
		if ((ml - point).manhattanLength() <= 4)
			return Left;
		if ((mr - point).manhattanLength() <= 4)
			return Right;

		return None;
	}

	HandleAnchor m_anchor = None;
};