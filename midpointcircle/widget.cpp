#include "widget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWidget>
#include <QEvent>
#include <cmath>

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
    QPoint st(startPoint),et(endPoint);
    painter.drawLine(st,et);//画半径
    int dx=et.x()-st.x();
    int dy=et.y()-st.y();
    int r=(int) std::sqrt(dx * dx + dy * dy);
    int x=0, y=r;
    int delta=1-r;//1.25-y0（0.25忽略不计）
    while(x<=y){
        drawPoints(painter, st, x, y);
        if(delta<0){
            delta+=2*x+3;
        }else{
            delta+=2*(x-y)+5;
            y--;
        }
        x++;
    }
}

void Widget::drawPoints(QPainter &painter, QPoint &center, int x, int y){
    painter.drawPoint(center.x()+x, center.y()+y);
    painter.drawPoint(center.x()-x, center.y()+y);
    painter.drawPoint(center.x()+x, center.y()-y);
    painter.drawPoint(center.x()-x, center.y()-y);
    painter.drawPoint(center.x()+y, center.y()+x);
    painter.drawPoint(center.x()-y, center.y()+x);
    painter.drawPoint(center.x()+y, center.y()-x);
    painter.drawPoint(center.x()-y, center.y()-x);
}
