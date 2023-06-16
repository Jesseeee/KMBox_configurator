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

	Arrow(TopologyItem		   *startItem,
		  TopologyItem		   *endItem,
		  QGraphicsEllipseItem *startAnchor,
		  QGraphicsEllipseItem *endAnchor,
		  QGraphicsItem		   *parent = nullptr);

	[[nodiscard]] int					type() const override { return Type; }
	[[nodiscard]] TopologyItem		   *startItem() const { return m_startItem; }
	[[nodiscard]] TopologyItem		   *endItem() const { return m_endItem; }
	[[nodiscard]] QGraphicsEllipseItem *startAnchor() const { return m_startAnchor; }
	[[nodiscard]] QGraphicsEllipseItem *endAnchor() const { return m_endAnchor; }
	void								updatePosition();

private:
	TopologyItem		 *m_startItem;
	TopologyItem		 *m_endItem;
	QGraphicsEllipseItem *m_startAnchor;
	QGraphicsEllipseItem *m_endAnchor;
};

#endif // ARROW_H
