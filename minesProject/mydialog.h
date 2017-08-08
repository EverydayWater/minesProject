#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QWidget> //组件
#include <QDialog> //对话
#include <QLabel> //标签
#include <QLineEdit> //文本行
#include <QHBoxLayout> //水平布局
#include <QGridLayout> //网格布局
#include <QPushButton> //按钮

class myDialog: public QDialog
{
    Q_OBJECT

public:
    myDialog(QWidget *parent = 0);
    ~myDialog();

signals:
    void sendInfo(const QString &t_lin,
                  const QString &t_col,
                  const QString &t_num);

public slots:
    void saveInfo();

private:
    QLabel *m_lineLabel; //行标签
    QLabel *m_columnLabel; //列标签
    QLabel *m_numberLabel; //布雷数

    QLineEdit *m_lineEdit; //行数 文本行
    QLineEdit *m_columnEdit;//列数 文本行
    QLineEdit *m_numberEdit; //雷数 文本行

    QPushButton *m_enterButton; //进入按钮
    QHBoxLayout *m_hLayout;//水平布局
    QGridLayout *m_gLayout; //网格布局
};

#endif // MYDIALOG_H
