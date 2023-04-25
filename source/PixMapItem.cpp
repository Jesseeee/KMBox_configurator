/**
 * @file PixMapItem.cpp
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
 * - Apr 25, 2023 ; TODO
 */

#include "PixMapItem.hpp"
#include "DiagramItem.hpp"

#include "Arrow.hpp"

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>

PixMapItem::PixMapItem(PixMapDiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent)
	: QGraphicsPixmapItem(parent)
	, m_myDiagramType(diagramType)
	, m_myContextMenu(contextMenu)
{
	QPainterPath path;
	switch (m_myDiagramType)
	{
		case PixMapDiagramType::Server:
			if (!m_myPixMap.load(":/images/server.png"))
			{
				qDebug() << "Failed to load image";
			}

		default:
			qDebug() << "Pass a valid type";
			break;
	}

	m_myPixMap = m_myPixMap.scaled(125, 125);

	setPixmap(m_myPixMap);
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void PixMapItem::removeArrow(Arrow *arrow)
{
	m_arrows.removeAll(arrow);
}

void PixMapItem::removeArrows()
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

void PixMapItem::addArrow(Arrow *arrow)
{
	m_arrows.append(arrow);
}

QPixmap PixMapItem::image() const
{
	return m_myPixMap;
}

void PixMapItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	scene()->clearSelection();
	setSelected(true);
	m_myContextMenu->popup(event->screenPos());
}

QVariant PixMapItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == QGraphicsItem::ItemPositionChange)
	{
		for (Arrow *arrow : std::as_const(m_arrows))
			arrow->updatePosition();
	}

	return value;
}
