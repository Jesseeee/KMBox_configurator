/**
 * @file LayoutManager.cpp
 *
 * @brief TODO
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
 * - May 08, 2023 ; jesvan
 */

#include "LayoutManager.hpp"

#include "layout/ResizeableRectItem.hpp"
#include "configuration/ConfigurationManager.hpp"

void LayoutManager::setTopologyWindow(TopologyWindow *pTopologyWindow)
{
	m_pTopologyWindow = pTopologyWindow;
	QObject::connect(m_pTopologyWindow, &TopologyWindow::saveTopology, this, &LayoutManager::topologySaved);
}
void LayoutManager::setLayoutWindow(LayoutWindow *pLayoutWindow)
{
	m_pLayoutWindow = pLayoutWindow;
	QObject::connect(m_pLayoutWindow, &LayoutWindow::saveLayout, [this]() { layoutSaved(); });
}

void LayoutManager::topologySaved()
{
	std::vector<TopologyItem *> items  = m_pTopologyWindow->getAllTopologyItems();
	std::vector<Arrow *>		arrows = m_pTopologyWindow->getAllArrows();
	qDebug() << "Arrows size is " << arrows.size();

	// TODO - Parse this as a sort of logical tree and set the allowed screens in the layoutwindow
}

void LayoutManager::layoutSaved()
{
	// TODO - on layout save execute configuration creation
	ConfigurationManager::KMLayout kmLayout;
	kmLayout.layoutName = "001";

	for (QGraphicsItem *item : m_pLayoutWindow->getAllItems())
	{
		const ResizeableRectItem *rectItem = dynamic_cast<ResizeableRectItem *>(item);
		if (rectItem != nullptr)
		{
			ConfigurationManager::LayoutScreen layoutScreen;
			layoutScreen.screenName = rectItem->getScreenName();
			layoutScreen.zValue		= rectItem->zValue();
			QRectF rect(rectItem->pos().x(), rectItem->pos().x(), rectItem->rect().width(), rectItem->rect().height());

			layoutScreen.layoutRect = rect;
			kmLayout.layoutScreens.push_back(layoutScreen);
		}
	}

	std::vector<ConfigurationManager::KMLayout> layouts;
	layouts.push_back(kmLayout);
	ConfigurationManager::instance().setLayouts(layouts);
}