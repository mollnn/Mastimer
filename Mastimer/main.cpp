#include "windowwidget.h"
#include <QApplication>
#include <QGridLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QListView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WindowWidget w;
    w.show();



    return a.exec();
}
