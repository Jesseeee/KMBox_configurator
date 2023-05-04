#include "MainWindow.hpp"

#include <QApplication>
#include <QtWidgets/QVBoxLayout>

#include "TabWindow.hpp"

int main(int argv, char *args[])
{
	Q_INIT_RESOURCE(configurator);

	QApplication app(argv, args);

	// QTabWidget *tabWidget = new QTabWidget;
	// MainWindow	mainWindow;
	// mainWindow.setGeometry(100, 100, 800, 500);
	// tabWidget->addTab(&mainWindow, "Topology");

	// QVBoxLayout *mainLayout = new QVBoxLayout;
	// mainLayout->addWidget(tabWidget);
	//  setLayout(mainLayout);

	// tabWidget->show();
	// mainWindow.show();

	TabWindow tabWindow;
	tabWindow.show();

	return app.exec();
}
