#include "traymenu.h"

TrayMenu::TrayMenu(QWidget *parent)
    : QMenu(parent)
{

}

TrayMenu::~TrayMenu()
{

}

// 添加菜单项
void TrayMenu::initActions()
{
    // 创建菜单项
    m_pShowAction = new QAction(QIcon(), QString::fromLocal8Bit("显示"), this);;

    // 添加菜单项
    addAction(m_pShowAction);

    // 连接信号-信号（仅列举连接显示窗口的信号）
    connect(m_pShowAction, SIGNAL(triggered(bool)), this, SIGNAL(showWindow()));
}
