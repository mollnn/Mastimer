#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVector>
#include <QDateTime>
#include <QLabel>

#include "todo.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

    QLabel* m_pctlPomoStatus;

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
    void ui_pomoStatusRefresh();
};

#endif // CONTROLLER_H
