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

private:
    QVector<Todo> m_todolist;
    bool m_pomoFlag;
    QDateTime m_pomoStartTime;


    int m_todolistSelectIndex;

    const int minimalPomoLength = 10;

public:
    bool PomoBegin();
    bool PomoCommit(int nId);
    bool PomoDestroy();
    QString PomoStatus();
    void ShuffleTodolist();
    Todo& GetTodo(int nId);
    void AddTodo();
    void DeleteTodo(int nId);
signals:

public slots:
    void pomoBegin();
    void pomoCommit();
    void pomoDestroy();
    void todoAdd();
    void todoDelete();
    void todoShuffle();
    void ui_pomoStatusRefresh();
    void ui_todolistRefresh();
    void ui_todolistSelectionChange();
    void changeTodoName(const QString&);
    void changeTodoUsed(int);
    void changeTodoTotal(int);
    void changeTodoWeight(int);
    void changeTodoUrgency(int);
    void changeTodoFocus(int);
};

#endif // CONTROLLER_H
