/**
 * @file ConfigurationWindow.cpp
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

#include "ConfigurationWindow.hpp"

#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

ConfigurationWindow::ConfigurationWindow(QWidget *parent)
	: QWidget(parent)
{
	QHBoxLayout *mainLayout			= new QHBoxLayout(this);
	QVBoxLayout *textEditLayout		= new QVBoxLayout();
	QVBoxLayout *buttonFieldsLayout = new QVBoxLayout();

	// Create a QTextEdit in the first tab
	m_xmlTextEdit = new QTextEdit(this);
	m_xmlTextEdit->setMaximumWidth(1000);
	textEditLayout->addWidget(m_xmlTextEdit);

	m_ipLabel = new QLabel(tr("IP address"), this);
	buttonFieldsLayout->addWidget(m_ipLabel);
	m_ipTextField = new QLineEdit(this);
	QObject::connect(m_ipTextField,
					 &QLineEdit::textChanged,
					 [this](const QString &ip) { m_KMAPIHandler.setKMAddress(ip); });
	buttonFieldsLayout->addWidget(m_ipTextField);
	m_userNameLabel = new QLabel(tr("Username"), this);
	buttonFieldsLayout->addWidget(m_userNameLabel);
	m_userNameField = new QLineEdit(this);
	QObject::connect(m_userNameField,
					 &QLineEdit::textChanged,
					 [this](const QString &username) { m_KMAPIHandler.setUsername(username); });
	buttonFieldsLayout->addWidget(m_userNameField);
	m_passwordLabel = new QLabel(tr("Password"), this);
	buttonFieldsLayout->addWidget(m_passwordLabel);
	m_passwordField = new QLineEdit(this);
	m_passwordField->setEchoMode(QLineEdit::EchoMode::Password);
	QObject::connect(m_passwordField,
					 &QLineEdit::textChanged,
					 [this](const QString &password) { m_KMAPIHandler.setPassword(password); });
	buttonFieldsLayout->addWidget(m_passwordField);

	// Create a QPushButton in the first tab
	QPushButton *uploadButton = new QPushButton(tr("Upload configuration"), this);
	QObject::connect(uploadButton,
					 &QPushButton::pressed,
					 [this]() { m_KMAPIHandler.sendConfiguration(m_xmlTextEdit->toPlainText()); });
	uploadButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	buttonFieldsLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	buttonFieldsLayout->addWidget(uploadButton);

	mainLayout->addLayout(textEditLayout);
	mainLayout->addLayout(buttonFieldsLayout);
	setLayout(mainLayout);
}

ConfigurationWindow::~ConfigurationWindow() {}