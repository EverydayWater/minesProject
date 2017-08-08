#include "infoDialog.h"
#include "ui_infoDialog.h"

infoDialog::infoDialog(QWidget *parent) :
    QDialog(parent), m_isOpenSound(false),ui(new Ui::infoDialog),
    m_priUiPlayNum(0),m_priUiWinNum(0),m_priUiWinRate(0),
    m_priUiPlayTime(0),m_i(1)
{
    //数据库读信息
    m_myWidget = new connectWidget;

    ui->setupUi(this);
    this->createConnectUi();
}

infoDialog::~infoDialog()
{
    delete ui;
}

//显示 初级统计信息
void infoDialog::priInfoGame()
{

    m_myWidget->addDBConn();

    m_priUiPlayNum = m_myWidget->m_priPlayNum;
    m_priUiWinNum = m_myWidget->m_priWinNum;
    m_priUiWinRate = m_myWidget->m_priWinRate;
    m_priUiPlayTime = m_myWidget->m_priPlayTime;

    ui->label_already->setText(QString::number(m_priUiPlayNum));
    ui->label_winNum->setText(QString::number(m_priUiWinNum));
    ui->label_winRate->setText(QString::number(m_priUiWinRate));
    ui->label_bestTime->setText(QString::number(m_priUiPlayTime));

}

//显示 中级统计信息
void infoDialog::midInfoGame()
{
    m_myWidget->addDBConn();

    m_midUiPlayNum = m_myWidget->m_midPlayNum;
    m_midUiWinNum = m_myWidget->m_midWinNum;
    m_midUiWinRate = m_myWidget->m_midWinRate;
    m_midUiPlayTime = m_myWidget->m_midPlayTime;

    ui->label_already->setText(QString::number(m_midUiPlayNum));
    ui->label_winNum->setText(QString::number(m_midUiWinNum));
    ui->label_winRate->setText(QString::number(m_midUiWinRate));
    ui->label_bestTime->setText(QString::number(m_midUiPlayTime));
}

//显示 高级统计信息
void infoDialog::highInfoGame()
{
    m_myWidget->addDBConn();

    qDebug() << "@@@@@@@@@@@@@22";
    qDebug() << m_myWidget->m_highPlayNum;
    qDebug() << m_myWidget->m_highWinNum;
    qDebug() << m_myWidget->m_highWinRate;
    qDebug() << m_myWidget->m_highPlayTime;

    m_highUiPlayNum = m_myWidget->m_highPlayNum;
    m_highUiWinNum = m_myWidget->m_highWinNum;
    m_highUiWinRate = m_myWidget->m_highWinRate;
    m_highUiPlayTime = m_myWidget->m_highPlayTime;

    ui->label_already->setText(QString::number(m_highUiPlayNum));
    ui->label_winNum->setText(QString::number(m_highUiWinNum));
    ui->label_winRate->setText(QString::number(m_highUiWinRate));
    ui->label_bestTime->setText(QString::number(m_highUiPlayTime));
}

void infoDialog::openGameSound()
{
    if(m_i)
    {
        m_isOpenSound = true;
        m_i = 0;
    }
    else
    {
        m_isOpenSound = false;
        m_i = 1;
    }
}


//创建与ui有关的连接
void infoDialog::createConnectUi()
{
    this->connect(ui->radioButton,SIGNAL(clicked()),
                  this,SLOT(priInfoGame()));

    this->connect(ui->radioButton_2,SIGNAL(clicked()),
                  this,SLOT(midInfoGame()));

    this->connect(ui->radioButton_3,SIGNAL(clicked()),
                  this,SLOT(highInfoGame()));

    this->connect(ui->checkBox,SIGNAL(clicked()),
                  this,SLOT(openGameSound()));

}


