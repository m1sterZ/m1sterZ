#include "blocks.h"

T::T()
{
    //初始化
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    this->score=0;
    //this->newnextblock();
    for(int i=0;i<MAPX;i++)
    {
        for(int j=0;j<MAPY;j++)
            box[i][j]=0;
    }

    for(int i=0;i<COUNT;i++)
    {
        block.x[i]=-1;
        block.y[i]=-1;
    }
    block.centerX=-1;
    block.centerY=-1;
    block.blockid=0;

    newnextblock();

}


void T::newblock()
{
    //newnextblock();
    for(int i=0;i<COUNT;i++)    //将下一个块的信息赋值给现在的块并刷新在地图上
    {
        block.x[i]=nextblock.x[i];
        block.y[i]=nextblock.y[i];
        //block.x[i]-=2;
        //block.y[i]+=2;
    }

    block.centerX=nextblock.centerX;
    block.centerY=nextblock.centerY;
    block.blockid=nextblock.blockid;

    //move(0,3);
    newnextblock();
}

Block T::getblock()
{
    return block;
}

Block T::getnextblock()
{
    return nextblock;
}

int T::getscore()
{
    return score;
}

int T::getbox(int x, int y)
{
    return box[x][y];   //用于判断该坐标是否有方块
}




bool T::move(int mx, int my)
{
    int newx[COUNT];
    int newy[COUNT];
    int newcx;
    int newcy;
    for(int i=0;i<COUNT;i++)
    {
        newx[i]=block.x[i]+mx;
        newy[i]=block.y[i]+my;

        //判断移动后的坐标是否越界或碰撞
        if(newx[i]<0||newx[i]>=MAPX)
            return false;
        if(newy[i]>0&&newy[i]<MAPY)
        {
            if(box[newx[i]][newy[i]]==1)//若地图该位置已有方块
                return false;
        }
        else if(newy[i]>=MAPY)
            return false;
    }

    //满足条件则移动
    newcx=block.centerX+mx;
    newcy=block.centerY+my;
    for(int i=0;i<COUNT;i++)
    {
        block.x[i]=newx[i];
        block.y[i]=newy[i];
    }
    block.centerX=newcx;
    block.centerY=newcy;

    return true;
}




bool T::goleft()
{
    if(move(-1,0))
    {
        return true;
    }
    else return false;
}

bool T::goright()
{
    if(move(1,0))
    {
        return true;
    }
    else return false;
}

bool T::godown()
{
    if(!move(0,1))
    {
        //如果不能下落，判断游戏是否结束
        blocktobox();
        clearline();
        if(gameover())
        {
            return false;//返回false即游戏结束
        }
        else newblock();
    }
    //move(0,1);
    return true;
}

//旋转
bool T::rotatable()
{
    int newx[COUNT];
    int newy[COUNT];
    //int newcx;
    //int newcy;

    if(block.blockid==0)    //正方形的方块旋不旋转都一样
        return false;
    for(int i=0;i<COUNT;i++)
    {
        //每一个小方块到块中心的距离
        int rx=block.x[i]-block.centerX;
        int ry=block.y[i]-block.centerY;

        //旋转后的坐标
        newx[i]=block.centerX-ry;
        newy[i]=block.centerY+rx;

        //判断旋转后坐标是否越界或碰撞
        if(newx[i]<0||newx[i]>=MAPX)
            return false;
        if(newy[i]>0&&newy[i]<MAPY)
        {
            if(box[newx[i]][newy[i]]==1)
                return false;
        }
        else if(newy[i]>=MAPY)
            return false;
    }

    //满足条件后旋转
    for(int i=0;i<COUNT;i++)
    {
        block.x[i]=newx[i];
        block.y[i]=newy[i];
    }
    return true;
}





bool T::gameover()  //若第一行有块则游戏结束
{

    for(int j=0;j<MAPX;j++)
    {
        int k=1;
        if(box[j][k]==1)
            return true;
    }
    return false;
}

void T::clearline()
{
    int clearrow=0;
    int temp=0;
    temp=getfullline();
    //除去被注释掉的条件解锁新难度
    while((getfullline()!=-1)/*&&clearcondition()*/)
    {
        for(int j=temp;j>0;j--)
        {
            for(int k=0;k<MAPX;k++)
            {
                box[k][j]=box[k][j-1];  //把上面所有行往下平移完成消行
                if(j<MAPY-1&&box[k][j+1]==0&&box[k][j]==1)
                {
                    box[k][j+1]=box[k][j];  //消行后如果下面有空格自动使上方的块下落，防止出现浮空的块

                }
            }
        }
        clearrow++;
    }
    //消行后刷新分数
    score+=clearrow*clearrow*5;
}

void T::restart()
{
    this->score=0;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0;i<MAPX;i++)
    {
        for(int j=0;j<MAPY;j++)
            this->box[i][j]=0;
    }

    for(int i=0;i<COUNT;i++)
    {
        this->block.x[i]=-1;
        this->block.y[i]=-1;
    }
    this->block.centerX=-1;
    this->block.centerY=-1;
    this->block.blockid=0;
    this->newnextblock();

}



//四个混行数的函数
int T::getwidth()
{
    return MAPX*WIDTH+(MAPX-1)*GAP;
}

