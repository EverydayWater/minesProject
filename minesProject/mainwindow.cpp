#include "mainwindow.h"
#include <QApplication>

//静态全局变量 时间计数
static int t_timeCount = 0;

//MainWindow 构造函数
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),m_xCoordinate(9),
      m_yCoordinate(9),m_mineNum(10),m_mineNum1(10),
      m_isHideWindow(false)
{

    //数据库读信息
    m_myWidget = new connectWidget;
    m_myWidget->addDBConn();

    //创建基本页面、布局
    this->createGame();
    //布雷
    this->setMines();
    //创建各种链接函数
    this->createConnectFun();
}

//MainWindow 析构函数
MainWindow::~MainWindow()
{

}

//创建基本页面、布局
void MainWindow::createGame()
{
    //设置中文名称
    this->setWindowTitle("经典扫雷");

    //创建menu
    m_gameMenu = new QMenu("游戏(&G)",this);
    m_optionMenu = new QMenu("难度(&T)",this);
    m_helpMenu = new QMenu("帮助(&H)",this);

    //创建action
    m_newAction = new QAction("新建(&N)",this);
    m_operAction = new QAction("自定义(&O)",this);
    m_infoAction = new QAction("统计信息(&I)",this);
    m_exitAction = new QAction("退出(&X)",this);

    m_primaryAction = new QAction("初级(&L)",this);
    m_middleAction =new  QAction("中级(&M)",this);
    m_highAction = new QAction("高级(&H)",this);


    m_aboutAction = new QAction("关于扫雷(&A)",this);
    m_aboutQtAction = new QAction("关于QT(&Q)",this);

    //添加menu
    this->menuBar()->addMenu(m_gameMenu);
    this->menuBar()->addMenu(m_optionMenu);
    this->menuBar()->addMenu(m_helpMenu);

    //添加action
    m_gameMenu->addAction(m_newAction);
    m_gameMenu->addAction(m_operAction);
    m_gameMenu->addAction(m_infoAction);
    m_gameMenu->addSeparator();
    m_gameMenu->addAction(m_exitAction);

    m_optionMenu->addAction(m_primaryAction);
    m_optionMenu->addAction(m_middleAction);
    m_optionMenu->addAction(m_highAction);

    m_helpMenu->addAction(m_aboutAction);
    m_helpMenu->addAction(m_aboutQtAction);

    //action设置图标
    //菜单一
    m_newAction->setIcon(QIcon(":/images/new_game.png"));
    m_operAction->setIcon(QIcon(":/images/rank.png"));
    m_infoAction->setIcon(QIcon(":/images/question.jpg"));
    m_exitAction->setIcon(QIcon(":/images/exit.png"));
    //菜单二
    m_primaryAction->setIcon(QIcon(":/images/easy_standard.png"));
    m_middleAction->setIcon(QIcon(":/images/middle_standard.png"));
    m_highAction->setIcon(QIcon(":/images/hard_standard.png"));
    //菜单三
    m_aboutAction->setIcon(QIcon(":/images/game.png"));
    m_aboutQtAction->setIcon(QIcon(":/images/qt.png"));

    //设置action快捷键
    //shortcut 快捷键 Key Sequence 键序列

    m_newAction->setShortcut(QKeySequence("Alt+N"));
    m_operAction->setShortcut(QKeySequence("Alt+O"));
    m_infoAction->setShortcut(QKeySequence("Alt+I"));
    m_exitAction->setShortcut(QKeySequence("Alt+X"));
    m_primaryAction->setShortcut(QKeySequence("Alt+L"));
    m_middleAction->setShortcut(QKeySequence("Alt+M"));
    m_highAction->setShortcut(QKeySequence("Alt+H"));

    //创建statusBar
    m_statusBar = new QStatusBar(this);
    //设置状态栏
    this->setStatusBar(m_statusBar);

    //显示默认字符
    m_statusBar->showMessage("经典就是经典！");
    //设置action在statusBar中的提示信息
    m_newAction->setStatusTip("新建游戏");
    m_operAction->setStatusTip("自定义游戏");
    m_infoAction->setStatusTip("统计信息");
    m_exitAction->setStatusTip("退出游戏");

    m_primaryAction->setStatusTip("初级难度");
    m_middleAction->setStatusTip("中等难度");
    m_highAction->setStatusTip("高级难度");

    m_aboutAction->setStatusTip("关于扫雷");
    m_aboutQtAction->setStatusTip("关于QT");

    //创建widget
    m_widget = new QWidget(this);

    QSize picSize(35,25);
    //创建lcd和笑脸button
    m_minePicture = new QLabel;
    m_minePicture->setPixmap(QPixmap(":/images/game.png").scaled(picSize,Qt::KeepAspectRatio));
    m_timePicture = new QLabel;
    m_timePicture->setPixmap(QPixmap(":/images/clock.png").scaled(picSize,Qt::KeepAspectRatio));

    m_minesLCD = new QLCDNumber;
    m_smileButton = new QPushButton;
    m_smileButton->setIcon(QIcon(":/images/smile.gif"));
    m_timeLCD = new QLCDNumber;

    //创建计时器
    m_timer = new QTimer;
    //设置多久计时
    m_timer->setInterval(1000);

    //创建调色板局部变量
    QPalette t_palette;

    //设置数字颜色
    t_palette.setColor(QPalette::Light,Qt::red);
    m_minesLCD->setPalette(t_palette);
    t_palette.setColor(QPalette::Light,Qt::red);
    m_timeLCD->setPalette(t_palette);
    //设置背景颜色
    m_minesLCD->setStyleSheet("background:black");
    m_timeLCD->setStyleSheet("background:black");

    //笑脸按钮
    m_smileButton->resize(35,25);
    m_smileButton->setIconSize(QSize(35,25));
    m_smileButton->setIcon(QIcon(":/images/smile.gif"));

    //创建水平布局
    m_hBoxLayout = new QHBoxLayout;

    //布局添加组件
    m_hBoxLayout->addWidget(m_minePicture);
    m_hBoxLayout->addWidget(m_minesLCD);
    m_hBoxLayout->addStretch();
    m_hBoxLayout->addWidget(m_smileButton);
    m_hBoxLayout->addStretch();
    m_hBoxLayout->addWidget(m_timePicture);
    m_hBoxLayout->addWidget(m_timeLCD);

    //雷的数目显示
    m_minesLCD->display(m_mineNum);

    //创建iew和scene
    m_view = new QGraphicsView;
    m_scene = new QGraphicsScene(this);

    //创建垂直布局
    m_layout = new QVBoxLayout;

    //view设置scene
    m_view->setScene(m_scene);

    //垂直布局添加组件
    m_layout->addLayout(m_hBoxLayout);
    m_layout->addWidget(m_view);

    //中心widget设置布局
    m_widget->setLayout(m_layout);

    //设置中心widget
    this->setCentralWidget(m_widget);

    //创建图片对象
    QPixmap t_pixmap(":/images/normal.png");

    //获取图片宽和高
    int t_width = t_pixmap.width();
    int t_height = t_pixmap.height();

    //循环生成图片道具
    for(int i=0;i<m_xCoordinate;i++)
    {
        //创建一行数据的vector
        vector<myItem *> t_vec;
        for(int j=0;j<m_yCoordinate;j++)
        {
            //创建item
            myItem * t_item = new myItem(i,j);
            //设置图片
            t_item->setPixmap(t_pixmap);
            //添加item
            m_scene->addItem(t_item);
            //设置位置
            t_item->setPos(i*t_width,j*t_height);
            //保存item
            t_vec.push_back(t_item);
        }
        //保存一行的item
        m_itemVec.push_back(t_vec);
    }
}

