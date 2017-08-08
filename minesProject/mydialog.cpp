#include "mydialog.h"

myDialog::myDialog(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle("自定义");

    //创建标签
    m_lineLabel = new QLabel("   行    ", this);
    m_columnLabel = new QLabel("   列    ", this);
    m_numberLabel = new QLabel("   雷数    ", this);

    //创建文本行
    m_lineEdit = new QLineEdit(this);
    m_columnEdit = new QLineEdit(this);
    m_numberEdit = new QLineEdit(this);

    //设置初始值
    m_lineEdit->setText("6");
    m_columnEdit->setText("6");
    m_numberEdit->setText("6");

    //创建水平布局
    m_hLayout = new QHBoxLayout;
    m_enterButton = new QPushButton("确定", this);

    //添加按钮
    m_hLayout->addStretch();
    m_hLayout->addWidget(m_enterButton);
    m_hLayout->addStretch();

    m_gLayout = new QGridLayout;
    //添加组件
    m_gLayout->addWidget(m_lineLabel, 0, 0);
    m_gLayout->addWidget(m_lineEdit, 0, 1);
    m_gLayout->addWidget(m_columnLabel, 1, 0);
    m_gLayout->addWidget(m_columnEdit, 1, 1);
    m_gLayout->addWidget(m_numberLabel, 2, 0);
    m_gLayout->addWidget(m_numberEdit, 2, 1);
    m_gLayout->addLayout(m_hLayout, 3, 1);

    //添加到页面布局
    this->setLayout(m_gLayout);

    //按钮点击信号 发送信息
    this->connect(m_enterButton, SIGNAL(clicked()),
                  this, SLOT(saveInfo()));
}

myDialog::~myDialog()
{

}

void myDialog::saveInfo()
{
    QString t_lin = m_lineEdit->text();
    QString t_col = m_columnEdit->text();
    QString t_num = m_numberEdit->text();

    this->sendInfo(t_lin, t_col, t_num);

    this->close();
}
