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

LayoutWindow::LayoutWindow(QWidget *parent)
	: QMainWindow(parent)
{
	scene = new LayoutScene(this);
	scene->setSceneRect(QRectF(0, 0, 5000, 5000));

	QHBoxLayout *layout = new QHBoxLayout;
	view				= new QGraphicsView(scene);

	view->setRenderHint(QPainter::Antialiasing);
	view->setDragMode(QGraphicsView::RubberBandDrag);

	layout->addWidget(view);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	setCentralWidget(widget);
	setUnifiedTitleAndToolBarOnMac(true);

	setGeometry(100, 100, 800, 500);

	// TODO - remove later, this is for proof of concept, which works!
	ResizableRectItem *rectItem = new ResizableRectItem;
	rectItem->setRect(50, 50, 100, 100);
	scene->addItem(rectItem);
}

LayoutWindow::~LayoutWindow() {}
