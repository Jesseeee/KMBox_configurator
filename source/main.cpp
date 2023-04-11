#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(configurator);

	QApplication a(argc, argv);
	MainWindow	 w;
	w.show();
	return QApplication::exec();
}
