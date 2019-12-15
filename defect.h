#ifndef DEFECT_H
#define DEFECT_H
#include "random"
#include <QString>

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
    double chance();
    int var();
    void Set_chance(const double chance);
    void Set_var(const int var);
    defect();
    defect(const QString type);
};

#endif // DEFECT_H
