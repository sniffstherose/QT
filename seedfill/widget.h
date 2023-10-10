#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPolygon>

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    bool shouldFill;
    QPoint seedPoint;
    QVector<QPolygon> polygons;
    QImage image;

    void seedFill(const QPoint &seed);
    bool isInsidePolygon(const QPoint &point,const QImage &image);

    bool isDrawingPolygon;
    QPolygon currentPolygon;
};

#endif // WIDGET_H
