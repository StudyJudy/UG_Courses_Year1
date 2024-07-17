#include "widget.h"
#include "ui_widget.h"
#include<time.h>
#include <QMessageBox>
#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
#include <QTime>
#include <QTimer>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //调整窗口尺寸布局
this->setFixedSize(QSize(750,1000));
    //初始化游戏
    InitGame();
 connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(StartGame()));
}

Widget::~Widget()
{
    delete ui;
}
void Widget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Up:
        BlockMove(UP);
        break;
    case Qt::Key_Down:
        BlockMove(DOWN);
        break;
    case Qt::Key_Left:
        BlockMove(LEFT);
        break;
    case Qt::Key_Right:
        BlockMove(RIGHT);
        break;
    case Qt::Key_Space:
        BlockMove(SPACE);
        break;
    default:
        break;
    }
}
int a;
void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //外墙
    painter.setPen(Qt::black);
    painter.setBrush(Qt::gray);
    painter.drawRect(10,160,620,800);
    //内墙
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawRect(20,170,600,780);

    //设置背景
    image1.load(":/背景图片/1.jpg");
    image2.load(":/背景图片/2.jpg");
    image3.load(":/背景图片/3.jpg");
    image4.load(":/背景图片/4.jpg");
    image5.load(":/背景图片/5.jpg");
    image6.load(":/背景图片/6.jpg");
    image7.load(":/背景图片/7.jpg");
    image8.load(":/背景图片/8.jpg");
    image9.load(":/背景图片/9.jpg");
    image10.load(":/背景图片/10.jpg");
    if(Score>=0&&Score<=20)
    {
         painter.drawPixmap(20,170,600,780,image1);
    }
    else if(Score>20&&Score<=40)
    {
        painter.drawPixmap(20,170,600,780,image2);
    }
      else if(Score>40&&Score<=60)
    {
         painter.drawPixmap(20,170,600,780,image3);
    }
    else if(Score>60&&Score<=80)
    {
         painter.drawPixmap(20,170,600,780,image4);
    }
    else if(Score>80&&Score<=100)
    {
         painter.drawPixmap(20,170,600,780,image5);
    }
    else if(Score>100&&Score<=120)
    {
         painter.drawPixmap(20,170,600,780,image6);
    }
    else if(Score>120&&Score<=140)
    {
         painter.drawPixmap(20,170,600,780,image7);
    }
    else if(Score>140&&Score<=160)
    {
         painter.drawPixmap(20,170,600,780,image8);
    }
    else if(Score>160&&Score<=180)
    {
         painter.drawPixmap(20,170,600,780,image9);
    }
    else
    {
         painter.drawPixmap(20,170,600,780,image10);
    }
    //画格子
    painter.setPen(Qt::gray);
    for(int i=6;i<=33;i++)
    {
        painter.drawLine(20,i*30-10,630,i*30-10);
    }
    for(int i=0;i<=20;i++)
    {
        painter.drawLine(i*30+20,170,i*30+20,960);
    }
    //画方块
    painter.setPen(Qt::black);
    for(int i=0;i<Row;i++)
    for(int j=0;j<Column;j++)
        {
            //绘制活动方块
            if(area[i][j]==1)
            {
                switch(a)
                {
                case 1:
                case 14:
                painter.setBrush(QBrush(QColor(190,180,255),Qt::SolidPattern));
                painter.drawRect(j*Block_size+Margin,i*Block_size+Margin,Block_size,Block_size);
                    break;
                case 2:
                case 13:
                    painter.setBrush(QBrush(QColor(170,204,255),Qt::SolidPattern));
                    painter.drawRect(j*Block_size+Margin,i*Block_size+Margin,Block_size,Block_size);
                    break;
                case 3:
                case 12:
                    painter.setBrush(QBrush(QColor(252,205,255),Qt::SolidPattern));
                    painter.drawRect(j*Block_size+Margin,i*Block_size+Margin,Block_size,Block_size);
                    break;
                case 4:
                case 11:
                    painter.setBrush(QBrush(QColor(255,228,89),Qt::SolidPattern));
                    painter.drawRect(j*Block_size+Margin,i*Block_size+Margin,Block_size,Block_size);
                    break;
                case 5:
                case 10:
                    painter.setBrush(QBrush(QColor(196,232,117),Qt::SolidPattern));
                    painter.drawRect(j*Block_size+Margin,i*Block_size+Margin,Block_size,Block_size);
                    break;
                case 6:
                case 9:
                    painter.setBrush(QBrush(QColor(234,216,239),Qt::SolidPattern));
                    painter.drawRect(j*Block_size+Margin,i*Block_size+Margin,Block_size,Block_size);
                    break;
                case 7:
                case 8:
                    painter.setBrush(QBrush(QColor(203,197,12),Qt::SolidPattern));
                    painter.drawRect(j*Block_size+Margin,i*Block_size+Margin,Block_size,Block_size);
                    break;
                default:
                    painter.setBrush(QBrush(QColor(255,228,89),Qt::SolidPattern));
                    painter.drawRect(j*Block_size+Margin,i*Block_size+Margin,Block_size,Block_size);
                    break;
                }
            }
            //绘制稳定方块
                else if(area[i][j]==2)
                {
                    painter.setBrush(QBrush(QColor(210,210,210),Qt::SolidPattern));
                    painter.drawRect(j*Block_size+Margin,i*Block_size+Margin,Block_size,Block_size);
                }
           }

    //绘制得分
    painter.setPen(Qt::white);
    painter.setBrush(QColor(170,204,255));
    painter.drawRect(420,100,100,48);
    painter.setFont(QFont("Comic Sans MS",12));
    painter.drawText(QRect(420,100,100,48),Qt::AlignCenter,QString::number(Score));
     }

  //初始化游戏
