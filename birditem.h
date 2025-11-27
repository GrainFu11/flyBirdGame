#ifndef BIRDITEM_H
#define BIRDITEM_H
#include <QGraphicsObject>
#include <QTimer>
#include <QPropertyAnimation>
//自定义的鸟儿图像 ，需要重写 paint,boundingRect
#define BIRD_SIZE 32

class BirdItem:public QGraphicsObject{

    Q_OBJECT
public:
    BirdItem(QGraphicsScene* scene);
    ~BirdItem();
    QRectF boundingRect()const;
    void flyUpAnimation();              //上升
    void flyDownAnimation();            //下降
    bool checkIsCollided();             //碰撞检测
    void keyPressEvent(QKeyEvent* event);//键盘事件
private:
    void paint(QPainter *, const QStyleOptionGraphicsItem*,QWidget*);//绘图事件


    bool m_IsDown;  //下降标识
    bool m_IsUp;    //上升标识
    int m_curFlyStatus; //翅膀扇动状态
    QPropertyAnimation* m_flyAnimation;//小鸟pos
    QGraphicsScene* m_scene;   //场景
    QTimer* m_birdTimer;  //刷新小鸟计时器

private slots:
    void onRefreshBird();
    void onFlyUpAnimationFinished();    //上升动画结束

};

#endif // BIRDITEM_H
