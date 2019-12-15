#ifndef DEFECT_H
#define DEFECT_H
#include "random"

enum TYPE {not_setted, A, B, C, D};
class defect
{
private:
    TYPE _type;
    double _chance;
    int _var;
public:
    void SetRandType();
    TYPE type();
    defect();
};

#endif // DEFECT_H
