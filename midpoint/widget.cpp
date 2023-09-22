#include "widget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWidget>
#include <QEvent>
#include <cmath>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{
}

void Widget::mousePressEvent(QMouseEvent* event){
    this->startPoint=event->pos();
}

void Widget::mouseMoveEvent(QMouseEvent* event){
    this->endPoint=event->pos();
    update();
}

void Widget::mouseReleaseEvent(QMouseEvent* event){
    this->endPoint=event->pos();
    update();
}

void Widget::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    QPoint st(startPoint), et(endPoint);
    int dx=et.x()-st.x();//x方向增量
    int dy=et.y()-st.y();//y方向增量
    int qd=dx*dy;//判断处理象限
    bool K=std::abs(dy)>std::abs(dx);//利用判别式的值判断以x为基准或以y为基准
    if(st.x()>et.x()){
        qSwap(st, et);
    }
    //假设直线方程为Ay+Bx+C=0
    int A=et.x()-st.x();
    int B=st.y()-et.y();
    if(qd>0){//一三象限

        if(K){//y的绝对增量大于x，则取y每加一定点
            int delta=B + 2 * A;
            int x=st.x();
            for(int y=st.y();y<=et.y();++y){
                painter.drawPoint(x,y);
                if(delta>=0){
                    x+=1;
                    delta+=A+B;
                }
                else{
                    x+=0;
                    delta+=A;
                }
            }
        }
        else{//x的绝对增量大于y，则取x每加一定点
            int delta=2 * B + A;
            int y=st.y();
            for(int x=st.x();x<=et.x();++x){
                painter.drawPoint(x,y);
                if(delta>=0){
                    y+=0;
                    delta+=B;
                }
                else{
                    y+=1;
                    delta+=A+B;
                }
            }
        }
    }
    else{//二四象限
        if(K){
            int delta=B - 2 * A;
            int x=st.x();
            for(int y=st.y();y>=et.y();--y){
                painter.drawPoint(x,y);
                if(delta>=0){
                    x+=0;
                    delta-=A;
                }
                else{
                    x+=1;
                    delta+=B-A;
                }
            }
        }
        else{
            int delta=2 * B - A;
            int y=st.y();
            for(int x=st.x();x<=et.x();++x){
                painter.drawPoint(x,y);
                if(delta>=0){
                    y-=1;
                    delta+=B-A;
                }
                else{
                    y-=0;
                    delta+=B;
                }
            }
        }
    }
}
