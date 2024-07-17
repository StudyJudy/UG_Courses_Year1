#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <qpainter.h>
#include <QPixmap>

QT_BEGIN_NAMESPACE
const int Block_size=30;//单个方块单元的边长
const int Margin=20;//场景行距
const int Row=31;//场景行数
const int Column=20;//场景列数
//方向
enum Direction
{
    DOWN,
    UP,
    LEFT,
    RIGHT,
    SPACE
};
//定义边界信息
class Border
{
public:
    int upbound;
    int downbound;
    int leftbound;
    int rightbound;
};
//坐标
class Point
{
public:
    int pointx;
    int pointy;
    //point(int x,int y):pointx(x),pointy(y);
};
QT_BEGIN_NAMESPACE
namespace Ui {class Widget;}
QT_END_NAMESPACE
class Widget : public QWidget
{
    Q_OBJECT
public:

    enum GameStatus
    {
        RUNNING,
        STOP,
        PAUSE
    };

    volatile GameStatus gamestatus=GameStatus::STOP;
    void InitGame();//初始化 0
    void StartGame();//开始游戏0
    //void PauseOrContinueGame();//暂停或结束游戏
    void GameOver();//游戏结束0
    void CreateBlock (int block[4][4],int block_id);//产生方块0
   void BlockMove(Direction direction);//方块变动0
   void BlockRotate(int block[4][4]);//方块旋转0
  void Block_cpy(int blocknew[4][4],int blockready[4][4]);//方块拷贝
   void ResetBlock();//产生新方块0
    void GetBorder(int block[4][4],Border &border);//计算边界0
   void FallenBlock(int x,int y);//稳定方块0
    bool Crash(int x,int y,Direction direction);//判断是否会发生碰撞0
public:
   explicit Widget(QWidget *parent = 0);
     ~Widget();
    virtual void paintEvent(QPaintEvent *event);//刷新
    virtual void timerEvent(QTimerEvent *event);//定时器
   virtual void keyPressEvent (QKeyEvent *event);// 键盘事件
     QString getRandomColor();
     void slotOnTimeOut();
private:
    Ui::Widget *ui;
private:
     int area[Row][Column];//场景区域0
         Point currpoint;//当前坐标0
          int currshape[4][4];//当前方块形状0
            int nextshape[4][4];//下一个方块形状0
          Border currborder;//当前方块边界0
             bool Fallen;//判断方块是否已经落地0
                 int Score;//成绩0
                 int timerstart;//游戏开始计时器0
                 int timerrefresh;//刷新计时器0
                 int speed_ms;//下落时间间隔0
                 int refresh_ms;//刷新时间间隔0
};
#endif // WIDGET_H