//确定周围坐标
QPoint g_aroundPoint[8] =
{
    QPoint(-1,1),
    QPoint(-1,0),
    QPoint(-1,-1),
    QPoint(0,1),
    QPoint(0,-1),
    QPoint(1,1),
    QPoint(1,0),
    QPoint(1,-1)
};

//鼠标左击释放事件 当道具为空时递归扩散
void MainWindow::spreadNull(const int &t_minesX, const int &t_minesY)
{
    for(int i = 0;i<8;i++)
    {
        //获取周围点坐标
        int t_x = t_minesX + g_aroundPoint[i].x();
        int t_y = t_minesY + g_aroundPoint[i].y();

        //判断越界
        if(t_x < 0 || t_x >= m_xCoordinate || t_y < 0 || t_y >= m_yCoordinate)
        {
            //跳过
            continue;
        }

        //判断该道具是否被打开
        if(m_itemVec[t_x][t_y]->isOpen())
        {
            //跳过
            continue;
        }

        //打开该道具
        m_itemVec[t_x][t_y]->setIsOpen(true);

        switch (m_itemVec[t_x][t_y]->getAroundMinesNum())
              {
                  case 0:
                        //递归循环
                      this->spreadNull(t_x,t_y);
                      m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/mine_0.png"));
                      break;
                  case 1:
                      m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/mine_1.png"));
                      break;
                  case 2:
                      m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/mine_2.png"));
                      break;
                  case 3:
                      m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/mine_3.png"));
                      break;
                  case 4:
                      m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/mine_4.png"));
                      break;
                  case 5:
                      m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/mine_5.png"));
                      break;
                  case 6:
                      m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/mine_6.png"));
                      break;
                  case 7:
                      m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/mine_7.png"));
                      break;
                  case 8:
                      m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/mine_8.png"));
                      break;
        }
    }
}

