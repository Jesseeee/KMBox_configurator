/**
 * @file TopologyList.cpp
 *
 * @brief List widget containing the topology icons
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

#include "TopologyList.hpp"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>

TopologyList::TopologyList(QWidget *parent)
	: QListWidget(parent)
{
	setDragEnabled(true);
	setViewMode(QListView::IconMode);
	setIconSize(QSize(30, 30));
	setSpacing(10);
	setAcceptDrops(true);
	setDropIndicatorShown(true);
}

void TopologyList::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat(TopologyList::topologyMimeType()))
		event->accept();
	else
		event->ignore();
}

void TopologyList::dragMoveEvent(QDragMoveEvent *event)
{
	if (event->mimeData()->hasFormat(TopologyList::topologyMimeType()))
	{
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

void TopologyList::dropEvent(QDropEvent *event)
{
	if (event->mimeData()->hasFormat(TopologyList::topologyMimeType()))
	{
		QByteArray	pieceData = event->mimeData()->data(TopologyList::topologyMimeType());
		QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
		QPixmap		pixmap;
		QPoint		location;
		dataStream >> pixmap >> location;

		addIcon(pixmap, location);

		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

void TopologyList::addIcon(const QPixmap &pixmap, const QPoint &location)
{
	QListWidgetItem *pieceItem = new QListWidgetItem(this);
	pieceItem->setIcon(QIcon(pixmap));
	pieceItem->setData(Qt::UserRole, QVariant(pixmap));
	pieceItem->setData(Qt::UserRole + 1, location);
	pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
}

void TopologyList::startDrag(Qt::DropActions /*supportedActions*/)
{
	const QListWidgetItem *item = currentItem();

	QByteArray	itemData;
	QDataStream dataStream(&itemData, QIODevice::WriteOnly);
	QPixmap		pixmap	 = qvariant_cast<QPixmap>(item->data(Qt::UserRole));
	QPoint		location = item->data(Qt::UserRole + 1).toPoint();

	dataStream << pixmap << location;

	QMimeData *mimeData = new QMimeData;
	mimeData->setData(TopologyList::topologyMimeType(), itemData);

	QDrag *drag = new QDrag(this);
	drag->setMimeData(mimeData);
	drag->setHotSpot(QPoint(pixmap.width() / 2, pixmap.height() / 2));
	drag->setPixmap(pixmap);

	if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
		delete takeItem(row(item));
}
