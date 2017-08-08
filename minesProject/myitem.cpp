#include "myitem.h"
#include "mainwindow.h"

myItem::myItem(const int &t_x, const int &t_y, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
      m_x(t_x),m_y(t_y),
      m_isMines(false),m_isOpen(false),
      m_aroundMinesNum(0)
{

}

myItem::~myItem()
{

}

//鼠标左键 右键 按压事件
void myItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    MainWindow * t_mainWindow = (MainWindow *)this->scene()->parent();

    if(event->button() == Qt::LeftButton)
    {
        if(!m_isOpen)
        {
            this->setPixmap(QPixmap(":/images/click.PNG"));
        }
        else
        {
            t_mainWindow->leftButtonTip(m_x,m_y);

        }
    }
    //右键按压
    else if(event->button() == Qt::RightButton)
   {
        //右键按压 是未知 变为假设的雷
        if(this->pixmap().cacheKey() ==
           QPixmap(":/images/normal.png").cacheKey())
        {
            this->setPixmap(QPixmap(":/images/flag.png"));
            t_mainWindow->receiveReduceFlagNum();
        }
        //右键按压 是假设 变未知的雷
        else if(this->pixmap().cacheKey() ==
                QPixmap(":/images/flag.png").cacheKey())
        {
            this->setPixmap(QPixmap(":/images/normal.png"));
            t_mainWindow->receiveAddFlagNum();
        }
        //右键按压 是空白 是数字 不做任何事
        else
        {
            return;
        }
    }
}

//鼠标释放事件
void myItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    MainWindow * t_mainWindow = (MainWindow *)this->scene()->parent();

    if(event->button() == Qt::LeftButton)
    {
        if( this->pixmap().cacheKey() ==
                QPixmap(":/images/click.PNG").cacheKey())
        {

            m_isOpen = true;
            if(m_isMines)
            {
                this->setPixmap(QPixmap(":/images/mine.png"));
                //游戏失败
                t_mainWindow->receiveGameOverInfo();

            }
            else
            {
                switch (m_aroundMinesNum)
                {
                    case 0:
                        t_mainWindow->receiveStartInfo();
                        //当图片为空时 递归扩散
                        t_mainWindow->spreadNull(m_x,m_y);
                        this->setPixmap(QPixmap(":/images/mine_0.png"));
                        break;
                    case 1:
                        t_mainWindow->receiveStartInfo();
                        this->setPixmap(QPixmap(":/images/mine_1.png"));
                        break;
                    case 2:
                        t_mainWindow->receiveStartInfo();
                        this->setPixmap(QPixmap(":/images/mine_2.png"));
                        break;
                    case 3:
                        t_mainWindow->receiveStartInfo();
                        this->setPixmap(QPixmap(":/images/mine_3.png"));
                        break;
                    case 4:
                        t_mainWindow->receiveStartInfo();
                        this->setPixmap(QPixmap(":/images/mine_4.png"));
                        break;
                    case 5:
                        t_mainWindow->receiveStartInfo();
                        this->setPixmap(QPixmap(":/images/mine_5.png"));
                        break;
                    case 6:
                        t_mainWindow->receiveStartInfo();
                        this->setPixmap(QPixmap(":/images/mine_6.png"));
                        break;
                    case 7:
                        t_mainWindow->receiveStartInfo();
                        this->setPixmap(QPixmap(":/images/mine_7.png"));
                        break;
                    case 8:
                        t_mainWindow->receiveStartInfo();
                        this->setPixmap(QPixmap(":/images/mine_8.png"));
                        break;
                }

            }
        }
        else
        {
                t_mainWindow->leftButtonReleaseTip(m_x,m_y);
        }
    }
     t_mainWindow->receiveGameWinInfo();
}

//是否为雷
bool myItem::isMines() const
{
    return m_isMines;
}

//设置为雷
void myItem::setIsMines(bool isMines)
{
    m_isMines = isMines;
}

//增添雷周围数字
void myItem::addAroundMinesNum()
{
    m_aroundMinesNum++;
}

//获取雷周围数字
const int &myItem::getAroundMinesNum() const
{
    return m_aroundMinesNum;
}

//是否打开道具
bool myItem::isOpen() const
{
    return m_isOpen;
}

//设置打开道具
void myItem::setIsOpen(bool isOpen)
{
    m_isOpen = isOpen;
}


