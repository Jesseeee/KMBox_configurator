/**
 * @file Arrow.hpp
 *
 * @brief TODO
 *
 * &copy; Copyright 2023 ScioTeq bv. All rights reserved.
 * +-------------------------------------------------------------------------------------------+
 * |                             Export Control Information                                    |
 * +--------+-------------+-------------------------------------+------------------------------+
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
#ifndef ARROW_HPP_
#define ARROW_HPP_

#include <QGraphicsLineItem>

class TopologyItem;

class Arrow : public QGraphicsLineItem
{
public:
	enum
	{
		Type = UserType + 4
	};

	Arrow(TopologyItem *startItem, TopologyItem *endItem, QGraphicsItem *parent = nullptr);

	int			  type() const override { return Type; }
	QRectF		  boundingRect() const override;
	QPainterPath  shape() const override;
	TopologyItem *startItem() const { return m_myStartItem; }
	TopologyItem *endItem() const { return m_myEndItem; }

	void updatePosition();

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
	TopologyItem *m_myStartItem;
	TopologyItem *m_myEndItem;
	QPolygonF	  m_arrowHead;
};

#endif // ARROW_H
