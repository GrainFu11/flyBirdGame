#include "startbtnitem.h"
#include <QGraphicsScene>
#include <QCursor>
#include <QRectF>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
StartBtnItem::StartBtnItem(const QPixmap &pix,QGraphicsScene *scene):m_pix(pix)
{

    scene->addItem(this);
    setCursor(QCursor(Qt::PointingHandCursor));//鼠标为手指形状

}

StartBtnItem::~StartBtnItem()
{

}

QRectF StartBtnItem::boundingRect() const
{
    return QRectF(QPointF(0,0),m_pix.size());
}

void StartBtnItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        emit clicked();
    }
}

void StartBtnItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0,m_pix);
}
