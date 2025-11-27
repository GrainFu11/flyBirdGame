#ifndef STARTBTNITEM_H
#define STARTBTNITEM_H

#include <QGraphicsObject>
#include <QPixmap>                 // 第1处：你忘了包含 QPixmap！
#include <QGraphicsSceneMouseEvent> // 第2处：mousePressEvent 要用到！
class StartBtnItem : public QGraphicsObject
{
    Q_OBJECT
public:
    StartBtnItem(const QPixmap &pix,QGraphicsScene *scene);
    ~StartBtnItem();
    QRectF boundingRect()const override;
private:
    void mousePressEvent(QGraphicsSceneMouseEvent* event)override;
    // void paint(QPainter *,QStyleOptionGraphicsItem*,QWidget*);
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget) override;
    QPixmap m_pix;

signals:
    void clicked();         //点击信号
};

#endif // STARTBTNITEM_H
