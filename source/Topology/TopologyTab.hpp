/**
 * @file TopologyTab.hpp
 *
 * @brief The tab for the physical topology
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
 * - Apr 15, 2023 ; jesvan59903
 */
#ifndef TOPOLOGYTAB_HPP_
#define TOPOLOGYTAB_HPP_

#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>

#include "TopologyList.hpp"
#include "TopologyWidget.hpp"

class TopologyTab : public QFrame
{
	Q_OBJECT
public:
	TopologyTab(QWidget *parent = nullptr);
	virtual ~TopologyTab();

private:
	// Disable copy and move semantics by default
	TopologyTab(const TopologyTab &)			= delete;
	TopologyTab(TopologyTab &&)					= delete;
	TopologyTab &operator=(const TopologyTab &) = delete;
	TopologyTab &operator=(TopologyTab &&)		= delete;

	QHBoxLayout	   m_tabLayout;
	TopologyList   m_topologyIconList;
	TopologyWidget m_topologyMainWidget;
};

#endif