/**
 * @file Arrow.cpp
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

#include "Arrow.hpp"
#include "TopologyItem.hpp"

#include <QPainter>
#include <QPen>
#include <QtMath>

Arrow::Arrow(TopologyItem		  *startItem,
			 TopologyItem		  *endItem,
			 QGraphicsEllipseItem *startAnchor,
			 QGraphicsEllipseItem *endAnchor,
			 QGraphicsItem		  *parent)
	: QGraphicsLineItem(parent)
	, m_startItem(startItem)
	, m_endItem(endItem)
	, m_startAnchor(startAnchor)
	, m_endAnchor(endAnchor)
{
	qDebug() << "Start and end anchor ptr val is " << m_startAnchor;
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

void Arrow::updatePosition()
{
	qDebug() << "scenepos is " << m_startAnchor->scenePos() << " " << m_endAnchor->scenePos();
	QPointF startOffset = m_startAnchor->boundingRect().center();
	QPointF endOffset	= m_endAnchor->boundingRect().center();
	QLineF	line(m_startAnchor->scenePos() + startOffset, m_endAnchor->scenePos() + endOffset);
	setLine(line);
}