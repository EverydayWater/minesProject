#ifndef CONNECTWIDGET_H
#define CONNECTWIDGET_H

#include <QWidget>
#include <QSqlDatabase> //数据库连接
#include <QDebug>
#include <QSqlQuery>

class connectWidget: public QWidget
{
    Q_OBJECT

public:
     connectWidget(QWidget* parent = 0);
     ~connectWidget();

    //从数据库读数据
     void addDBConn();
     //向数据库写入数据
     void writeConn();

     //初级
     //已玩次数
     double m_priPlayNum;
     //胜利次数
     double m_priWinNum;
     //游戏胜率
     double m_priWinRate;
     //游戏时间
     int m_priPlayTime;

     //中级
     //已玩次数
     double m_midPlayNum;
     //胜利次数
     double m_midWinNum;
     //游戏胜率
     double m_midWinRate;
     //游戏时间
     int m_midPlayTime;

     //高级
     //已玩次数
     double m_highPlayNum;
     //胜利次数
     double m_highWinNum;
     //游戏胜率
     double m_highWinRate;
     //游戏时间
     int m_highPlayTime;

private:

     QSqlDatabase m_db;
     QSqlQuery * m_query;

};

#endif // CONNECTWIDGET_H

