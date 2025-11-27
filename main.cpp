#include "gamewindow.h"

#include <QApplication>
#include <QTime>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    //设置时间为随机种子
    srand(QTime(0,0,0).secsTo(QTime::currentTime()));
    w.show();
    return a.exec();
}