//左键 按压 提示事件
void MainWindow::leftButtonTip(const int &t_leftX, const int &t_leftY)
{
    for(int i = 0;i<8;i++)
    {
        //获取周围点坐标
        int t_x = t_leftX + g_aroundPoint[i].x();
        int t_y = t_leftY + g_aroundPoint[i].y();

        //判断越界
        if(t_x < 0 || t_x >= m_xCoordinate || t_y < 0 || t_y >= m_yCoordinate)
        {
            //跳过
            continue;
        }

        //判断该道具是否被打开 或者 标记
        if(m_itemVec[t_x][t_y]->pixmap().cacheKey() ==QPixmap(":/images/flag.png").cacheKey() )
        {
            //跳过
            continue;
        }

        if(m_itemVec[t_x][t_y]->pixmap().cacheKey() ==QPixmap(":/images/normal.png").cacheKey() )
        {
                    m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/release.png"));
            //跳过
            continue;
        }

     }
      m_smileButton->setIcon(QIcon(":/images/surprise.gif"));

}

//左键 释放 提示事件
void MainWindow::leftButtonReleaseTip(const int &t_leftX, const int &t_leftY)
{
        int t_countFlag = 0;
        int t_countMines = 0;

        //第一次循环 确定旗数 和 雷数
        for(int i = 0;i<8;i++)
        {
            //获取周围点坐标
            int t_x = t_leftX + g_aroundPoint[i].x();
            int t_y = t_leftY + g_aroundPoint[i].y();

            //判断越界
            if(t_x < 0 || t_x >= m_xCoordinate || t_y < 0 || t_y >= m_yCoordinate)
            {
                //跳过
                continue;
            }

                // 是否是标记
                if( m_itemVec[t_x][t_y]->pixmap().cacheKey() ==
                        QPixmap(":/images/flag.png").cacheKey())
                {
                    //旗数加1
                    t_countFlag++;
                }

                if(m_itemVec[t_x][t_y]->isMines())
                {
                    //雷数加1
                    t_countMines++;
                }
            }
        //第二次 循环 如果旗数和雷数相同则 打开
        if(t_countFlag == t_countMines)
        {

            for(int i = 0;i<8;i++)
            {
                //获取周围点坐标
                int t_x = t_leftX + g_aroundPoint[i].x();
                int t_y = t_leftY + g_aroundPoint[i].y();

                //判断越界
                if(t_x < 0 || t_x >= m_xCoordinate || t_y < 0 || t_y >= m_yCoordinate)
                {
                    //跳过
                      continue;
                }

                if( m_itemVec[t_x][t_y]->pixmap().cacheKey() ==
                        QPixmap(":/images/flag.png").cacheKey())
                {
                      continue;
                }

                if(m_itemVec[t_x][t_y]->isMines())
                {
                    m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/mine.png"));

                    //游戏失败
                    this->receiveGameOverInfo();

                    /*****@**BUG**@*****/
                    break;
                }

                if(!m_itemVec[t_x][t_y]->isMines())
                {
                    switch (m_itemVec[t_x][t_y]->getAroundMinesNum())
                    {
                        case 0:
                            //当图片为空时 递归扩散
                            this->spreadNull(t_x,t_y);
                            m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/mine_0.png"));
                            m_itemVec[t_x][t_y]->setIsOpen(true);
                            break;
                        case 1:
                            m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/mine_1.png"));
                            m_itemVec[t_x][t_y]->setIsOpen(true);
                            break;
                        case 2:
                            m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/mine_2.png"));
                            m_itemVec[t_x][t_y]->setIsOpen(true);
                            break;
                        case 3:
                            m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/mine_3.png"));
                            m_itemVec[t_x][t_y]->setIsOpen(true);
                            break;
                        case 4:
                            m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/mine_4.png"));
                            m_itemVec[t_x][t_y]->setIsOpen(true);
                            break;
                        case 5:
                            m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/mine_5.png"));
                            m_itemVec[t_x][t_y]->setIsOpen(true);
                            break;
                        case 6:
                            m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/mine_6.png"));
                            m_itemVec[t_x][t_y]->setIsOpen(true);
                            break;
                        case 7:
                            m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/mine_7.png"));
                            m_itemVec[t_x][t_y]->setIsOpen(true);
                            break;
                        case 8:
                            m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/mine_8.png"));
                            m_itemVec[t_x][t_y]->setIsOpen(true);
                            break;
                    }

                }

              }
          }
        //第三次循环 如果旗数和雷数不同
        else
        {
            for(int i = 0;i<8;i++)
            {
                //获取周围点坐标
                int t_x = t_leftX + g_aroundPoint[i].x();
                int t_y = t_leftY + g_aroundPoint[i].y();

                //判断越界
                if(t_x < 0 || t_x >= m_xCoordinate || t_y < 0 || t_y >= m_yCoordinate)
                {
                    //跳过
                    continue;
                }
                //判断该道具打开 是标记旗
                if(m_itemVec[t_x][t_y]->pixmap().cacheKey() ==QPixmap(":/images/flag.png").cacheKey() )
                {
                    //跳过
                    continue;
                }

                if(m_itemVec[t_x][t_y]->pixmap().cacheKey() ==QPixmap(":/images/release.png").cacheKey() )
                {
                            m_itemVec[t_x][t_y]->setPixmap(QPixmap(":/images/normal.png"));
                    //跳过
                    continue;
                }

             }
        }
        m_smileButton->setIcon(QIcon(":/images/smile.gif"));
}
//布雷
void MainWindow::setMines()
{
    /*雷的个数*/
    m_mineNum1 = m_mineNum;
    int t_minesNum = m_mineNum1;

    //设置随机数种子
    srand(time(0));
    while(t_minesNum)
    {
        //求随机下标
        int t_x = rand()%m_xCoordinate;
        int t_y = rand()%m_yCoordinate;

        //如果有重复的雷
        if(m_itemVec[t_x][t_y]->isMines())
        {
            //重新循环
            continue;
        }

        //设置该道具是雷
        m_itemVec[t_x][t_y]->setIsMines(true);

        //设置雷周围的数字
        setAroundMinesNum(t_x,t_y);

        //雷数自减
        t_minesNum--;
    }
}

