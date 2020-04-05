#include "auto.h"
#include "random.h"


available::available()
{
    ModelAndManufacturer = {make_pair("X5","BMW-AG"), make_pair("X6","BMW-AG"), make_pair("X7","BMW-AG"),
                            make_pair("Camry","Toyota"), make_pair("RAV4","Toyota"), make_pair("Corolla","Toyota"),
                            make_pair("Juke","Nissan"), make_pair("X-TRAIL","Nissan"), make_pair("Navara","Nissan"),
                            make_pair("Panamera","Porsche"), make_pair("Taycan","Porsche"), make_pair("Macan","Porsche")};
}


Auto Auto::generateAuto()
{
    const QDate currDate = QDate::currentDate();

    const int i = Random::RandInt(0, ModelAndManufacturer.size() - 1);
    _model = ModelAndManufacturer[i].first;
    _manufacturer = ModelAndManufacturer[i].second;
    _year = Random::RandInt(2000, currDate.year() - 1);
    _mileage = 1000*Random::RandInt(5, 20) + 12000*(currDate.year() - _year);
    int count = Random::RandInt(1, 4) + currDate.year() - _year;
    _generateHystory(count);

    return *this;
}

void Auto::_generateHystory(const int &count)
{
    const QDate currDate = QDate::currentDate();

    DefectInformation element;
    int day, mon, year;

    for (int i = 0; i < count; i++) {
        element.Defect.SetRandType();
        day = Random::RandInt(1, 31);
        mon = Random::RandInt(1, 12);
        year = Random::RandInt(_year, currDate.year() - 1);
        element.appeared.setDate(year, mon, day);
        day = day + Random::RandInt(1, 31);
        if(day > 31) { day = day - 31; mon++; }
        mon = mon + Random::RandInt(1, 12);
        if(mon > 12) { mon = mon - 12; year++; }
        element.fixed.setDate(year, mon, day);


        hystory.push_back(element);
    }
}

QString Auto::hystoryInString()
{
    QString hystoryInString;
    QString type;
    for(unsigned long long int j = 0; j < hystory.size(); j++) {
        if(hystory[j].Defect.type() == A) {
            type = "A";
        } else if (hystory[j].Defect.type() == B) {
            type = "B";
        } else if (hystory[j].Defect.type() == C) {
            type = "C";
        } else {
            type = "D";
        }
        hystoryInString = hystoryInString + "\nDefect № " + QString::number(j + 1) +
                "\n  Type: " + type +
                "\n  Appeared: " + hystory[j].appeared.toString() +
                "\n  Fixed: " + hystory[j].fixed.toString();
    }
    return hystoryInString;
}

double Auto::currDefChanceCalculatingForAuto(defect &currDef, const int &userTimeInYears)
{
    const int num = Random::RandInt(1, 4);
    if(num == 1) { //fix
        return currDef.chance();
    } else if (num == 2) { //_year
        currDef.Set_chance(currDef.chance() + 0.01*(QDate::currentDate().year() + userTimeInYears - _year));
        return currDef.chance();
    } else if (num == 3) {
        currDef.Set_chance((_mileage + 12000*userTimeInYears)*0.000001 + currDef.chance());
        return currDef.chance();
    } else {
        for(int j = 0; j < hystory.size(); j++) {
            if(currDef.type() == hystory[j].Defect.type()) {
                currDef.Set_chance(currDef.chance() + 0.02);
            }
        }
        return currDef.chance();
    }
}

int Auto::currDefVarCalculatingForAuto(defect &currDef, const int &userTimeInYears)
{
    const int num = Random::RandInt(1, 4);
    if (currDef.var() == -1) {
        return currDef.var();
    } else if (num == 1) {
        return currDef.var();
    } else if (num == 2) {
        currDef.Set_var(currDef.var() + 600*(QDate::currentDate().year() + userTimeInYears - _year));
        return currDef.var();
    } else if (num == 3) {
        currDef.Set_var(currDef.var() + ((_mileage + 12000*userTimeInYears) * 0.05));
        return currDef.var();
    } else {
        if(_manufacturer == "BMW-AG") {
            currDef.Set_var(currDef.var() + 7800);
        } else if (_manufacturer == "Toyota") {
            currDef.Set_var(currDef.var() + 5500);
        } else if (_manufacturer == "Nissan") {
            currDef.Set_var(currDef.var() + 4800);
        } else {//Porsche
            currDef.Set_var(currDef.var() + 13300);
        }
        return currDef.var();
    }
}


QString Auto::model()
{
    return _model;
}

QString Auto::manufacturer()
{
    return _manufacturer;
}

int Auto::year()
{
    return _year;
}

int Auto::miliage()
{
    return _mileage;
}

Auto::Auto()
{
    _year = 0;
    _mileage = 0;
}
