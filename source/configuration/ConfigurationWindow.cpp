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

ConfigurationWindow::ConfigurationWindow(QWidget *parent)
	: QWidget(parent)
{
	QHBoxLayout *mainLayout			= new QHBoxLayout(this);
	QVBoxLayout *textEditLayout		= new QVBoxLayout();
	QVBoxLayout *buttonFieldsLayout = new QVBoxLayout();

	// Create a QTextEdit in the first tab
	QTextEdit *textEdit = new QTextEdit(this);
	textEdit->setMaximumWidth(1000);
	textEditLayout->addWidget(textEdit);

	// Create a QPushButton in the first tab
	QPushButton *uploadButton = new QPushButton(tr("Upload configuration"), this);
	QObject::connect(uploadButton, &QPushButton::pressed, this, &ConfigurationWindow::uploadConfiguration);
	uploadButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	buttonFieldsLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	buttonFieldsLayout->addWidget(uploadButton);

	mainLayout->addLayout(textEditLayout);
	mainLayout->addLayout(buttonFieldsLayout);
	setLayout(mainLayout);
}

ConfigurationWindow::~ConfigurationWindow() {}

void ConfigurationWindow::uploadConfiguration()
{
	// TODO - get the text from the textedit and try to upload it, validate it first
}
