/**
 * @file KMAPIHandler.hpp
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
#ifndef KMAPIHANDLER_HPP_
#define KMAPIHANDLER_HPP_

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QAuthenticator>

class KMAPIHandler : public QObject
{
	Q_OBJECT
public:
	KMAPIHandler();
	~KMAPIHandler() override = default;

	// Disable copy and move semantics by default
	KMAPIHandler(const KMAPIHandler &)			  = delete;
	KMAPIHandler(KMAPIHandler &&)				  = delete;
	KMAPIHandler &operator=(const KMAPIHandler &) = delete;
	KMAPIHandler &operator=(KMAPIHandler &&)	  = delete;

	void setUsername(const QString &username);
	void setPassword(const QString &password);

	void setKMAddress(const QHostAddress &address) { m_address = address; }
	void setKMAddress(const QString &address) { m_address = QHostAddress(address); }

	void sendConfiguration(const QString &configurationXml);

private slots:
	void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);

private:
	QNetworkAccessManager m_manager;
	QSslConfiguration	  m_sslConfig;

	QString		 m_username;
	QString		 m_password;
	QByteArray	 m_basicAuthHash;
	QHostAddress m_address;
};

#endif