int T::getheight()
{
    return MAPY*HEIGHT+(MAPY-1)*GAP;
}

int T::getnextwidth()
{
    return NEXTX*WIDTH+(NEXTX-1)*GAP;
}

int T::getnextheight()
{
    return NEXTY*HEIGHT+(NEXTY-1)*GAP;
}



void T::newnextblock()  //随机刷新下一个块
{
    int centerx=(MAPX-1)/2;
    int blockid=qrand()%7;

    switch (blockid)
    {
        case 0:
        //##
        //##
            nextblock.x[0]=centerx;
            nextblock.x[1]=centerx;
            nextblock.x[2]=centerx+1;
            nextblock.x[3]=centerx+1;
            nextblock.y[0]=-2;
            nextblock.y[1]=-1;
            nextblock.y[2]=-2;
            nextblock.y[3]=-1;
            nextblock.centerX=0;
            nextblock.centerY=0;
            nextblock.blockid=0;
            break;

        case 1:
        //####
        //
            nextblock.x[0]=centerx-1;
            nextblock.x[1]=centerx;
            nextblock.x[2]=centerx+1;
            nextblock.x[3]=centerx+2;
            nextblock.y[0]=-1;
            nextblock.y[1]=-1;
            nextblock.y[2]=-1;
            nextblock.y[3]=-1;
            nextblock.centerX=centerx;
            nextblock.centerY=-1;
            nextblock.blockid=1;
            break;

        case 2:
        //#
        //###
            nextblock.x[0]=centerx-1;
            nextblock.x[1]=centerx-1;
            nextblock.x[2]=centerx;
            nextblock.x[3]=centerx+1;
            nextblock.y[0]=-2;
            nextblock.y[1]=-1;
            nextblock.y[2]=-1;
            nextblock.y[3]=-1;
            nextblock.centerX=centerx;
            nextblock.centerY=-1;
            nextblock.blockid=2;
            break;

        case 3:
        //  #
        //###
            nextblock.x[0]=centerx+1;
            nextblock.x[1]=centerx-1;
            nextblock.x[2]=centerx;
            nextblock.x[3]=centerx+1;
            nextblock.y[0]=-2;
            nextblock.y[1]=-1;
            nextblock.y[2]=-1;
            nextblock.y[3]=-1;
            nextblock.centerX=centerx;
            nextblock.centerY=-1;
            nextblock.blockid=3;
            break;

        case 4:
        //##
        // ##
            nextblock.x[0]=centerx-1;
            nextblock.x[1]=centerx;
            nextblock.x[2]=centerx;
            nextblock.x[3]=centerx+1;
            nextblock.y[0]=-2;
            nextblock.y[1]=-2;
            nextblock.y[2]=-1;
            nextblock.y[3]=-1;
            nextblock.centerX=centerx;
            nextblock.centerY=-2;
            nextblock.blockid=4;
            break;

        case 5:
        // ##
        //##
            nextblock.x[0]=centerx;
            nextblock.x[1]=centerx+1;
            nextblock.x[2]=centerx-1;
            nextblock.x[3]=centerx;
            nextblock.y[0]=-2;
            nextblock.y[1]=-2;
            nextblock.y[2]=-1;
            nextblock.y[3]=-1;
            nextblock.centerX=centerx;
            nextblock.centerY=-2;
            nextblock.blockid=5;
            break;

        case 6:
        // #
        //###
            nextblock.x[0]=centerx;
            nextblock.x[1]=centerx-1;
            nextblock.x[2]=centerx;
            nextblock.x[3]=centerx+1;
            nextblock.y[0]=-2;
            nextblock.y[1]=-1;
            nextblock.y[2]=-1;
            nextblock.y[3]=-1;
            nextblock.centerX=centerx;
            nextblock.centerY=-1;
            nextblock.blockid=6;
        default:
            break;
    }
}


//把方块的信息更新到地图
void T::blocktobox()
{
    for(int i=0;i<COUNT;i++)
    {
        int x=block.x[i];
        int y=block.y[i];
        if(y>=0)//若方块未从地图上方落下,不刷新
        {
            box[x][y]=1;
        }
    }
}


int T::getfullline()//找到被填满的行
{
     for(int j=1;j<MAPY;j++)
     {
         bool judge=true;
         for(int k=0;k<MAPX;k++)
         {
             if(box[k][j]==0)
             {
                 judge=false;
                 break; //只要该行有一个空位则跳到下一行检测
             }
         }
         if(judge)
             return j;
     }
     return -1; //若无填满的整行则返回-1
}


bool T::clearcondition()    //消去整行的特殊条件
{
    for(int i=0;i<MAPX-1;i++)   //对于任意一列，一旦发现其右边一列的方块高度高于它，则不能消除填满的整行
    {
        for(int j=0;j<MAPY;j++)     //从上往下遍历
        {
            if(j>1&&box[i][j-1]==1&&box[i+1][j-1]==0)   //如果先前已经发现右边不高于左边，跳出循环检测下一列
                break;
            if(j>1&&box[i][j-1]==1&&box[i+1][j-1]==1)
                break;
            if(box[i][j]==0&&box[i+1][j]==1)    //从上往下遍历，如果先出现了左边无块，右边有块的情况，直接判为不能消行
                return false;
        }
    }
    return true;
}



