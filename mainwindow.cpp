#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)/*,
    ui(new Ui::MainWindow)*/
{
    //初始化对象
    this->gamebox=new Box;
    this->gamenextbox=new Nextbox;

    this->nextblocklabel=new QLabel(tr("下一个方块："));
    this->controllabel=new QLabel(tr("控制键位："));
    this->w_controllabel=new QLabel(tr("W--旋转"));
    this->a_controllabel=new QLabel(tr("A--左移"));
    this->s_controllabel=new QLabel(tr("S--下移"));
    this->d_controllabel=new QLabel(tr("D--右移"));
    this->p_controllabel=new QLabel(tr("P--暂停"));
    this->b_controllabel=new QLabel(tr("B--开始"));
    this->r_controllabel=new QLabel(tr("R--重新开始"));

    this->scorelabel=new QLabel(tr("0"));
    this->scoretitle=new QLabel(tr("得分："));

    //设置窗口大小
    this->mainlayout=new QGridLayout;
    this->mainlayout->setHorizontalSpacing(20);
    this->mainlayout->setVerticalSpacing(25);
    this->mainlayout->setAlignment(Qt::AlignCenter);//

    this->mainlayout->addWidget(gamebox,0,0,13,1);
    this->mainlayout->addWidget(nextblocklabel,0,1);
    this->mainlayout->addWidget(gamenextbox,1,1,1,2);
    this->mainlayout->addWidget(scoretitle,2,1);
    this->mainlayout->addWidget(scorelabel,2,2);
    this->mainlayout->addWidget(controllabel,4,1);
    this->mainlayout->addWidget(w_controllabel,5,1);
    this->mainlayout->addWidget(a_controllabel,5,2);
    this->mainlayout->addWidget(s_controllabel,6,1);
    this->mainlayout->addWidget(d_controllabel,6,2);
    this->mainlayout->addWidget(p_controllabel,7,1);
    this->mainlayout->addWidget(b_controllabel,7,2);
    this->mainlayout->addWidget(r_controllabel,8,1);

    QWidget *widget = new QWidget(this);
    widget->setLayout(mainlayout);
    setCentralWidget(widget);

    //设置窗口背景
    setPalette(Qt::black);
    QDesktopWidget *desktopWidget = QApplication::desktop();//窗口居中
    int w = (desktopWidget->width() - this->width()) / 2;
    int h = 5;
    move(w, h);

    this->status=OFF;
    gamenextbox->updatenexttetris(tetris);
    setWindowTitle(tr("TETRIS_GAME OFF"));

    timer=new QTimer(this);

    //ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    //delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //w a s d 的移动
    if(event->key()==Qt::Key_W)
    {
        if(tetris.rotatable())
        {
            if(this->status==ON)
                gamebox->updatetetris(tetris);
        }
    }

    else if(event->key()==Qt::Key_A)
    {
        if(this->status==ON)
        {
            if(tetris.goleft())
            {
                //tetris.move(-1,0);
                gamebox->updatetetris(tetris);
            }
        }
    }

    else if(event->key()==Qt::Key_S)
    {
        if(this->status==ON)
        {
            if(tetris.godown())//godown返回false即游戏结束
            {
                //tetris.move(0,1);
                gamebox->updatetetris(tetris);
                gamenextbox->updatenexttetris(tetris);
                showscore();
            }
            else
            {
                this->timer->stop();
                this->status=OVER;
                setWindowTitle(tr("TETRIS_GAME OVER"));
                QString str;
                str+=QString("Game Over!!!      \nHesitation is defeat!     \nYour Score is  %1\n").arg(tetris.score); //犹豫就会败北
                QMessageBox::information(this,tr("Game Over"),str);
            }
        }
    }

    else if(event->key()==Qt::Key_D)
    {
        if(this->status==ON)
        {
            if(tetris.goright())
            {
                tetris.move(1,0);
                gamebox->updatetetris(tetris);
            }
        }
    }

    //b键开始游戏
    else if(event->key()==Qt::Key_B)
    {
        if(this->status==OFF)//从未开始游戏时按开始键
        {
            //初始化
            tetris.newblock();
            gamebox->updatetetris(tetris);
            gamenextbox->updatenexttetris(tetris);
            showscore();
            this->status=ON;
            timer->start(500);
            //
            connect(timer,SIGNAL(timeout()),this,SLOT(timing()));
            timer->start(1000);
            setWindowTitle(tr("TETRIS_GAME ON"));
        }

        if(this->status==PAUSE)//从暂停时按开始键
        {
            timer->start(50);
            this->status=ON;
            //
            connect(timer,SIGNAL(timeout()),this,SLOT(timing()));
            timer->start(1000);
            setWindowTitle(tr("TETRIS_GAME ON"));
        }

        if(this->status==OVER)//游戏结束后按下开始键
        {
            tetris.restart();//先清空地图,再初始化
            tetris.newblock();
            gamebox->updatetetris(tetris);
            gamenextbox->updatenexttetris(tetris);
            showscore();
            this->status=ON;
            timer->start(50);
            //
            connect(timer,SIGNAL(timeout()),this,SLOT(timing()));
            timer->start(1000);
            setWindowTitle(tr("TETRIS_GAME ON"));
        }
    }

    //P键暂停
    else if(event->key()==Qt::Key_P)
    {
        if(this->status==ON)//游戏进行时才可以暂停
        {
            this->timer->stop();
            this->status=PAUSE;
            setWindowTitle(tr("TETRIS_GAME PAUSE"));
        }
    }

    //R键重新开始
    else if(event->key()==Qt::Key_R)
    {
        this->timer->stop();
        tetris.restart();
        tetris.newblock();
        gamebox->updatetetris(tetris);
        gamenextbox->updatenexttetris(tetris);
        showscore();

        //从未开始状态进入游戏
        this->status=OFF;
        setWindowTitle(tr("TETRIS_GAME OFF"));
    }
}


void MainWindow::changeEvent(QEvent *event)
{
    if(event->type()!=QEvent::WindowStateChange)
        return;
    if(windowState()==Qt::WindowMinimized)  //若游戏窗口最小化则停止计时
        this->timer->stop();
}


void MainWindow::timing()
{
    if(tetris.godown())
    {
        gamebox->updatetetris(tetris);
        gamenextbox->updatenexttetris(tetris);
        showscore();
    }
    else
    {
        this->timer->stop();
        this->status=OVER;
        setWindowTitle(tr("TETRIS_GAME OVER"));
        QString str;
        str+=QString("Game Over!!!      \nHesitation is defeat!     \nYour Score is  %1\n").arg(tetris.score); //
        QMessageBox::information(this,tr("Game Over"),str);
    }
}


void MainWindow::showscore()
{
    QString scorestring;
    int score=tetris.getscore();
    scorestring+=QString("%1").arg(score);
    this->scorelabel->setText(scorestring);
}




