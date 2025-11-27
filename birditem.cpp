#include "birditem.h"
#include <QGraphicsScene>
#include <QRectF>
#include <QPainter>
#include <QKeyEvent>
BirdItem::BirdItem(QGraphicsScene* scene):
    m_curFlyStatus(0),m_IsDown(true),m_IsUp(true)
{
    scene->addItem(this);     //将对象鸟添加到游戏场景
    m_scene=scene;

    m_birdTimer=new QTimer(this);   //初始化计时器
    connect(m_birdTimer,&QTimer::timeout,this,&BirdItem::onRefreshBird);
    m_birdTimer->start(10);

    m_flyAnimation=new QPropertyAnimation(this,"pos");//位置属性

}

BirdItem::~BirdItem()
{

}

//重写绘图区域
QRectF BirdItem::boundingRect() const
{
    return QRectF(60,BIRD_SIZE * 5,BIRD_SIZE,BIRD_SIZE);
}

void BirdItem::flyUpAnimation()
{
    connect(m_flyAnimation,&QPropertyAnimation::finished,this,&BirdItem::onFlyUpAnimationFinished);
    if(m_IsUp){
        m_IsUp=false;
        m_flyAnimation->stop();//动画停止

        int nMove=pos().y();
        if(nMove>-180){ //以屏幕中心为原点
            m_flyAnimation->setDuration(300);//动画时长
            m_flyAnimation->setEndValue(QPoint(pos().x(),nMove-BIRD_SIZE));
        }
        else{
            m_flyAnimation->setDuration(300);//动画时长
            m_flyAnimation->setEndValue(pos());
        }
        m_flyAnimation->setEasingCurve(QEasingCurve::OutQuad);
        m_flyAnimation->start();
    }

}

void BirdItem::flyDownAnimation()
{
    if(m_IsDown){
        m_IsDown=false;
        m_flyAnimation->stop();
        m_flyAnimation->setDuration(500);
        m_flyAnimation->setEndValue(pos()+QPoint(0,BIRD_SIZE));
        m_flyAnimation->setEasingCurve(QEasingCurve::OutQuad);
        m_flyAnimation->start();

    }
}

bool BirdItem::checkIsCollided()
{
    if(collidingItems().isEmpty())return false;
    return true;
}

void BirdItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(m_curFlyStatus<10){
        painter->drawImage(boundingRect(),QImage(":/BirdGame/Resources/image/bird1.png"));
    }
    else if(m_curFlyStatus<20){
        painter->drawImage(boundingRect(),QImage(":/BirdGame/Resources/image/bird2.png"));
    }
    else if(m_curFlyStatus<30){
        painter->drawImage(boundingRect(),QImage(":/BirdGame/Resources/image/bird3.png"));
    }
    if(m_curFlyStatus>=30)m_curFlyStatus=0;
    m_curFlyStatus++;
}

void BirdItem::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Space){
        m_IsUp=true;
        flyUpAnimation();
    }
}


void BirdItem::onRefreshBird()
{
    update();
}

void BirdItem::onFlyUpAnimationFinished()
{
    m_IsDown=true;
    flyDownAnimation();
}
