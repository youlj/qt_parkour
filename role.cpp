#include "role.h"

Role::Role():x{roleX},y{roleY},width{roleWidth},height{roleHeight}
{
    for(int i=0;i<runImgCount;++i)
    {
        run_img[i].load(QString(runImg).arg(i+1));
    }
    jump_img.load(jumpImg);
    runImg_timer.setInterval(runInterval);
    QObject::connect(&runImg_timer,&QTimer::timeout,[this]()
    {
        currentRunImg=(currentRunImg+1)%runImgCount;
    });
    hp_timer.setInterval(hpInterval);
    QObject::connect(&hp_timer,&QTimer::timeout,[this]()
    {
        if(hp<hpMax)
        {
            hp+=hpAdd;//缓慢加血
        }
    });
    jump_timer.setInterval(jumpOffset);
    jump_timer.setSingleShot(true);//触发一次
}

QPixmap Role::getImg()
{
    QPixmap img;
    if(y<roleMaxY)//跳跃
    {
        img=jump_img;
    }
    else
    {
        img=run_img[currentRunImg];
    }
    return img;
}

void Role::move(bool up, bool down, bool left, bool right)
{
    //首先说明一点,坐标是从左上角出发的

    if(y==roleMaxY)//在地上
    {
        canJumpTwice=true;//可以两段跳
        fall_speed=0;
    }
    if(up)//向上跳
    {
        if(y==roleMaxY)
        {
            jump_timer.start();
            jump_once=false;
        }

        //在空中,一段跳结束,可以进行两段跳
        if(y<roleMaxY&&jump_once&&canJumpTwice)
        {
            jump_timer.start();
            fall_speed=0;
            canJumpTwice=false;
        }

        if(jump_timer.isActive())
        {
            y-=jump_speed*jump_timer.remainingTime()/jumpOffset;
        }
    }
    else
    {
        jump_timer.stop();
        jump_once=true;
    }

    //自由下落
    y+=fall_speed;

    //确保人物在画面内
    if(y<roleMinY)
    {
        y=roleMinY;
    }
    if(y>roleMaxY)
    {
        y=roleMaxY;
    }
    if(x<roleMinX)
    {
        x=roleMinX;
    }
    if(x>roleMaxX)
    {
        x=roleMaxX;
    }

    //不再向上跳,开始下落
    if(!jump_timer.isActive())
    {
        fall_speed+=fallAcc;
    }
    else
    {
        fall_speed=0;
    }

    //加速下落
    if(down)
    {
        //角色在空中且没有往上跳
        if(y<roleMaxY&&!jump_timer.isActive())
        {
            fall_speed+=accOffset*fallAcc;
        }
    }

    //向左移动
    if(left)
    {
        x-=speedUp;
    }
    else
    {
        x-=speedDown;//缓慢归位
    }

    if(right)
    {
        x+=speedUp;
    }
    else
    {
        x-=speedDown;
    }

    ++score;//加分,这个是根据定时器触发的时间来计算的
}
