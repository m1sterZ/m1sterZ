#ifndef BLOCKS_H
#define BLOCKS_H
#include<QTime>
#include<QtGlobal>
#include<iostream>

#define MAPX 9  //地图每行的格子数
#define MAPY 20   //地图每列的格子数
#define WIDTH 30    //每个格子的宽度
#define HEIGHT 30   //每个格子的高度
#define GAP 4   //格子之间的间隔
#define COUNT 4 //每个块block占的格数
#define NEXTX  6 //显示下一个块block的窗口每行的格子数
#define NEXTY  6 //显示下一个块block的窗口每列的格子数

struct Block
{
    //每个方格的x和y坐标
    int x[COUNT];
    int y[COUNT];

    //中心的x和y坐标
    int centerX;
    int centerY;

    int blockid;
};

class T
{
public:
    T();
    void newblock();    //创建新的块
    int getscore();
    int getbox(int x,int y);    //对应坐标的状态
    Block getblock();   //获取当前的块的信息
    Block getnextblock();  //获取下一个块的信息

    int getwidth();
    int getheight();
    int getnextwidth();
    int getnextheight();
    int getfullline();//从上到下找到填满的行

    void newnextblock();
    void blocktobox();
    bool move(int mx,int my);


    //判断块是否能做以下动作
    bool goleft();
    bool goright();
    bool godown();
    bool rotatable();

    bool clearcondition();//消去行的其他条件
    bool gameover();


    void restart(); //重新初始化
    void clearline();   //消去整行

public:
    int score;
    Block block;
    Block nextblock;
    int box[MAPX][MAPY];    //地图中的方格，0表示空，1表示有方块
};



#endif // BLOCKS_H
