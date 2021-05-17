#include "windowwidget.h"

WindowWidget::WindowWidget(QWidget *parent)
    : QWidget(parent)
{
}

WindowWidget::~WindowWidget()
{
}

void WindowWidget::closeEvent(QCloseEvent* event)
{
    this->hide();	 // 隐藏窗口
    event->ignore(); // 忽视原来的关闭事件
}
