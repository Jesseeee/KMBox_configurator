/**
 * @file ResizeableRectItem.hpp
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
 * - May 07, 2023 ; jesvan
 */

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QMouseEvent>

class ResizeableRectItem : public QGraphicsRectItem
{
public:
	explicit ResizeableRectItem(QGraphicsItem *parent = nullptr);

	enum class HandleAnchor
	{
		Left,
		TopLeft,
		Top,
		TopRight,
		Right,
		BottomRight,
		Bottom,
		BottomLeft,
		None
	};

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

	// Disable copy and move semantics by default
	ResizeableRectItem(const ResizeableRectItem &)			  = delete;
	ResizeableRectItem(ResizeableRectItem &&)				  = delete;
	ResizeableRectItem &operator=(const ResizeableRectItem &) = delete;
	ResizeableRectItem &operator=(ResizeableRectItem &&)	  = delete;

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
	HandleAnchor getHandleAnchor(const QPointF &point) const;

	HandleAnchor m_anchor = HandleAnchor::None;
};