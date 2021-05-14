#include "todo.h"

Todo::Todo(QObject *parent) : QObject(parent)
{

}

void Todo::GenerateRandomFactor()
{
    randfactor=qrand()*1.0/RAND_MAX;
}

double Todo::Evaluation()
{
    return (weight+urgency+focus)*randfactor;
}