//设置雷周围的数字
void MainWindow::setAroundMinesNum(const int & t_minesX,const int & t_minesY)
{
    for(int i = 0;i<8;i++)
    {
        //获取周围点坐标
        int t_x = t_minesX + g_aroundPoint[i].x();
        int t_y = t_minesY + g_aroundPoint[i].y();

        //判断越界
        if(t_x < 0 || t_x >= m_xCoordinate || t_y < 0 || t_y >= m_yCoordinate)
        {
            //跳过
            continue;
        }

        //周围数字自增
        m_itemVec[t_x][t_y]->addAroundMinesNum();

    }

}

//关于信号 槽函数的链接
void MainWindow::createConnectFun()
{
    //点击扫雷简介
    this->connect( m_aboutAction,SIGNAL(triggered()),
                  this,SLOT(gameProfile()));
    //关于QT
    this->connect(m_aboutQtAction,SIGNAL(triggered()),
                  qApp,SLOT(aboutQt()));

    //新建游戏
    this->connect(m_newAction,SIGNAL(triggered()),
                  this,SLOT(restartGame()));

    //点击笑脸新建游戏
    this->connect(m_smileButton,SIGNAL(clicked()),
                  this,SLOT(smileButtonGame()));

    //扫雷计时
    this->connect(m_timer,SIGNAL(timeout()),
                  this,SLOT(gameTime()));

    //初级
    this->connect(m_primaryAction,SIGNAL(triggered()),
                  this,SLOT(primaryFun()));
   //中级
    this->connect(m_middleAction,SIGNAL(triggered()),
                  this,SLOT(middleFun()));
    //高级
    this->connect(m_highAction,SIGNAL(triggered()),
                  this,SLOT(highFun()));

    //自定义  创建一个新的dialog
    m_dialog = new myDialog;
    this->connect(m_operAction,SIGNAL(triggered()),
                  m_dialog,SLOT(show()));
    this->connect(m_dialog,SIGNAL(sendInfo(QString,QString,QString)),
                  this,SLOT(receiveInfo(QString,QString,QString)));

   //自定义  创建一个新的dialog
    m_infoDialog = new infoDialog;
    //ui 设计统计信息页面
    this->connect(m_infoAction,SIGNAL(triggered()),
                  m_infoDialog,SLOT(show()));

    //点击m_exitAction退出程序
    this->connect(m_exitAction,SIGNAL(triggered()),
                  this,SLOT(close()));
}

