#include "tetrishomework.h"
#include "ui_tetrishomework.h"
#include<time.h>
#include <QMessageBox>
#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setGeometry(QRect(800,200,1010,1200));
    //调整窗口尺寸布局
    resize (Column*Block_size+Margin*4+4*Block_size,Row*Block_size+Margin*2);
    //初始化游戏
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    //画游戏背景
    //外墙
    painter.setPen(Qt::green);
    painter.setBrush(Qt::yellow);
    painter.drawRect(10,30,610,760);
    //内墙
    painter.setPen(Qt::blue);
    painter.setBrush(Qt::white);
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
    //画所有n种基本方块
    //田字形(2*2)
    int shape1[4][4];
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            shape1[i][j]=0;
        }
    }
    shape1[1][1]=shape1[1][2]=shape1[2][1]=shape1[2][2]=1;
    //田字形（3*3）
    int shape2[4][4];
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            shape2[i][j]=0;
        }
    }
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            shape2[i][j]=1;
        }
    }
    //田字形(4*4)
    int shape3[4][4];
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            shape3[i][j]=1;
        }
    }
    //4竖
    int shape4[4][4];
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            shape4[i][j]=0;
        }
    }
   shape4[0][1]=shape4[1][1]=shape4[2][1]=shape4[3][1]=1;
   //3竖
   int shape5[4][4];
   for(int i=0;i<4;i++)
   {
       for(int j=0;j<4;j++)
       {
           shape5[i][j]=0;
       }
   }
   shape5[0][1]=shape5[1][1]=shape5[2][1]=1;
   //2竖
   int shape6[4][4];
   for(int i=0;i<4;i++)
   {
       for(int j=0;j<4;j++)
       {
           shape6[i][j]=0;
       }
   }
   shape6[0][1]=shape6[1][1]=1;
   //1格
   int shape7[4][4];
   for(int i=0;i<4;i++)
   {
       for(int j=0;j<4;j++)
       {
           shape7[i][j]=0;
       }
   }
   shape7[0][1]=1;
   //凸
   int shape8[4][4];
   for(int i=0;i<4;i++)
   {
       for(int j=0;j<4;j++)
       {
           shape8[i][j]=0;
       }
   }
   shape8[0][2]=shape8[1][1]=shape8[1][2]=shape8[1][3]=1;
   //左L（3*2）
   int shape9[4][4];
   for(int i=0;i<4;i++)
   {
       for(int j=0;j<4;j++)
       {
           shape9[i][j]=0;
       }
   }
   shape9[0][2]=shape9[1][2]=shape9[2][2]=shape9[2][1]=1;
   //右L（3*2）
   int shape10[4][4];
   for(int i=0;i<4;i++)
   {
       for(int j=0;j<4;j++)
       {
           shape10[i][j]=0;
       }
   }
   shape10[0][2]=shape10[1][2]=shape10[2][2]=shape10[2][3]=1;
   //左L（3*3）
   int shape11[4][4];
   for(int i=0;i<4;i++)
   {
       for(int j=0;j<4;j++)
       {
           shape11[i][j]=0;
       }
   }
   shape11[0][2]=shape11[1][2]=shape11[2][2]=shape11[2][1]=shape11[2][0]=1;
   //右L（3*3）
   int shape12[4][4];
   for(int i=0;i<4;i++)
   {
       for(int j=0;j<4;j++)
       {
           shape12[i][j]=0;
       }
   }
   shape12[0][1]=shape12[1][1]=shape12[2][1]=shape12[2][2]=shape12[2][3]=1;
   //右S
   int shape13[4][4];
   for(int i=0;i<4;i++)
   {
       for(int j=0;j<4;j++)
       {
           shape13[i][j]=0;
       }
   }
   shape13[0][1]=shape13[1][1]=shape13[1][2]=shape13[2][2]=1;
   //左S
   int shape14[4][4];
   for(int i=0;i<4;i++)
   {
       for(int j=0;j<4;j++)
       {
           shape14[i][j]=0;
       }
   }
   shape14[0][2]=shape14[1][1]=shape14[1][2]=shape14[2][1]=1;
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

}
