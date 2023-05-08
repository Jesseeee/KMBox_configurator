/**
 * @file TabWindow.hpp
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
 * - May 04, 2023 ; jesvan
 */
#ifndef TABWINDOW_HPP_
#define TABWINDOW_HPP_

#include <QtWidgets/QMainWindow>

class TabWindow : public QMainWindow
{
public:
	explicit TabWindow(QWidget *parent = nullptr);

	// Disable copy and move semantics by default
	TabWindow(const TabWindow &)			= delete;
	TabWindow(TabWindow &&)					= delete;
	TabWindow &operator=(const TabWindow &) = delete;
	TabWindow &operator=(TabWindow &&)		= delete;

private Q_SLOTS:
	void about();

private:
	QTabWidget *tabWidget = nullptr;

	QMenu *fileMenu	 = nullptr;
	QMenu *aboutMenu = nullptr;

	QAction *exitAction	 = nullptr;
	QAction *aboutAction = nullptr;
};

#endif