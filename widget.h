#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QPushButton;
class GameWgt;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    bool eventFilter(QObject *watched, QEvent *event)override;

private:
    void initControl();

    //创建按钮,参数x表示向x轴移动的距离,y表示向y轴移动的距离
    //按钮参数传递指针引用,如果单纯传递指针就是深拷贝,实参仍旧为空
    void createBtn(QPushButton*&btn,const char*png,int x,int y);

    //鼠标悬停或离开时改变按钮图标
    void changeBtnIcon(QPushButton*&btn,const char*pngNormal,
                       const char*pngEnter, QEvent*event);

private slots:
    void btnClickSlot();

private:
    QPushButton*startBtn=nullptr;//开始
    QPushButton*operateBtn=nullptr;//操作
    QPushButton*recordBtn=nullptr;//最高纪录
    QPushButton*methodBtn=nullptr;//玩法
    GameWgt*gameWgt=nullptr;//游戏主界面
};
#endif // WIDGET_H
