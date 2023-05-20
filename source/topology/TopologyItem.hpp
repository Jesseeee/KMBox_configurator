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
		KMBox,
		Server,
		Display
	};

	struct anchorPoint
	{
		anchorPoint(std::string name, QGraphicsEllipseItem *anchor)
			: m_name(name)
			, m_anchor(anchor)
		{
		}
		std::string			  m_name;
		QGraphicsEllipseItem *m_anchor;
	};

	TopologyItem(TopologyType diagramType, QGraphicsItem *parent = nullptr);

	void					   removeArrow(Arrow *arrow);
	void					   removeArrows();
	[[nodiscard]] TopologyType diagramType() const { return m_myDiagramType; }
	void					   addArrow(Arrow *arrow);
	[[nodiscard]] int		   type() const override { return Type; }

	std::map<std::string, std::string> getAttributes() const { return m_attributes; }

	void setAttributeValue(const std::string &key, const std::string &value) { m_attributes[key] = value; }

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
	QGraphicsEllipseItem *createAnchor(const QPointF &pos);

	TopologyType					   m_myDiagramType;
	QList<Arrow *>					   m_arrows;
	QPixmap							   m_myPixMap;
	std::vector<anchorPoint>		   m_anchors;
	std::map<std::string, std::string> m_attributes;
};

#endif // DIAGRAMITEM_H
