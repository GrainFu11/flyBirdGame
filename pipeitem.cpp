#include "pipeitem.h"
#include <QPainter>
#include <QPropertyAnimation>

PipeItem::PipeItem(QGraphicsScene * scene):m_scene(scene)
{
    scene->addItem(this);
    createPipeHeight();
    startMove();
}

PipeItem::~PipeItem()
{

}

QRectF PipeItem::boundingRect() const
{
    return  QRectF(m_scene->width(),0,60,m_scene->height());
}

void PipeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget*)
{
    painter->drawImage(QRectF(m_scene->width(),0,60,m_upPipeHeight),QImage(":/BirdGame/Resources/image/tubeup.png"));
    painter->drawImage(QRectF(m_scene->width(),m_upPipeHeight+115,60,m_downPipeHeight),QImage(":/BirdGame/Resources/image/tubedown.png"));

}

void PipeItem::startMove()
{
    QPropertyAnimation *moveAnimation=new QPropertyAnimation(this,"pos");
    moveAnimation->setLoopCount(-1);
    moveAnimation->setDuration(3000);
    moveAnimation->setStartValue(QPoint(0,pos().y()));
    moveAnimation->setEndValue(QPoint(0-m_scene->width()-60,pos().y()));
    moveAnimation->setEasingCurve(QEasingCurve::Linear);
    moveAnimation->start();

    connect(moveAnimation,&QPropertyAnimation::currentLoopChanged,this,[=](){
        createPipeHeight();
    });

}

void PipeItem::createPipeHeight()
{
    m_upPipeHeight=rand()%100+80;
    m_downPipeHeight=m_scene->height()-m_upPipeHeight-178;
    // update();
}
