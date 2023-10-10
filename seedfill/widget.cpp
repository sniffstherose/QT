#include "widget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QStack>
#include <QPolygon>

Widget::Widget(QWidget *parent) : QWidget(parent), shouldFill(false)
{
    isDrawingPolygon = false;
    image = QImage(width(), height(), QImage::Format_ARGB32);
    image.fill(Qt::white);
}

Widget::~Widget(){};

void Widget::mousePressEvent(QMouseEvent *event)
{
    QRect rect;
    if (event->button() == Qt::LeftButton)
    {
        if (!isDrawingPolygon)
        {
            // 开始新的多边形
            currentPolygon.clear();
            isDrawingPolygon = true;
        }
        currentPolygon << event->pos();
        rect = QRect(event->pos(), event->pos()).normalized();
    }
    else if (event->button() == Qt::RightButton)
    {
        if (isDrawingPolygon)
        {
            polygons << currentPolygon;
            currentPolygon.clear();
            isDrawingPolygon = false;
            rect = currentPolygon.boundingRect();
        }
        else
        {
            // 设置种子点并标记需要进行种子填充
            seedPoint = event->pos();
            shouldFill = true;
            rect = QRect(seedPoint, seedPoint).normalized();
        }
    }
    update(); // 仅更新改变的部分
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter;

    painter.begin(&image);

    if (isDrawingPolygon)
    {
        painter.setPen(Qt::blue);
        painter.drawPolyline(currentPolygon);
    }
    painter.setPen(Qt::black);
    for (const QPolygon &polygon : polygons)
    {
        painter.drawPolygon(polygon);
    }

    if (shouldFill)
    {
        int width = this->width();
        int height = this->height();

        QStack<QPoint> stack;
        QVector<QVector<bool>> visited(width, QVector<bool>(height, false));
        stack.push(seedPoint);
        visited[seedPoint.x()][seedPoint.y()] = true;

        while (!stack.isEmpty())
        {
            QPoint p = stack.pop();
            int x=p.x(),y=p.y();
            painter.drawPoint(p);
            QPoint neighbors[4]={
                QPoint(x-1,y),
                QPoint(x,y-1),
                QPoint(x+1,y),
                QPoint(x,y+1)
            };
            for(QPoint neighbor:neighbors){
                if (neighbor.x() < width && neighbor.y() < height && !visited[neighbor.x()][neighbor.y()])
                {
                    if(!isInsidePolygon(neighbor,image)){
                        stack.push(neighbor);
                        visited[neighbor.x()][neighbor.y()]=true;
                    }
                }
            }
        }
        shouldFill = false;
    }
    painter.end();
    painter.begin(this);
    painter.drawImage(0,0,image);
}
bool Widget::isInsidePolygon(const QPoint &point, const QImage &image)
{
    QColor color = image.pixelColor(point);
    return color == Qt::black;
}
