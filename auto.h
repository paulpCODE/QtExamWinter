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

class Auto : private available
{
private:
    QString _model;
    QString _manufacturer;
    int _year;
    int _mileage;


    void _generateHystory(const int &count);
public:
    std::vector<DefectInformation> hystory;
    QString hystoryInString();

    double currDefChanceCalculatingForAuto(defect &currDef, const int &userTimeInYears);
    int currDefVarCalculatingForAuto(defect &currDef, const int &userTimeInYears);
    Auto generateAuto();


    QString model();
    QString manufacturer();
    int year();
    int miliage();

    Auto();
};

#endif // AUTO_H