//游戏开始函数
void MainWindow::gameTime()
{
    t_timeCount++;

    //timelcd显示时间数字
    m_timeLCD->display(t_timeCount);
}

//声音延时函数
void MainWindow::delaySoundTime(const int &t_time)
{
    QTime overTime = QTime::currentTime().addMSecs(t_time);
    while(QTime::currentTime() < overTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

//窗口显示事件
void MainWindow::showEvent(QShowEvent *)
{
    if(m_isHideWindow)
    {
        m_timer->start();
    }
}

//窗口隐藏事件
void MainWindow::hideEvent(QHideEvent *)
{
    m_timer->stop();
}



//游戏失败函数
void MainWindow::receiveGameOverInfo()
{
    //停止计时
    m_timer->stop();

    //循环显示所有的雷
    for(int i=0;i<m_xCoordinate;i++)
    {
        for(int j=0;j<m_yCoordinate;j++)
        {
            if(m_itemVec[i][j]->isMines())
            {
                this->delaySoundTime(200);
                //打开该道具
                m_itemVec[i][j]->setPixmap(QPixmap(":/images/mine.png"));

                if(m_infoDialog->m_isOpenSound)
                {
                    //失败雷声
                    QSound::play(":/music/fail.wav");
                }
            }
        }
    }

     m_smileButton->setIcon(QIcon(":/images/cry.gif"));
/*
    //显示游戏失败信息
     QSize picSizelose(80,100);
     QMessageBox win(QMessageBox::NoIcon,"抱歉","继续努力！");
     win.setIconPixmap(QPixmap(":/images/lose.png").scaled(picSizelose, Qt::KeepAspectRatio));
     win.exec();
*/

    QSize picSizelose(80,100);
     m_msgBox.setIconPixmap(QPixmap(":/images/lose.png").scaled(picSizelose, Qt::KeepAspectRatio));
     m_msgBox.setWindowTitle(tr("失败！"));
     m_msgBox.setText(tr("抱歉，继续努力！"));

     QPushButton *m_quitButton = m_msgBox.addButton(tr("退出游戏"),QMessageBox::AcceptRole);
     QPushButton *m_restartButton = m_msgBox.addButton(tr("再来一局"),QMessageBox::AcceptRole);

     m_msgBox.exec();

     if(10 == m_mineNum)
     {
         m_myWidget->m_priPlayNum++;
         m_myWidget->writeConn();
     }

     if(40 == m_mineNum)
     {
         m_myWidget->m_midPlayNum++;
         m_myWidget->writeConn();
     }

     if(80 == m_mineNum)
     {
         m_myWidget->m_highPlayNum++;
         m_myWidget->writeConn();
     }


     if (m_msgBox.clickedButton() == m_restartButton)
     {
         this->restartGame();
         m_msgBox.removeButton(m_restartButton);
         m_msgBox.removeButton(m_quitButton);
     }
     else if(m_msgBox.clickedButton() == m_quitButton)
     {
         this->close();
     }

}

//赢得游戏函数
void MainWindow::receiveGameWinInfo()
{
    if(isWinGame())
   {
        //停止计时
        m_timer->stop();

        if(m_infoDialog->m_isOpenSound)
        {
            //胜利雷声
            QSound::play(":/music/win.wav");
        }
/*
        QSize picSizelose(80,100);
        QMessageBox win(QMessageBox::NoIcon,"恭喜你","赢得游戏 ！");
        win.setIconPixmap(QPixmap(":/images/win.png").scaled(picSizelose, Qt::KeepAspectRatio));
        win.exec();
*/
        QSize picSizelose(80,100);
         m_msgBox.setIconPixmap(QPixmap(":/images/win.png").scaled(picSizelose, Qt::KeepAspectRatio));
         m_msgBox.setWindowTitle(tr("胜利！"));
         m_msgBox.setText(tr("恭喜您，赢得游戏！"));

         QPushButton *m_quitButton = m_msgBox.addButton(tr("退出游戏"),QMessageBox::AcceptRole);
         QPushButton *m_restartButton = m_msgBox.addButton(tr("再来一局"),QMessageBox::AcceptRole);

         m_msgBox.exec();
         if(10 == m_mineNum)
         {
             m_myWidget->m_priPlayNum++;
             m_myWidget->m_priWinNum++;
             m_myWidget->m_priWinRate = (m_myWidget->m_priWinNum/m_myWidget->m_priPlayNum);

             if(m_myWidget->m_priPlayTime > t_timeCount )
             {
                    m_myWidget->m_priPlayTime = t_timeCount;
             }
             else if(0 == m_myWidget->m_priPlayTime)
             {
                 m_myWidget->m_priPlayTime = t_timeCount;
             }
             qDebug() << "****************";
             qDebug() << m_myWidget->m_priPlayNum;
             qDebug() << m_myWidget->m_priWinNum;
             qDebug() << m_myWidget->m_priWinRate;
             qDebug() << m_myWidget->m_priPlayTime;

             m_myWidget->writeConn();

         }

         if(40 == m_mineNum)
         {
             m_myWidget->m_midPlayNum++;
             m_myWidget->m_midWinNum++;
             m_myWidget->m_midWinRate = (m_myWidget->m_midWinNum/m_myWidget->m_midPlayNum);

             if(m_myWidget->m_midPlayTime > t_timeCount )
             {
                    m_myWidget->m_midPlayTime = t_timeCount;
             }
             else if(0 == m_myWidget->m_midPlayTime)
             {
                 m_myWidget->m_midPlayTime = t_timeCount;
             }

             m_myWidget->writeConn();
         }

         if(80 == m_mineNum)
         {
             m_myWidget->m_highPlayNum++;
             m_myWidget->m_highWinNum++;
             m_myWidget->m_highWinRate = (m_myWidget->m_highWinNum/m_myWidget->m_highPlayNum);

             if(m_myWidget->m_highPlayTime > t_timeCount )
             {
                    m_myWidget->m_highPlayTime = t_timeCount;
             }
             else if(0 == m_myWidget->m_highPlayTime)
             {
                 m_myWidget->m_highPlayTime = t_timeCount;
             }

             m_myWidget->writeConn();
         }

         if (m_msgBox.clickedButton() == m_restartButton)
         {
             this->restartGame();
             m_msgBox.removeButton(m_restartButton);
             m_msgBox.removeButton(m_quitButton);
         }
         else if(m_msgBox.clickedButton() == m_quitButton)
         {
             this->close();
         }

    }
}


//是否赢得游戏
bool MainWindow::isWinGame()
{
    int t_countMine = 0;
    int t_countFlag= 0;

    int t_count = 0;
    int t_flag = 0;

   for(int i = 0; i < m_xCoordinate; i++)
   {
       for(int j = 0; j < m_yCoordinate; j++)
       {
           if( m_itemVec[i][j]->pixmap().cacheKey() ==
                   QPixmap(":/images/flag.png").cacheKey())
           {
                t_countFlag++;
           }
            if(m_itemVec[i][j]->isMines())
            {
                t_countMine++;

                if( m_itemVec[i][j]->pixmap().cacheKey() ==
                        QPixmap(":/images/flag.png").cacheKey())
                {

                }
                else
                {
                    /**********此处else用的妙***********/
                    t_flag = 1;
                    break;
                }
            }
       }
   }

   if(t_flag == 1)
   {
    for(int i = 0; i < m_xCoordinate; i++)
    {
        for(int j = 0; j < m_yCoordinate; j++)
        {
            if(!(m_itemVec[i][j]->isMines()))
            {
                if(m_itemVec[i][j]->pixmap().cacheKey() !=
                        QPixmap(":/images/normal.png").cacheKey() &&
                        m_itemVec[i][j]->pixmap().cacheKey() !=
                     QPixmap(":/images/flag.png").cacheKey())

                {
                     t_count++;
                }
                else
                {
                return false;
                }
            }
         }
    }
   }
   //两种胜利情况
   if(t_countFlag == t_countMine || (m_xCoordinate * m_yCoordinate) ==
           (t_count + m_mineNum))
    {
        return true;
    }

   return false;
}

//笑脸新建游戏事件
void MainWindow::smileButtonGame()
{
        this->restartGame();
}
//重新开始本局游戏
void MainWindow::restartGame()
{
    //重开本局函数
    this->restartGameFun();
}

//重开本局函数
void MainWindow::restartGameFun()
{

    for(int i = 0; i < m_xCoordinate; i++)
    {
        for(int j = 0; j < m_yCoordinate; j++)
        {
            delete m_itemVec[i][j];
        }
    }

    m_itemVec.clear();

    //停止计时
    m_timer->stop();
    //使计时器归零
    t_timeCount = 0;

    m_minesLCD->display(m_mineNum);
    m_timeLCD->display(t_timeCount);

    this->addGriphics();

    this->setMines();
 }

//添加图像函数
void MainWindow::addGriphics()
{

    //创建widget
    m_widget = new QWidget(this);

    QSize picSize(35,25);
    //创建lcd和笑脸button
    m_minePicture = new QLabel;
    m_minePicture->setPixmap(QPixmap(":/images/game.png").scaled(picSize,Qt::KeepAspectRatio));
    m_timePicture = new QLabel;
    m_timePicture->setPixmap(QPixmap(":/images/clock.png").scaled(picSize,Qt::KeepAspectRatio));

    m_minesLCD = new QLCDNumber;
    m_smileButton = new QPushButton;
    m_smileButton->setIcon(QIcon(":/images/smile.gif"));
    m_timeLCD = new QLCDNumber;

    //创建调色板局部变量
    QPalette t_palette;

    //设置数字颜色
    t_palette.setColor(QPalette::Light,Qt::red);
    m_minesLCD->setPalette(t_palette);
    t_palette.setColor(QPalette::Light,Qt::red);
    m_timeLCD->setPalette(t_palette);
    //设置背景颜色
    m_minesLCD->setStyleSheet("background:black");
    m_timeLCD->setStyleSheet("background:black");

    //笑脸按钮
    m_smileButton->resize(35,25);
    m_smileButton->setIconSize(QSize(35,25));
    m_smileButton->setIcon(QIcon(":/images/smile.gif"));

    //创建水平布局
    m_hBoxLayout = new QHBoxLayout;

    //布局添加组件
    m_hBoxLayout->addWidget(m_minePicture);
    m_hBoxLayout->addWidget(m_minesLCD);
    m_hBoxLayout->addStretch();
    m_hBoxLayout->addWidget(m_smileButton);
    m_hBoxLayout->addStretch();
    m_hBoxLayout->addWidget(m_timePicture);
    m_hBoxLayout->addWidget(m_timeLCD);

    //雷的数目显示
    m_minesLCD->display(m_mineNum);

    //点击笑脸新建游戏
    this->connect(m_smileButton,SIGNAL(clicked()),
                  this,SLOT(smileButtonGame()));

    //创建iew和scene
    m_view = new QGraphicsView;
    m_scene = new QGraphicsScene(this);

    //创建垂直布局
    m_layout = new QVBoxLayout;

    //view设置scene
    m_view->setScene(m_scene);

    //垂直布局添加组件
    m_layout->addLayout(m_hBoxLayout);
    m_layout->addWidget(m_view);

    //中心widget设置布局
    m_widget->setLayout(m_layout);

    //设置中心widget
    this->setCentralWidget(m_widget);

    if(m_infoDialog->m_isOpenSound)
    {
        QSound::play(":/music/start.wav");
    }

    m_isHideWindow = false;

    //创建图片对象
    QPixmap t_pixmap(":/images/normal.png");

    //获取图片宽和高
    int t_width = t_pixmap.width();
    int t_height = t_pixmap.height();

    //循环生成图片道具
    for(int i=0;i<m_xCoordinate;i++)
    {
        //创建一行数据的vector
        vector<myItem *> t_vec;
        for(int j=0;j<m_yCoordinate;j++)
        {
            //创建item
            myItem * t_item = new myItem(i,j);
            //设置图片
            t_item->setPixmap(t_pixmap);
            //添加item
            m_scene->addItem(t_item);
            //设置位置
            t_item->setPos(i*t_width,j*t_height);
            //保存item
            t_vec.push_back(t_item);
        }
        //保存一行的item
        m_itemVec.push_back(t_vec);
    }
   this->resize(m_xCoordinate * t_width + 40,m_yCoordinate *t_height +120);
}

//初级
void MainWindow::primaryFun()
{
    m_xCoordinate = 9;
    m_yCoordinate = 9;
    m_mineNum = 10;

    m_itemVec.clear();

    this->addGriphics();
    this->setMines();
}

//中级
void MainWindow::middleFun()
{
    m_xCoordinate = 16;
    m_yCoordinate = 16;
    m_mineNum = 40;

    m_itemVec.clear();

    this->addGriphics();
    this->setMines();
}

//高级
void MainWindow::highFun()
{
    m_xCoordinate = 28;
    m_yCoordinate = 16;
    m_mineNum = 80;

    m_itemVec.clear();

    this->addGriphics();
    this->setMines();

}

//自定义的界面行列以及雷数
void MainWindow::receiveInfo(const QString &t_lin,
                             const QString &t_col,
                             const QString &t_num)
{

    //列转为X轴 行转为Y轴
    m_xCoordinate = t_col.toInt();
    m_yCoordinate = t_lin.toInt();
    m_mineNum = t_num.toInt();

    m_itemVec.clear();

    this->addGriphics();
    this->setMines();
}

//右键按压标记撤销 雷数加一
void MainWindow::receiveAddFlagNum()
{
    m_mineNum1++;
    //雷的数目显示
    m_minesLCD->display(m_mineNum1);
}
//右键按压标记 雷数减一
void MainWindow::receiveReduceFlagNum()
{
    m_mineNum1--;
    //雷的数目显示f
    m_minesLCD->display(m_mineNum1);
}

//时间开始计时
void MainWindow::receiveStartInfo()
{
    //isActive()判断 计时器是否开始
    if(!m_timer->isActive())
    {
        m_timer->start();
        m_isHideWindow = true;
    }
}

//帮助--扫雷介绍
void MainWindow::gameProfile()
{
    QMessageBox::about(this,("扫雷简介"),"《扫雷》是一款大众类的益智小游戏，\
于1992年发行。\
游戏目标是在最短的时间内根据点击格子出现的数字找出所有非雷格子，\
同时避免踩雷。\
[1]  扫雷最初的流行伴随着1992年发布的windows 3.1，\
之后迅速成为了各种操作系统中必不可少的一款游戏\
（包括windows的winmine， KDE桌面环境下的KMines，\
  GNOME桌面环境下的gnomine等），\
  也出现于一些智能手机平台\
 （比如Android系统的Minesweeper Classic，\
 苹果ios系统的Minesweeper Q）。\
  同时，"\
  "Minesweeper Clone等功能更为丰富的“专业”\
  扫雷软件也应时而生。");
}

