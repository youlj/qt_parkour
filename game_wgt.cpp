#include "game_wgt.h"
#include"role.h"

#include<QFile>
#include<QSound>
#include<QKeyEvent>
#include<QMessageBox>
#include<QPushButton>
#include<QTime>
#include<QPainter>
#include<QDebug>

GameWgt::GameWgt(QWidget *parent,int width,int height) : QWidget(parent),
    groundY{height-groundHeight}
{
    //打开文件记录最高分
    {
        QFile file(recordFile);
        if(file.open(QFile::ReadOnly))
        {
            scoreMax=file.readAll().toInt();
            file.close();
        }
    }

    setFixedSize(width,height);
    startImg.load(startBg);
    groundImg.load(groundBg);
    hurtImg.load(hurtBg);
    pauseImg.load(pauseBg);
    gameOverImg.load(overBg);
    for(int i=0;i<gameBgCount;++i)
    {
        gameBg[i].load(QString(gameImg).arg(i));
    }
    grabKeyboard();//激活键盘事件
    attckTimer.setInterval(attckInterval);
    attckTimer.setSingleShot(true);//开启定时器后执行一次就结束

    beginTimer.setInterval(beginInterval);
    connect(&beginTimer,&QTimer::timeout,[this]()
    {
        role->move(up,down,left,right);

        //随时间提高难度
        if(difficulty<difficultyMax)
        {
            difficulty+=difficultyOffset;
        }
        else
        {
            difficulty=difficultyMax;
        }

        //处理墙体障碍物
        for(auto wallItor=wallVec.begin();wallItor!=wallVec.end();)
        {
            if((*wallItor)->over())
            {
                wallItor=wallVec.erase(wallItor);//执行erase后原先迭代器失效,所以不在for循环那里进行++,需要额外小心
            }
            else
            {
                //碰到障碍物了
                if((*wallItor)->isCollide(role->getX(),role->getY(),role->getWidth(),role->getHeight()))
                {
                    QSound::play(collideMusic);
                    role->decreaseHp();//减血
                    role->setScore(-scoreOffset);//减分
                    hurtAlpha=hurtAlphaVal;
                    wallItor=wallVec.erase(wallItor);
                }
                else
                {
                    (*wallItor)->move();
                    ++wallItor;
                }
            }
        }

        //处理绿色的爱心(角色碰撞后可按空格键攻击)
        for(auto bloodItor=greenBloodVec.begin();bloodItor!=greenBloodVec.end();)
        {
            if((*bloodItor)->over())
            {
                bloodItor=greenBloodVec.erase(bloodItor);
            }
            else
            {
                if((*bloodItor)->isCollide(role->getX(),role->getY(),role->getWidth(),role->getHeight()))
                {
                    QSound::play(collideMusic);
                    bloodItor=greenBloodVec.erase(bloodItor);
                    attckTimer.start();//开启定时器,按下空格键即可进行攻击
                }
                else
                {
                    (*bloodItor)->move();
                    ++bloodItor;
                }
            }
        }

        //处理金币
        for(auto coinItor=coinVec.begin();coinItor!=coinVec.end();)
        {
            if((*coinItor)->over())
            {
                coinItor=coinVec.erase(coinItor);
            }
            else
            {
                if((*coinItor)->isCollide(role->getX(),role->getY(),role->getWidth(),role->getHeight()))
                {
                    QSound::play(collideMusic);
                    coinItor=coinVec.erase(coinItor);
                    ++coinCount;//金币+1
                }
                else
                {
                    (*coinItor)->move();
                    ++coinItor;
                }
            }
        }

        //处理箭头
        for(auto arrowItor=arrowVec.begin();arrowItor!=arrowVec.end();)
        {
            if((*arrowItor)->over())
            {
                arrowItor=arrowVec.erase(arrowItor);
            }
            else
            {
                if((*arrowItor)->isCollide(role->getX(),role->getY(),role->getWidth(),role->getHeight()))
                {
                    QSound::play(collideMusic);
                    role->decreaseHp();
                    role->setScore(-scoreOffset);
                    hurtAlpha=hurtAlphaVal;
                    arrowItor=arrowVec.erase(arrowItor);
                }
                else
                {
                    (*arrowItor)->move();
                    ++arrowItor;
                }
            }
        }

        //处理血瓶
        for(auto bloodItor=bloodVec.begin();bloodItor!=bloodVec.end();)
        {
            if((*bloodItor)->over())
            {
                bloodItor=bloodVec.erase(bloodItor);
            }
            else
            {
                if((*bloodItor)->isCollide(role->getX(),role->getY(),role->getWidth(),role->getHeight()))
                {
                    QSound::play(collideMusic);
                    bloodItor=bloodVec.erase(bloodItor);
                    role->increaseHp();
                }
                else
                {
                    (*bloodItor)->move();
                    ++bloodItor;
                }
            }
        }

        //处理角色攻击
        for(auto attckItor=attckVec.begin();attckItor!=attckVec.end();)
        {
            bool isContinue=false;
            if((*attckItor)->over())
            {
                attckItor=attckVec.erase(attckItor);
            }
            else
            {
                //遍历相关障碍物,进行碰撞检测,但是这种方法效率太低了感觉,有啥好方法么

                for(auto wallItor=wallVec.begin();wallItor!=wallVec.end();)
                {
                    if((*attckItor)->isCollide((*wallItor)->getX(),(*wallItor)->getY(),
                                               (*wallItor)->getWidth(),(*wallItor)->getHeight()))
                    {
                        QSound::play(collideMusic);
                        attckItor=attckVec.erase(attckItor);
                        (*wallItor)->blood-=wallBloodDec;
                        if((*wallItor)->blood<=0)
                        {
                            wallItor=wallVec.erase(wallItor);
                        }
                        isContinue=true;
                        break;
                    }
                    else
                    {
                        ++wallItor;
                    }
                }

                if(isContinue)//角色攻击时发出的物体已消失,所以没必要往下执行了
                {
                    continue;
                }

                for(auto arrowItor=arrowVec.begin();arrowItor!=arrowVec.end();)
                {
                    if((*attckItor)->isCollide((*arrowItor)->getX(),(*arrowItor)->getY(),
                                               (*arrowItor)->getWidth(),(*arrowItor)->getHeight()))
                    {
                        QSound::play(collideMusic);
                        attckItor=attckVec.erase(attckItor);
                        arrowItor=arrowVec.erase(arrowItor);
                        isContinue=true;
                        break;
                    }
                    else
                    {
                        ++arrowItor;
                    }
                }

                if(isContinue)
                {
                    continue;
                }


                (*attckItor)->move();
                ++attckItor;
            }
        }

        if(isRunning)
        {
            if(role->getHp()<=0)
            {
                gameOver();
            }
            addBarrier();//添加障碍物
        }
        update();//关键,刷新绘图事件,调用paintEvent()
    });
}

