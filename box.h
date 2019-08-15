#ifndef BOX_H
#define BOX_H
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

class Box : public QWidget
{
    Q_OBJECT

public:
    explicit Box(QWidget *parent=nullptr);
    void updatetetris(T tetris);
    //QPaintEvent *event;
    void paintEvent(QPaintEvent *e);
    Block block;
    int box[MAPX][MAPY];

};

#endif // BOX_H
