#include "todo.h"

Todo::Todo()
{

}

void Todo::GenerateRandomFactor()
{
    randfactor=qrand()*1.0/RAND_MAX;
}

double Todo::Evaluation() const
{
    return (weight+urgency+focus)*randfactor;
}
