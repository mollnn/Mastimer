#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButtonBeginPomo, &QPushButton::clicked, [&](){

    });
    connect(ui->pushButtonCommitPomo, &QPushButton::clicked, [&](){

    });
    connect(ui->pushButtonDeletePomo, &QPushButton::clicked, [&](){

    });
    connect(ui->pushButtonTodolistReorder, &QPushButton::clicked, [&](){

    });
    connect(ui->pushButtonSetting, &QPushButton::clicked, [&](){

    });
    connect(ui->pushButtonAddTodo, &QPushButton::clicked, [&](){
        todolist->AddTodo();
        RefreshTodolist();
    });
    connect(ui->pushButtonEditTodo, &QPushButton::clicked, [&](){

    });
    connect(ui->pushButtonDeleteTodo, &QPushButton::clicked, [&](){
        todolist->DeleteTodo(ui->listWidget->currentRow());
        RefreshTodolist();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::RefreshTodolist()
{
    int t_selectRow = ui->listWidget->currentRow();
    ui->listWidget->clear();
    for (auto &todo : todolist->todolist())
    {
        ui->listWidget->addItem(QString().sprintf("%s (%d/%d) F%d, W%d, U%d", todo.name.toUtf8().data(), todo.used, todo.total, todo.focus, todo.weight, todo.urgency));
    }
    if (t_selectRow >= 0)
    {
        ui->listWidget->setCurrentRow(t_selectRow);
    }
}
