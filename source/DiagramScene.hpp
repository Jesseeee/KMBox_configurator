#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include "DiagramItem.hpp"

#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
QT_END_NAMESPACE

class DiagramScene : public QGraphicsScene
{
	Q_OBJECT

public:
	enum class Mode
	{
		InsertItem,
		InsertLine,
		MoveItem
	};

	explicit DiagramScene(QMenu *itemMenu, QObject *parent = nullptr);

public slots:
	void setMode(Mode mode);
	void setItemType(DiagramItem::DiagramType type);

signals:
	void itemInserted(DiagramItem *item);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
	bool isItemChange(int type) const;

	DiagramItem::DiagramType m_myItemType	  = DiagramItem::DiagramType::Step;
	QMenu					*m_myItemMenu	  = nullptr;
	Mode					 m_myMode		  = Mode::MoveItem;
	bool					 m_leftButtonDown = false;
	QPointF					 m_startPoint;
	QGraphicsLineItem		*m_line = nullptr;
};

#endif // DIAGRAMSCENE_H
