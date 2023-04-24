#include "MainWindow.hpp"

#include <QApplication>

int main(int argv, char *args[])
{
	Q_INIT_RESOURCE(configurator);

	QApplication app(argv, args);
	MainWindow	 mainWindow;
	mainWindow.setGeometry(100, 100, 800, 500);
	mainWindow.show();

	return app.exec();
}
