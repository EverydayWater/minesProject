#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QtWidgets/qdialog.h>

class myItem : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    myItem(const int & t_x,const int & t_y,QGraphicsItem *parent = 0);
    ~myItem();
    //鼠标按压事件
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //鼠标释放事件
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    //是否为雷
    bool isMines() const;
    //设置为雷
    void setIsMines(bool isMines);

    //添加雷周围的数字
    void addAroundMinesNum();
    //获取雷周围的数字
    const int & getAroundMinesNum() const;

    //是否打开
    bool isOpen() const;
    void setIsOpen(bool isOpen);

signals:

    //增加标记的数量
    void sendAddFlagNum();
    //减少标记的数量
    void sendReduceFlagNum();

private :
    //静态打开的个数
    static int m_openNum;

    int m_x;
    int m_y;

    //是否为雷？
    bool m_isMines;
    //是否打开？
    bool m_isOpen;

    int m_aroundMinesNum;
};

#endif // MYITEM_H
