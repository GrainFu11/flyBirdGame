#include "gamewindow.h"
#include "./ui_gamewindow.h"
#include <QFile>
#include <QRectF>
#include <QGraphicsView>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QPaintEvent>
#include <QStyleOption>
#include "startbtnitem.h"
#include <QGraphicsObject>
#include "pipeitem.h"
#include <QAudioOutput>
GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWindow),m_startGame(false)
{
    ui->setupUi(this);
    this->setObjectName("GameWindow");
    this->setWindowTitle("飞行小鸟");
    setAttribute(Qt::WA_StyledBackground, true);
    initBackGroundMusic();
    initControl();

}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::initControl()
{
    loadStyleSheet("GameWindow");
    QRectF gameRect=rect();
    m_scene=new GameScene(this,gameRect);
    //初始化游戏视图
    QGraphicsView* view=new QGraphicsView(m_scene,this);
    // view->setScene(m_scene);
    view->setStyleSheet("border:none;background:transparent;");
    view->setCacheMode(QGraphicsView::CacheBackground);//设置缓存背景模式
    startWelcom();

}

void GameWindow::initBackGroundMusic()
{
    m_welcomPlayer=new QMediaPlayer(this);
    QAudioOutput *audioOutput=new QAudioOutput(this);
    m_welcomPlayer->setSource(QUrl("qrc:/BirdGame/Resources/sound/welcome.mp3"));
    m_welcomPlayer->setLoops(QMediaPlayer::Infinite);
    m_welcomPlayer->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.7);
    m_welcomPlayer->play();
}

void GameWindow::loadStyleSheet(const QString &sheetName)
{
    QFile file(QString(":/BirdGame/Resources/qss/%1.css").arg(sheetName));
    if(file.open(QFile::ReadOnly)){
        // QString sheetCss=file.readAll();
        // this->setStyleSheet(sheetCss);
        QString strStyleSheet=this->styleSheet();
        strStyleSheet=file.readAll();
        this->setStyleSheet(strStyleSheet);
        file.close();
    }



}

void GameWindow::startWelcom()
{

    //道路
    RoadItem *roadItem=new RoadItem(m_scene);
    //管道
    PipeItem* pipeItem=new PipeItem(m_scene);
    //鸟
    m_birdItem=new BirdItem(m_scene);

    //游戏状态检测
    m_checkGameStatusTimer=new QTimer(this);
    connect(m_checkGameStatusTimer,&QTimer::timeout,this,&GameWindow::onCheckGameOver);

    //字母
    // static int nLetters=7;
    struct titleData{
        const char *word;
        qreal initx,inity;
        qreal endx,endy;
    };
    titleData data[]={
        {"飞",-400,-1000,150,100},
        {"吧",-200,-1000,200,100},
        {",",0,-1000,250,100},
        {"笨",200,-1000,300,100},
        {"笨",400,-1000,350,100},
        {"鸟",600,-1000,400,100},
        {"!",800,-1000,450,100}
    };

    QSequentialAnimationGroup* wordGroup=new QSequentialAnimationGroup(this);
    QParallelAnimationGroup* fadeWordGroup=new QParallelAnimationGroup(this);
    for(int i=0;i<sizeof(data)/sizeof(data[0]);i++){
        QString text=data[i].word;
        QGraphicsTextItem *word=new QGraphicsTextItem(text);
        QFont font("Microsoft YaHei", 30, QFont::Bold);
        font.setStyleStrategy(QFont::PreferAntialias);
        word->setFont(font);
        word->setDefaultTextColor(QColor("Red"));
        word->setPos(QPoint(data[i].initx,data[i].inity));
        //文本属性
        QPropertyAnimation *moveAni=new QPropertyAnimation(word,"pos",wordGroup);
        moveAni->setEndValue(QPoint(data[i].endx,data[i].endy));
        moveAni->setDuration(200);
        moveAni->setEasingCurve(QEasingCurve::OutCurve);
        wordGroup->addAnimation(moveAni);
        wordGroup->addPause(50);
        //渐渐消失
        QPropertyAnimation *fade=new QPropertyAnimation(word,"opacity",fadeWordGroup);
        fade->setDuration(1000);
        fade->setStartValue(1.0);
        fade->setEndValue(0);
        fade->setEasingCurve(QEasingCurve::OutBack);
        fadeWordGroup->addAnimation(fade);

        m_scene->addItem(word);
    }
    wordGroup->start(QAbstractAnimation::DeleteWhenStopped);

    QPixmap pix;
    pix.load(":/BirdGame/Resources/image/startButton.png");
    StartBtnItem *btnItem=new StartBtnItem(pix,m_scene);
    btnItem->setPos(QPointF(235,300));
    QPropertyAnimation *btnAnimation=new QPropertyAnimation(btnItem,"opacity",fadeWordGroup);
    btnAnimation->setDuration(1000);
    btnAnimation->setStartValue(1.0);
    btnAnimation->setEndValue(0);
    btnAnimation->setEasingCurve(QEasingCurve::OutBack);
    fadeWordGroup->addAnimation(btnAnimation);
    connect(btnItem,&StartBtnItem::clicked,this,[=](){
        fadeWordGroup->start(QAbstractAnimation::DeleteWhenStopped);
        m_startGame=true;
        m_checkGameStatusTimer->start(10);
        m_birdItem->flyDownAnimation();
        m_welcomPlayer->stop();
    });


}

void GameWindow::GameOver()
{
    // m_birdItem->clearFocus();
    struct titleData{
        const char *word;
        qreal initx,inity;
        qreal endx,endy;
    };
    titleData data[]={
        {"输",-400,-1000,150,100},
        {"啦",-200,-1000,200,100},
        {",",0,-1000,250,100},
        {"笨",200,-1000,300,100},
        {"笨",400,-1000,350,100},
        {"鸟",600,-1000,400,100},
        {"!",800,-1000,450,100}
    };
    QSequentialAnimationGroup* wordGroup=new QSequentialAnimationGroup(this);
    QParallelAnimationGroup* fadeWordGroup=new QParallelAnimationGroup(this);
    for(int i=0;i<sizeof(data)/sizeof(data[0]);i++){
        QString text=data[i].word;
        QGraphicsTextItem *word=new QGraphicsTextItem(text);
        QFont font("Microsoft YaHei", 30, QFont::Bold);
        font.setStyleStrategy(QFont::PreferAntialias);
        word->setFont(font);
        word->setDefaultTextColor(QColor("Red"));
        word->setPos(QPoint(data[i].initx,data[i].inity));
        //文本属性
        QPropertyAnimation *moveAni=new QPropertyAnimation(word,"pos",wordGroup);
        moveAni->setEndValue(QPoint(data[i].endx,data[i].endy));
        moveAni->setDuration(200);
        moveAni->setEasingCurve(QEasingCurve::OutCurve);
        wordGroup->addAnimation(moveAni);
        wordGroup->addPause(50);
        //渐渐消失
        QPropertyAnimation *fade=new QPropertyAnimation(word,"opacity",fadeWordGroup);
        fade->setDuration(1000);
        fade->setStartValue(1.0);
        fade->setEndValue(0);
        fade->setEasingCurve(QEasingCurve::OutBack);
        fadeWordGroup->addAnimation(fade);

        m_scene->addItem(word);
    }
    wordGroup->start(QAbstractAnimation::DeleteWhenStopped);
    m_scene->removeItem(m_birdItem);
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    if(m_startGame)m_birdItem->keyPressEvent(event);
}

void GameWindow::onCheckGameOver()
{
    if(m_birdItem->checkIsCollided()){
        GameOver();
        // m_startGame=false;
    }
}
