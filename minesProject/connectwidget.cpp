#include "connectwidget.h"
#include <QDebug>

connectWidget::connectWidget(QWidget *parent)
    :QWidget(parent),m_priPlayNum(0),m_priWinNum(0),
      m_priWinRate(0.0),m_priPlayTime(0)
{

}

connectWidget::~connectWidget()
{

}

//创建数据库数据链接  数据库操作
void connectWidget::addDBConn()
{
    //创建一个数据库对象
    m_db = QSqlDatabase::addDatabase("QMYSQL");

    //设置数据库的相关配置
    m_db.setDatabaseName("myQtMine");
    m_db.setHostName("localhost");
    m_db.setUserName("root");
    m_db.setPassword("654321");
    m_db.setPort(3306);

    //打开数据库
    if(!m_db.open())
    {
        qDebug() << "mysql open error...";
    }

        qDebug() << "mysql open successfully...";

    //创建一个query并指定database
    m_query = new QSqlQuery(m_db);

    //初级 执行sql语句
    m_query->exec("select * from pri;");

    //判断query存在内容
    while(m_query->next())
    {
        //初级 输出query内的值
        m_priPlayNum = m_query->value("playNum").toDouble();
        m_priWinNum = m_query->value("winNum").toDouble();
        m_priWinRate = m_query->value("winRate").toDouble();
        m_priPlayTime = m_query->value("bestTime").toInt();

//        qDebug() << m_priPlayNum;
//        qDebug() << m_priWinNum;
//        qDebug() << m_priPlayNum;
//        qDebug() << m_priWinNum;
    }

    //中级
    m_query->exec("select * from middle;");
    //判断query存在内容
    while(m_query->next())
    {
       //中级 输出query内的值
        m_midPlayNum = m_query->value("midPlayNum").toDouble();
        m_midWinNum = m_query->value("midWinNum").toDouble();
        m_midWinRate = m_query->value("midWinRate").toDouble();
        m_midPlayTime = m_query->value("midBestTime").toInt();
    }

    //高级
    m_query->exec("select * from high;");
    //判断query存在内容
    while(m_query->next())
    {
       //高级 输出query内的值
        m_highPlayNum = m_query->value("highPlayNum").toDouble();
        m_highWinNum = m_query->value("highWinNum").toDouble();
        m_highWinRate = m_query->value("highWinRate").toDouble();
        m_highPlayTime = m_query->value("highBestTime").toInt();
    }
    qDebug() << "#############33";
    qDebug() << m_highPlayNum;
    qDebug() << m_highWinNum;
    qDebug() << m_highWinRate;
    qDebug() << m_highPlayTime;
}

void connectWidget::writeConn()
{
    QSqlQuery t_priQuery(m_db);
    QSqlQuery t_midQuery(m_db);
    QSqlQuery t_highQuery(m_db);

    //初级
    t_priQuery.exec("delete from pri;");
    t_priQuery.prepare("insert into pri(playNum,winNum,winRate,bestTime) values(?,?,?,?);");
    t_priQuery.addBindValue(m_priPlayNum);
    t_priQuery.addBindValue(m_priWinNum);
    t_priQuery.addBindValue(m_priWinRate);
    t_priQuery.addBindValue(m_priPlayTime);
    t_priQuery.exec();

    //中级
    t_midQuery.exec("delete from middle;");
    t_midQuery.prepare("insert into middle(midPlayNum,midWinNum,midWinRate,midBestTime) values(?,?,?,?);");
    t_midQuery.addBindValue(m_midPlayNum);
    t_midQuery.addBindValue(m_midWinNum);
    t_midQuery.addBindValue(m_midWinRate);
    t_midQuery.addBindValue(m_midPlayTime);
    t_midQuery.exec();

    //高级
    t_highQuery.exec("delete from high;");
    t_highQuery.prepare("insert into high(highPlayNum,highWinNum,highWinRate,highBestTime) values(?,?,?,?);");
    t_highQuery.addBindValue(m_highPlayNum);
    t_highQuery.addBindValue(m_highWinNum);
    t_highQuery.addBindValue(m_highWinRate);
    t_highQuery.addBindValue(m_highPlayTime);
    t_highQuery.exec();

}