GameWgt::~GameWgt()
{
    if(role)
    {
        delete role;
        role=nullptr;
    }
}

void GameWgt::startGame()
{
    role=new Role();
    role->hp_timer.start();
    role->runImg_timer.start();
    beginTimer.start();
    isRunning=true;
    isGameOver=false;
    coinCount=0;
    isBack=false;
    update();
}

void GameWgt::addBarrier()
{
    qsrand(QTime::currentTime().msec());

    //添加墙
    static int lastWall=0;
    if(lastWall>wallDifficulty-difficulty)
    {
        //墙y坐标
        int wallY=groundY-wallShowMin-qrand()%static_cast<int>(groundY*wallHeightAffct);

        wallVec.emplace_back(new Wall(width(),wallY,wallWidth,groundY-wallY));
        lastWall=0;
    }
    ++lastWall;

    //添加绿色爱心
    static int lastGreenBlood=0;
    if(lastGreenBlood>greenBloodDifficulty-difficulty)
    {
        greenBloodVec.emplace_back(new GreenBlood(width(),groundY-greenBloodShowMin-qrand()%greenBloodShowMin,
                                                  bloodSize,bloodSize));
        lastGreenBlood=0;
    }
    ++lastGreenBlood;

    //添加金币
    static int lastCoin=0;
    if(lastCoin>coinDifficulty-difficulty)
    {
        coinVec.emplace_back(new Coin(width(),groundY-coinShowMin-qrand()%coinRandom,
                                      coinSize,coinSize));
        lastCoin=0;
    }
    ++lastCoin;

    //添加箭头
    static int lastArrow=0;
    if(lastArrow>arrowDifficulty-difficulty)
    {
        arrowVec.emplace_back(new Arrow(width(),groundY-arrowShowMin-qrand()%arrowRandom,
                                        arrowWidth,arrowHeight));
        lastArrow=0;
    }
    ++lastArrow;

    //添加血瓶
    static int lastBlood=0;
    if(lastBlood>bloodDifficulty-difficulty)
    {
        bloodVec.emplace_back(new Blood(width(),groundY-bloodShowMin-qrand()%bloodShowMin,
                                        bloodSize,bloodSize));
        lastBlood=0;
    }
    ++lastBlood;
}

