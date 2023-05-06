/**
 * @file TopologyWindow.hpp
 *
 * @brief TODO
 *
 * &copy; Copyright 2023 ScioTeq bv. All rights reserved.
 * +-------------------------------------------------------------------------------------------+
 * |                             Export Control Information                                    |
 * +--------+-------------+-------------------------------------+------------------------------+
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
 * - May 06, 2023 ; jesvan
 */
#ifndef TOPOLOGYWINDOW_HPP_
#define TOPOLOGYWINDOW_HPP_

#include "TopologyItem.hpp"

#include <QMainWindow>

#include <functional>

class TopologyScene;

QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QComboBox;
class QButtonGroup;
class QToolButton;
class QAbstractButton;
class QGraphicsView;
QT_END_NAMESPACE

class TopologyWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit TopologyWindow(QWidget *parent = nullptr);

private slots:
	void buttonGroupClicked(QAbstractButton *button);
	void deleteItem();
	void pointerGroupClicked();
	void bringToFront();
	void sendToBack();
	void itemInserted(TopologyItem *item);
	void sceneScaleChanged(const QString &scale);

private:
	void	 createToolBox();
	void	 createActions();
	void	 createToolbars();
	QWidget *createCellWidget(const QString &text, TopologyItem::TopologyType type);

	TopologyScene *scene;
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
