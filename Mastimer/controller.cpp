#include "controller.h"
#include <QtAlgorithms>
#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QTextStream>
#include <QGraphicsOpacityEffect>
#include <QSystemTrayIcon>
#include <QtMath>

QColor BlendColor(const QColor &a, const QColor &b, double k)
{
    return QColor(a.red() * k + b.red() * (1 - k), a.green() * k + b.green() * (1 - k), a.blue() * k + b.blue() * (1 - k));
}

Controller::Controller(QObject *parent) : QObject(parent)
{
    m_pomoFlag = false;
    m_pomoFinishFlag = false;
    m_relaxFlag = false;
    m_todolistSelectIndex = -1;
    connect(&timerRelax, SIGNAL(timeout()), this, SLOT(relaxEnd()));
    connect(&timerPomoFinish, SIGNAL(timeout()), this,SLOT(onTimerPomoFinish()));
}

void Controller::InitSystemTray()
{
    QSystemTrayIcon *pSystemTray = new QSystemTrayIcon(m_pctlWindow);

    trayIconMenu = new QMenu();

    showAction = new QAction(m_pctlWindow);
    quitAction = new QAction(m_pctlWindow);

    showAction->setText(tr("显示"));
    quitAction->setText(tr("退出"));

    trayIconMenu->addAction(showAction);
    trayIconMenu->addAction(quitAction);

    connect(showAction, SIGNAL(triggered()), this, SLOT(showWindow()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));

    // 设置系统托盘的上下文菜单
    pSystemTray->setContextMenu(trayIconMenu);

    // 设置系统托盘提示信息、托盘图标
    pSystemTray->setToolTip(("Mastimer"));
    pSystemTray->setIcon(QIcon(":/Mastimer.ico"));

    // 连接信号槽
    connect(pSystemTray , SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));

    // 显示系统托盘
    pSystemTray->show();

    // 显示系统托盘提示信息
    pSystemTray->showMessage(("欢迎使用Mastimer"), ("开始新番茄吧！"));

    m_pSystemTray=pSystemTray;
}

void Controller::showWindow()
{
    m_pctlWindow->hide();
    m_pctlWindow->show();
}

void Controller::showMenu()
{
    trayIconMenu->show();
}

void Controller::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Context:
        showMenu();
        break;
    case QSystemTrayIcon::Trigger:
        break;
    case QSystemTrayIcon::DoubleClick:
        showWindow();
        break;
    default:
        break;

    }
}

bool Controller::PomoBegin()
{
    if (m_pomoFlag == 0)
    {
        m_pomoFlag = 1;
        m_pomoFinishFlag=0;
        m_pomoStartTime = QDateTime::currentDateTime();
        timerRelax.stop();
        this->m_relaxFlag = false;
        return true;
    }
    else
    {
        return false;
    }
}

