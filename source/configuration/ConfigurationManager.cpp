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
	QXmlStreamWriter writer(&m_configuration);
	writer.setAutoFormatting(true);

	writer.writeDefaultNamespace("http://www.esterline.com/device/configuration"); // Add default namespace
	writer.writeStartElement("configuration");
	writer.writeEndElement(); // configuration root end
	qDebug() << m_configuration;
}