/**
 * @file RectDetailWidget.hpp
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
 * - May 20, 2023 ; jesvan
 */
#ifndef RECTDETAILWIDGET_HPP_
#define RECTDETAILWIDGET_HPP_

#include <QWidget>

class QGraphicsRectItem;
class QLabel;
class QSpinBox;

class RectDetailWidget : public QWidget
{
public:
	RectDetailWidget();
	virtual ~RectDetailWidget();

	void setRectItem(QGraphicsRectItem *item);

	// Disable copy and move semantics by default
	RectDetailWidget(const RectDetailWidget &)			  = delete;
	RectDetailWidget(RectDetailWidget &&)				  = delete;
	RectDetailWidget &operator=(const RectDetailWidget &) = delete;
	RectDetailWidget &operator=(RectDetailWidget &&)	  = delete;

private slots:
	void xposChanged(int xpos);
	void yposChanged(int ypos);
	void widthChanged(int width);
	void heightChanged(int height);

private:
	QGraphicsRectItem *currentRectItem = nullptr;

	QLabel	 *xposLabel;
	QSpinBox *xposSpinBox;
	QLabel	 *yposlabel;
	QSpinBox *yposSpinBox;
	QLabel	 *widthLabel;
	QSpinBox *widthSpinBox;
	QLabel	 *heightLabel;
	QSpinBox *heightSpinBox;
};

#endif