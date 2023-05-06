/**
 * @file LayoutScene.hpp
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
 * - May 06, 2023 ; jesvan
 */
#ifndef LAYOUTSCENE_HPP_
#define LAYOUTSCENE_HPP_

#include <QGraphicsScene>

class LayoutScene : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit LayoutScene(QObject *parent = nullptr);
	~LayoutScene() override;

	// Disable copy and move semantics by default
	LayoutScene(const LayoutScene &)			= delete;
	LayoutScene(LayoutScene &&)					= delete;
	LayoutScene &operator=(const LayoutScene &) = delete;
	LayoutScene &operator=(LayoutScene &&)		= delete;
};

#endif