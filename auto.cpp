#include "auto.h"


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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distNum(0, ModelAndManufacturer.size() - 1);
    std::uniform_int_distribution<> distCount(1, 4);
    std::uniform_int_distribution<> distYear(2000, currDate.year() - 1);
    std::uniform_int_distribution<> distmileage(5, 20);

    const int i = distNum(gen);
    int count = 0;
    _model = ModelAndManufacturer[i].first;
    _manufacturer = ModelAndManufacturer[i].second;
    _year = distYear(gen);
    _mileage = 1000*distmileage(gen) + 12000*(currDate.year() - _year);
    count = distCount(gen) + currDate.year() - _year;
    _generateHystory(count);

    return *this;
}

void Auto::_generateHystory(const int &count)
{
    const QDate currDate = QDate::currentDate();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distDay(1, 31);
    std::uniform_int_distribution<> distMon(1, 12);
    std::uniform_int_distribution<> distYear(_year, currDate.year() - 1);

    DefectInformation element;
    int day, mon, year;

    for (int i = 0; i < count; i++) {
        element.Defect.SetRandType();
        day = distDay(gen);
        mon = distMon(gen);
        year = distYear(gen);
        element.appeared.setDate(year, mon, day);
        day = day + distDay(gen);
        if(day > 31) { day = day - 31; mon++; }
        mon = mon + distMon(gen);
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

double Auto::currDefChanceCalculatingForAuto(defect &currDef, Auto car, const int &userTimeInYears)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rand(1, 4);
    const int num = rand(gen);
    if(num == 1) { //fix
        return currDef.chance();
    } else if (num == 2) { //_year
        currDef.Set_chance(currDef.chance() + 0.001*(QDate::currentDate().year() + userTimeInYears - _year));
        return currDef.chance();
    } else if (num == 3) {
        currDef.Set_chance(currDef.chance() + ((_mileage + 12000*userTimeInYears) / 10000000));
        return currDef.chance();
    } else {
        for(int j = 0; j < hystory.size(); j++) {
            if(currDef.type() == hystory[j].Defect.type()) {
                currDef.Set_chance(currDef.chance() + 0.002);
            }
        }
        return currDef.chance();
    }
}

int Auto::currDefVarCalculatingForAuto(defect &currDef, Auto car, const int &userTimeInYears)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rand(1, 4);
    const int num = rand(gen);
    if (currDef.var() == -1) {
        return currDef.var();
    } else if (num == 1) {
        return currDef.var();
    } else if (num == 2) {
        currDef.Set_var(currDef.var() + 1100*(QDate::currentDate().year() + userTimeInYears - _year));
        return currDef.var();
    } else if (num == 3) {
        currDef.Set_var(currDef.var() + ((_mileage + 12000*userTimeInYears) / 10));
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
