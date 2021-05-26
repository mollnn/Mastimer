#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVector>
#include <QDateTime>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QApplication>
#include <QMenu>
#include <QSystemTrayIcon>

#include "todo.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

    // UI control addresses
    QLabel *m_pctlPomoStatus;
    QListWidget *m_pctlTodolist;
    QLineEdit *m_pctlTodoName;
    QSpinBox *m_pctlTodoUsed;
    QSpinBox *m_pctlTodoTotal;
    QSpinBox *m_pctlTodoWeight;
    QSpinBox *m_pctlTodoUrgency;
    QSpinBox *m_pctlTodoFocus;
    QSpinBox *m_pctlPomoLength;
    QWidget *m_pctlWindow;

    // System tray icon/menu
    QSystemTrayIcon *m_pSystemTray;
    QMenu *trayIconMenu;
    QAction *showAction;
    QAction *quitAction;

    // App
    QApplication *pApp;

private:
    // Members
    QVector<Todo> m_todolist;
    int m_pomoFlag;
    int m_pomoFinishFlag;
    int m_relaxFlag;
    QDateTime m_pomoStartTime;

    // UI: selected item
    int m_todolistSelectIndex;

    // Settings
    int minimalPomoLength = 500;
    int minimalRelaxLength = 50;
    const QColor colorReady = QColor("#f2e7e5");
    const QColor colorWorking = QColor("#f2cac9");
    const QColor colorFinish = QColor("#ed3b2f");
    const QColor colorRelax = QColor("#add5a2");

    // Timers
    QTimer timerRelax;
    QTimer timerPomoFinish;

public:
    bool PomoBegin();
    bool PomoCommit(int nId);
    bool PomoDestroy();
    QString PomoStatus();
    void ShuffleTodolist();
    Todo &GetTodo(int nId);
    void AddTodo();
    void DeleteTodo(int nId);
    void SaveTodolist();
    void LoadTodolist();
    void WriteLog(const QString &strLog);
signals:

public slots:
    // Window Operations
    void showWindow();

    // Tray Operations
    void InitSystemTray();
    void showMenu();
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);

    // Functional Operations
    void pomoBegin();
    void pomoCommit();
    void pomoDestroy();
    void todoAdd();
    void todoDelete();
    void todoShuffle();
    void todolistSave();
    void todolistLoad();

    // UI Operations
    void ui_pomoStatusRefresh();
    void ui_todolistRefresh();
    void ui_todolistSelectionChange();
    void ui_updateBackgroundColor();

    // Modify Operations
    void changeTodoName(const QString &);
    void changeTodoUsed(int);
    void changeTodoTotal(int);
    void changeTodoWeight(int);
    void changeTodoUrgency(int);
    void changeTodoFocus(int);
    void changePomoLength(int);

    // ...
    void autoSave();
    void autoLoad();
    void relaxEnd();
    void quit();
    void onTimerPomoFinish();
};

#endif // CONTROLLER_H
