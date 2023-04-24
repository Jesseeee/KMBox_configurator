#include "Arrow.hpp"
#include "DiagramItem.hpp"

#include <QPainter>
#include <QPen>
#include <QtMath>

Arrow::Arrow(DiagramItem *startItem, DiagramItem *endItem, QGraphicsItem *parent)
	: QGraphicsLineItem(parent)
	, m_myStartItem(startItem)
	, m_myEndItem(endItem)
{
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setPen(QPen(m_myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF Arrow::boundingRect() const
{
	qreal extra = (pen().width() + 20) / 2.0;

	return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(), line().p2().y() - line().p1().y()))
		.normalized()
		.adjusted(-extra, -extra, extra, extra);
}

QPainterPath Arrow::shape() const
{
	QPainterPath path = QGraphicsLineItem::shape();
	path.addPolygon(m_arrowHead);
	return path;
}

void Arrow::updatePosition()
{
	QLineF line(mapFromItem(m_myStartItem, 0, 0), mapFromItem(m_myEndItem, 0, 0));
	setLine(line);
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	if (m_myStartItem->collidesWithItem(m_myEndItem))
		return;

	QPen myPen = pen();
	myPen.setColor(m_myColor);
	qreal arrowSize = 20;
	painter->setPen(myPen);
	painter->setBrush(m_myColor);

	QLineF	  centerLine(m_myStartItem->pos(), m_myEndItem->pos());
	QPolygonF endPolygon = m_myEndItem->polygon();
	QPointF	  p1		 = endPolygon.first() + m_myEndItem->pos();
	QPointF	  intersectPoint;
	for (int i = 1; i < endPolygon.count(); ++i)
	{
		QPointF					 p2(endPolygon.at(i) + m_myEndItem->pos());
		QLineF					 polyLine(p1, p2);
		QLineF::IntersectionType intersectionType(polyLine.intersects(centerLine, &intersectPoint));
		if (intersectionType == QLineF::BoundedIntersection)
			break;
		p1 = p2;
	}

	setLine(QLineF(intersectPoint, m_myStartItem->pos()));

	double angle = std::atan2(-line().dy(), line().dx());

	QPointF arrowP1 = line().p1() + QPointF(sin(angle + M_PI / 3) * arrowSize, cos(angle + M_PI / 3) * arrowSize);
	QPointF arrowP2
		= line().p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize, cos(angle + M_PI - M_PI / 3) * arrowSize);

	m_arrowHead.clear();
	m_arrowHead << line().p1() << arrowP1 << arrowP2;
	painter->drawLine(line());
	painter->drawPolygon(m_arrowHead);
	if (isSelected())
	{
		painter->setPen(QPen(m_myColor, 1, Qt::DashLine));
		QLineF myLine = line();
		myLine.translate(0, 4.0);
		painter->drawLine(myLine);
		myLine.translate(0, -8.0);
		painter->drawLine(myLine);
	}
}
