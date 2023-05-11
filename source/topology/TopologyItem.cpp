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

static const qreal ANCHOR_SIZE = 10;

TopologyItem::TopologyItem(TopologyType diagramType, QGraphicsItem *parent)
	: QGraphicsPixmapItem(parent)
	, m_myDiagramType(diagramType)
{
	// We still create the polygon as it's abused for line drawing
	switch (m_myDiagramType)
	{
		case TopologyType::KMBox:
			m_myPixMap.load(":/images/KMBox.png");
			break;
		case TopologyType::Server:
			m_myPixMap.load(":/images/server.png");
			m_myPixMap = m_myPixMap.scaled(125, 125);
			break;
		case TopologyType::Display:
			m_myPixMap.load(":/images/display.png");
			m_myPixMap = m_myPixMap.scaled(175, 125);
			break;
		default:
			qDebug() << "Invalid type passed";
			break;
	}
	setPixmap(m_myPixMap);
	setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsGeometryChanges);

	// Create four anchor points in the corners of the pixmap
	// TODO - needs to be adjusted per different topology item
	if (m_myDiagramType == TopologyType::KMBox)
	{
		const QPointF USB1Anchor(m_myPixMap.width() / 6 * 1 - ANCHOR_SIZE / 2, m_myPixMap.height() - ANCHOR_SIZE);
		const QPointF USB2Anchor(m_myPixMap.width() / 6 * 2 - ANCHOR_SIZE / 2, m_myPixMap.height() - ANCHOR_SIZE);
		const QPointF USB3Anchor(m_myPixMap.width() / 6 * 3 - ANCHOR_SIZE / 2, m_myPixMap.height() - ANCHOR_SIZE);
		const QPointF USB4Anchor(m_myPixMap.width() / 6 * 4 - ANCHOR_SIZE / 2, m_myPixMap.height() - ANCHOR_SIZE);
		const QPointF USB5Anchor(m_myPixMap.width() / 6 * 5 - ANCHOR_SIZE / 2, m_myPixMap.height() - ANCHOR_SIZE);
		m_anchors.emplace_back("usb1", createAnchor(USB1Anchor));
		m_anchors.emplace_back("usb2", createAnchor(USB2Anchor));
		m_anchors.emplace_back("usb3", createAnchor(USB3Anchor));
		m_anchors.emplace_back("usb4", createAnchor(USB4Anchor));
		m_anchors.emplace_back("usb5", createAnchor(USB5Anchor));
	}
	else if (m_myDiagramType == TopologyType::Display)
	{
		const QPointF topMiddleAnchor(m_myPixMap.width() / 2 - ANCHOR_SIZE, 0);
		m_anchors.emplace_back("VideoIn", createAnchor(topMiddleAnchor));
	}
	else if (m_myDiagramType == TopologyType::Server)
	{
		const QPointF topMiddleAnchor(m_myPixMap.width() / 2 - ANCHOR_SIZE, 0);
		const QPointF topBottomAnchor(m_myPixMap.width() / 2 - ANCHOR_SIZE, m_myPixMap.height() - ANCHOR_SIZE);

		m_anchors.emplace_back("VideoOut", createAnchor(topMiddleAnchor));
		m_anchors.emplace_back("USB-B", createAnchor(topBottomAnchor));
	}
	else
	{
		qDebug() << "Can't create anchors for unknown type";
	}
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

QVariant TopologyItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == QGraphicsItem::ItemPositionChange)
	{
		for (Arrow *arrow : std::as_const(m_arrows))
		{
			arrow->updatePosition();
		}
	}

	return value;
}

void TopologyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	// Paint the pixmap as usual
	QGraphicsPixmapItem::paint(painter, option, widget);

	// Paint the anchor points
	for (const auto &[name, anchor] : m_anchors)
	{
		anchor->paint(painter, option, widget);
	}
}

QGraphicsEllipseItem *TopologyItem::createAnchor(const QPointF &pos)
{
	QGraphicsEllipseItem *anchor = new QGraphicsEllipseItem(QRectF(pos, QSizeF(ANCHOR_SIZE, ANCHOR_SIZE)), this);
	anchor->setPen(QPen(Qt::black, 1));
	anchor->setBrush(QBrush(Qt::red));
	anchor->setFlag(QGraphicsItem::ItemIsMovable, true);
	anchor->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
	return anchor;
}
