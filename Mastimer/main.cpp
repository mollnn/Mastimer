#include "windowwidget.h"
#include <QApplication>
#include <QGridLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>
#include <QTimer>
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WindowWidget w;

    QLabel* pctlPomoStatus = new QLabel;
    QPushButton* pctlPomoBegin = new QPushButton("开始番茄");
    QPushButton* pctlPomoCommit = new QPushButton("提交番茄");
    QPushButton* pctlPomoDestroy = new QPushButton("删除番茄");
    QPushButton* pctlShuffle = new QPushButton("重排序");

    QListWidget* pctlTodolist = new QListWidget;
    QPushButton* pctlAddTodo = new QPushButton("新增任务");
    QPushButton* pctlDeleteTodo = new QPushButton("删除任务");

    QLineEdit* pctlTodoName = new QLineEdit;
    QSpinBox* pctlTodoUsed=new QSpinBox;
    QSpinBox* pctlTodoTotal = new QSpinBox;
    QSpinBox* pctlTodoWeight = new QSpinBox;
    QSpinBox* pctlTodoUrgency = new QSpinBox;
    QSpinBox* pctlTodoFocus = new QSpinBox;

    QLabel* pctlLabelTodoName = new QLabel("任务名称");
    QLabel* pctlLabelTodoUsed = new QLabel("已用番茄数");
    QLabel* pctlLabelTodoTotal = new QLabel("预计番茄数");
    QLabel* pctlLabelTodoWeight = new QLabel("重要度");
    QLabel* pctlLabelTodoUrgency = new QLabel("紧迫度");
    QLabel* pctlLabelTodoFocus = new QLabel("专注指数");
    QLabel* pctlLabelTodolist = new QLabel("任务列表");
    QLabel* pctlLabelTodoEdit = new QLabel("任务信息编辑");

    Controller* pController = new Controller;
    pController->m_pctlPomoStatus=pctlPomoStatus;
    pController->m_pctlTodolist=pctlTodolist;
    pController->m_pctlTodoName=pctlTodoName;
    pController->m_pctlTodoUsed=pctlTodoUsed;
    pController->m_pctlTodoTotal=pctlTodoTotal;
    pController->m_pctlTodoWeight=pctlTodoWeight;
    pController->m_pctlTodoFocus=pctlTodoFocus;
    pController->m_pctlTodoUrgency=pctlTodoUrgency;

    QTimer *pPomoStatusTimer= new QTimer;
    pPomoStatusTimer->setInterval(100);
    QObject::connect(pPomoStatusTimer,SIGNAL(timeout()),pController,SLOT(ui_pomoStatusRefresh()));
    pPomoStatusTimer->start();

    QObject::connect(pctlPomoBegin,SIGNAL(clicked()),pController,SLOT(pomoBegin()));
    QObject::connect(pctlPomoCommit,SIGNAL(clicked()),pController,SLOT(pomoCommit()));
    QObject::connect(pctlPomoDestroy,SIGNAL(clicked()),pController,SLOT(pomoDestroy()));

    QObject::connect(pctlAddTodo,SIGNAL(clicked()),pController,SLOT(todoAdd()));
    QObject::connect(pctlDeleteTodo,SIGNAL(clicked()),pController,SLOT(todoDelete()));

    QObject::connect(pctlTodolist,SIGNAL(itemSelectionChanged()),pController,SLOT(ui_todolistSelectionChange()));

    QObject::connect(pctlTodoName, SIGNAL(textChanged(const QString&)), pController,SLOT(changeTodoName(const QString&)));
    QObject::connect(pctlTodoUsed, SIGNAL(valueChanged(int)), pController,SLOT(changeTodoUsed(int)));
    QObject::connect(pctlTodoTotal, SIGNAL(valueChanged(int)), pController,SLOT(changeTodoTotal(int)));
    QObject::connect(pctlTodoWeight, SIGNAL(valueChanged(int)), pController,SLOT(changeTodoWeight(int)));
    QObject::connect(pctlTodoUrgency, SIGNAL(valueChanged(int)), pController,SLOT(changeTodoUrgency(int)));
    QObject::connect(pctlTodoFocus, SIGNAL(valueChanged(int)), pController,SLOT(changeTodoFocus(int)));

    QGridLayout* pGridLayout = new QGridLayout;

    pGridLayout->addWidget(pctlPomoStatus,1,1);
    pGridLayout->addWidget(pctlPomoBegin,1,2);
    pGridLayout->addWidget(pctlPomoCommit,1,3);
    pGridLayout->addWidget(pctlPomoDestroy,1,4);
    pGridLayout->addWidget(pctlShuffle,1,5);

    pGridLayout->addWidget(pctlLabelTodolist,10,1,1,5);
    pGridLayout->addWidget(pctlTodolist,11,1,1,5);

    pGridLayout->addWidget(pctlLabelTodoEdit,30,1,1,5);
    pGridLayout->addWidget(pctlLabelTodoName,31,1,1,1);

    pGridLayout->addWidget(pctlTodoName,31,2,1,2);
    pGridLayout->addWidget(pctlAddTodo,31,4);
    pGridLayout->addWidget(pctlDeleteTodo,31,5);

    pGridLayout->addWidget(pctlLabelTodoUsed,40,1);
    pGridLayout->addWidget(pctlLabelTodoTotal,40,2);
    pGridLayout->addWidget(pctlLabelTodoFocus,40,3);
    pGridLayout->addWidget(pctlLabelTodoWeight,40,4);
    pGridLayout->addWidget(pctlLabelTodoUrgency,40,5);

    pGridLayout->addWidget(pctlTodoUsed,41,1);
    pGridLayout->addWidget(pctlTodoTotal,41,2);
    pGridLayout->addWidget(pctlTodoFocus,41,3);
    pGridLayout->addWidget(pctlTodoWeight,41,4);
    pGridLayout->addWidget(pctlTodoUrgency,41,5);

    w.setLayout(pGridLayout);

    w.show();

    return a.exec();
}
