#ifndef TODOLIST_H
#define TODOLIST_H

#include <QObject>
#include <todo.h>

class Todolist: QObject
{
    Q_OBJECT
public:
    Todolist();

private:
    QVector<Todo> m_todolist;

public:
    void ShuffleTodolist();
    Todo &GetTodo(int nId);
    void AddTodo();
    void DeleteTodo(int nId);
    QVector<Todo>& todolist();
};

#endif // TODOLIST_H
