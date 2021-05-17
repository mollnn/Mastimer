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

#include "todo.h"

#include "traymenu.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

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
    QSystemTrayIcon *m_pSystemTray;

private:
    QVector<Todo> m_todolist;
    int m_pomoFlag;
    int m_pomoFinishFlag;
    int m_relaxFlag;
    QDateTime m_pomoStartTime;

    int m_todolistSelectIndex;

    int minimalPomoLength = 500;
    int minimalRelaxLength = 50;

    const QColor colorReady = QColor("#f2e7e5");
    const QColor colorWorking = QColor("#f2cac9");
    const QColor colorFinish = QColor("#ed3b2f");
    const QColor colorRelax = QColor("#add5a2");

    QTimer timerRelax;

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
    void InitSystemTray();
    void showWindow();
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void pomoBegin();
    void pomoCommit();
    void pomoDestroy();
    void todoAdd();
    void todoDelete();
    void todoShuffle();
    void todolistSave();
    void todolistLoad();
    void ui_pomoStatusRefresh();
    void ui_todolistRefresh();
    void ui_todolistSelectionChange();
    void ui_updateBackgroundColor();
    void changeTodoName(const QString &);
    void changeTodoUsed(int);
    void changeTodoTotal(int);
    void changeTodoWeight(int);
    void changeTodoUrgency(int);
    void changeTodoFocus(int);
    void changePomoLength(int);
    void autoSave();
    void autoLoad();
    void relaxEnd();
};

#endif // CONTROLLER_H
