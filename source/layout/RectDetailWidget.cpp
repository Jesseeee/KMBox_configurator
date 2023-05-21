/**
 * @file RectDetailWidget.cpp
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
 * - May 20, 2023 ; jesvan
 */

#include "RectDetailWidget.hpp"

#include <QGraphicsRectItem>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>

RectDetailWidget::RectDetailWidget()
{
	auto *layout = new QVBoxLayout(this);
	layout->setAlignment(Qt::AlignTop);

	xposLabel	= new QLabel(tr("X position"), this);
	xposSpinBox = new QSpinBox(this);
	xposSpinBox->setMinimum(0);
	xposSpinBox->setMaximum(0x7FFF);
	QObject::connect(xposSpinBox, &QSpinBox::valueChanged, this, &RectDetailWidget::xposChanged);
	yposlabel	= new QLabel(tr("Y position"), this);
	yposSpinBox = new QSpinBox(this);
	yposSpinBox->setMinimum(0);
	yposSpinBox->setMaximum(0x7FFF);
	QObject::connect(yposSpinBox, &QSpinBox::valueChanged, this, &RectDetailWidget::yposChanged);
	widthLabel	 = new QLabel(tr("Width"), this);
	widthSpinBox = new QSpinBox(this);
	widthSpinBox->setMinimum(0);
	widthSpinBox->setMaximum(0x7FFF);
	QObject::connect(widthSpinBox, &QSpinBox::valueChanged, this, &RectDetailWidget::widthChanged);
	heightLabel	  = new QLabel(tr("height"), this);
	heightSpinBox = new QSpinBox(this);
	heightSpinBox->setMinimum(0);
	heightSpinBox->setMaximum(0x7FFF);
	QObject::connect(heightSpinBox, &QSpinBox::valueChanged, this, &RectDetailWidget::heightChanged);

	layout->addWidget(xposLabel);
	layout->addWidget(xposSpinBox);
	layout->addWidget(yposlabel);
	layout->addWidget(yposSpinBox);
	layout->addWidget(widthLabel);
	layout->addWidget(widthSpinBox);
	layout->addWidget(heightLabel);
	layout->addWidget(heightSpinBox);

	setLayout(layout);
}

RectDetailWidget::~RectDetailWidget() {}

void RectDetailWidget::setRectItem(QGraphicsRectItem *item)
{
	currentRectItem = item;
	QRectF rect		= item->rect();
	xposSpinBox->setValue(item->pos().x());
	yposSpinBox->setValue(item->pos().y());
	widthSpinBox->setValue(rect.width());
	heightSpinBox->setValue(rect.height());
}

void RectDetailWidget::xposChanged(int xpos)
{
	if (currentRectItem)
	{
		currentRectItem->setPos(xpos, currentRectItem->pos().y());
	}
}

void RectDetailWidget::yposChanged(int ypos)
{
	if (currentRectItem)
	{
		currentRectItem->setPos(currentRectItem->pos().x(), ypos);
	}
}

void RectDetailWidget::widthChanged(int width)
{
	if (currentRectItem)
	{
		QRectF rect = currentRectItem->rect();
		rect.setWidth(width);
		currentRectItem->setRect(rect);
	}
}

void RectDetailWidget::heightChanged(int height)
{
	if (currentRectItem)
	{
		QRectF rect = currentRectItem->rect();
		rect.setHeight(height);
		currentRectItem->setRect(rect);
	}
}
