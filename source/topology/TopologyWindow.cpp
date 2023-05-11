/**
 * @file TopologyWindow.cpp
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

#include "Arrow.hpp"
#include "TopologyItem.hpp"
#include "TopologyScene.hpp"
#include "TopologyWindow.hpp"

#include <QtWidgets>

TopologyWindow::TopologyWindow(QWidget *parent)
	: QMainWindow(parent)
{
	createActions();
	createToolBox();

	scene = new TopologyScene(this);
	scene->setSceneRect(QRectF(0, 0, 5000, 5000));
	connect(scene, &TopologyScene::itemInserted, this, &TopologyWindow::itemInserted);
	createToolbars();

	auto *layout = new QHBoxLayout;
	layout->addWidget(toolBox);
	view = new QGraphicsView(scene);
	layout->addWidget(view);

	auto *widget = new QWidget;
	widget->setLayout(layout);

	setCentralWidget(widget);
	setUnifiedTitleAndToolBarOnMac(true);

	setGeometry(100, 100, 800, 500);
}

std::vector<TopologyItem *> TopologyWindow::getAllTopologyItems() const
{
	std::vector<TopologyItem *> topologyItems;
	for (QGraphicsItem *item : scene->items())
	{
		if (item->type() == TopologyItem::Type)
		{
			topologyItems.push_back(qgraphicsitem_cast<TopologyItem *>(item));
		}
	}
	return topologyItems;
}

std::vector<Arrow *> TopologyWindow::getAllArrows() const
{
	std::vector<Arrow *> arrows;
	for (QGraphicsItem *item : scene->items())
	{
		Arrow *arrow = qgraphicsitem_cast<Arrow *>(item);
		if (arrow)
		{
			arrows.push_back(arrow);
		}
	}
	return arrows;
}

void TopologyWindow::buttonGroupClicked(QAbstractButton *button)
{
	for (const QAbstractButton *myButton : buttonGroup->buttons())
	{
		if (myButton != button)
			button->setChecked(false);
	}
	const int id = buttonGroup->id(button);
	scene->setItemType(TopologyItem::TopologyType(id));
	scene->setMode(TopologyScene::Mode::InsertItem);
}

void TopologyWindow::deleteItem()
{
	QList<QGraphicsItem *> selectedItems = scene->selectedItems();
	for (QGraphicsItem *item : std::as_const(selectedItems))
	{
		if (item->type() == Arrow::Type)
		{
			scene->removeItem(item);
			Arrow *arrow = qgraphicsitem_cast<Arrow *>(item);
			arrow->startItem()->removeArrow(arrow);
			arrow->endItem()->removeArrow(arrow);
			delete item;
		}
	}

	selectedItems = scene->selectedItems();
	for (QGraphicsItem *item : std::as_const(selectedItems))
	{
		if (item->type() == TopologyItem::Type)
			qgraphicsitem_cast<TopologyItem *>(item)->removeArrows();
		scene->removeItem(item);
		delete item;
	}
}

void TopologyWindow::pointerGroupClicked()
{
	scene->setMode(TopologyScene::Mode(pointerTypeGroup->checkedId()));
}

void TopologyWindow::bringToFront()
{
	if (scene->selectedItems().isEmpty())
	{
		return;
	}

	QGraphicsItem				*selectedItem = scene->selectedItems().first();
	const QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

	qreal zValue = 0;
	for (const QGraphicsItem *item : overlapItems)
	{
		if (item->zValue() >= zValue && item->type() == TopologyItem::Type)
		{
			zValue = item->zValue() + 0.1;
		}
	}
	selectedItem->setZValue(zValue);
}

void TopologyWindow::sendToBack()
{
	if (scene->selectedItems().isEmpty())
	{
		return;
	}

	QGraphicsItem				*selectedItem = scene->selectedItems().first();
	const QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

	qreal zValue = 0;
	for (const QGraphicsItem *item : overlapItems)
	{
		if (item->zValue() <= zValue && item->type() == TopologyItem::Type)
		{
			zValue = item->zValue() - 0.1;
		}
	}
	selectedItem->setZValue(zValue);
}

void TopologyWindow::itemInserted(TopologyItem *item)
{
	pointerTypeGroup->button(int(TopologyScene::Mode::MoveItem))->setChecked(true);
	scene->setMode(TopologyScene::Mode(pointerTypeGroup->checkedId()));
	buttonGroup->button(int(item->diagramType()))->setChecked(false);
}

void TopologyWindow::sceneScaleChanged(const QString &scale)
{
	const double	 newScale  = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
	const QTransform oldMatrix = view->transform();
	view->resetTransform();
	view->translate(oldMatrix.dx(), oldMatrix.dy());
	view->scale(newScale, newScale);
}

void TopologyWindow::createToolBox()
{
	buttonGroup = new QButtonGroup(this);
	buttonGroup->setExclusive(false);
	connect(buttonGroup,
			QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
			this,
			&TopologyWindow::buttonGroupClicked);
	auto *layout = new QGridLayout;
	layout->addWidget(createCellWidget(tr("KMBox"), TopologyItem::TopologyType::KMBox), 0, 0);
	layout->addWidget(createCellWidget(tr("Server"), TopologyItem::TopologyType::Server), 1, 0);
	layout->addWidget(createCellWidget(tr("Display"), TopologyItem::TopologyType::Display), 2, 0);
	layout->setRowStretch(3, 10);
	layout->setColumnStretch(2, 10);

	auto *itemWidget = new QWidget;
	itemWidget->setLayout(layout);

	toolBox = new QToolBox;
	toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
	toolBox->setMinimumWidth(itemWidget->sizeHint().width());
	toolBox->addItem(itemWidget, tr("Topology icons"));
}

void TopologyWindow::createActions()
{
	toFrontAction = new QAction(QIcon(":/images/bringtofront.png"), tr("Bring to &Front"), this);
	toFrontAction->setShortcut(tr("Ctrl+F"));
	toFrontAction->setStatusTip(tr("Bring item to front"));
	connect(toFrontAction, &QAction::triggered, this, &TopologyWindow::bringToFront);

	sendBackAction = new QAction(QIcon(":/images/sendtoback.png"), tr("Send to &Back"), this);
	sendBackAction->setShortcut(tr("Ctrl+T"));
	sendBackAction->setStatusTip(tr("Send item to back"));
	connect(sendBackAction, &QAction::triggered, this, &TopologyWindow::sendToBack);

	deleteAction = new QAction(QIcon(":/images/delete.png"), tr("&Delete"), this);
	deleteAction->setShortcut(tr("Delete"));
	deleteAction->setStatusTip(tr("Delete item from diagram"));
	connect(deleteAction, &QAction::triggered, this, &TopologyWindow::deleteItem);

	saveTopologyAction = new QAction(QIcon(":/images/save.png"), tr("Save the topology"), this);
	saveTopologyAction->setShortcut(tr("Ctrl+Enter"));
	saveTopologyAction->setStatusTip(tr("Save the topology so it can be used in the layout"));
	connect(saveTopologyAction, &QAction::triggered, this, &TopologyWindow::saveTopology);
}

void TopologyWindow::createToolbars()
{
	editToolBar = addToolBar(tr("Edit"));
	editToolBar->addAction(saveTopologyAction);
	editToolBar->addAction(deleteAction);
	editToolBar->addAction(toFrontAction);
	editToolBar->addAction(sendBackAction);

	auto *pointerButton = new QToolButton;
	pointerButton->setCheckable(true);
	pointerButton->setChecked(true);
	pointerButton->setIcon(QIcon(":/images/pointer.png"));
	auto *linePointerButton = new QToolButton;
	linePointerButton->setCheckable(true);
	linePointerButton->setIcon(QIcon(":/images/linepointer.png"));

	pointerTypeGroup = new QButtonGroup(this);
	pointerTypeGroup->addButton(pointerButton, int(TopologyScene::Mode::MoveItem));
	pointerTypeGroup->addButton(linePointerButton, int(TopologyScene::Mode::InsertLine));
	connect(pointerTypeGroup,
			QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
			this,
			&TopologyWindow::pointerGroupClicked);

	sceneScaleCombo = new QComboBox;
	QStringList scales;
	scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
	sceneScaleCombo->addItems(scales);
	sceneScaleCombo->setCurrentIndex(2);
	connect(sceneScaleCombo, &QComboBox::currentTextChanged, this, &TopologyWindow::sceneScaleChanged);

	pointerToolbar = addToolBar(tr("Pointer type"));
	pointerToolbar->addWidget(pointerButton);
	pointerToolbar->addWidget(linePointerButton);
	pointerToolbar->addWidget(sceneScaleCombo);
}

QWidget *TopologyWindow::createCellWidget(const QString &text, TopologyItem::TopologyType type)
{
	const TopologyItem item(type);
	const QIcon		   icon(item.pixmap());

	auto *button = new QToolButton;
	button->setIcon(icon);
	button->setIconSize(QSize(50, 50));
	button->setCheckable(true);
	buttonGroup->addButton(button, int(type));

	auto *layout = new QGridLayout;
	layout->addWidget(button, 0, 0, Qt::AlignHCenter);
	layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

	auto *widget = new QWidget;
	widget->setLayout(layout);

	return widget;
}
