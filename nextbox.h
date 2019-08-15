#ifndef NEXTBOX_H
#define NEXTBOX_H
#include<QWidget>
#include<QObject>
#include<QPaintEvent>
#include<QPainter>
#include<QPalette>
#include<QPen>
#include<QBrush>
#include<QColor>
#include<QLabel>
#include<QTimer>
#include<QTime>
#include<QGraphicsItem>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QGuiApplication>
#include<QGraphicsWidget>
#include"blocks.h"
#define TRANSX 2  //(MAPX-NEXTX)/2
#define TRANSY 4

class Nextbox : public QWidget
{
    Q_OBJECT
public:
    explicit Nextbox(QWidget *parent = nullptr);
    void updatenexttetris(T tetris);
    void paintEvent(QPaintEvent *event);
    Block nextblock;
};

#endif // NEXTBOX_H
