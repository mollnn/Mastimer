#ifndef WINDOWWIDGET_H
#define WINDOWWIDGET_H

#include <QWidget>

class WindowWidget : public QWidget
{
    Q_OBJECT

public:
    WindowWidget(QWidget *parent = 0);
    ~WindowWidget();
};

#endif // WINDOWWIDGET_H
