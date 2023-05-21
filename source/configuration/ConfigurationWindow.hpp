/**
 * @file ConfigurationWindow.hpp
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
 * - May 21, 2023 ; jesvan
 */
#ifndef CONFIGURATIONWINDOW_HPP_
#define CONFIGURATIONWINDOW_HPP_

#include <QWidget>

#include "ConfigurationManager.hpp"

class ConfigurationWindow : public QWidget
{
	Q_OBJECT
public:
	ConfigurationWindow(QWidget *parent = nullptr);
	virtual ~ConfigurationWindow();

	// Disable copy and move semantics by default
	ConfigurationWindow(const ConfigurationWindow &)			= delete;
	ConfigurationWindow(ConfigurationWindow &&)					= delete;
	ConfigurationWindow &operator=(const ConfigurationWindow &) = delete;
	ConfigurationWindow &operator=(ConfigurationWindow &&)		= delete;

private slots:
	void uploadConfiguration();
};

#endif