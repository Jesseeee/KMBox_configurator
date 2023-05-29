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

#include "network/KMAPIHandler.hpp"

class QLabel;
class QTextEdit;
class QLineEdit;

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
	void configurationChanged(const QString &configuration);

private:
	KMAPIHandler m_KMAPIHandler;
	QTextEdit	*m_xmlTextEdit	 = nullptr;
	QLabel		*m_ipLabel		 = nullptr;
	QLineEdit	*m_ipTextField	 = nullptr;
	QLabel		*m_userNameLabel = nullptr;
	QLineEdit	*m_userNameField = nullptr;
	QLabel		*m_passwordLabel = nullptr;
	QLineEdit	*m_passwordField = nullptr;
};

#endif