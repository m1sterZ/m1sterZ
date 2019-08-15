#include"nextbox.h"
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
#include<QKeyEvent>

Nextbox::Nextbox(QWidget *parent) : QWidget (parent)
{
    for(int i=0;i<COUNT;i++)//初始化下一个刷新的块
    {
        nextblock.x[i]=-1;
        nextblock.y[i]=-1;
    }
    nextblock.centerX=-1;
    nextblock.centerY=-1;
    nextblock.blockid=0;

    int wide=200;
    int high=200;
    setFixedSize(wide,high);
    setPalette(QPalette(Qt::gray));
    setAutoFillBackground(true);

}


void Nextbox::updatenexttetris(T tetris)
{
    nextblock=tetris.getnextblock();
    for(int i=0;i<COUNT;i++)
    {
        nextblock.x[i]-=TRANSX;
        nextblock.y[i]+=TRANSY;
    }
    repaint();
}


void Nextbox::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    QBrush brush;

    pen.setStyle(Qt::SolidLine);
    pen.setColor(QColor(255,255,255));

    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(255,255,255));

    painter.setPen(pen);
    painter.setBrush(brush);

    for(int i=0;i<COUNT;i++)
    {
        int x=nextblock.x[i];
        int y=nextblock.y[i];
        int bx=x*(WIDTH+GAP);
        int by=y*(HEIGHT+GAP);
        painter.drawRect(bx,by,WIDTH,HEIGHT);
    }
}
