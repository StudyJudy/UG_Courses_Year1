#include "tetrishomework.h"
#include "ui_tetrishomework.h"
#include<time.h>
#include <QMessageBox>
#include <QDebug>
#include <QPainter>
#include <QKeyEvent>

void Widget::paintevent(QPaintEvent* event)//update()或程序第一次启动时自动执行，用于画图
{
    QPainter painter(this);
    //画游戏背景
    //外墙
    painter.setPen(Qt::white);
    painter.setBrush(Qt::yellow);
    painter.drawRect(10,30,610,760);
    //内墙
    painter.setPen(Qt::blue);
    painter.setBrush(Qt::gray);
    painter.drawRect(20,40,600,750);
    //画格子
    painter.setPen(Qt::gray);
    for(int i=0;i<=25;i++)
    {
        painter.drawLine(20,i*30+40,610,i*30+40);
    }
    for(int i=0;i<=20;i++)
    {
        painter.drawLine(i*30+20,40,i*30+20,760);
    }

//在侧边画当前下落方块的下一个方块
   painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
   for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(nextshape[i][j]==1)
            {
                painter.drawRect(Margin*3+Column*Block_size+j*Block_size,Margin+i*Block_size+60,Block_size,Block_size);
            }
        }
    }
   //绘制得分
   painter.setPen(Qt::black);
   painter.setFont(QFont("Arial",10));
   painter.drawText(QRect(Margin*3+Column*Block_size,Margin*2+4*Block_size+20,Block_size*4, Block_size*4),Qt::AlignCenter,"score: "+QString::number(Score));

   for(int i=0;i<Row;i++)
    {
       //画下落中的方块,0表示空，1表示活动的方块，2表示稳定的方块
      for (int j=0;j<Column ;j++)
      {
          if(area[i][j]==1)
          {
       painter.setBrush(QBrush(Qt::green,Qt::SolidPattern));
       painter.drawRect(j*Block_size+Margin,i*Block_size+Margin+20,Block_size,Block_size);
          }
          //下落后的方块
          else if(area[i][j]==2)
          {
              painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
               painter.drawRect(j*Block_size+Margin,i*Block_size+Margin+20,Block_size,Block_size);
          }
      }
 }
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
  void Widget:: Block_cpy(int blocknew[4][4],int blockready[4][4])
   {
       for(int i=0;i<Row;i++)
       {
           for(int j=0;j<Column;j++)
           {
               blocknew[i][j]=blockready[i][j];
           }
       }
   }
  //初始化游戏
void Widget::InitGame()
   {
     for(int i=0;i<Row;i++)
    {
        for(int j=0;i<Column;i++)
       {
        area[i][j]=0;
       }
    }
    speed_ms=800;
    refresh_ms=30;
    srand(time(0));
    Score=0;
    StartGame();
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
    int block_id=rand()%14;
    CreateBlock(nextshape,block_id);
    //设置初始方块坐标，左上角为头
   Point Firstpoint;
   Firstpoint.pointx=Column/2-2;
   Firstpoint.pointy=0;
   currpoint=Firstpoint;
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
    int i=0,j=0;
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
      int curr_block[4][4];
      for(int i=0;i<4;i++)
      {
          for(int j=0;j<4;j++)
          {
              curr_block[3-j][i]=block[i][j];
          }
      }
      for(int i=0;i<4;i++)
      {
          for(int j=0;j<4;j++)
          {
              block[3-j][i]=curr_block[i][j];
          }
      }
  }
// 暂停或结束游戏
  void Widget::PauseOrContinueGame()
  {
      if(gamestatus==GameStatus::RUNNING)
      {
          gamestatus=GameStatus::PAUSE;
      killTimer(timerstart);
      killTimer(timerrefresh);
      }
      else
      {
          gamestatus=GameStatus::RUNNING;
         timerstart=startTimer(speed_ms);//开启游戏timer
         timerrefresh=startTimer(refresh_ms);
         //产生初始下一个方块
         int block_id=rand()%14;
         CreateBlock(nextshape,block_id);
         ResetBlock();//产生方块
      }
  }

  void Widget::GameOver()
  {
      gamestatus=GameStatus::STOP;
      //停止计时器
      killTimer(timerstart);
      killTimer(timerrefresh);
      QMessageBox::information(this,"failed","gameover");
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
         {
             for(int j=tempborder.leftbound;j<=tempborder.rightbound;j++)
             {
                 if((area[y+i][x+j]==2&&temp[i][j]==1)||x+tempborder.leftbound<0||x+tempborder.rightbound>Column-1)
                 {
                     return true;
                 }
             }
         }
         return false;
     }


