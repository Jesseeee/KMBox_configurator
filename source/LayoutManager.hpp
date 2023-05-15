/**
 * @file LayoutManager.hpp
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
 * - May 08, 2023 ; jesvan
 */
#ifndef LAYOUTMANAGER_HPP_
#define LAYOUTMANAGER_HPP_

#include <QObject>

#include "topology/TopologyWindow.hpp"
#include "layout/LayoutWindow.hpp"

class LayoutManager : public QObject
{
	Q_OBJECT
public:
	LayoutManager()			  = default;
	~LayoutManager() override = default;

	void setTopologyWindow(TopologyWindow *pTopologyWindow);
	void setLayoutWindow(LayoutWindow *pLayoutWindow);

	// Disable copy and move semantics by default
	LayoutManager(const LayoutManager &)			= delete;
	LayoutManager(LayoutManager &&)					= delete;
	LayoutManager &operator=(const LayoutManager &) = delete;
	LayoutManager &operator=(LayoutManager &&)		= delete;

private Q_SLOTS:
	void topologySaved();
	void layoutSaved();

private:
	TopologyWindow *m_pTopologyWindow = nullptr;
	LayoutWindow   *m_pLayoutWindow	  = nullptr;
};

#endif