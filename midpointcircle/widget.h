#include <QPainter>
#include <QMouseEvent>
#include <QWidget>
#include <QEvent>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);

private:
    QPoint startPoint;
    QPoint endPoint;
    void drawPoints(QPainter &painter, QPoint &center, int x, int y);
};