void Widget::InitGame()
{
    for(int i=0;i<Row;i++)
        for(int j=0;j<Column;j++)
        {
            area[i][j]=0;
        }
    speed_ms=1000;
    refresh_ms=20;
    srand(time(0));
    Score=0;
}

void Widget::StartGame()
{
    gamestatus=GameStatus::RUNNING;
    timerstart=startTimer(speed_ms);
    timerrefresh=startTimer(refresh_ms);
    //产生初始下一个方块
    int block_id=rand()%14;
    CreateBlock(nextshape,block_id);
    ResetBlock();
}
//产生方块
void Widget::ResetBlock()
{
   //产生当前方块
    Block_cpy(currshape,nextshape);
    GetBorder(currshape,currborder);
    //产生下一个方块
    int block_id=a=rand()%14;
    CreateBlock(nextshape,block_id);
    //设置初始方块坐标
   Point Firstpoint;
   Firstpoint.pointy=4;
   Firstpoint.pointx=Column/2-3;
   currpoint=Firstpoint;
}
//画14种基本方块
//田字形(2*2)
int shape1[4][4]=
{
    {0,0,0,0},
    {0,1,1,0},
    {0,1,1,0},
    {0,0,0,0}
};
//田字形（3*3）
int shape2[4][4]=
{
    {1,1,1,0},
    {1,1,1,0},
    {1,1,1,0},
    {0,0,0,0}
};
//田字形(4*4)
int shape3[4][4]=
{
    {1,1,1,1},
    {1,1,1,1},
    {1,1,1,1},
    {1,1,1,1}
};
//4竖
int shape4[4][4]=
{
    {0,1,0,0},
    {0,1,0,0},
    {0,1,0,0},
    {0,1,0,0}
};
//3竖
int shape5[4][4]=
{
    {0,1,0,0},
    {0,1,0,0},
    {0,1,0,0},
    {0,0,0,0}
};
//2竖
int shape6[4][4]=
{
    {0,0,0,0},
    {0,1,0,0},
    {0,1,0,0},
    {0,0,0,0}
};
//1格
int shape7[4][4]=
{
    {0,1,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
};
//凸
int shape8[4][4]=
{
    {0,0,1,0},
    {0,1,1,1},
    {0,0,0,0},
    {0,0,0,0}
};
//左L（3*2）
int shape9[4][4]=
{
    {0,0,1,0},
    {0,0,1,0},
    {0,1,1,0},
    {0,0,0,0}
};
//右L（3*2）
int shape10[4][4]=
{
    {0,0,1,0},
    {0,0,1,0},
    {0,0,1,1},
    {0,0,0,0}
};
//左L（3*3）
int shape11[4][4]=
{
    {0,0,1,0},
    {0,0,1,0},
    {1,1,1,0},
    {0,0,0,0}
};
//右L（3*3）
int shape12[4][4]=
{
    {0,1,0,0},
    {0,1,0,0},
    {0,1,1,1},
    {0,0,0,0}
};
//右S
int shape13[4][4]=
{
    {0,1,0,0},
    {0,1,1,0},
    {0,0,1,0},
    {0,0,0,0}
};
//左S
int shape14[4][4]=
{
    {0,0,1,0},
    {0,1,1,0},
    {0,1,0,0},
    {0,0,0,0}
};

//拷贝方块图案
void Widget::Block_cpy(int blocknew[4][4],int blockready[4][4])
{
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            blocknew[i][j]=blockready[i][j];
}

//产生方块形状
void Widget::CreateBlock (int block[4][4],int block_id)
{
    switch(block_id)
    {
    case 0:
        Block_cpy(block,shape1);
        break;
    case 1:
        Block_cpy(block,shape2);
        break;
    case 2:
        Block_cpy(block,shape3);
        break;
    case 3:
        Block_cpy(block,shape4);
        break;
    case 4:
        Block_cpy(block,shape5);
        break;
    case 5:
        Block_cpy(block,shape6);
        break;
    case 6:
        Block_cpy(block,shape7);
        break;
    case 7:
        Block_cpy(block,shape8);
        break;
    case 8:
        Block_cpy(block,shape9);
        break;
    case 9:
        Block_cpy(block,shape10);
        break;
    case 10:
        Block_cpy(block,shape11);
        break;
    case 11:
        Block_cpy(block,shape12);
        break;
    case 12:
        Block_cpy(block,shape13);
        break;
    case 13:
        Block_cpy(block,shape14);
        break;
    default:
        break;
    }
}
//计算边界
void Widget:: GetBorder(int block[4][4],Border &border)
{
    //上
    for(int i=3;i>=0;i--)
    {
        for(int j=0;j<4;j++)
        {
            if(block[i][j]==1)
            {
                border.upbound=i;
                break;
            }
        }
    }
    //下
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(block[i][j]==1)
            {
                border.downbound=i;
                break;
            }
        }
    }
    //左
    for(int j=3;j>=0;j--)
    {
        for(int i=0;i<4;i++)
        {
            if(block[i][j]==1)
            {
                border.leftbound=j;
                break;
            }
        }
    }
    //右
    for(int j=0;j<4;j++)
    {
        for(int i=0;i<4;i++)
        {
            if(block[i][j]==1)
            {
                border.rightbound=j;
                break;
            }
        }
    }
}
//稳定方块
 void Widget:: FallenBlock(int x,int y)
  {
      for(int i=currborder.upbound;i<=currborder.downbound;i++)
      {
          for(int j=currborder.leftbound;j<=currborder.rightbound;j++)
          {
              if(currshape[i][j]==1)
              {
                  area[y+i][x+j]=2;
              }
          }
      }
  }
  //方块旋转（逆时针90度）
 void Widget::BlockRotate(int block[4][4])
 {
     int temp[4][4];
     for(int i=0;i<4;i++)
         for(int j=0;j<4;j++)
             temp[3-j][i]=block[i][j];
     for(int i=0;i<4;i++)
         for(int j=0;j<4;j++)
             block[i][j]=temp[i][j];
 }

  void Widget::GameOver()
  {
          //游戏结束停止计时器
          killTimer( timerstart);
          killTimer(timerrefresh);
          QMessageBox::information(this,"failed","game over");
  }

  //判断碰撞
     bool Widget::Crash(int x,int y,Direction direction)
     {
         int temp[4][4];
         Block_cpy(temp, currshape);
         Border tempborder;
         GetBorder(temp,tempborder);
         switch(direction)
         {
         case UP:
             BlockRotate(temp);
             GetBorder(temp,tempborder);
             break;
         case DOWN:
             y+=1;
             break;
          case LEFT:
             x-=1;
             break;
         case RIGHT:
             x+=1;
             break;
         default:
             break;
         }
         for(int i=tempborder.upbound;i<=tempborder.downbound;i++)
             for(int j=tempborder.leftbound;j<=tempborder.rightbound;j++)
                 if(((area[y+i][x+j]==2)&&(temp[i][j]==1))||x+tempborder.leftbound<0||x+tempborder.rightbound>Column-1)
                     return true;
         return false;
     }
