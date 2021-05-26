#include "todo.h"

Todo::Todo(): name("New Todo"),  weight(3), urgency(3), focus(0), used(0), total(1)
{
}

void Todo::GenerateRandomFactor()
{
    randfactor = qrand() * 1.0 / RAND_MAX;
}

double Todo::Evaluation() const
{
    return (weight + urgency + focus) * randfactor;
}
