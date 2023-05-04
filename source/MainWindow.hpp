#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "DiagramItem.hpp"

#include <QMainWindow>

class DiagramScene;

QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QButtonGroup;
class QLineEdit;
class QToolButton;
class QAbstractButton;
class QGraphicsView;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);

private slots:
	void buttonGroupClicked(QAbstractButton *button);
	void deleteItem();
	void pointerGroupClicked();
	void bringToFront();
	void sendToBack();
	void itemInserted(DiagramItem *item);
	void sceneScaleChanged(const QString &scale);

private:
	void	 createToolBox();
	void	 createActions();
	void	 createToolbars();
	QWidget *createCellWidget(const QString &text, DiagramItem::DiagramType type);

	DiagramScene  *scene;
	QGraphicsView *view;

	QAction *addAction;
	QAction *deleteAction;

	QAction *toFrontAction;
	QAction *sendBackAction;

	QToolBar *editToolBar;
	QToolBar *pointerToolbar;

	QComboBox *sceneScaleCombo;

	QToolBox	 *toolBox;
	QButtonGroup *buttonGroup;
	QButtonGroup *pointerTypeGroup;
	QButtonGroup *backgroundButtonGroup;
};

#endif // MAINWINDOW_H
