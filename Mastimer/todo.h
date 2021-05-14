#ifndef TODO_H
#define TODO_H

#include <QObject>

class Todo : public QObject
{
    Q_OBJECT
public:
    explicit Todo(QObject *parent = nullptr);

    QString name;
    int weight;
    int urgency;
    int focus;
    int used;
    int total;

private:
    double randfactor;

public:
    void generateRandomFactor();
    double Evaluation();
signals:

public slots:
};

#endif // TODO_H
