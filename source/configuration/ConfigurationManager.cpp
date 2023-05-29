/**
 * @file ConfigurationManager.cpp
 *
 * @brief Can create a configuration based on the layout and topology and has utilities to change the configuration
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
 * - May 21, 2023 ; jesvan
 */

#include "ConfigurationManager.hpp"

#include <QXmlStreamWriter>
#include <QDebug>

ConfigurationManager::~ConfigurationManager() {}

void ConfigurationManager::setServers(const std::map<std::string, std::string> &servers)
{
	m_servers.clear();
	m_screens.clear();
	m_servers = servers;

	// TODO Perform a sanity check
}

void ConfigurationManager::setScreens(const std::map<std::string, std::string> &screens)
{
	// TODO - checking
	m_screens = screens;
}

void ConfigurationManager::setLayouts(const std::vector<KMLayout> &layouts)
{
	// TODO checking

	m_layouts = layouts;

	createConfiguration();
}

void ConfigurationManager::createConfiguration()
{
	m_configuration = "";

	int amountOfScreens = 0;

	QStringList		 screenElements;
	QXmlStreamWriter writer(&m_configuration);
	writer.setAutoFormatting(true);

	writer.writeDefaultNamespace("http://www.esterline.com/device/configuration"); // Add default namespace
	writer.writeStartElement("configuration"); // Start configuration root element

	for (KMLayout &layout : m_layouts)
	{
		for (LayoutScreen &screen : layout.layoutScreens)
		{
			QString usb		   = QString::fromStdString(m_servers[m_screens[screen.screenName]]);
			QString screenName = usb + ":screen" + QString::number(amountOfScreens);
			amountOfScreens++;
			QString worldLocation;
			worldLocation += QString::number(screen.layoutRect.x()) + " ";
			worldLocation += QString::number(screen.layoutRect.y()) + " ";
			worldLocation += QString::number(screen.layoutRect.width()) + " ";
			worldLocation += QString::number(screen.layoutRect.height());
			writer.writeStartElement("screen");
			writer.writeAttribute("name", screenName);
			writer.writeAttribute("worldlocation", worldLocation);
			writer.writeEndElement(); // close screen elements
			screen.kmName = screenName;
		}
	}

	writer.writeStartElement("layouts");

	for (const KMLayout &layout : m_layouts)
	{
		writer.writeStartElement("layout");
		writer.writeAttribute("name", layout.layoutName);
		for (const LayoutScreen &screen : layout.layoutScreens)
		{
			writer.writeStartElement("screen");
			writer.writeAttribute("name", screen.kmName);
			writer.writeAttribute("absolute", "true");
			writer.writeEndElement(); // close screen element
		}
		writer.writeEndElement(); // close layout element
	}

	writer.writeEndElement(); // close layouts element

	writer.writeEndElement(); // Close the configuration root element

	writer.writeEndDocument();

	configurationChanged(m_configuration);
}