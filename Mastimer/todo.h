#ifndef TODO_H
#define TODO_H

#include <QObject>

#include <QDataStream>

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

    friend QDataStream &operator<<(QDataStream &output, const Todo &data)
    {
        output << data.name << data.used << data.total << data.urgency << data.weight << data.focus;
        return output;
    }

    friend QDataStream &operator>>(QDataStream &input, Todo &data)
    {
        input >> data.name >> data.used >> data.total >> data.urgency >> data.weight >> data.focus;
        return input;
    }
};

#endif // TODO_H
