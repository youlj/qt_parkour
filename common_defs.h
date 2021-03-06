#ifndef COMMON_DEFS_H
#define COMMON_DEFS_H

//没有用宏,因为宏不便于调试
static const int win_size_width=1280;//窗体宽度
static const int win_size_height=720;
static const int startBtnX=900;//开始按钮x坐标
static const int startBtnY=400;
static const int operateBtnX=500;//操作按钮x坐标
static const int operateBtnY=425;
static const int methodBtnX=700;//玩法按钮x坐标
static const int methodBtnY=425;
static const int recordBtnX=300;//最高纪录按钮x坐标
static const int recordBtnY=425;
static const int btnOffset=50;
static const int moveOffset=5;
static const int runImgCount=5;
static const int hp_=3000;//血量值
static const int hpMax_=3000;
static const int hpOffset=500;
static const int hpAdd=1;
static const int roleX=100;//角色x坐标
static const int roleY=150;
static const int roleWidth=30;//角色宽度
static const int roleHeight=40;
static const int jumpHeight=100;//跳跃高度
static const float jumpSpeed=30.0;
static const float fallAcc=0.9;//下落加速度
static const int accOffset=2;
static const int runInterval=100;
static const int hpInterval=20;
static const int roleMaxY=610;//角色刚好触地的y坐标
static const int roleMinY=150;
static const int roleMinX=100;
static const int roleMaxX=1100;
static const int dashOffset=400;//位移
static const int jumpOffset=400;
static const int speedUp=20;//加速
static const int speedDown=1;//减速
static const int gameBgCount=2;//游戏背景图张数
static const int groundHeight=70;
static const int groundSpeed_=1;//地面移动速度
static const int beginInterval=20;
static const int difficultyMax=100;
static const float difficultyOffset=0.0015;
static const int scoreOffset=10;
static const int hurtAlphaVal=255;
static const int hurtOffset=3;
static const int wallWidth=70;//墙体障碍物宽度
static const float wallHeightAffct=0.2;
static const int wallShowMin=100;
static const int wallDifficulty=150;
static const int overX=240;//游戏结束图片x坐标
static const int overY=60;
static const int overWidth=800;//游戏结束图片宽度
static const int overHeight=600;
static const int bloodX=1000;//血条绘制x坐标
static const int bloodY=50;
static const int bloodWidth=150;//血条宽度
static const int bloodHeight=10;
static const int bloodLineOffset=50;
static const int bloodDifficulty=300;
static const int bloodShowMin=200;
static const int percentVal=100;
static const int attckSpeed=20;//角色攻击速度
static const int attckInterval=10000;//攻击持续10秒
static const int attckWidth=15;//角色扔出的攻击物宽度
static const int attckHeight=15;
static const int greenBloodDifficulty=500;
static const int greenBloodShowMin=200;
static const int bloodSize=40;
static const int wallBlood=100;//墙体障碍物血条值
static const int wallBloodDec=50;
static const int coinNumber=4;
static const int coinSize=16;//金币大小
static const int coinInterval=100;
static const int coinDifficulty=30;
static const int coinShowMin=30;
static const int coinRandom=300;
static const int arrowMoveSpeed=10;
static const int arrowDifficulty=100;
static const int arrowShowMin=100;
static const int arrowRandom=300;
static const int arrowWidth=110;//箭头障碍物宽度
static const int arrowHeight=20;
static const int pauseImgWidth=500;//暂停游戏图片宽度
static const int pauseImgHeight=300;
static const int coinTxtX=100;//绘制金币数量x坐标
static const int coinTxtY=100;
static const int scoreTxtX=500;//绘制分数x坐标
static const int scoreTxtY=100;
static const int gameBgSpeed_=1;//游戏背景图移动速度
static const int fontSize=13;
static const char* win_icon=":/image/title.png";
static const char* bg_sound=":/sound/Theme.wav";
static const char* startBtnNormal=":/image/startBtn1.png";
static const char* startBtnEnter=":/image/startBtn2.png";
static const char* methodBtnNormal=":/image/instruction1.png";
static const char* methodBtnEnter=":/image/instruction2.png";
static const char* operateBtnNormal=":/image/keyboard1.png";
static const char* operateBtnEnter=":/image/keyboard2.png";
static const char* recordBtnNormal=":/image/archive1.png";
static const char* recordBtnEnter=":/image/archive2.png";
static const char* bgStart=":/image/background.png";
static const char* wallImg=":/image/wall%1.png";
static const char* runImg=":/image/run_%1.png";
static const char* jumpImg=":/image/jump.png";
static const char* startBg=":/image/background.png";
static const char* groundBg=":/image/ground.png";
static const char* hurtBg=":/image/hurt.png";
static const char* overBg=":/image/gameover.jpg";
static const char* pauseBg=":/image/pause.jpg";
static const char* bloodBg=":/image/blood.png";
static const char* greenBloodBg=":/image/greenBlood.png";
static const char* attckImg=":/image/circle.png";
static const char* arrowImg=":/image/arrow.png";
static const char* coinImg=":/image/coin_00%1.png";
static const char* gameImg=":/image/gameBg%1.png";
static const char* jumpMusic=":/sound/jump.wav";
static const char* coinMusic=":/sound/coin.wav";
static const char* overMusic=":/sound/over.wav";
static const char* collideMusic=":/sound/collision.wav";
static const char* recordFile="record.txt";

#endif // COMMON_DEFS_H
