#include "todo.h"

Todo::Todo()
{
    this->name="New Todo";
    this->used=0;
    this->total=1;
    this->urgency=3;
    this->weight=3;
    this->focus=0;
}

void Todo::GenerateRandomFactor()
{
    randfactor=qrand()*1.0/RAND_MAX;
}

double Todo::Evaluation() const
{
    return (weight+urgency+focus)*randfactor;
}

