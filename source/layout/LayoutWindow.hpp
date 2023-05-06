/**
 * @file LayoutWindow.hpp
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
#ifndef LAYOUTWINDOW_HPP_
#define LAYOUTWINDOW_HPP_

#include <QMainWindow>

class LayoutScene;
class QGraphicsView;

class LayoutWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit LayoutWindow(QWidget *parent = nullptr);
	~LayoutWindow() override;

	// Disable copy and move semantics by default
	LayoutWindow(const LayoutWindow &)			  = delete;
	LayoutWindow(LayoutWindow &&)				  = delete;
	LayoutWindow &operator=(const LayoutWindow &) = delete;
	LayoutWindow &operator=(LayoutWindow &&)	  = delete;

private:
	LayoutScene	  *scene = nullptr;
	QGraphicsView *view;
};

#endif