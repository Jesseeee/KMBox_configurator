/**
 * @file MainWindow.cpp
 *
 * @brief Main window for the GUI
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

#include "MainWindow.hpp"

#include <QtWidgets/QMenuBar>
#include <QtWidgets/QFileDialog>
#include <QtCore/QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setupMenus();
	setupWidgets();
	setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

	setWindowTitle("KMBox configuration");
}

MainWindow::~MainWindow() {}

void MainWindow::setupMenus()
{
	QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

	QAction *exitAction = fileMenu->addAction(tr("&Exit"), qApp, &QCoreApplication::quit);
	exitAction->setShortcuts(QKeySequence::Quit);
}

void MainWindow::setupWidgets() {}
