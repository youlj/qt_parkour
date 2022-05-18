#ifndef GAMEWGT_H
#define GAMEWGT_H

#include"barrier.h"

#include <QWidget>
#include<vector>
#include<QPixmap>
#include<QTimer>

class Role;
class QPushButton;

class GameWgt : public QWidget
{
    Q_OBJECT
public:
    explicit GameWgt(QWidget *parent = nullptr,
                     int width=win_size_width,int height=win_size_height);
    ~GameWgt();
    void startGame();
    inline void setRun(bool flag)
    {
        isRunning=flag;
    }
    inline int getMaxScore()
    {
        return scoreMax;
    }

private:
    void addBarrier();//添加障碍物
    void gameOver();
    void back();//返回主菜单
    inline void attck();

protected:
    //重写绘图、键盘相关事件
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

public:
    QPushButton* startBtn=nullptr;
    QPushButton* operateBtn=nullptr;
    QPushButton* recordBtn=nullptr;
    QPushButton* methodBtn=nullptr;

private:
    std::vector<Wall*>wallVec;//管理墙体障碍物
    std::vector<Attack*>attckVec;//管理角色攻击时扔出的物体
    std::vector<GreenBlood*>greenBloodVec;//绿色的爱心,吃下它即可进行攻击
    std::vector<Coin*>coinVec;
    std::vector<Arrow*>arrowVec;
    std::vector<Blood*>bloodVec;
    Role*role=nullptr;//主人公
    QPixmap startImg;//开始前背景
    QPixmap gameBg[gameBgCount];//游戏背景
    QPixmap groundImg;//地面
    QPixmap pauseImg;//暂停时的图片
    QPixmap hurtImg;
    QPixmap gameOverImg;
    int hurtAlpha=0;
    int groundX=0;//地面x坐标
    int groundY;//地面y坐标
    int groundSpeed=groundSpeed_;//地面移动速度
    int coinCount=0;//金币数量
    int score=0;//得分
    int scoreMax=0;//最高得分纪录
    int difficulty=0;//困难度
    int gameBgX[gameBgCount]={0};//游戏背景x坐标
    int gameBgSpeed=gameBgSpeed_;//游戏背景移动速度
    bool isRunning=false;//是否在游戏中
    bool isPaused=false;//是否暂停游戏
    bool isGameOver=false;
    bool isBack=true;//是否返回主菜单
    bool up=false;//按下向上键(w键)
    bool down=false;//s键
    bool left=false;//a键
    bool right=false;//d键
    QTimer beginTimer;//开始游戏
    QTimer attckTimer;//可以进行攻击的时限
};

#endif // GAMEWGT_H
