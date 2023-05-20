/**
 * @file ItemDetailWidget.cpp
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
 * - May 17, 2023 ; jesvan
 */

#include "ItemDetailWidget.hpp"

#include "TopologyItem.hpp"
#include "QVBoxLayout"
#include <QLineEdit>
#include <QLabel>

ItemDetailWidget::ItemDetailWidget() {}

ItemDetailWidget::~ItemDetailWidget() {}

void ItemDetailWidget::setFields(TopologyItem *item, std::map<std::string, std::string> attributes)
{
	currentItem	 = item;
	auto *layout = new QVBoxLayout(this);
	layout->setAlignment(Qt::AlignTop);

	for (const auto &[key, val] : attributes)
	{
		layout->addWidget(new QLabel(QString::fromStdString(key), this));
		auto *lineEdit = new QLineEdit(this);
		lineEdit->setText(QString::fromStdString(val));
		layout->addWidget(lineEdit);
		lineEditMapper.emplace(lineEdit, key);
		QObject::connect(lineEdit, &QLineEdit::textChanged, this, &ItemDetailWidget::fieldTextChanged);
	}

	setLayout(layout);
}

void ItemDetailWidget::fieldTextChanged(const QString &text)
{
	currentItem->setAttributeValue(lineEditMapper[(QLineEdit *)sender()], text.toStdString());
}