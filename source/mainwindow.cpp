#include "mainwindow.h"

#include <QtWidgets/QMenuBar>
#include <QtWidgets/QFileDialog>
#include <QtCore/QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setupMenus();
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
