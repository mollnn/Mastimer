#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVector>
#include <QDateTime>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>
#include <QSpinBox>

#include "todo.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

    QLabel* m_pctlPomoStatus;
    QListWidget* m_pctlTodolist;
    QLineEdit* m_pctlTodoName;
    QSpinBox* m_pctlTodoUsed;
    QSpinBox* m_pctlTodoTotal;
    QSpinBox* m_pctlTodoWeight;
    QSpinBox* m_pctlTodoUrgency;
    QSpinBox* m_pctlTodoFocus;
    QWidget* m_pctlWindow;

private:
    QVector<Todo> m_todolist;
    bool m_pomoFlag;
    QDateTime m_pomoStartTime;


    int m_todolistSelectIndex;

    const int minimalPomoLength = 10;

    const QColor colorReady=QColor("#f2e7e5");
    const QColor colorWorking=QColor("#f2cac9");
    const QColor colorFinish=QColor("#ed3b2f");

public:
    bool PomoBegin();
    bool PomoCommit(int nId);
    bool PomoDestroy();
    QString PomoStatus();
    void ShuffleTodolist();
    Todo& GetTodo(int nId);
    void AddTodo();
    void DeleteTodo(int nId);
    void SaveTodolist();
    void LoadTodolist();
signals:

public slots:
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
    void changeTodoName(const QString&);
    void changeTodoUsed(int);
    void changeTodoTotal(int);
    void changeTodoWeight(int);
    void changeTodoUrgency(int);
    void changeTodoFocus(int);
    void autoSave();
};

#endif // CONTROLLER_H
