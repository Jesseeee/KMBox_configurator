#include "Arrow.hpp"
#include "DiagramItem.hpp"
#include "DiagramScene.hpp"
#include "MainWindow.hpp"

#include <QtWidgets>

MainWindow::MainWindow()
{
	createActions();
	createToolBox();
	createMenus();

	scene = new DiagramScene(itemMenu, this);
	scene->setSceneRect(QRectF(0, 0, 5000, 5000));
	connect(scene, &DiagramScene::itemInserted, this, &MainWindow::itemInserted);
	createToolbars();

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(toolBox);
	view = new QGraphicsView(scene);
	layout->addWidget(view);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	setCentralWidget(widget);
	setWindowTitle(tr("KMBox configurator"));
	setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::buttonGroupClicked(QAbstractButton *button)
{
	for (const QAbstractButton *myButton : buttonGroup->buttons())
	{
		if (myButton != button)
			button->setChecked(false);
	}
	const int id = buttonGroup->id(button);
	scene->setItemType(DiagramItem::DiagramType(id));
	scene->setMode(DiagramScene::Mode::InsertItem);
}

void MainWindow::deleteItem()
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
		if (item->type() == DiagramItem::Type)
			qgraphicsitem_cast<DiagramItem *>(item)->removeArrows();
		scene->removeItem(item);
		delete item;
	}
}

void MainWindow::pointerGroupClicked()
{
	scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}

void MainWindow::bringToFront()
{
	if (scene->selectedItems().isEmpty())
		return;

	QGraphicsItem				*selectedItem = scene->selectedItems().first();
	const QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

	qreal zValue = 0;
	for (const QGraphicsItem *item : overlapItems)
	{
		if (item->zValue() >= zValue && item->type() == DiagramItem::Type)
			zValue = item->zValue() + 0.1;
	}
	selectedItem->setZValue(zValue);
}

void MainWindow::sendToBack()
{
	if (scene->selectedItems().isEmpty())
		return;

	QGraphicsItem				*selectedItem = scene->selectedItems().first();
	const QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

	qreal zValue = 0;
	for (const QGraphicsItem *item : overlapItems)
	{
		if (item->zValue() <= zValue && item->type() == DiagramItem::Type)
			zValue = item->zValue() - 0.1;
	}
	selectedItem->setZValue(zValue);
}

void MainWindow::itemInserted(DiagramItem *item)
{
	pointerTypeGroup->button(int(DiagramScene::Mode::MoveItem))->setChecked(true);
	scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
	buttonGroup->button(int(item->diagramType()))->setChecked(false);
}

void MainWindow::sceneScaleChanged(const QString &scale)
{
	double	   newScale	 = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
	QTransform oldMatrix = view->transform();
	view->resetTransform();
	view->translate(oldMatrix.dx(), oldMatrix.dy());
	view->scale(newScale, newScale);
}

void MainWindow::about()
{
	QMessageBox::about(this,
					   tr("About KMBox Configurator"),
					   tr("The configurator allows graphically designing a KMBox configuration"));
}

void MainWindow::createToolBox()
{
	buttonGroup = new QButtonGroup(this);
	buttonGroup->setExclusive(false);
	connect(buttonGroup,
			QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
			this,
			&MainWindow::buttonGroupClicked);
	auto *layout = new QGridLayout;
	layout->addWidget(createCellWidget(tr("Conditional"), DiagramItem::DiagramType::Conditional), 0, 0);
	layout->addWidget(createCellWidget(tr("Process"), DiagramItem::DiagramType::Step), 0, 1);
	layout->addWidget(createCellWidget(tr("Input/Output"), DiagramItem::DiagramType::Io), 1, 0);
	layout->setRowStretch(3, 10);
	layout->setColumnStretch(2, 10);

	auto *itemWidget = new QWidget;
	itemWidget->setLayout(layout);

	toolBox = new QToolBox;
	toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
	toolBox->setMinimumWidth(itemWidget->sizeHint().width());
	toolBox->addItem(itemWidget, tr("Topology icons"));
}

void MainWindow::createActions()
{
	toFrontAction = new QAction(QIcon(":/images/bringtofront.png"), tr("Bring to &Front"), this);
	toFrontAction->setShortcut(tr("Ctrl+F"));
	toFrontAction->setStatusTip(tr("Bring item to front"));
	connect(toFrontAction, &QAction::triggered, this, &MainWindow::bringToFront);

	sendBackAction = new QAction(QIcon(":/images/sendtoback.png"), tr("Send to &Back"), this);
	sendBackAction->setShortcut(tr("Ctrl+T"));
	sendBackAction->setStatusTip(tr("Send item to back"));
	connect(sendBackAction, &QAction::triggered, this, &MainWindow::sendToBack);

	deleteAction = new QAction(QIcon(":/images/delete.png"), tr("&Delete"), this);
	deleteAction->setShortcut(tr("Delete"));
	deleteAction->setStatusTip(tr("Delete item from diagram"));
	connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteItem);

	exitAction = new QAction(tr("E&xit"), this);
	exitAction->setShortcuts(QKeySequence::Quit);
	exitAction->setStatusTip(tr("Quit Scenediagram example"));
	connect(exitAction, &QAction::triggered, this, &QWidget::close);

	aboutAction = new QAction(tr("A&bout"), this);
	aboutAction->setShortcut(tr("F1"));
	connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(exitAction);

	itemMenu = menuBar()->addMenu(tr("&Item"));
	itemMenu->addAction(deleteAction);
	itemMenu->addSeparator();
	itemMenu->addAction(toFrontAction);
	itemMenu->addAction(sendBackAction);

	aboutMenu = menuBar()->addMenu(tr("&Help"));
	aboutMenu->addAction(aboutAction);
}

void MainWindow::createToolbars()
{
	editToolBar = addToolBar(tr("Edit"));
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
	pointerTypeGroup->addButton(pointerButton, int(DiagramScene::Mode::MoveItem));
	pointerTypeGroup->addButton(linePointerButton, int(DiagramScene::Mode::InsertLine));
	connect(pointerTypeGroup,
			QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
			this,
			&MainWindow::pointerGroupClicked);

	sceneScaleCombo = new QComboBox;
	QStringList scales;
	scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
	sceneScaleCombo->addItems(scales);
	sceneScaleCombo->setCurrentIndex(2);
	connect(sceneScaleCombo, &QComboBox::currentTextChanged, this, &MainWindow::sceneScaleChanged);

	pointerToolbar = addToolBar(tr("Pointer type"));
	pointerToolbar->addWidget(pointerButton);
	pointerToolbar->addWidget(linePointerButton);
	pointerToolbar->addWidget(sceneScaleCombo);
}

QWidget *MainWindow::createBackgroundCellWidget(const QString &text, const QString &image)
{
	auto *button = new QToolButton;
	button->setText(text);
	button->setIcon(QIcon(image));
	button->setIconSize(QSize(50, 50));
	button->setCheckable(true);
	backgroundButtonGroup->addButton(button);

	auto *layout = new QGridLayout;
	layout->addWidget(button, 0, 0, Qt::AlignHCenter);
	layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

	auto *widget = new QWidget;
	widget->setLayout(layout);

	return widget;
}

QWidget *MainWindow::createCellWidget(const QString &text, DiagramItem::DiagramType type)
{
	DiagramItem item(type, itemMenu);
	QIcon		icon(item.image());

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
