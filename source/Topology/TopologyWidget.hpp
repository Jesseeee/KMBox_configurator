/**
 * @file TopologyWidget.hpp
 *
 * @brief Widget to drag and drop topology icons into
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
 * - Apr 12, 2023 ; jesvan59903
 */
#ifndef TOPOLOGYWIDGET_HPP_
#define TOPOLOGYWIDGET_HPP_

#include <QPoint>
#include <QPixmap>
#include <QList>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class QMouseEvent;
QT_END_NAMESPACE

class TopologyWidget : public QWidget
{
	Q_OBJECT
public:
	explicit TopologyWidget(int imageSize, QWidget *parent = nullptr);
	~TopologyWidget() override = default;

	void clear();

	int pieceSize() const;
	int imageSize() const;

signals:
	void puzzleCompleted();

protected:
	void dragEnterEvent(QDragEnterEvent *event) override;
	void dragLeaveEvent(QDragLeaveEvent *event) override;
	void dragMoveEvent(QDragMoveEvent *event) override;
	void dropEvent(QDropEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void paintEvent(QPaintEvent *event) override;

private:
	// Disable copy and move semantics by default
	TopologyWidget(const TopologyWidget &)			  = delete;
	TopologyWidget(TopologyWidget &&)				  = delete;
	TopologyWidget &operator=(const TopologyWidget &) = delete;
	TopologyWidget &operator=(TopologyWidget &&)	  = delete;

	struct Piece
	{
		QPixmap pixmap;
		QRect	rect;
		QPoint	location;
	};

	int	  findPiece(const QRect &pieceRect) const;
	QRect targetSquare(const QPoint &position) const;

	QList<Piece> m_pieces;
	QRect		 m_highlightedRect;
	int			 m_inPlace;
	int			 m_imageSize;
};

#endif