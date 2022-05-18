#include "widget.h"
#include"game_wgt.h"

#include<QIcon>
#include<QSound>
#include<QPushButton>
#include<QMouseEvent>
#include<QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    initControl();
}

Widget::~Widget()
{
}

void Widget::initControl()
{
    setFixedSize(win_size_width,win_size_height);
    setWindowIcon(QIcon(win_icon));
    setWindowTitle("天天跑酷");
    QSound*startSound=new QSound(bg_sound,this);
    startSound->play();
    startSound->setLoops(QSound::Infinite);//无限循环
    gameWgt=new GameWgt(this,width(),height());

    createBtn(startBtn,startBtnNormal,startBtnX,startBtnY);
    createBtn(operateBtn,operateBtnNormal,operateBtnX,operateBtnY);
    createBtn(methodBtn,methodBtnNormal,methodBtnX,methodBtnY);
    createBtn(recordBtn,recordBtnNormal,recordBtnX,recordBtnY);
}

void Widget::createBtn(QPushButton *&btn, const char *png, int x, int y)
{
    btn=new QPushButton(this);
    btn->setStyleSheet("QPushButton{border:0px;}");
    btn->move(x,y);
    QPixmap pix(png);
    btn->setFixedSize(pix.size());
    btn->setIcon(pix);
    btn->setIconSize(pix.size());
    btn->installEventFilter(this);//注册事件过滤器,以便鼠标悬停或离开时切换图片
    connect(btn,&QPushButton::clicked,this,&Widget::btnClickSlot);
}

void Widget::changeBtnIcon(QPushButton *&btn, const char *pngNormal,
                           const char*pngEnter, QEvent *event)
{
    if(event->type()==QEvent::Enter)//鼠标进入
    {
        QPixmap pix(pngEnter);
        btn->setFixedSize(pix.size());
        btn->setIcon(pix);
        btn->setIconSize(pix.size());
        btn->move(btn->x()-btnOffset,btn->y()-btnOffset);
    }
    else if(event->type()==QEvent::Leave)//鼠标离开
    {
        QPixmap pix(pngNormal);
        btn->setFixedSize(pix.size());
        btn->setIcon(pix);
        btn->setIconSize(pix.size());
        btn->move(btn->x()+btnOffset,btn->y()+btnOffset);
    }
}

void Widget::btnClickSlot()
{
    QPushButton*btn=qobject_cast<QPushButton*>(sender());
    if(btn==startBtn)
    {
        gameWgt->setRun(true);
        gameWgt->startBtn=startBtn;
        gameWgt->operateBtn=operateBtn;
        gameWgt->recordBtn=recordBtn;
        gameWgt->methodBtn=methodBtn;
        gameWgt->startGame();
        startBtn->hide();
        operateBtn->hide();
        recordBtn->hide();
        methodBtn->hide();
    }
    else if(btn==operateBtn)
    {
        QMessageBox::about(this,"按键操作","按 键 操 作 :\n"
                                        "1.按下W键控制火柴人向上跳跃，在空中可进行二次跳跃。\n"
                                        "2.按下S键控制火柴人加速下落。\n"
                                        "3.按下A键控制火柴人向左加速移动。\n"
                                        "4.按下D键控制火柴人向右加速。\n"
                                        "5.按下Q键控制火柴人向右闪现。\n"
                                        "6.吃到绿色爱心后即可按空格键进行攻击。\n"
                                        "7.游戏中按下esc键暂停游戏，再次按下esc键继续游戏。\n"
                                        "8.游戏结束后按下R键重新开始游戏，按下B键返回游戏主菜单。");
    }
    else if(btn==methodBtn)
    {
        QMessageBox::about(this,"玩法说明","游 戏 玩 法 :\n"
                                        "1.点击开始以进入游戏。\n"
                                        "2.游戏以控制火柴人避开障碍物，吃到尽可能多的金币为主要目标。\n"
                                        "3.控制火柴人跑得越远得分越高，吃到金币会有加分并增加金币数，碰到障碍物会有扣分。\n"
                                        "4.吃到红心会加速回血。\n"
                                        "5.不碰到障碍物人物会自动缓慢回血，血条为空时死亡，游戏结束。\n"
                                        "6.游戏会自动记录你的最高记录，试着打破它！");
    }
    else if(btn==recordBtn)
    {
        QMessageBox::about(this,"历史记录",QString("历史最高分:%1").arg(gameWgt->getMaxScore()));
    }
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==startBtn)
    {
        changeBtnIcon(startBtn,startBtnNormal,startBtnEnter,event);
    }
    else if(watched==operateBtn)
    {
        changeBtnIcon(operateBtn,operateBtnNormal,operateBtnEnter,event);
    }
    else if(watched==methodBtn)
    {
        changeBtnIcon(methodBtn,methodBtnNormal,methodBtnEnter,event);
    }
    else if(watched==recordBtn)
    {
        changeBtnIcon(recordBtn,recordBtnNormal,recordBtnEnter,event);
    }

    return QWidget::eventFilter(watched,event);
}

