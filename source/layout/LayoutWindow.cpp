/**
 * @file LayoutWindow.cpp
 *
 * @brief TODO
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
 * - May 06, 2023 ; jesvan
 */

#include "LayoutWindow.hpp"
#include "LayoutScene.hpp"

#include "ResizeableRectItem.hpp"

#include <QHBoxLayout>
#include <QGraphicsView>
#include <QToolBar>

LayoutWindow::LayoutWindow(QWidget *parent)
	: QMainWindow(parent)
{
	scene = new LayoutScene(this);
	scene->setSceneRect(QRectF(0, 0, 4000, 4000));

	auto *layout = new QHBoxLayout;
	view		 = new QGraphicsView(scene);

	const QTransform oldMatrix = view->transform();
	view->resetTransform();
	view->translate(oldMatrix.dx(), oldMatrix.dy());
	view->scale(0.5, 0.5);

	view->setRenderHint(QPainter::Antialiasing);
	view->setDragMode(QGraphicsView::RubberBandDrag);

	layout->addWidget(view);

	auto *widget = new QWidget;
	widget->setLayout(layout);

	setCentralWidget(widget);
	setUnifiedTitleAndToolBarOnMac(true);

	setGeometry(100, 100, 800, 500);

	saveLayoutAction = new QAction(QIcon(":/images/save.png"), tr("Save the layouts"), this);
	saveLayoutAction->setShortcut(tr("Ctrl+Enter"));
	saveLayoutAction->setStatusTip(tr("Save the topology so it can be used in the layout"));
	connect(saveLayoutAction, &QAction::triggered, this, &LayoutWindow::saveLayout);

	editToolBar = addToolBar(tr("Edit"));
	editToolBar->addAction(saveLayoutAction);

	// TODO - remove later, this is for proof of concept, which works!
	auto *rectItem = new ResizeableRectItem;
	rectItem->setRect(50, 50, 100, 100);
	rectItem->setBrush(QColor(160, 0, 0));
	QGraphicsTextItem *textItem = new QGraphicsTextItem("screen1");
	textItem->setFont(QFont("Arial", 16));
	textItem->setPos(rectItem->boundingRect().center() - textItem->boundingRect().center());
	textItem->setParentItem(rectItem);

	auto *rectItem2 = new ResizeableRectItem;
	rectItem2->setRect(50, 250, 100, 100);
	rectItem2->setBrush(QColor(0, 160, 0));
	QGraphicsTextItem *textItem2 = new QGraphicsTextItem("screen2");
	textItem2->setFont(QFont("Arial", 16));
	textItem2->setPos(rectItem2->boundingRect().center() - textItem2->boundingRect().center());
	textItem2->setParentItem(rectItem2);

	auto *rectItem3 = new ResizeableRectItem;
	rectItem3->setRect(50, 450, 100, 100);
	rectItem3->setBrush(QColor(0, 100, 160));
	QGraphicsTextItem *textItem3 = new QGraphicsTextItem("screen3");
	textItem3->setFont(QFont("Arial", 16));
	textItem3->setPos(rectItem3->boundingRect().center() - textItem3->boundingRect().center());
	textItem3->setParentItem(rectItem3);
	scene->addItem(rectItem);
	scene->addItem(rectItem2);
	scene->addItem(rectItem3);
}

LayoutWindow::~LayoutWindow() {}

std::vector<QGraphicsItem *> LayoutWindow::getAllItems() const
{
	QList<QGraphicsItem *> items = scene->items();
	return std::vector<QGraphicsItem *>(items.begin(), items.end());
}
