/**
 * @file TopologyList.hpp
 *
 * @brief List widget containing the topology icons
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
 * - Apr 12, 2023 ; jesvan59903
 */
#ifndef TOPOLOGYLIST_HPP_
#define TOPOLOGYLIST_HPP_

#include <QListWidget>

class TopologyList : public QListWidget
{
	Q_OBJECT
public:
	explicit TopologyList(QWidget *parent = nullptr);
	~TopologyList() override = default;

	void addIcon(const QPixmap &pixmap, const QPoint &location);

	static QString topologyMimeType() { return QStringLiteral("image/x-topology-icon"); }

protected:
	void dragEnterEvent(QDragEnterEvent *event) override;
	void dragMoveEvent(QDragMoveEvent *event) override;
	void dropEvent(QDropEvent *event) override;
	void startDrag(Qt::DropActions supportedActions) override;

private:
	// Disable copy and move semantics by default
	TopologyList(const TopologyList &)			  = delete;
	TopologyList(TopologyList &&)				  = delete;
	TopologyList &operator=(const TopologyList &) = delete;
	TopologyList &operator=(TopologyList &&)	  = delete;
};

#endif