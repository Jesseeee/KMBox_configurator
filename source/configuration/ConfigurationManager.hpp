/**
 * @file ConfigurationManager.hpp
 *
 * @brief Can create a configuration based on the layout and topology and has utilities to change the configuration
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
 * - May 21, 2023 ; jesvan
 */
#ifndef CONFIGURATIONMANAGER_HPP_
#define CONFIGURATIONMANAGER_HPP_

#include <map>
#include <string>
#include <vector>

#include <QRectF>
#include <QString>

class ConfigurationManager
{
public:
	virtual ~ConfigurationManager();

	static ConfigurationManager &instance()
	{
		static ConfigurationManager instance;
		return instance;
	}

	/// @brief The screen inside a layout with it's name and rectangle (position)
	struct LayoutScreen
	{
		std::string screenName;
		QRectF		layoutRect;
		qreal		zValue;
	};

	/// @brief A single layout with a layout name and the screens inside it
	struct KMLayout
	{
		std::string				  layoutName;
		std::vector<LayoutScreen> layoutScreens;
	};

	void setServers(const std::map<std::string, std::string> &servers);
	void setScreens(const std::map<std::string, std::string> &screens);
	void setLayouts(const std::vector<KMLayout> &layouts);

	// Disable copy and move semantics by default
	ConfigurationManager(const ConfigurationManager &)			  = delete;
	ConfigurationManager(ConfigurationManager &&)				  = delete;
	ConfigurationManager &operator=(const ConfigurationManager &) = delete;
	ConfigurationManager &operator=(ConfigurationManager &&)	  = delete;

private:
	// TODO - remove function call, only for testing now
	ConfigurationManager() { createConfiguration(); }

	void createConfiguration();

private:
	/// @brief The servers are a map of server name and usb-name
	std::map<std::string, std::string> m_servers;
	///	@brief The screens are a map of screen names and server names
	std::map<std::string, std::string> m_screens;
	/// @brief Vector of layouts
	std::vector<KMLayout>			   m_layouts;
	/// @brief The configuration XML
	QString							   m_configuration;
};

#endif