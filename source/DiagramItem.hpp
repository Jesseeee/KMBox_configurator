#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QGraphicsPixmapItem>
#include <QList>

QT_BEGIN_NAMESPACE
class QPixmap;
class QGraphicsSceneContextMenuEvent;
class QMenu;
class QPolygonF;
QT_END_NAMESPACE

class Arrow;

class DiagramItem : public QGraphicsPolygonItem
{
public:
	enum
	{
		Type = UserType + 15
	};
	enum class DiagramType
	{
		Step,
		Conditional,
		StartEnd,
		Io
	};

	DiagramItem(DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent = nullptr);

	void		removeArrow(Arrow *arrow);
	void		removeArrows();
	DiagramType diagramType() const { return m_myDiagramType; }
	QPolygonF	polygon() const { return m_myPolygon; }
	void		addArrow(Arrow *arrow);
	QPixmap		image() const;
	int			type() const override { return Type; }

protected:
	void	 contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
	DiagramType	   m_myDiagramType;
	QPolygonF	   m_myPolygon;
	QMenu		  *m_myContextMenu;
	QList<Arrow *> m_arrows;
};

#endif // DIAGRAMITEM_H