void GameWgt::gameOver()
{
    QSound::play(overMusic);
    score=role->getScore();
    role->hp_timer.stop();//停止缓慢加血

    //保存分数记录
    if(score>scoreMax)
    {
        scoreMax=score;
        QFile file(recordFile);
        if(file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(QString::number(scoreMax).toStdString().c_str());
            file.close();
        }
    }

    QMessageBox::about(this,"游戏结束",QString("你的得分:%1\n历史最高分:%2").arg(score).arg(scoreMax));

    isRunning=false;
    isGameOver=true;
    beginTimer.stop();
    role->runImg_timer.stop();
    wallVec.clear();
    delete role;
    role=nullptr;
    update();
}

void GameWgt::back()
{
    isBack=true;
    startBtn->show();
    operateBtn->show();
    recordBtn->show();
    methodBtn->show();
    update();
}

void GameWgt::attck()
{
    attckVec.emplace_back(new Attack(role->getX()+role->getWidth(),role->getY()+role->getHeight()/2,
                                     attckWidth,attckHeight));
}

void GameWgt::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);//event参数没用到,消除警告

    QPainter painter(this);
    if(!isRunning&&isBack)//首页
    {
        painter.drawPixmap(0,0,width(),height(),startImg);
    }
    else if(isGameOver)
    {
        painter.drawPixmap(overX,overY,overWidth,overHeight,gameOverImg);
    }
    else//游戏中绘制
    {
        //叠加背景图片并移动
        for(int i=0;i<gameBgCount;++i)
        {
            painter.drawPixmap(QRect(0,0,width(),groundY),gameBg[i],
                               QRect(gameBgX[i],0,width(),groundY));
            if(gameBg[i].width()-gameBgX[i]<width())//要绘制的图片宽度<窗口宽度,这时有空白,需要填补
            {
                painter.drawPixmap(QRect(gameBg[i].width()-gameBgX[i],0,width()-(gameBg[i].width()-gameBgX[i]),groundY),
                                   gameBg[i],QRect(0,0,width()-(gameBg[i].width()-gameBgX[i]),groundY));
            }
            if(isRunning&&!isPaused)
            {
                if((gameBgX[i]+=gameBgSpeed)>=gameBg[i].width())//如果超出图片宽度,从头开始
                {
                    gameBgX[i]-=gameBg[i].width();
                }
            }
        }

        //地面移动
        painter.drawPixmap(QRect(0,groundY,width(),height()-groundY),groundImg
                           ,QRect(groundX,0,width(),height()-groundY));
        if(groundImg.width()-groundX<width())//要绘制的图片宽度<窗口宽度,这时有空白,需要填补
        {
            painter.drawPixmap(QRect(groundImg.width()-groundX,groundY,width()-(groundImg.width()-groundX),height()-groundY)
                               ,groundImg,QRect(0,0,width()-(groundImg.width()-groundX),height()-groundY));
        }
        if(isRunning&&!isPaused)
        {
            if((groundX+=groundSpeed)>=groundImg.width())//如果超出图片宽度,从头开始
            {
                groundX-=groundImg.width();
            }
        }

        //绘制角色
        painter.drawPixmap(role->getX(),role->getY(),role->getWidth(),role->getHeight(),role->getImg());

        //绘制血条、分数、金币数量
        painter.drawRect(QRect(bloodX,bloodY,bloodWidth,bloodHeight));
        painter.fillRect(QRect(bloodX,bloodY,role->getHpPercent()*bloodWidth/percentVal,bloodHeight),Qt::red);
        painter.drawLine(bloodX+bloodLineOffset,bloodY,bloodX+bloodLineOffset,bloodY+bloodHeight);
        painter.drawLine(bloodX+2*bloodLineOffset,bloodY,bloodX+2*bloodLineOffset,bloodY+bloodHeight);
        painter.setFont(QFont("",fontSize));
        painter.drawText(bloodX,2*bloodY,QString("HP: %1%").arg(role->getHpPercent()));
        painter.drawText(coinTxtX,coinTxtY,QString("金币数量: %1").arg(coinCount));
        painter.drawText(scoreTxtX,scoreTxtY,QString("分数: %1").arg(role->getScore()));

        //受伤绘制
        if(hurtAlpha>0)
        {
            QPixmap pix(hurtImg.size());
            pix.fill(Qt::transparent);
            QPainter p(&pix);
            p.setCompositionMode(QPainter::CompositionMode_Source);
            p.drawPixmap(0,0,hurtImg);
            p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
            p.fillRect(pix.rect(),QColor(0,0,0,hurtAlpha));
            painter.drawPixmap(0,0,width(),height(),pix);
            hurtAlpha-=hurtOffset;
        }

        //绘制障碍物
        for(auto& wall:wallVec)
        {
            painter.drawPixmap(QRect(wall->getX(),wall->getY(),wall->getWidth(),wall->getHeight()),wall->getImg());
        }
        for(auto& greenBlood:greenBloodVec)
        {
            painter.drawPixmap(QRect(greenBlood->getX(),greenBlood->getY(),
                                     greenBlood->getWidth(),greenBlood->getWidth()),greenBlood->getImg());
        }
        for(auto& attck:attckVec)
        {
            painter.drawPixmap(QRect(attck->getX(),attck->getY(),attck->getWidth(),attck->getHeight()),attck->getImg());
        }
        for(auto& coin:coinVec)
        {
            painter.drawPixmap(QRect(coin->getX(),coin->getY(),coin->getWidth(),coin->getHeight()),coin->getImg());
        }
        for(auto& arrow:arrowVec)
        {
            painter.drawPixmap(QRect(arrow->getX(),arrow->getY(),arrow->getWidth(),arrow->getHeight()),arrow->getImg());
        }
        for(auto& blood:bloodVec)
        {
            painter.drawPixmap(QRect(blood->getX(),blood->getY(),blood->getWidth(),blood->getHeight()),blood->getImg());
        }

        //居中绘制游戏暂停图片
        if(isPaused&&!isGameOver)
        {
            painter.drawPixmap(width()/2-pauseImgWidth/2,height()/2-pauseImgHeight/2,
                               pauseImgWidth,pauseImgHeight,pauseImg);
        }
    }
}

