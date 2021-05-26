#include "todolist.h"

Todolist::Todolist()
{

}

bool cmp_ShuffleTodolist(const Todo &lhs, const Todo &rhs)
{
    return lhs.Evaluation() > rhs.Evaluation();
}

void Todolist::ShuffleTodolist()
{
    for (auto &todo : m_todolist)
    {
        todo.GenerateRandomFactor();
    }
    std::sort(m_todolist.begin(), m_todolist.end(), cmp_ShuffleTodolist);
}

Todo &Todolist::GetTodo(int nId)
{
    return m_todolist[nId];
}

void Todolist::AddTodo()
{
    m_todolist.append(Todo());
}

void Todolist::DeleteTodo(int nId)
{
    if(nId<0 || nId>=m_todolist.size()) return;
    m_todolist.erase(m_todolist.begin() + nId);
}

QVector<Todo>& Todolist::todolist()
{
    return m_todolist;
}
