/**
 * @file TopologyItem.cpp
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
 * - May 06, 2023 ; jesvan
 */

#include "TopologyItem.hpp"
#include "Arrow.hpp"

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>

TopologyItem::TopologyItem(TopologyType diagramType, QGraphicsItem *parent)
	: QGraphicsPixmapItem(parent)
	, m_myDiagramType(diagramType)
{
	// We still create the polygon as it's abused for line drawing
	QPainterPath path;
	switch (m_myDiagramType)
	{
		case TopologyType::Server:
			m_myPolygon << QPointF(0, 0) << QPointF(100, 0) << QPointF(100, 100) << QPointF(0, 100) << QPointF(0, 0);
			m_myPixMap.load(":/images/server.png");
			m_myPixMap = m_myPixMap.scaled(125, 125);
			break;
		case TopologyType::Display:
			m_myPolygon << QPointF(0, 0) << QPointF(100, 0) << QPointF(100, 100) << QPointF(0, 100) << QPointF(0, 0);
			m_myPixMap.load(":/images/display.png");
			m_myPixMap = m_myPixMap.scaled(175, 125);
			break;
		default:
			m_myPolygon << QPointF(-120, -80) << QPointF(-70, 80) << QPointF(120, 80) << QPointF(70, -80)
						<< QPointF(-120, -80);
			break;
	}
	setPixmap(m_myPixMap);
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void TopologyItem::removeArrow(Arrow *arrow)
{
	m_arrows.removeAll(arrow);
}

void TopologyItem::removeArrows()
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

void TopologyItem::addArrow(Arrow *arrow)
{
	m_arrows.append(arrow);
}

QPixmap TopologyItem::image() const
{
	if (!m_myPixMap.isNull())
	{
		return m_myPixMap;
	}

	QPixmap pixmap(250, 250);
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);
	painter.setPen(QPen(Qt::black, 8));
	painter.translate(125, 125);
	painter.drawPolyline(m_myPolygon);

	return pixmap;
}

QVariant TopologyItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == QGraphicsItem::ItemPositionChange)
	{
		for (Arrow *arrow : std::as_const(m_arrows))
			arrow->updatePosition();
	}

	return value;
}