void Widget::BlockMove(Direction direction)
{
    switch (direction)
    {
    case UP:
        if(Crash(currpoint.pointx,currpoint.pointy,UP))
            break;
        //逆时针旋转90度
        BlockRotate(currshape);
        //i和j从0到4重新设置方块
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                area[currpoint.pointy+i][currpoint.pointx+j]=currshape[i][j];
        //重新计算边界
        GetBorder(currshape,currborder);
        break;
    case DOWN:
        //方块到达边界则不再移动
        if(currpoint.pointy+currborder.downbound==Row-1)
        {
            FallenBlock(currpoint.pointx,currpoint.pointy);
            ResetBlock();
            break;
        }
        //碰撞检测，只计算上下左右边界，先尝试走一格，如果碰撞则稳定方块后跳出
        if(Crash(currpoint.pointx,currpoint.pointy,DOWN))
        {
            //只有最终不能下落才转成稳定方块
            FallenBlock(currpoint.pointx,currpoint.pointy);
            ResetBlock();
            break;
        }
        //恢复方块上场景,为了清除移动过程中的方块残留
        for(int j=currborder.leftbound;j<=currborder.rightbound;j++)
            area[currpoint.pointy][currpoint.pointx+j]=0;
        //没有碰撞则下落一格
        currpoint.pointy+=1;
        //方块下降一格，拷贝到场景,注意左右边界
        for(int i=0;i<4;i++) //必须是0到4而不是边界索引，考虑到旋转后边界重新计算
            for(int j=currborder.leftbound;j<=currborder.rightbound;j++)
                if(currpoint.pointx+i<=Row-1&&area[currpoint.pointy+i][currpoint.pointx+j]!=2) //注意场景数组不越界,而且不会擦出稳定的方块
                    area[currpoint.pointy+i][currpoint.pointx+j]=currshape[i][j];
        break;
    case LEFT:
        //到左边界或者碰撞不再往左
        if(currpoint.pointx+currborder.leftbound==0||Crash(currpoint.pointx,currpoint.pointy,LEFT))
            break;
        //恢复方块右场景
        for(int i=currborder.upbound;i<=currborder.downbound;i++)
            area[currpoint.pointy+i][currpoint.pointx+3]=0;
       currpoint.pointx-=1;
        //方块左移一格，拷贝到场景
        for(int i=currborder.upbound;i<=currborder.downbound;i++)
            for(int j=0;j<4;j++)
                if(currpoint.pointx+j>=0&&area[currpoint.pointy+i][currpoint.pointx+j]!=2) //注意场景数组不越界
                   area[currpoint.pointy+i][currpoint.pointx+j]=currshape[i][j];
        break;
    case RIGHT:
        if(currpoint.pointx+currborder.rightbound==Column-1||Crash(currpoint.pointx,currpoint.pointy,RIGHT))
            break;
        //恢复方块左场景
        for(int i=currborder.upbound;i<=currborder.downbound;i++)
            area[currpoint.pointy+i][currpoint.pointx]=0;
       currpoint.pointx+=1;
        //方块右移一格，拷贝到场景
        for(int i=currborder.upbound;i<=currborder.downbound;i++)
            for(int j=0;j<4;j++)
                if(currpoint.pointx+j<=Column-1&&area[currpoint.pointy+i][currpoint.pointx+j]!=2)
                    area[currpoint.pointy+i][currpoint.pointx+j]=currshape[i][j];
        break;
    case SPACE: //一次到底
        //一格一格下移
      while(currpoint.pointy+currborder.downbound<Row-1&&!Crash(currpoint.pointx,currpoint.pointy,DOWN))
        {
            //恢复方块上场景
            for(int j=currborder.leftbound;j<=currborder.rightbound;j++)
                area[currpoint.pointy][currpoint.pointx+j]=0;
            //没有碰撞则下落一格
           currpoint.pointy+=1;
            //方块下降一格，拷贝到场景,注意左右边界
            for(int i=0;i<4;i++)
                for(int j=currborder.leftbound;j<=currborder.rightbound;j++)
                    if(currpoint.pointy+i<=Row-1&&area[currpoint.pointy+i][currpoint.pointx+j]!=2)
                        area[currpoint.pointy+i][currpoint.pointx+j]=currshape[i][j];
        }
       FallenBlock(currpoint.pointx,currpoint.pointy);
        ResetBlock();
        break;
    default:
        break;
    }
    //处理消行，整个场景上面的行依次下移
    int i=Row-1;
    int line_count=0; //记消行数
    while(i>=1)
    {
        bool flag=true;
        for(int j=0;j<Column;j++)
            if(area[i][j]==0)
            {
                flag=false;
                i--;
                break;
            }
        if(flag)
        {
            for(int k=i;k>=1;k--)
                for(int j=0;j<Column;j++)
                    area[k][j]=area[k-1][j];
            line_count++;//每次增加消行的行数
        }
    }
    Score+=line_count*10; //得分
    //判断游戏是否结束
    for(int j=0;j<Column;j++)
        if(area[4][j]==2) //最顶端也有稳定方块
            GameOver();
}

void Widget::timerEvent(QTimerEvent *event)
{
    //方块下落
    if(event->timerId()==timerstart)
        BlockMove(DOWN);
    //刷新画面
    if(event->timerId()==timerrefresh)
        update();
}

