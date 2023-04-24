#include "DiagramItem.hpp"
#include "Arrow.hpp"

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>

DiagramItem::DiagramItem(DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent)
	: QGraphicsPolygonItem(parent)
	, m_myDiagramType(diagramType)
	, m_myContextMenu(contextMenu)
{
	QPainterPath path;
	switch (m_myDiagramType)
	{
		case DiagramType::StartEnd:
			path.moveTo(200, 50);
			path.arcTo(150, 0, 50, 50, 0, 90);
			path.arcTo(50, 0, 50, 50, 90, 90);
			path.arcTo(50, 50, 50, 50, 180, 90);
			path.arcTo(150, 50, 50, 50, 270, 90);
			path.lineTo(200, 25);
			m_myPolygon = path.toFillPolygon();
			break;
		case DiagramType::Conditional:
			m_myPolygon << QPointF(-100, 0) << QPointF(0, 100) << QPointF(100, 0) << QPointF(0, -100)
						<< QPointF(-100, 0);
			break;
		case DiagramType::Step:
			m_myPolygon << QPointF(-100, -100) << QPointF(100, -100) << QPointF(100, 100) << QPointF(-100, 100)
						<< QPointF(-100, -100);
			break;
		default:
			m_myPolygon << QPointF(-120, -80) << QPointF(-70, 80) << QPointF(120, 80) << QPointF(70, -80)
						<< QPointF(-120, -80);
			break;
	}
	setPolygon(m_myPolygon);
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void DiagramItem::removeArrow(Arrow *arrow)
{
	m_arrows.removeAll(arrow);
}

void DiagramItem::removeArrows()
{
	// need a copy here since removeArrow() will
	// modify the m_arrows container
	const auto arrowsCopy = m_arrows;
	for (Arrow *arrow : arrowsCopy)
	{
		arrow->startItem()->removeArrow(arrow);
		arrow->endItem()->removeArrow(arrow);
		scene()->removeItem(arrow);
		delete arrow;
	}
}

void DiagramItem::addArrow(Arrow *arrow)
{
	m_arrows.append(arrow);
}

QPixmap DiagramItem::image() const
{
	QPixmap pixmap(250, 250);
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);
	painter.setPen(QPen(Qt::black, 8));
	painter.translate(125, 125);
	painter.drawPolyline(m_myPolygon);

	return pixmap;
}

void DiagramItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	scene()->clearSelection();
	setSelected(true);
	m_myContextMenu->popup(event->screenPos());
}

QVariant DiagramItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == QGraphicsItem::ItemPositionChange)
	{
		for (Arrow *arrow : std::as_const(m_arrows))
			arrow->updatePosition();
	}

	return value;
}
