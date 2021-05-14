#ifndef TODO_H
#define TODO_H

#include <QObject>

class Todo
{
public:
    Todo();

    QString name;
    int weight;
    int urgency;
    int focus;
    int used;
    int total;

private:
    double randfactor;

public:
    void GenerateRandomFactor();
    double Evaluation() const;
};

#endif // TODO_H
