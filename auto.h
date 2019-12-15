#ifndef AUTO_H
#define AUTO_H
#include <iostream>
#include <QString>
#include <QDate>
#include "defect.h"
#include <vector>


using std::make_pair;

struct available {
    std::vector<std::pair<QString, QString>> ModelAndManufacturer;
    available();
};

struct DefectInformation {
    defect Defect;
    QDate appeared;
    QDate fixed;
};

class Auto : public available
{
private:
    QString _model;
    QString _manufacturer;
    int _year;
    int _mileage;

    std::vector<DefectInformation> _hystory;
    void _generateHystory(const int &count);
public:
    void clearHystory();
    Auto generateAuto();
    QString model();
    QString manufacturer();

    Auto();
};

#endif // AUTO_H
