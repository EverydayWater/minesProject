#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include "connectwidget.h"

namespace Ui {
class infoDialog;
}

class infoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit infoDialog(QWidget *parent = 0);
    ~infoDialog();

    void createConnectUi();
    //是否打开声音？
    bool m_isOpenSound;

public slots:
    void priInfoGame();
    void midInfoGame();
    void highInfoGame();
    void openGameSound();

private:
    Ui::infoDialog *ui;

    //初级 信息记录
    double m_priUiPlayNum;
    double m_priUiWinNum;
    double m_priUiWinRate;
    int m_priUiPlayTime;

    //中级 信息记录
    double m_midUiPlayNum;
    double m_midUiWinNum;
    double m_midUiWinRate;
    int m_midUiPlayTime;

    //高级 信息记录
    double m_highUiPlayNum;
    double m_highUiWinNum;
    double m_highUiWinRate;
    int m_highUiPlayTime;

    int m_i;
    connectWidget *m_myWidget;
};

#endif // INFODIALOG_H
