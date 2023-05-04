/**
 * @file TabWindow.cpp
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
 * - May 04, 2023 ; jesvan
 */

#include "TabWindow.hpp"

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMessageBox>
#include "MainWindow.hpp"

TabWindow::TabWindow(QWidget *parent)
	: QMainWindow(parent)
{
	tabWidget			   = new QTabWidget;
	MainWindow *mainWindow = new MainWindow(this);
	tabWidget->addTab(mainWindow, tr("Topology"));

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(tabWidget);

	QWidget *widget = new QWidget;
	widget->setLayout(mainLayout);

	setCentralWidget(widget);

	setWindowTitle(tr("KMBox configurator"));

	// TODO move to create actions
	exitAction = new QAction(tr("E&xit"), this);
	exitAction->setShortcuts(QKeySequence::Quit);
	exitAction->setStatusTip(tr("Quit Scenediagram example"));
	connect(exitAction, &QAction::triggered, this, &QWidget::close);

	aboutAction = new QAction(tr("A&bout"), this);
	aboutAction->setShortcut(tr("F1"));
	connect(aboutAction, &QAction::triggered, this, &TabWindow::about);

	// TODO move to createMenus function
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(exitAction);

	aboutMenu = menuBar()->addMenu(tr("&Help"));
	aboutMenu->addAction(aboutAction);
}

TabWindow::~TabWindow() {}

void TabWindow::about()
{
	QMessageBox::about(this,
					   tr("About KMBox Configurator"),
					   tr("The configurator allows graphically designing a KMBox configuration"));
}
