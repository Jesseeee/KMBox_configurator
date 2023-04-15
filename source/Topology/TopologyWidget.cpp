/**
 * @file TopologyWidget.cpp
 *
 * @brief Widget to drag and drop topology icons into
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
 * - Apr 12, 2023 ; jesvan59903
 */

#include "TopologyWidget.hpp"
#include "TopologyList.hpp"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>

TopologyWidget::TopologyWidget(int imageSize, QWidget *parent)
	: QWidget(parent)
	, m_imageSize(imageSize)
{
	setAcceptDrops(true);
	setMinimumSize(m_imageSize, m_imageSize);
	setMaximumSize(m_imageSize, m_imageSize);
}

void TopologyWidget::clear()
{
	m_pieces.clear();
	m_highlightedRect = QRect();
	m_inPlace		  = 0;
	update();
}

void TopologyWidget::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat(TopologyList::topologyMimeType()))
		event->accept();
	else
		event->ignore();
}

void TopologyWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
	QRect updateRect  = m_highlightedRect;
	m_highlightedRect = QRect();
	update(updateRect);
	event->accept();
}

void TopologyWidget::dragMoveEvent(QDragMoveEvent *event)
{
	QRect updateRect = m_highlightedRect.united(targetSquare(event->position().toPoint()));

	if (event->mimeData()->hasFormat(TopologyList::topologyMimeType())
		&& findPiece(targetSquare(event->position().toPoint())) == -1)
	{
		m_highlightedRect = targetSquare(event->position().toPoint());
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
	else
	{
		m_highlightedRect = QRect();
		event->ignore();
	}

	update(updateRect);
}

void TopologyWidget::dropEvent(QDropEvent *event)
{
	if (event->mimeData()->hasFormat(TopologyList::topologyMimeType())
		&& findPiece(targetSquare(event->position().toPoint())) == -1)
	{
		QByteArray	pieceData = event->mimeData()->data(TopologyList::topologyMimeType());
		QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
		Piece		piece;
		piece.rect = targetSquare(event->position().toPoint());
		dataStream >> piece.pixmap >> piece.location;

		m_pieces.append(piece);

		m_highlightedRect = QRect();
		update(piece.rect);

		event->setDropAction(Qt::MoveAction);
		event->accept();

		if (piece.location == piece.rect.topLeft() / pieceSize())
		{
			m_inPlace++;
			if (m_inPlace == 25)
				emit puzzleCompleted();
		}
	}
	else
	{
		m_highlightedRect = QRect();
		event->ignore();
	}
}

int TopologyWidget::findPiece(const QRect &pieceRect) const
{
	for (int i = 0, size = m_pieces.size(); i < size; ++i)
	{
		if (m_pieces.at(i).rect == pieceRect)
			return i;
	}
	return -1;
}

void TopologyWidget::mousePressEvent(QMouseEvent *event)
{
	QRect	  square = targetSquare(event->position().toPoint());
	const int found	 = findPiece(square);

	if (found == -1)
		return;

	Piece piece = m_pieces.takeAt(found);

	if (piece.location == square.topLeft() / pieceSize())
		m_inPlace--;

	update(square);

	QByteArray	itemData;
	QDataStream dataStream(&itemData, QIODevice::WriteOnly);

	dataStream << piece.pixmap << piece.location;

	QMimeData *mimeData = new QMimeData;
	mimeData->setData(TopologyList::topologyMimeType(), itemData);

	QDrag *drag = new QDrag(this);
	drag->setMimeData(mimeData);
	drag->setHotSpot(event->position().toPoint() - square.topLeft());
	drag->setPixmap(piece.pixmap);

	if (drag->exec(Qt::MoveAction) != Qt::MoveAction)
	{
		m_pieces.insert(found, piece);
		update(targetSquare(event->position().toPoint()));

		if (piece.location == square.topLeft() / pieceSize())
			m_inPlace++;
	}
}

void TopologyWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.fillRect(event->rect(), Qt::white);

	if (m_highlightedRect.isValid())
	{
		painter.setBrush(QColor("#ffcccc"));
		painter.setPen(Qt::NoPen);
		painter.drawRect(m_highlightedRect.adjusted(0, 0, -1, -1));
	}

	for (const Piece &piece : m_pieces)
		painter.drawPixmap(piece.rect, piece.pixmap);
}

QRect TopologyWidget::targetSquare(const QPoint &position) const
{
	QPoint topLeft = QPoint(position.x() / pieceSize(), position.y() / pieceSize()) * pieceSize();
	return QRect(topLeft, QSize(pieceSize(), pieceSize()));
}

int TopologyWidget::pieceSize() const
{
	return m_imageSize / 5;
}

int TopologyWidget::imageSize() const
{
	return m_imageSize;
}