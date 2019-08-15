#include"box.h"
#include"blocks.h"
#include<QKeyEvent>
#include<QGraphicsItemGroup>
#include<QGraphicsObject>
#include<QObject>
#include<QPaintEvent>
#include<QWidget>

Box::Box(QWidget *parent) : QWidget(parent)
{
    //初始化方块
    for(int i=0;i<COUNT;i++)
    {
        block.x[i]=-1;
        block.y[i]=-1;
    }
    block.centerX=-1;
    block.centerY=-1;
    block.blockid=-1;

    //初始化地图
    for(int i=0;i<MAPX;i++)
    {
        for(int j=0;j<MAPY;j++)
            box[i][j]=0;
    }

    int wide=302;//T::getwidth()
    int high=676;//T::getheight()
    setFixedSize(wide,high);
    setPalette(QPalette(Qt::gray));
    setAutoFillBackground(true);
}


void Box::updatetetris(T tetris)
{
    block=tetris.getblock();
    for(int i=0;i<MAPX;i++)
    {
        for(int j=0;j<MAPY;j++)
        {
            box[i][j]=tetris.getbox(i,j);

        }
    }
    repaint();  //调用下面的涂色函数涂色
}


void Box::paintEvent(QPaintEvent *e)
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

    //对地图上已有的块涂色
    for(int i=0;i<MAPX;i++)
    {
        for(int j=0;j<MAPY;j++)
        {
            if(box[i][j]==1)
            {
                int x=i*(WIDTH+GAP);
                int y=j*(HEIGHT+GAP);
                painter.drawRect(x,y,WIDTH,HEIGHT);
            }
        }
    }

    //对block
    for(int i=0;i<COUNT;i++)
    {
        int x=block.x[i];
        int y=block.y[i];
        int bx=x*(WIDTH+GAP);
        int by=y*(HEIGHT+GAP);
        painter.drawRect(bx,by,WIDTH,HEIGHT);
    }
}









