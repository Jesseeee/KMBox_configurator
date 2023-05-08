#include <QApplication>
#include <QtWidgets/QVBoxLayout>

#include "TabWindow.hpp"

int main(int argv, char *args[])
{
	Q_INIT_RESOURCE(configurator);

	const QApplication app(argv, args);

	TabWindow tabWindow;
	tabWindow.show();

	return QApplication::exec();
}
