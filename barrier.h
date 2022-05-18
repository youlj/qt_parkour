#ifndef BARRIER_H
#define BARRIER_H

#include"common_defs.h"

#include<QPixmap>
#include<QTimer>

//障碍物抽象基类
class Barrier
{
public:
    explicit Barrier(int x,int y,int width,int height);
    virtual ~Barrier();
    inline void setX(int x)
    {
        this->x=x;
    }
    inline void setY(int y)
    {
        this->y=y;
    }
    inline int getX()
    {
        return x;
    }
    inline int getY()
    {
        return y;
    }
    inline int getWidth()
    {
        return width;
    }
    inline int getHeight()
    {
        return height;
    }
    virtual bool isCollide(int x,int y,int width,int height)////碰撞检测
    {
        QRect rect1(getX(),getY(),getWidth(),getHeight());
        QRect rect2(x,y,width,height);
        return rect1.intersects(rect2);
    }

    virtual QPixmap getImg()=0;
    virtual void move()=0;//障碍物移动
    virtual bool over()=0;//障碍物移动是否离开窗口

private:
    //每个障碍物自身都有一个矩形区域,x、y坐标,宽高
    int x,y,width,height;
};

//墙
class Wall:public Barrier
{
public:
    Wall(int x,int y,int width,int height);
    inline QPixmap getImg() override
    {
        return img;
    }
    inline void move() override
    {
        setX(getX()-moveOffset);//向左移动
    }
    inline bool over() override
    {
        //物体x坐标加上它的宽度如果<=0则意味着离开窗体了
        return getX()+getWidth()<=0;
    }

public:
    int blood=wallBlood;//血条

private:
    QPixmap img;
};

//角色攻击时放出的物体
class Attack:public Barrier
{
public:
    Attack(int x,int y,int width,int height);
    inline QPixmap getImg() override
    {
        return img;
    }
    inline void move() override
    {
        setX(getX()+attckSpeed);//向右移动
    }
    inline bool over() override
    {
        return getX()>=win_size_width;
    }

private:
    QPixmap img;
};

//角色碰撞后就可以按住空格键进行攻击了
class GreenBlood:public Barrier
{
public:
    GreenBlood(int x,int y,int width,int height);
    inline QPixmap getImg() override
    {
        return img;
    }
    inline void move() override
    {
        setX(getX()-moveOffset);//向左移动
    }
    inline bool over() override
    {
        return getX()+getWidth()<=0;
    }

private:
    QPixmap img;
};

//金币
class Coin:public Barrier
{
public:
    Coin(int x,int y,int width,int height);
    inline void move() override
    {
        setX(getX()-moveOffset);
    }
    inline bool over() override
    {
        return getX()+getWidth()<=0;
    }
    inline QPixmap getImg() override
    {
        return img[currentCoin];
    }

public:
    QTimer coinTimer;//切换图片,产生一种金币在旋转的假象

private:
    QPixmap img[coinNumber];
    int currentCoin=0;
};

//箭
class Arrow:public Barrier
{
public:
    Arrow(int x,int y,int width,int height);
    inline void move() override
    {
        setX(getX()-arrowMoveSpeed);
    }
    inline bool over() override
    {
        return getX()+getWidth()<=0;
    }
    inline QPixmap getImg() override
    {
        return img;
    }

private:
    QPixmap img;
};

//血瓶,可加血
class Blood:public Barrier
{
public:
    Blood(int x,int y,int width,int height);
    inline QPixmap getImg() override
    {
        return img;
    }
    inline void move() override
    {
        setX(getX()-moveOffset);
    }
    inline bool over() override
    {
        return getX()+getWidth()<=0;
    }

private:
    QPixmap img;
};

#endif // BARRIER_H
