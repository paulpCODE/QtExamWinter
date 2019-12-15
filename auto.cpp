#include "auto.h"


available::available()
{
    ModelAndManufacturer = {make_pair("X5","BMW AG"), make_pair("X6","BMW AG"), make_pair("X7","BMW AG"),
                            make_pair("Camry","Toyota"), make_pair("RAV4","Toyota"), make_pair("Corolla","Toyota"),
                            make_pair("Juke","Nissan"), make_pair("X-TRAIL","Nissan"), make_pair("Navara","Nissan"),
                            make_pair("Panamera","Porsche"), make_pair("Taycan","Porsche"), make_pair("Macan","Porsche")};
}


Auto Auto::generateAuto()
{
    const QDate currDate = QDate::currentDate();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distNum(0, 11);
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


        _hystory.push_back(element);
    }
}

void Auto::clearHystory()
{
    _hystory.clear();
}

QString Auto::model()
{
    return _model;
}

QString Auto::manufacturer()
{
    return _manufacturer;
}

Auto::Auto()
{
    _year = 0;
    _mileage = 0;
}
