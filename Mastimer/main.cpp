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
    QPushButton* pctlPomoBegin = new QPushButton;
    QPushButton* pctlPomoCommit = new QPushButton;
    QPushButton* pctlPomoDestroy = new QPushButton;
    QPushButton* pctlShuffle = new QPushButton;
    QListWidget* pctlTodolist = new QListWidget;
    QLineEdit* pctlTodoName = new QLineEdit;
    QPushButton* pctlAddTodo = new QPushButton;
    QPushButton* pctlDeleteTodo = new QPushButton;
    QSpinBox* pctlTodoUsed=new QSpinBox;
    QSpinBox* pctlTodoTotal = new QSpinBox;
    QSpinBox* pctlTodoWeight = new QSpinBox;
    QSpinBox* pctlTodoUrgency = new QSpinBox;
    QSpinBox* pctlTodoFocus = new QSpinBox;

    Controller* pController = new Controller;
    pController->m_pctlPomoStatus=pctlPomoStatus;

    QTimer *pPomoStatusTimer= new QTimer;
    pPomoStatusTimer->setInterval(100);
    QObject::connect(pPomoStatusTimer,SIGNAL(timeout()),pController,SLOT(ui_pomoStatusRefresh()));
    pPomoStatusTimer->start();

    QObject::connect(pctlPomoBegin,SIGNAL(clicked()),pController,SLOT(pomoBegin()));
    QObject::connect(pctlPomoCommit,SIGNAL(clicked()),pController,SLOT(pomoCommit()));
    QObject::connect(pctlPomoDestroy,SIGNAL(clicked()),pController,SLOT(pomoDestroy()));

    QGridLayout* pGridLayout = new QGridLayout;

    pGridLayout->addWidget(pctlPomoStatus,1,1);
    pGridLayout->addWidget(pctlPomoBegin,1,2);
    pGridLayout->addWidget(pctlPomoCommit,1,3);
    pGridLayout->addWidget(pctlPomoDestroy,1,4);
    pGridLayout->addWidget(pctlShuffle,1,5);

    pGridLayout->addWidget(pctlTodolist,2,1,1,5);

    pGridLayout->addWidget(pctlTodoName,3,1,1,3);
    pGridLayout->addWidget(pctlAddTodo,3,4);
    pGridLayout->addWidget(pctlDeleteTodo,3,5);

    pGridLayout->addWidget(pctlTodoUsed,4,1);
    pGridLayout->addWidget(pctlTodoTotal,4,2);
    pGridLayout->addWidget(pctlTodoWeight,4,3);
    pGridLayout->addWidget(pctlTodoUrgency,4,4);
    pGridLayout->addWidget(pctlTodoFocus,4,5);

    w.setLayout(pGridLayout);



    w.show();

    return a.exec();
}