bool Controller::PomoCommit(int nId)
{
    if (m_pomoFlag == 1)
    {
        if (m_pomoStartTime.secsTo(QDateTime::currentDateTime()) >= minimalPomoLength)
        {
            if (nId >= 0 && nId < m_todolist.size())
            {
                m_todolist[nId].used++;
                m_pctlPomoStatus->setText("committed");
                m_pomoFlag = 0;
                this->ui_pomoStatusRefresh();
                this->ui_todolistRefresh();
                this->WriteLog(QDateTime::currentDateTime().toString("yyyyMMdd,hh:mm:ss") + "," + m_todolist[nId].name + ","
                               + QString().sprintf("%lld,%d",m_pomoStartTime.secsTo(QDateTime::currentDateTime()), m_todolist[nId].used)+"\n");
                timerRelax.setInterval(minimalRelaxLength * 1000);
                this->m_relaxFlag = true;
                timerRelax.start();
                timerPomoFinish.stop();
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Controller::PomoDestroy()
{
    if (m_pomoFlag == 1)
    {
        // todo: ask the user
        m_pomoFlag = 0;
        m_pomoFinishFlag=0;
        timerPomoFinish.stop();
        return true;
    }
    else
    {
        return false;
    }
}

QString Controller::PomoStatus()
{
    if (m_pomoFlag == 1)
    {
        qint64 t_pomoRunTime = m_pomoStartTime.secsTo(QDateTime::currentDateTime());
        qint64 t_pomoTotalTime = minimalPomoLength;
        return QString().sprintf("运行 %lld/%lld", t_pomoRunTime, t_pomoTotalTime);
    }
    else
    {
        return QString("空闲");
    }
}

bool cmp_ShuffleTodolist(const Todo &lhs, const Todo &rhs)
{
    return lhs.Evaluation() > rhs.Evaluation();
}

void Controller::ShuffleTodolist()
{
    for (auto &todo : m_todolist)
    {
        todo.GenerateRandomFactor();
    }
    std::sort(m_todolist.begin(), m_todolist.end(), cmp_ShuffleTodolist);
    if (m_todolist.size() > 0)
    {
        m_pctlTodolist->setCurrentRow(0);
    }
    this->ui_todolistRefresh();
}

Todo &Controller::GetTodo(int nId)
{
    return m_todolist[nId];
}

void Controller::AddTodo()
{
    m_todolist.append(Todo());
    this->ui_todolistRefresh();
    m_pctlTodolist->setCurrentRow(m_todolist.size()-1);
}

void Controller::DeleteTodo(int nId)
{
    m_todolist.erase(m_todolist.begin() + nId);
    this->ui_todolistRefresh();
    if(nId-1>=0 && nId-1<m_todolist.size())
    {
        m_pctlTodolist->setCurrentRow(nId-1);
    }
}

void Controller::SaveTodolist()
{
    QString filename = QFileDialog::getSaveFileName(nullptr, "Save", "", "Mastimer Todolist File (*.todolist)");
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly) == false)
    {
        qDebug() << "Fail to save file";
        return;
    }
    QDataStream dataStream(&file);
    dataStream << m_todolist;
    file.close();
}

void Controller::LoadTodolist()
{
    QString filename = QFileDialog::getOpenFileName(nullptr, "Open", "", "Mastimer Todolist File (*.todolist)");
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly) == false)
    {
        qDebug() << "Fail to open file";
        return;
    }
    QDataStream dataStream(&file);
    dataStream >> m_todolist;
    file.close();
    this->ui_todolistRefresh();
}

void Controller::WriteLog(const QString &strLog)
{
    QString filename = "log" + QDateTime::currentDateTime().toString("yyyyMMdd") + ".csv";
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite | QIODevice::Append) == false)
    {
        qDebug() << "Fail to write log";
        return;
    }
    QTextStream textStream(&file);
    textStream << strLog;
    file.close();
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
    int t_selectRow = m_pctlTodolist->currentRow();
    m_pctlTodolist->clear();
    for (auto &todo : m_todolist)
    {
        m_pctlTodolist->addItem(QString().sprintf("%s (%d/%d) F%d, W%d, U%d", todo.name.toUtf8().data(), todo.used, todo.total, todo.focus, todo.weight, todo.urgency));
    }
    if (t_selectRow >= 0)
    {
        m_pctlTodolist->setCurrentRow(t_selectRow);
    }
}

void Controller::ui_todolistSelectionChange()
{
    m_todolistSelectIndex = m_pctlTodolist->currentRow();
    if (m_todolistSelectIndex >= 0 && m_todolistSelectIndex < m_todolist.size())
    {
        m_pctlTodoName->setText(m_todolist[m_todolistSelectIndex].name);
        m_pctlTodoUsed->setValue(m_todolist[m_todolistSelectIndex].used);
        m_pctlTodoTotal->setValue(m_todolist[m_todolistSelectIndex].total);
        m_pctlTodoWeight->setValue(m_todolist[m_todolistSelectIndex].weight);
        m_pctlTodoUrgency->setValue(m_todolist[m_todolistSelectIndex].urgency);
        m_pctlTodoFocus->setValue(m_todolist[m_todolistSelectIndex].focus);
    }
}

void Controller::ui_updateBackgroundColor()
{
    QColor newColor = colorReady;
    if (m_pomoFlag == 1)
    {
        newColor = colorWorking;
        if (m_pomoStartTime.secsTo(QDateTime::currentDateTime()) >= minimalPomoLength)
        {
            newColor = colorFinish;
            if(m_pomoFinishFlag==0)
            {
                m_pSystemTray->showMessage(("Mastimer"), ("番茄已完成！"));
                timerPomoFinish.setInterval(30000);
                timerPomoFinish.start();
            }
            m_pomoFinishFlag=1;
        }
    }
    else if (m_relaxFlag == 1)
    {
        newColor = colorRelax;
    }
    QPalette oldPalette = m_pctlWindow->palette();
    oldPalette.setColor(QPalette::Background, BlendColor(m_pctlWindow->palette().background().color(), newColor, 0.9));
    m_pctlWindow->setPalette(oldPalette);
    m_pctlTodolist->setStyleSheet("background-color:rgba(255,255,255,0.5)");
}

