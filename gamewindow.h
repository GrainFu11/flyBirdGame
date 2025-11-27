#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include "gamescene.h"
#include "birditem.h"
#include "roaditem.h"
#include <QMediaPlayer>
QT_BEGIN_NAMESPACE
namespace Ui {
class GameWindow;
}
QT_END_NAMESPACE

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private:
    Ui::GameWindow *ui;
    GameScene* m_scene;                 //游戏场景
    BirdItem *m_birdItem;               //鸟
    bool m_startGame;                   //游戏开始标志
    QTimer* m_checkGameStatusTimer;     //检测游戏状态
    QMediaPlayer *m_welcomPlayer;

    void initControl();
    void initBackGroundMusic();
    void loadStyleSheet(const QString& sheetName);
    void startWelcom();
    void GameOver();
    void keyPressEvent(QKeyEvent* event);
    // void paintEvent(QPaintEvent* event)override;
private slots:
    void onCheckGameOver();
};
#endif // GAMEWINDOW_H
