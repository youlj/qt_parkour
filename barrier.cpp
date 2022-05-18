#include "barrier.h"

#include<QTime>

Barrier::Barrier(int x, int y, int width, int height)
    :x{x},y{y},width{width},height{height}
{

}

Barrier::~Barrier()
{

}

Wall::Wall(int x, int y, int width, int height)
    :Barrier{x,y,width,height}
{
    qsrand(QTime::currentTime().msec());//设置随机种子
    this->img.load(QString(wallImg).arg(qrand()%2+1));//随机加载wall1.png或者wall2.png
}

Attack::Attack(int x, int y, int width, int height)
    :Barrier{x,y,width,height}
{
    img.load(attckImg);
}

GreenBlood::GreenBlood(int x, int y, int width, int height)
    :Barrier{x,y,width,height}
{
    img.load(greenBloodBg);
}

Coin::Coin(int x, int y, int width, int height)
    :Barrier{x,y,width,height}
{
    for(int i=0;i<coinNumber;++i)
    {
        img[i].load(QString(coinImg).arg(i+1));
    }

    coinTimer.setInterval(coinInterval);
    QObject::connect(&coinTimer,&QTimer::timeout,[this]()
    {
        currentCoin=(currentCoin+1)%coinNumber;
    });
    coinTimer.start();
}

Arrow::Arrow(int x, int y, int width, int height)
    :Barrier{x,y,width,height}
{
    img.load(arrowImg);
}

Blood::Blood(int x, int y, int width, int height)
    :Barrier{x,y,width,height}
{
    img.load(bloodBg);
}
