#include <QApplication>
#include <QtWidgets/QVBoxLayout>

#include "TabWindow.hpp"
#include "LayoutManager.hpp"

int main(int argv, char *args[])
{
	Q_INIT_RESOURCE(configurator);

	const QApplication app(argv, args);

	LayoutManager *pLayoutManager = new LayoutManager();
	TabWindow	   tabWindow(pLayoutManager);
	tabWindow.show();

	return QApplication::exec();
}
