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

	enum class HandleAnchor
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
		QRectF currentrect = this->rect();
		painter->setPen(QPen(Qt::black, 1));
		painter->drawRect(currentrect);
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
	void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE
	{
		m_anchor = getHandleAnchor(event->pos());
		QGraphicsRectItem::mousePressEvent(event);
	}

	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE
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

	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE
	{
		m_anchor = HandleAnchor::None;
		QGraphicsRectItem::mouseReleaseEvent(event);
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
			return HandleAnchor::TopLeft;
		if ((tr - point).manhattanLength() <= 4)
			return HandleAnchor::TopRight;
		if ((bl - point).manhattanLength() <= 4)
			return HandleAnchor::BottomLeft;
		if ((br - point).manhattanLength() <= 4)
			return HandleAnchor::BottomRight;
		if ((mt - point).manhattanLength() <= 4)
			return HandleAnchor::Top;
		if ((mb - point).manhattanLength() <= 4)
			return HandleAnchor::Bottom;
		if ((ml - point).manhattanLength() <= 4)
			return HandleAnchor::Left;
		if ((mr - point).manhattanLength() <= 4)
			return HandleAnchor::Right;

		return HandleAnchor::None;
	}

	HandleAnchor m_anchor = HandleAnchor::None;
};