void GameWgt::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_W:
        {
            if(!isPaused&&!isGameOver)
            {
                up=true;
                QSound::play(jumpMusic);
            }
            break;
        }
        case Qt::Key_S:
        {
            if(!isPaused&&!isGameOver)
            {
                down=true;
            }
            break;
        }
        case Qt::Key_A:
        {
            if(!isPaused&&!isGameOver)
            {
                left=true;
            }
            break;
        }
        case Qt::Key_D:
        {
            if(!isPaused&&!isGameOver)
            {
                right=true;
            }
            break;
        }
        case Qt::Key_Escape:
        {
            if(!isGameOver)
            {
                if(isPaused)
                {
                    isPaused=false;
                    beginTimer.start();
                    role->continueRole();
                    role->hp_timer.start();
                }
                else
                {
                    isPaused=true;
                    beginTimer.stop();
                    role->pauseRole();
                    role->hp_timer.stop();
                    update();//便于绘制游戏暂停图片
                }
            }
            break;
        }
        case Qt::Key_Q:
        {
            if(!isGameOver&&!isPaused)
            {
                role->dashMove();//闪现
            }
            break;
        }
        case Qt::Key_R:
        {
            if(isGameOver)
            {
                startGame();
            }
            break;
        }
        case Qt::Key_B:
        {
            if(isGameOver)
            {
                back();
            }
            break;
        }
        case Qt::Key_Space://按下空格键进行攻击
        {
            if(isRunning&&!isPaused&&attckTimer.isActive())
            {
                attck();
            }
            break;
        }
        default:
        {
            return QWidget::keyPressEvent(event);
        }
    }
}

void GameWgt::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_W:
        {
            up=false;
            break;
        }
        case Qt::Key_S:
        {
            down=false;
            break;
        }
        case Qt::Key_A:
        {
            left=false;
            break;
        }
        case Qt::Key_D:
        {
            right=false;
            break;
        }
        default:
        {
            return QWidget::keyPressEvent(event);
        }
    }
}
