/**
 * @file TopologyScene.hpp
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
#ifndef TOPOLOGYSCENE_HPP_
#define TOPOLOGYSCENE_HPP_

#include "TopologyItem.hpp"

#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QPointF;
class QGraphicsLineItem;
QT_END_NAMESPACE

class TopologyScene : public QGraphicsScene
{
	Q_OBJECT
public:
	enum class Mode
	{
		InsertItem,
		InsertLine,
		MoveItem
	};

	explicit TopologyScene(QObject *parent = nullptr);

public slots:
	void setMode(Mode mode) { m_myMode = mode; };
	void setItemType(TopologyItem::TopologyType type) { m_myItemType = type; };

signals:
	void itemInserted(TopologyItem *item);
	void itemClicked(TopologyItem *item, std::map<std::string, std::string> attributes);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
	[[nodiscard]] bool isItemChange(int type) const;

	TopologyItem::TopologyType m_myItemType		= TopologyItem::TopologyType::Server;
	Mode					   m_myMode			= Mode::MoveItem;
	bool					   m_leftButtonDown = false;
	QGraphicsLineItem		  *m_line			= nullptr;
};

#endif // DIAGRAMSCENE_H
