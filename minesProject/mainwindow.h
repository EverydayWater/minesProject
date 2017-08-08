#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar> //菜单栏
#include <QMenu> //菜单
#include <QAction> //行为
#include <QLCDNumber> //液晶显示数字
#include <QPalette>  //调色板
#include <QPushButton> //按钮button
#include <QStatusBar> //状态栏
#include <QHBoxLayout> //水平布局
#include <QVBoxLayout> //垂直布局
#include <QWidget> //小部件
#include <QMessageBox> //消息盒子
#include <QGraphicsView> //画板的实现 视图 舞台
#include <QGraphicsScene> //图形的场景 场景 镜头
#include <QPixmap> //图像 创建图片
#include <QTime>             //时间
#include <QTimer>            //计时器

#include "myitem.h"
#include "mydialog.h"
#include "infoDialog.h"
#include "connectwidget.h"

#include <vector> //向量
#include <stdlib.h>
#include <time.h>
#include <QPoint>
#include <QSound>
#include <QDebug>

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //递归扩散
    void spreadNull(const int & t_minesX, const int & t_minesY);
    //左键提示
    void leftButtonTip(const int & t_leftX,const int & t_leftY);
    void leftButtonReleaseTip(const int & t_leftX,const int & t_leftY);

    //是否成功完成游戏
    bool isWinGame();

    //时间延时
    void delaySoundTime(const int & t_time);

    //显示窗口
    void showEvent(QShowEvent *);
    //隐藏窗口
    void hideEvent(QHideEvent *);

public slots:

    //游戏失败
    void receiveGameOverInfo();
    //赢得游戏
    void receiveGameWinInfo();

    //标记去除 雷加一
    void receiveAddFlagNum();
    //加上标记 雷减一
    void receiveReduceFlagNum();
    //扫雷简介
    void gameProfile();

    //开始游戏--计时器开始计时
    void receiveStartInfo();
    //游戏计时
    void gameTime();

    //初级
    void primaryFun();
    //中级
    void middleFun();
    //高级
    void highFun();
    //自定义的界面大小以及雷数
    void receiveInfo(const QString &t_lin,
                     const QString &t_col,
                     const QString &t_num);

    //重新开始本局游戏
    void restartGame();
    //笑脸按钮新建游戏
    void smileButtonGame();

private:
    //创建游戏基本页面、布局
    void createGame();
    //布雷
    void setMines();
    //设置雷周围的数字
    void setAroundMinesNum(const int & t_minesX,const int & t_minesY);
    //创建各种链接函数
    void createConnectFun();

    //重新添加图片
    void addGriphics();

    //新建游戏
    void restartGameFun();

private:
    //游戏、帮助菜单
    QMenu * m_gameMenu;
    QMenu * m_helpMenu;
    QMenu * m_optionMenu;

    QAction * m_newAction;
    QAction * m_operAction;
    QAction * m_infoAction;
    QAction * m_exitAction;

    QAction *m_primaryAction; //初级
    QAction *m_middleAction; //中级
    QAction *m_highAction; //高级

    QAction * m_aboutAction;
    QAction * m_aboutQtAction;
    QStatusBar *m_statusBar; //状态栏

    QWidget * m_widget;

    QLabel * m_minePicture;
    QLabel * m_timePicture;
    QLCDNumber * m_minesLCD;
    QPushButton * m_smileButton;
    QLCDNumber * m_timeLCD;

    QTimer *m_timer;

    QHBoxLayout * m_hBoxLayout;

    QGraphicsView * m_view;
    QGraphicsScene * m_scene;
    QVBoxLayout * m_layout;

    //自定义对话框
    myDialog *m_dialog;
    //ui设计统计信息画面
    infoDialog *m_infoDialog;
    //显示统计信息
    connectWidget  *m_myWidget;
    myItem *m_myItem;

    //消息盒子
    QMessageBox m_msgBox;
    QPushButton *m_restartButton;
    QPushButton *m_quitButton;


    //图形行、列数，雷的数目
    int m_xCoordinate;
    int m_yCoordinate;

    //雷数
    int m_mineNum;
    //右键标记时 雷数中间变量
    int m_mineNum1;

    //是否隐藏窗口？
    bool m_isHideWindow;

     vector<vector<myItem *> > m_itemVec;
};

#endif // MAINWINDOW_H
