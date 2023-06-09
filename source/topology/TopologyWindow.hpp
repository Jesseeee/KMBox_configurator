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

	std::vector<TopologyItem *> getAllTopologyItems() const;
	std::vector<Arrow *>		getAllArrows() const;

Q_SIGNALS:
	void saveTopology();

private slots:
	void buttonGroupClicked(QAbstractButton *button);
	void deleteItem();
	void pointerGroupClicked();
	void bringToFront();
	void sendToBack();
	void itemInserted(TopologyItem *item);
	void itemClicked(TopologyItem *item, std::map<std::string, std::string> attributes);
	void sceneScaleChanged(const QString &scale);

private:
	void				   createToolBox();
	void				   createActions();
	void				   createToolbars();
	[[nodiscard]] QWidget *createCellWidget(const QString &text, TopologyItem::TopologyType type);

	TopologyScene *scene = nullptr;
	QGraphicsView *view	 = nullptr;

	QDockWidget *m_detailsDockWidget = nullptr;

	QAction *saveTopologyAction = nullptr;
	QAction *deleteAction		= nullptr;

	QAction *toFrontAction	= nullptr;
	QAction *sendBackAction = nullptr;

	QToolBar *editToolBar	 = nullptr;
	QToolBar *pointerToolbar = nullptr;

	QComboBox *sceneScaleCombo = nullptr;

	QToolBox	 *toolBox				= nullptr;
	QButtonGroup *buttonGroup			= nullptr;
	QButtonGroup *pointerTypeGroup		= nullptr;
	QButtonGroup *backgroundButtonGroup = nullptr;
};

#endif // MAINWINDOW_H
