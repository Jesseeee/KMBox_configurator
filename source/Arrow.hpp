#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>

class DiagramItem;

class Arrow : public QGraphicsLineItem
{
public:
	enum
	{
		Type = UserType + 4
	};

	Arrow(DiagramItem *startItem, DiagramItem *endItem, QGraphicsItem *parent = nullptr);

	int			 type() const override { return Type; }
	QRectF		 boundingRect() const override;
	QPainterPath shape() const override;
	DiagramItem *startItem() const { return m_myStartItem; }
	DiagramItem *endItem() const { return m_myEndItem; }

	void updatePosition();

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
	DiagramItem *m_myStartItem;
	DiagramItem *m_myEndItem;
	QPolygonF	 m_arrowHead;
};

#endif // ARROW_H
