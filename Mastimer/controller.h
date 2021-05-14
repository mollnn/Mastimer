#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVector>
#include <QTime>

#include "todo.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);


private:
    QVector<Todo> m_todolist;
    bool m_pomoFlag;
    QTime m_pomoStartTime;

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
};

#endif // CONTROLLER_H
