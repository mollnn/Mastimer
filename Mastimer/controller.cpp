#include "controller.h"
#include <QtAlgorithms>
#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent)
{
    m_pomoFlag=false;
    m_todolistSelectIndex=-1;
}


bool Controller::PomoBegin()
{
    if(m_pomoFlag==0)
    {
        m_pomoFlag=1;
        m_pomoStartTime=QDateTime::currentDateTime();
        return true;
    }
    else
    {
        return false;
    }
}

bool Controller::PomoCommit(int nId)
{
    if(m_pomoFlag==1)
    {
        if(m_pomoStartTime.secsTo(QDateTime::currentDateTime())>=minimalPomoLength)
        {
            if(nId>=0 && nId<=m_todolist.size())
            {
                // todo: modify the status of the todo
                // todo: show the success
                m_pomoFlag=0;
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Controller::PomoDestroy()
{
    if(m_pomoFlag==1)
    {
        // todo: ask the user
        m_pomoFlag=0;
        return true;
    }
    else {
        return false;
    }
}

QString Controller::PomoStatus()
{
    if(m_pomoFlag==1)
    {
        qint64 t_pomoRunTime = m_pomoStartTime.secsTo(QDateTime::currentDateTime());
        qint64 t_pomoTotalTime = minimalPomoLength;
        return QString().sprintf("%lld/%lld",t_pomoRunTime,t_pomoTotalTime);
    }
    else {
        return QString("ready");
    }
}

bool cmp_ShuffleTodolist(const Todo& lhs, const Todo& rhs)
{
    return lhs.Evaluation() < rhs.Evaluation();
}

void Controller::ShuffleTodolist()
{
    for(auto &todo:m_todolist)
    {
        todo.GenerateRandomFactor();
    }
    std::sort(m_todolist.begin(),m_todolist.end(),cmp_ShuffleTodolist);
    this->ui_todolistRefresh();
}

Todo& Controller::GetTodo(int nId)
{
    return m_todolist[nId];
}

void Controller::AddTodo()
{
    m_todolist.append(Todo());
    this->ui_todolistRefresh();
}

void Controller::DeleteTodo(int nId)
{
    m_todolist.erase(m_todolist.begin()+nId);
    this->ui_todolistRefresh();
}

void Controller::pomoBegin()
{
    this->PomoBegin();
}

void Controller::pomoCommit()
{
    this->PomoCommit(m_todolistSelectIndex);
}

void Controller::pomoDestroy()
{
    this->PomoDestroy();
}

void Controller::ui_pomoStatusRefresh()
{
    m_pctlPomoStatus->setText(this->PomoStatus());
}

void Controller::ui_todolistRefresh()
{
    m_pctlTodolist->clear();
    for(auto &todo:m_todolist)
    {
        m_pctlTodolist->addItem(todo.name);
    }
}

void Controller::ui_todolistSelectionChange()
{
    m_todolistSelectIndex=m_pctlTodolist->currentRow();
}

void Controller::todoAdd()
{
    this->AddTodo();
}

void Controller::todoDelete()
{
    this->DeleteTodo(m_todolistSelectIndex);
}

void Controller::changeTodoName(const QString& param)
{
    m_todolist[m_todolistSelectIndex].name=param;
    ui_todolistRefresh();
}

void Controller::changeTodoUsed(int param)
{
    m_todolist[m_todolistSelectIndex].used=param;
    ui_todolistRefresh();
}

void Controller::changeTodoTotal(int param)
{
    m_todolist[m_todolistSelectIndex].total=param;
    ui_todolistRefresh();
}

void Controller::changeTodoWeight(int param)
{
    m_todolist[m_todolistSelectIndex].weight=param;
    ui_todolistRefresh();
}

void Controller::changeTodoUrgency(int param)
{
    m_todolist[m_todolistSelectIndex].urgency=param;
    ui_todolistRefresh();
}

void Controller::changeTodoFocus(int param)
{
    m_todolist[m_todolistSelectIndex].focus=param;
    ui_todolistRefresh();
}

