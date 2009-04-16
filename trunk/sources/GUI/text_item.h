/**
 * File: GUI/text_item.h - Implementational header for text item of GUI in MiptVis tool.
 * Copyright (C) 2009  Ivan Mashintsev
 */
#ifndef TEXT_ITEM_H
#define TEXT_ITEM_H
#include <QtGui/QGraphicsTextItem>

class Line;

/**
 * Class Text. Class Text represents the node of the graph
 */
class Text:public QGraphicsTextItem
{
private:
    QList<Line *> lines;
    QPolygonF myPolygon;
    QColor myColor;
    qreal myAdjust;
public:
    Text( QString * text = 0, QGraphicsItem * parent = 0, QGraphicsScene * scene = 0);
    inline QPolygonF polygon() const
    {
        return myPolygon;
    };
    inline void setMyColor( QColor color)
    {
        myColor = color;
    };
    inline void setMyAdjust( qreal adjust)
    {
        myAdjust = adjust;
    };
    void removeLine( Line * line);
    void removeLines();
    void addLine( Line * line);
    QRectF boundingRect() const;
protected:
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    QVariant itemChange( GraphicsItemChange change, const QVariant &value);
    void focusInEvent ( QFocusEvent * event);
    void focusOutEvent ( QFocusEvent * event);
    void mouseDoubleClickEvent( QGraphicsSceneMouseEvent * mouseEvent);
    void mousePressEvent( QGraphicsSceneMouseEvent * mouseEvent);
    void mouseReleaseEvent( QGraphicsSceneMouseEvent * event);
};
#endif