#include "mainwindow.h"

#include <QApplication>
#include "todolist.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Todolist *todolist = new Todolist;
    w.todolist=todolist;
    w.show();
    return a.exec();
}
