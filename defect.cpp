#include "defect.h"

void defect::SetRandType()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 10);
    const int i = dist(gen);
    if (i == 2 || i == 3) {
        _type = B;
    }
    else if (i >= 4 && i <= 6) {
        _type = C;
    }
    else {
        _type = D;
    }
}

TYPE defect::type()
{
    return _type;
}

double defect::chance()
{
    return _chance;
}

int defect::var()
{
    return _var;
}

void defect::Set_chance(const double chance)
{
    _chance = chance;
}

void defect::Set_var(const int var)
{
    _var = var;
}

defect::defect()
{
    _var = 0;
    _chance = 0;
    _type = not_setted;

}

defect::defect(const QString type)
{
    if(type == "A") {
        _type = A;
        _chance = 0.01;
        _var = -1;
    } else if (type == "B") {
        _type = B;
        _chance = 0.04;
        _var = 20000;
    } else if (type == "C") {
        _type = C;
        _chance = 0.07;
        _var = 10000;
    } else if (type == "D") {
        _type = D;
        _chance = 0.1;
        _var = 2000;
    }
}
