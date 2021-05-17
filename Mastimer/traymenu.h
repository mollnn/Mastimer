#ifndef TRAYMENU_H
#define TRAYMENU_H


#include <QMenu>

class TrayMenu : public QMenu
{
    Q_OBJECT

public:
    explicit TrayMenu(QWidget *parent = nullptr);
    ~TrayMenu();

signals:
    // 自定义信号
    void showWindow();

private:
    // 添加菜单项
    void initActions();

private:
    QAction *m_pShowAction;
};

#endif // TRAYMENU_H
