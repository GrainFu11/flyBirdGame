#ifndef ROADITEM_H
#define ROADITEM_H

#include <QGraphicsObject>
#include <QGraphicsScene>
class RoadItem : public QGraphicsObject
{
    Q_OBJECT
public:
    RoadItem(QGraphicsScene * scene);
    ~RoadItem();
    QRectF boundingRect()const;

private:
    void paint(QPainter *,const QStyleOptionGraphicsItem*,QWidget*);
    void startMove();

    QGraphicsScene* m_scene;
};

#endif // ROADITEM_H
