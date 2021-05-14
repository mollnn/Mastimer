#include "controller.h"

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

void Controller::ShuffleTodolist()
{

}

Todo& Controller::GetTodo(int nId)
{

}

void Controller::AddTodo()
{

}

void Controller::DeleteTodo(int nId)
{

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
