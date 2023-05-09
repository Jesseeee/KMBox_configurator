/**
 * @file TopologyItem.hpp
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
#ifndef TOPOLOGYITEM_HPP_
#define TOPOLOGYITEM_HPP_

#include <QGraphicsPixmapItem>
#include <QList>
#include <QPixmap>

QT_BEGIN_NAMESPACE
class QGraphicsSceneContextMenuEvent;
class QMenu;
class QPolygonF;
QT_END_NAMESPACE

class Arrow;

class TopologyItem : public QGraphicsPixmapItem
{
public:
	enum
	{
		Type = UserType + 15
	};
	enum class TopologyType
	{
		Server,
		Display
	};

	TopologyItem(TopologyType diagramType, QGraphicsItem *parent = nullptr);

	void					   removeArrow(Arrow *arrow);
	void					   removeArrows();
	[[nodiscard]] TopologyType diagramType() const { return m_myDiagramType; }
	[[nodiscard]] QPolygonF	   polygon() const { return m_myPolygon; }
	void					   addArrow(Arrow *arrow);
	[[nodiscard]] QPixmap	   image() const;
	[[nodiscard]] int		   type() const override { return Type; }

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

	/// @brief Override the mouse press to handle icon moves and when an anchor is clicked for arrow drawing
	/// @param event The mouse event
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	/// @brief Override the mouse release event so if an arrow is being drawn and released on an anchor we handle it
	/// @param event The mouse event
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
	QGraphicsEllipseItem *createAnchor(const QPointF &pos, qreal size);

	TopologyType						m_myDiagramType;
	QPolygonF							m_myPolygon;
	QList<Arrow *>						m_arrows;
	QPixmap								m_myPixMap;
	std::vector<QGraphicsEllipseItem *> m_anchors;
};

#endif // DIAGRAMITEM_H
