/**
 * @file PixMapItem.hpp
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
 * - Apr 25, 2023 ; TODO
 */
#ifndef PIXMAPITEM_HPP_
#define PIXMAPITEM_HPP_

#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QList>

QT_BEGIN_NAMESPACE
class QPixmap;
class QGraphicsSceneContextMenuEvent;
class QMenu;
class QPolygonF;
QT_END_NAMESPACE

class Arrow;

class PixMapItem : public QGraphicsPixmapItem
{
public:
	enum
	{
		Type = UserType + 16
	};
	enum class PixMapDiagramType
	{
		Server
	};

	PixMapItem(PixMapDiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent = nullptr);

	void			  removeArrow(Arrow *arrow);
	void			  removeArrows();
	PixMapDiagramType diagramType() const { return m_myDiagramType; }
	QPolygonF		  polygon() const { return m_myPolygon; }
	void			  addArrow(Arrow *arrow);
	QPixmap			  image() const;
	int				  type() const override { return Type; }

protected:
	void	 contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
	PixMapDiagramType m_myDiagramType;
	QPixmap			  m_myPixMap;
	QPolygonF		  m_myPolygon;
	QMenu			 *m_myContextMenu;
	QList<Arrow *>	  m_arrows;
};

#endif