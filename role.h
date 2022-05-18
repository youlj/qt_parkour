#ifndef ROLE_H
#define ROLE_H

#include"common_defs.h"

#include<QPixmap>
#include<QTimer>

class Role
{
public:
    Role();
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
    inline int getScore()
    {
        return score;
    }
    inline void setScore(int value)
    {
        score+=value;
        if(score<=0)
        {
            score=0;
        }
    }
    inline void pauseRole()
    {
        runImg_timer.stop();
    }
    inline void continueRole()
    {
        runImg_timer.start();
    }
    inline void increaseHp()//加血
    {
        hp+=hpOffset;
        if(hp>hpMax)
        {
            hp=hpMax;
        }
    }
    inline void decreaseHp()
    {
        hp-=hpOffset;
        if(hp<0)
        {
            hp=0;
        }
    }
    inline int getHp()
    {
        return hp;
    }
    inline int getHpPercent()//血条百分比
    {
        return hp*percentVal/hpMax;
    }
    inline void dashMove()//向前位移
    {
        x+=dashOffset;
    }
    QPixmap getImg();
    void move(bool up,bool down,bool left,bool right);

public:
    QTimer runImg_timer;//用于奔跑时切换角色图片,造成角色在奔跑的假象
    QTimer hp_timer;//缓慢加血

private:
    QPixmap run_img[runImgCount];//奔跑图片
    QPixmap jump_img;
    int currentRunImg=0;//当前奔跑图片
    int x,y,width,height;//角色x、y坐标及宽高
    int hp=hp_;//血量
    int hpMax=hpMax_;
    int score=0;//得分
    double fall_speed=0;//下落速度
    double fall_acc=fallAcc;//下落加速度
    double jump_speed=jumpSpeed;//上升速度
    int jump_height=jumpHeight;//一次跳跃高度
    bool jump_once;//已经跳了一次
    bool jump_twice;//跳了两次
    bool isFall;//是否在下落
    bool canJumpTwice;//可以两次跳
    QTimer jump_timer;//辅助向上跳相关逻辑
};

#endif // ROLE_H
