#include "roaditem.h"
#include <QRectF>
#include <QPainter>
#include <QPropertyAnimation>
#include <QPoint>
RoadItem::RoadItem(QGraphicsScene * scene):m_scene(scene) {
    scene->addItem(this);
    startMove();

}

RoadItem::~RoadItem()
{

}

QRectF RoadItem::boundingRect() const
{
    return QRectF(0,m_scene->height()-64,m_scene->width()*2,64);
}

void RoadItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //前后两段马路
    painter->drawImage(QRectF(0,m_scene->height()-64,m_scene->width(),64),QImage(":/BirdGame/Resources/image/road.png"));

    painter->drawImage(QRectF(m_scene->width(),m_scene->height()-64,m_scene->width(),64),QImage(":/BirdGame/Resources/image/road.png"));
}

void RoadItem::startMove()
{
    QPropertyAnimation *moveAnimation=new QPropertyAnimation(this,"pos");
    moveAnimation->setLoopCount(-1);
    moveAnimation->setDuration(6000);
    moveAnimation->setStartValue(QPoint(0,pos().y()));
    moveAnimation->setEndValue(QPoint(0-m_scene->width(),pos().y()));
    moveAnimation->setEasingCurve(QEasingCurve::Linear);
    moveAnimation->start();
}
