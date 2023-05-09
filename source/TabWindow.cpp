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
#include "LayoutManager.hpp"
#include "topology/TopologyWindow.hpp"
#include "layout/LayoutWindow.hpp"

TabWindow::TabWindow(LayoutManager *layoutManager, QWidget *parent)
	: QMainWindow(parent)
{
	tabWidget = new QTabWidget(this);

	auto *topologyWindow = new TopologyWindow(this);
	auto *layoutWindow	 = new LayoutWindow(this);

	tabWidget->addTab(topologyWindow, tr("Topology"));
	tabWidget->addTab(layoutWindow, tr("Layout"));

	layoutManager->setLayoutWindow(layoutWindow);
	layoutManager->setTopologyWindow(topologyWindow);

	auto *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(tabWidget);

	auto *widget = new QWidget;
	widget->setLayout(mainLayout);

	setCentralWidget(widget);

	setWindowTitle(tr("KMBox configurator"));

	// TODO move to create actions
	exitAction = new QAction(tr("E&xit"), this);
	exitAction->setShortcuts(QKeySequence::Quit);
	exitAction->setStatusTip(tr("Quit KMBox configurator"));
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

void TabWindow::about()
{
	QMessageBox::about(this,
					   tr("About KMBox Configurator"),
					   tr("The configurator allows graphically designing a KMBox configuration"));
}
