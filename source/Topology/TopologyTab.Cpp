/**
 * @file TopologyTab.Cpp
 *
 * @brief The tab for the physical topology
 *
 * &copy; Copyright 2023 ScioTeq bv. All rights reserved.
 * +-------------------------------------------------------------------------------------------+
 * |                             Export Control Information                                    |
 * +--------+-------------+-------------------------------------+----------->-------------------+
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

#include "TopologyTab.hpp"

TopologyTab::TopologyTab(QWidget *parent)
	: QFrame(parent)
	, m_tabLayout(this)
	, m_topologyIconList(this)
	, m_topologyMainWidget(400, this)
{
	m_tabLayout.addWidget(&m_topologyIconList);
	m_tabLayout.addWidget(&m_topologyMainWidget);
}

TopologyTab::~TopologyTab() {}
