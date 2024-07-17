#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <qpainter.h>
#include <QPixmap>
QT_BEGIN_NAMESPACE
const int Block_size=30;//单个方块单元的边长
const int Margin=20;//场景行距
const int Row=25;//场景行数
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
namespace Ui
{ class Widget; }
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
    int Score;//成绩
    void InitGame();//初始化
    void InitMenu();//初始化菜单
    void StartGame();//开始游戏
    void PauseOrContinueGame();//暂停或结束游戏
    volatile GameStatus gamestatus=GameStatus::STOP;
    int timerstart;//游戏开始计时器
    int timerrefresh;//刷新计时器
    int speed_ms;//下落时间间隔
    int refresh_ms;//刷新时间间隔
    void GameOver();//游戏结束
    int area[Row][Column];//场景区域
    void CreateBlock (int block[4][4],int block_id);//产生方块
    Point currpoint;//当前坐标
    int currshape[4][4];//当前方块形状
    int nextshape[4][4];//下一个方块形状
   void BlockMove(Direction direction);//方块变动
   void BlockRoate(int block[4][4]);//方块旋转
   void Block_cpy(int blocknew[4][4],int blockready[4][4]);//方块拷贝
   void ResetBlock();//产生方块
    void GetBorder(int block[4][4],Border &border);//计算边界
   void FallenBlock(int x,int y);//稳定方块
   Border currborder;//当前方块边界
    bool Crash(int x,int y,Direction direction);//判断是否会发生碰撞
   bool Fallen;//判断方块是否已经落地
public:
  explicit  Widget(QWidget *parent = nullptr);
     ~Widget();
    virtual void paintevent(QPaintEvent *event);//刷新
    virtual void timerevent(QTimerEvent *event);//定时器
    virtual void keyevent (QKeyEvent *event);// 键盘事件
  signals:
    public slots:
    void SlotPauseGame();
    void SlotStartGame();
    void SlotStopGame();
private:
    Ui::Widget *ui;
public:

};
#endif // WIDGET_H
