#include "DiagramScene.hpp"
#include "Arrow.hpp"

#include <QGraphicsSceneMouseEvent>
#include <QTextCursor>

DiagramScene::DiagramScene(QObject *parent)
	: QGraphicsScene(parent)
{
}

void DiagramScene::setMode(Mode mode)
{
	m_myMode = mode;
}

void DiagramScene::setItemType(DiagramItem::DiagramType type)
{
	m_myItemType = type;
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (mouseEvent->button() != Qt::LeftButton)
		return;

	DiagramItem *item;
	switch (m_myMode)
	{
		case Mode::InsertItem:
			item = new DiagramItem(m_myItemType);
			addItem(item);
			item->setPos(mouseEvent->scenePos());
			emit itemInserted(item);
			break;
		case Mode::InsertLine:
			m_line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
			m_line->setPen(QPen(Qt::black, 2));
			addItem(m_line);
			break;
		default:;
	}
	QGraphicsScene::mousePressEvent(mouseEvent);
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (m_myMode == Mode::InsertLine && m_line != nullptr)
	{
		QLineF newLine(m_line->line().p1(), mouseEvent->scenePos());
		m_line->setLine(newLine);
	}
	else if (m_myMode == Mode::MoveItem)
	{
		QGraphicsScene::mouseMoveEvent(mouseEvent);
	}
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (m_line != nullptr && m_myMode == Mode::InsertLine)
	{
		QList<QGraphicsItem *> startItems = items(m_line->line().p1());
		if (startItems.count() && startItems.first() == m_line)
			startItems.removeFirst();
		QList<QGraphicsItem *> endItems = items(m_line->line().p2());
		if (endItems.count() && endItems.first() == m_line)
			endItems.removeFirst();

		removeItem(m_line);
		delete m_line;

		if (!startItems.empty() && !endItems.empty() && startItems.first()->type() == DiagramItem::Type
			&& endItems.first()->type() == DiagramItem::Type && startItems.first() != endItems.first())
		{
			DiagramItem *startItem = qgraphicsitem_cast<DiagramItem *>(startItems.first());
			DiagramItem *endItem   = qgraphicsitem_cast<DiagramItem *>(endItems.first());
			Arrow		*arrow	   = new Arrow(startItem, endItem);
			startItem->addArrow(arrow);
			endItem->addArrow(arrow);
			arrow->setZValue(-1000.0);
			addItem(arrow);
			arrow->updatePosition();
		}
	}
	m_line = nullptr;
	QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

bool DiagramScene::isItemChange(int type) const
{
	const QList<QGraphicsItem *> items = selectedItems();
	const auto					 cb	   = [type](const QGraphicsItem *item) { return item->type() == type; };
	return std::find_if(items.begin(), items.end(), cb) != items.end();
}
