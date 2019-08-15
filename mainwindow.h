#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QEvent>
#include<QPainter>
#include<QPaintEvent>
#include<QColor>
#include<QBrush>
#include<QPen>
#include<QTime>
#include<QTimer>
#include<QKeyEvent>
#include<QGridLayout>
#include<QLabel>
#include<QMessageBox>
#include<QApplication>
#include<QDesktopWidget>
#include<QWidget>
#include<QString>

#include"blocks.h"
#include"box.h"
#include"nextbox.h"

#define ON 0
#define PAUSE 1
#define OFF 2
#define OVER 3

/*namespace Ui {
class MainWindow;
}*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event);//键盘控制
    void changeEvent(QEvent *event);
    void showscore();//刷新并显示分数

public slots:
    void timing();

private:
    //Ui::MainWindow *ui;
    int status; //游戏状态，对应前面的define
    T tetris;
    QTimer *timer;
    Box *gamebox;
    Nextbox *gamenextbox; //显示下一个块的窗口
    QLabel *nextblocklabel; //
    QLabel *controllabel; //
    QLabel *scorelabel;
    QLabel *scoretitle;

    //设置各个控制按键
    QLabel *w_controllabel;
    QLabel *a_controllabel;
    QLabel *s_controllabel;
    QLabel *d_controllabel;
    QLabel *p_controllabel; //pause
    QLabel *b_controllabel; //begin
    QLabel *r_controllabel; //restart

    QGridLayout *mainlayout;

};

#endif // MAINWINDOW_H
