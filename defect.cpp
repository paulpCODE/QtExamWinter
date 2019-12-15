#include "defect.h"

void defect::SetRandType()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 10);
    const int i = dist(gen);
    if (i == 1) {
        _type = A;
    }
    else if (i == 2 || i == 3) {
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

defect::defect()
{
    _var = 0;
    _chance = 0;
    _type = not_setted;

}
