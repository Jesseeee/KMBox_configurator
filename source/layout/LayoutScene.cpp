/**
 * @file LayoutScene.cpp
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

#include "LayoutScene.hpp"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsSceneDragDropEvent>
#include <QWidget>

LayoutScene::LayoutScene(QObject *parent)
	: QGraphicsScene(parent)
{
}

LayoutScene::~LayoutScene() {}

void LayoutScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	QGraphicsScene::mousePressEvent(mouseEvent);
	if (mouseEvent->button() == Qt::LeftButton)
	{
		QGraphicsRectItem *rectItem
			= qgraphicsitem_cast<QGraphicsRectItem *>(itemAt(mouseEvent->scenePos(), QTransform()));
		if (rectItem)
		{
			rectClicked(rectItem);
		}
	}
}
