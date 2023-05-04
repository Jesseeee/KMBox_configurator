#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QGraphicsPixmapItem>
#include <QList>
#include <QPixmap>

QT_BEGIN_NAMESPACE
class QGraphicsSceneContextMenuEvent;
class QMenu;
class QPolygonF;
QT_END_NAMESPACE

class Arrow;

class DiagramItem : public QGraphicsPixmapItem
{
public:
	enum
	{
		Type = UserType + 15
	};
	enum class DiagramType
	{
		Server,
		Display
	};

	DiagramItem(DiagramType diagramType, QGraphicsItem *parent = nullptr);

	void		removeArrow(Arrow *arrow);
	void		removeArrows();
	DiagramType diagramType() const { return m_myDiagramType; }
	QPolygonF	polygon() const { return m_myPolygon; }
	void		addArrow(Arrow *arrow);
	QPixmap		image() const;
	int			type() const override { return Type; }

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
	DiagramType	   m_myDiagramType;
	QPolygonF	   m_myPolygon;
	QList<Arrow *> m_arrows;
	QPixmap		   m_myPixMap;
};

#endif // DIAGRAMITEM_H