void Controller::todoAdd()
{
    this->AddTodo();
}

void Controller::todoDelete()
{
    this->DeleteTodo(m_todolistSelectIndex);
}

void Controller::todoShuffle()
{
    this->ShuffleTodolist();
}

void Controller::changeTodoName(const QString &param)
{
    if (m_todolistSelectIndex >= 0 && m_todolistSelectIndex < m_todolist.size())
    {
        if (m_todolist[m_todolistSelectIndex].name == param)
            return;
        m_todolist[m_todolistSelectIndex].name = param;
        ui_todolistRefresh();
    }
}

void Controller::changeTodoUsed(int param)
{
    if (m_todolistSelectIndex >= 0 && m_todolistSelectIndex < m_todolist.size())
    {
        if (m_todolist[m_todolistSelectIndex].used == param)
            return;
        m_todolist[m_todolistSelectIndex].used = param;
        ui_todolistRefresh();
    }
}

void Controller::changeTodoTotal(int param)
{
    if (m_todolistSelectIndex >= 0 && m_todolistSelectIndex < m_todolist.size())
    {
        if (m_todolist[m_todolistSelectIndex].total == param)
            return;
        m_todolist[m_todolistSelectIndex].total = param;
        ui_todolistRefresh();
    }
}

void Controller::changeTodoWeight(int param)
{
    if (m_todolistSelectIndex >= 0 && m_todolistSelectIndex < m_todolist.size())
    {
        if (m_todolist[m_todolistSelectIndex].weight == param)
            return;
        m_todolist[m_todolistSelectIndex].weight = param;
        ui_todolistRefresh();
    }
}

void Controller::changeTodoUrgency(int param)
{
    if (m_todolistSelectIndex >= 0 && m_todolistSelectIndex < m_todolist.size())
    {
        if (m_todolist[m_todolistSelectIndex].urgency == param)
            return;
        m_todolist[m_todolistSelectIndex].urgency = param;
        ui_todolistRefresh();
    }
}

void Controller::changeTodoFocus(int param)
{
    if (m_todolistSelectIndex >= 0 && m_todolistSelectIndex < m_todolist.size())
    {
        if (m_todolist[m_todolistSelectIndex].focus == param)
            return;
        m_todolist[m_todolistSelectIndex].focus = param;
        ui_todolistRefresh();
    }
}

void Controller::changePomoLength(int param)
{
    minimalPomoLength = param;
    if (minimalPomoLength != m_pctlPomoLength->value())
    {
        m_pctlPomoLength->setValue(minimalPomoLength);
    }
}

void Controller::todolistSave()
{
    this->SaveTodolist();
}

void Controller::todolistLoad()
{
    this->LoadTodolist();
}

void Controller::autoSave()
{
    QDateTime curDateTime = QDateTime::currentDateTime();
    QString filename = "./autosave/autosave_" + curDateTime.toString("yyyy-MM-dd-hh-mm-ss") + ".todolist";
    QFile file(filename);

    if (curDateTime.time().second() == 0)
    {
        if (file.open(QIODevice::WriteOnly) == false)
        {
            qDebug() << "Fail to autobackup file";
            return;
        }
        QDataStream dataStream(&file);
        dataStream << m_todolist;
        file.close();
    }

    QFile file2("default.todolist");
    if (file2.open(QIODevice::WriteOnly) == false)
    {
        qDebug() << "Fail to autosave file";
        return;
    }
    QDataStream dataStream(&file2);
    dataStream << m_todolist;
    file2.close();
}

void Controller::autoLoad()
{
    QFile file2("default.todolist");
    if (file2.open(QIODevice::ReadOnly) == false)
    {
        qDebug() << "Fail to autoload file";
        return;
    }
    QDataStream dataStream(&file2);
    dataStream >> m_todolist;
    file2.close();
    ui_todolistRefresh();
}

void Controller::relaxEnd()
{
    this->m_relaxFlag = false;
    m_pSystemTray->showMessage("休息结束！","休息时间到，开始新番茄吧！",QIcon(),60000);
}

void Controller::quit()
{
    pApp->quit();
}

void Controller::onTimerPomoFinish()
{
    m_pSystemTray->showMessage(("Mastimer"), ("番茄已完成！"));
}