void Widget::BlockMove(Direction direction)
{
    switch(direction)
    {
    case UP:
        //如果碰撞
        if(Crash(currpoint.pointx,currpoint.pointy,UP))
        {
            break;
        }
        //逆时针90度
    BlockRotate(currshape);
    //拷贝到场景
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
           area[currpoint.pointy+i][currpoint.pointx+j]=currshape[i][j];
        }
    }
    //重新计算边界
    GetBorder(currshape,currborder);
        break;
    case DOWN:
        if(currpoint.pointy+currborder.downbound==Row-1)
        {
            FallenBlock(currpoint.pointx,currpoint.pointy);
            ResetBlock();
            break;
        }
    //如果碰撞
        if(Crash(currpoint.pointx,currpoint.pointy,DOWN))
        {
            //到底了，不能下落
            FallenBlock(currpoint.pointx,currpoint.pointy);
            ResetBlock();
            break;
        }
        //恢复上场景，清除残留方块
        for(int j=currborder.leftbound;j<=currborder.rightbound;j++)
        {
            area[currpoint.pointy][currpoint.pointx+j]=0;
        }
        //下落一格
        currpoint.pointy+=1;
        //拷贝到场景
        for(int i=0;i<4;i++)
        {
            for(int j=currborder.leftbound;j<=currborder.rightbound;j++)
            {
                if(currpoint.pointy+i<=Row-1&&area[currpoint.pointy+i][currpoint.pointx+j]!=2)
                {
                    area[currpoint.pointy+i][currpoint.pointx+j]=currshape[i][j];
                }
            }
        }
        break;
    case LEFT:
        //到左边界或者碰撞不再往左
        if(currpoint.pointx+currborder.leftbound==0||Crash(currpoint.pointx,currpoint.pointy,LEFT))
        {
            break;
        }
        //恢复右场景，清除残留方块
        for(int i=currborder.upbound;i<=currborder.downbound;i++)
        {
            area[currpoint.pointy+i][currpoint.pointx+3]=0;
        }
        currpoint.pointx-=1;
        //拷贝到场景
        for(int i=currborder.upbound;i<=currborder.downbound;i++)
        {
            for(int j=0;j<4;j++)
            {
                if(currpoint.pointx+j>=0&&area[currpoint.pointy+i][currpoint.pointx+j]!=2)
                {
                    area[currpoint.pointy+i][currpoint.pointx+j]=currshape[i][j];
                }
            }
        }
        break;
    case RIGHT:
        //到右边界或者碰撞不再往右
        if(currpoint.pointx+currborder.rightbound==Column-1||Crash(currpoint.pointx,currpoint.pointy,RIGHT))
        {
            break;
        }
        //恢复左场景，清除残留方块
        for(int i=currborder.upbound;i<=currborder.downbound;i++)
        {
            area[currpoint.pointy+i][currpoint.pointx]=0;
        }
        currpoint.pointx+=1;
        //拷贝到场景
        for(int i=currborder.upbound;i<=currborder.downbound;i++)
        {
            for(int j=0;j<4;j++)
            {
                if(currpoint.pointx+j<=Column-1&&area[currpoint.pointy+i][currpoint.pointx+j]!=2)
                {
                    area[currpoint.pointy+i][currpoint.pointx+j]=currshape[i][j];
                }
            }
        }
        break;
    case SPACE:
        //一格一格下移，一次到底，直到下落不了
        while(currpoint.pointy+currborder.downbound<Row-1&&!Crash(currpoint.pointx,currpoint.pointy,DOWN))
        {
            for(int j=currborder.leftbound;j<=currborder.rightbound;j++)
            {
                //恢复上场景，清除残留方块
                area[currpoint.pointy][currpoint.pointx+j]=0;
            }
            currpoint.pointy+=1;
            //拷贝到场景
            for(int i=0;i<4;i++)
            {
                for(int j=currborder.leftbound;j<=currborder.rightbound;j++)
                {
                    if(currpoint.pointy+i<=Row-1&&area[currpoint.pointy+i][currpoint.pointx+j]!=2)
                    {
                      area[currpoint.pointy+i][currpoint.pointx+j]=currshape[i][j];
                    }
                }
            }
        }
        FallenBlock(currpoint.pointx,currpoint.pointy);
        ResetBlock();
        break;
    default:
        break;
   }
    //消行，下移一行
    int i=Row-1;
    int deletelinenum=0;//消行数
    while(i>=1)
    {
        bool flag=true;
        for(int j=0;j<Column;j++)
        {
            if(area[i][j]==0)
            {
                flag=false;
                i--;
                break;
            }
        }
        if(flag==true)
        {
            for(int k=i;k>=1;k--)
            {
                for(int j=0;j<Column;j++)
                {
                    area[k][j]=area[k-1][j];
                }
            }
        }
        deletelinenum+=1;
    }
   Score+=deletelinenum*10;
   //判断游戏是否结束
   for(int j=0;j<Column;j++)
   {
       if(area[0][j]==2)
       {
           GameOver();
       }
   }
}
void Widget::timerevent(QTimerEvent *event)
{
    //方块下落
    if(event->timerId()==timerstart)
    {
        BlockMove(DOWN);
    }
    //刷新
    if(event->timerId()==timerrefresh)
    {
        update();
    }
}

void Widget::keyevent(QKeyEvent *event)
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

