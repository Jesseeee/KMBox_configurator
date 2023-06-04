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
#include "RectDetailWidget.hpp"

#include <QHBoxLayout>
#include <QGraphicsView>
#include <QToolBar>
#include <QDockWidget>

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

	// Get the screen's logical DPI
	qreal dpi = QGuiApplication::primaryScreen()->logicalDotsPerInch();

	// Calculate the scale factor based on a reference DPI
	qreal referenceDpi = 144.0; // Adjust this to your desired reference DPI
	qreal scaleFactor  = dpi / referenceDpi;

	// Apply the scale factor to the view transformation
	view->setTransform(QTransform::fromScale(scaleFactor, scaleFactor));

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

	m_rectDetailsDockWidget = new QDockWidget(tr("Screen Details"));
	m_rectDetailWidget		= new RectDetailWidget();
	// set the dock widget properties
	m_rectDetailsDockWidget->setAllowedAreas(Qt::RightDockWidgetArea);
	m_rectDetailsDockWidget->setWidget(m_rectDetailWidget);
	m_rectDetailsDockWidget->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
	m_rectDetailsDockWidget->hide();
	m_rectDetailsDockWidget->setMinimumWidth(150);
	m_rectDetailsDockWidget->setMinimumHeight(centralWidget()->height());
	addDockWidget(Qt::RightDockWidgetArea, m_rectDetailsDockWidget);
	m_rectDetailsDockWidget->show();
	layout->addWidget(m_rectDetailsDockWidget);

	QObject::connect(scene, &LayoutScene::rectClicked, this, &LayoutWindow::rectClicked);
}

LayoutWindow::~LayoutWindow() {}

std::vector<QGraphicsItem *> LayoutWindow::getAllItems() const
{
	QList<QGraphicsItem *> items = scene->items();
	return std::vector<QGraphicsItem *>(items.begin(), items.end());
}

void LayoutWindow::rectClicked(QGraphicsRectItem *rectItem)
{
	m_rectDetailWidget->setRectItem(rectItem);
}

void LayoutWindow::clearScreens()
{
	scene->clear();
}

void LayoutWindow::addScreen(qreal xpos, qreal ypos, qreal width, qreal height, std::string name)
{
	auto *rectItem = new ResizeableRectItem;
	rectItem->setScreenName(name);
	rectItem->setRect(0, 0, width, height);
	rectItem->setPos(xpos, ypos);
	rectItem->setBrush(QColor(0, 100, 160));
	QGraphicsTextItem *textItem = new QGraphicsTextItem(QString::fromStdString(name));
	textItem->setFont(QFont("Arial", 16));
	textItem->setPos(rectItem->boundingRect().center() - textItem->boundingRect().center());
	textItem->setParentItem(rectItem);

	scene->addItem(rectItem);
}