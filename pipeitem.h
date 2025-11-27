#ifndef PIPEITEM_H
#define PIPEITEM_H

#include <QGraphicsObject>
#include <QGraphicsScene>
class PipeItem : public QGraphicsObject
{
    Q_OBJECT
public:
    PipeItem(QGraphicsScene * scene);
    ~PipeItem();
    QRectF boundingRect()const;

private:
    void paint(QPainter*,const QStyleOptionGraphicsItem*,QWidget*);
    void startMove();
    void createPipeHeight();

    int m_upPipeHeight;
    int m_downPipeHeight;
    QGraphicsScene *m_scene;

};

#endif // PIPEITEM_H
