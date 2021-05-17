#ifndef WINDOWWIDGET_H
#define WINDOWWIDGET_H

#include <QWidget>
#include <QCloseEvent>

class WindowWidget : public QWidget
{
    Q_OBJECT

public:
    WindowWidget(QWidget *parent = 0);
    ~WindowWidget();

protected:
        //重写事件
        void closeEvent(QCloseEvent* event);
};

#endif // WINDOWWIDGET_H
