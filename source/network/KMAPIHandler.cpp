/**
 * @file KMAPIHandler.cpp
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
 * - May 21, 2023 ; jesvan
 */

#include <string>
#include <QByteArray>
#include <QNetworkProxy>

#include "KMAPIHandler.hpp"

KMAPIHandler::KMAPIHandler()
{
	m_manager.setProxy(QNetworkProxy::NoProxy);
	QObject::connect(&m_manager, &QNetworkAccessManager::authenticationRequired, this, authenticationRequired);

	QObject::connect(&m_manager,
					 &QNetworkAccessManager::sslErrors,
					 [](QNetworkReply *reply, const QList<QSslError> &errors) { qDebug() << "SSL errors " << errors; });

	m_sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
	m_sslConfig.setProtocol(QSsl::TlsV1_2OrLater); // Use TLS 1.2
	m_sslConfig.setSslOption(QSsl::SslOptionDisableSessionTickets, true);
}

void KMAPIHandler::setUsername(const QString &username)
{
	m_username = username;
	if (m_password.size() != 0)
	{
		QString pass	= m_username + ":" + m_password;
		m_basicAuthHash = "Basic " + pass.toUtf8().toBase64();
	}
}

void KMAPIHandler::setPassword(const QString &password)
{
	m_password = password;
	if (m_username.size() != 0)
	{
		QString pass	= m_username + ":" + m_password;
		m_basicAuthHash = "Basic " + pass.toUtf8().toBase64();
	}
}

void KMAPIHandler::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
	qDebug() << "Set authentication";
	if (m_username.isNull() || m_password.isNull())
	{
		qDebug() << "Need to provide a username and password for authentication";
	}
	qDebug() << "user:pass is " << m_username << ":" << m_password;
	authenticator->setUser(m_username);
	authenticator->setPassword(m_password);
	Q_UNUSED(reply)
}

void KMAPIHandler::sendConfiguration(const QString &configurationXml)
{
	if (m_basicAuthHash.size() == 0)
	{
		qDebug() << "Need a username and password to try initiate the request";
	}
	QUrl			url = "https://" + m_address.toString() + "/dapi/device_v1/configuration/?command=set";
	QNetworkRequest request(url);

	request.setRawHeader("Authorization", m_basicAuthHash);

	// Configure other SSL settings as needed
	request.setSslConfiguration(m_sslConfig);

	QNetworkReply *reply = m_manager.put(request, configurationXml.toUtf8());
	QObject::connect(reply,
					 &QNetworkReply::finished,
					 [reply]()
					 {
						 if (reply->error() == QNetworkReply::NoError)
						 {
							 qDebug() << "Request sent!";
						 }
						 else
						 {
							 qDebug() << "Request failed:" << reply->errorString();
							 qDebug() << int(reply->error());
						 }
						 qDebug() << reply->readAll();
						 reply->deleteLater();
					 });
}