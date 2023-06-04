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
#include "topology/Arrow.hpp"
#include "topology/TopologyItem.hpp"

void LayoutManager::setTopologyWindow(TopologyWindow *pTopologyWindow)
{
	m_pTopologyWindow = pTopologyWindow;
	QObject::connect(m_pTopologyWindow, &TopologyWindow::saveTopology, [this]() { topologySaved(); });
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

	std::map<std::string, std::string> servers;
	std::map<std::string, std::string> screens;

	for (const Arrow *arrow : arrows)
	{
		TopologyItem *startItem = arrow->startItem();
		TopologyItem *endItem	= arrow->endItem();
		std::string	  startAnchorName;
		std::string	  endAnchorName;
		for (const TopologyItem::anchorPoint &anchorPoint : startItem->getAnchors())
		{
			if (anchorPoint.m_anchor == arrow->startAnchor())
			{
				startAnchorName = anchorPoint.m_name;
			}
		}
		for (const TopologyItem::anchorPoint &anchorPoint : endItem->getAnchors())
		{
			if (anchorPoint.m_anchor == arrow->endAnchor())
			{
				endAnchorName = anchorPoint.m_name;
			}
		}

		if (startItem->diagramType() == TopologyItem::TopologyType::KMBox)
		{
			if (endItem->diagramType() == TopologyItem::TopologyType::Server)
			{
				if (endAnchorName == "USB-B")
				{
					// Valid connection, so let's fill it up
					servers.try_emplace(endItem->getAttributes()["server name"], startAnchorName);
				}
			}
		}
		else if (startItem->diagramType() == TopologyItem::TopologyType::Server)
		{
			if (endItem->diagramType() == TopologyItem::TopologyType::KMBox)
			{
				if (startAnchorName == "USB-B")
				{
					// Valid connection, so let's fill it up
					servers.try_emplace(startItem->getAttributes()["server name"], endAnchorName);
				}
			}
			if (endItem->diagramType() == TopologyItem::TopologyType::Display)
			{
				if (startAnchorName == "VideoOut")
				{
					// Valid connection, so let's fill it up
					screens.try_emplace(endItem->getAttributes()["display name"],
										startItem->getAttributes()["server name"]);
				}
			}
		}
		else if (startItem->diagramType() == TopologyItem::TopologyType::Display)
		{
			if (endItem->diagramType() == TopologyItem::TopologyType::Server)
			{
				if (endAnchorName == "VideoOut")
				{
					screens.try_emplace(startItem->getAttributes()["display name"],
										endItem->getAttributes()["server name"]);
				}
			}
		}
	}

	ConfigurationManager::instance().setServers(servers);
	ConfigurationManager::instance().setScreens(screens);

	m_pLayoutWindow->clearScreens();

	int screenCount = 0;
	for (const auto [screen, server] : screens)
	{
		m_pLayoutWindow->addScreen(100 * screenCount, 0, 100, 100, screen);
		screenCount++;
	}

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
			QRectF rect(qRound(rectItem->pos().x()),
						qRound(rectItem->pos().y()),
						qRound(rectItem->rect().width()),
						qRound(rectItem->rect().height()));

			layoutScreen.layoutRect = rect;
			kmLayout.layoutScreens.push_back(layoutScreen);
		}
	}

	std::vector<ConfigurationManager::KMLayout> layouts;
	layouts.push_back(kmLayout);
	ConfigurationManager::instance().setLayouts(layouts);
}