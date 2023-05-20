/**
 * @file ItemDetailWidget.hpp
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
 * - May 17, 2023 ; jesvan
 */
#ifndef ITEMDETAILWIDGET_HPP_
#define ITEMDETAILWIDGET_HPP_

#include <map>
#include <string>
#include <QWidget>

class TopologyItem;
class QLineEdit;

class ItemDetailWidget : public QWidget
{
public:
	ItemDetailWidget();
	virtual ~ItemDetailWidget();

	void setFields(TopologyItem *item, std::map<std::string, std::string> attributes);

	void fieldTextChanged(const QString &text);

private:
	// Disable copy and move semantics by default
	ItemDetailWidget(const ItemDetailWidget &)			  = delete;
	ItemDetailWidget(ItemDetailWidget &&)				  = delete;
	ItemDetailWidget &operator=(const ItemDetailWidget &) = delete;
	ItemDetailWidget &operator=(ItemDetailWidget &&)	  = delete;

	std::map<QLineEdit *, std::string> lineEditMapper;
	TopologyItem					  *currentItem;
};

#endif