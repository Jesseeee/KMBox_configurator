/**
 * @file TopologyScene.cpp
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

#include "TopologyScene.hpp"
#include "Arrow.hpp"

#include <QGraphicsSceneMouseEvent>
#include <QTextCursor>

TopologyScene::TopologyScene(QObject *parent)
	: QGraphicsScene(parent)
{
}

void TopologyScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (mouseEvent->button() != Qt::LeftButton)
	{
		return;
	}

	TopologyItem *item = nullptr;
	switch (m_myMode)
	{
		case Mode::InsertItem:
			item = new TopologyItem(m_myItemType);
			addItem(item);
			item->setPos(mouseEvent->scenePos());
			emit itemInserted(item);
			break;
		case Mode::InsertLine:
			m_line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
			m_line->setPen(QPen(Qt::black, 2));
			addItem(m_line);
			break;
		default:;
	}
	QGraphicsScene::mousePressEvent(mouseEvent);
}

void TopologyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (m_myMode == Mode::InsertLine && m_line != nullptr)
	{
		const QLineF newLine(m_line->line().p1(), mouseEvent->scenePos());
		m_line->setLine(newLine);
	}
	else if (m_myMode == Mode::MoveItem)
	{
		QGraphicsScene::mouseMoveEvent(mouseEvent);
	}
}

void TopologyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (m_line != nullptr && m_myMode == Mode::InsertLine)
	{
		QList<QGraphicsItem *> startItems = items(m_line->line().p1());
		if (startItems.count() && startItems.first() == m_line)
		{
			startItems.removeFirst();
		}
		QList<QGraphicsItem *> endItems = items(m_line->line().p2());
		if (endItems.count() && endItems.first() == m_line)
		{
			endItems.removeFirst();
		}

		removeItem(m_line);
		delete m_line;

		if (!startItems.empty() && !endItems.empty() && startItems.first() != endItems.first())
		{
			QGraphicsEllipseItem *startItem = qgraphicsitem_cast<QGraphicsEllipseItem *>(startItems.first());
			QGraphicsEllipseItem *endItem	= qgraphicsitem_cast<QGraphicsEllipseItem *>(endItems.first());
			if (startItem && endItem)
			{
				TopologyItem *startTopologyItem = qgraphicsitem_cast<TopologyItem *>(startItem->parentItem());
				TopologyItem *endTopologyItem	= qgraphicsitem_cast<TopologyItem *>(endItem->parentItem());
				auto		 *arrow				= new Arrow(startTopologyItem, endTopologyItem, startItem, endItem);
				startTopologyItem->addArrow(arrow);
				endTopologyItem->addArrow(arrow);
				arrow->setZValue(-1000.0);
				addItem(arrow);
				arrow->updatePosition();
			}
		}
	}
	m_line = nullptr;
	QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

bool TopologyScene::isItemChange(int type) const
{
	const QList<QGraphicsItem *> items = selectedItems();
	const auto					 cb	   = [type](const QGraphicsItem *item) { return item->type() == type; };
	return std::ranges::find_if(items, cb) != items.end();
}
