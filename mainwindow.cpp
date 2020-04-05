#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "random.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createAutoList();
}

void MainWindow::createAutoList()
{
    const int autoListSize = Random::RandInt(6, 10);
    Auto car;
    for(int i = 0; i < autoListSize; i++) {
        QListWidgetItem *carInfo = new QListWidgetItem;
        car.generateAuto();
        autoList.push_back(car);
        car.hystory.clear();
        carInfo->setText(autoList.back().model() + "  " + autoList.back().manufacturer());
        ui->AutoList->addItem(carInfo);
    }

}



MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_SetTimeButton_clicked()
{
    if(ui->SettedDefect->toPlainText() == "" || ui->SettedAuto->toPlainText() == "" || (ui->SetTime->text().toInt() < 1 || ui->SetTime->text().toInt() > 10)) { return; }
    defect currDef(ui->SettedDefect->toPlainText());
    const int userTimeInYears = ui->SetTime->text().toInt();
    const int i = ui->AutoList->currentRow();
    const double updatedChance = autoList[i].currDefChanceCalculatingForAuto(currDef, userTimeInYears);
    const int updatedVar = autoList[i].currDefVarCalculatingForAuto(currDef, userTimeInYears);

    ui->AlgorithmResults->setText("CAR: " + autoList[i].model() + " " + autoList[i].manufacturer() +
                                  "\nDEFECT TYPE: " + ui->SettedDefect->toPlainText() +
                                  "\nTIME PERIOD: " + QString::number(userTimeInYears) + " years" +
                                  "\n\nExpacted Chance: " + QString::number(updatedChance) +
                                  "\n\nExpacted Var: " + QString::number(updatedVar));

}

void MainWindow::on_DefectList_itemSelectionChanged()
{
    QListWidgetItem *i = new QListWidgetItem;
    i = ui->DefectList->currentItem();
    ui->SettedDefect->setText(i->text());
    SetDefectInformation(i->text());
}

void MainWindow::SetDefectInformation(const QString type)
{
    if(type == "A") {
        ui->DefectInformation->setText("Type A. High defect."
                                       "\nDefault chance: " + QString::number(defect("A").chance()) +
                                       "\nDefault var: " + QString::number(defect("A").var()) + " (faulty)"
                                       "\n\nManifested in next cars:" + hystoryChecking("A"));
    } else if (type == "B") {
        ui->DefectInformation->setText("Type B. Middle defect."
                                       "\nDefault chance: " + QString::number(defect("B").chance()) +
                                       "\nDefault var: " + QString::number(defect("B").var()) +
                                       "\n\nManifested in next cars:" + hystoryChecking("B"));
    } else if (type == "C") {
        ui->DefectInformation->setText("Type C. Middle-Light defect."
                                       "\nDefault chance: " + QString::number(defect("C").chance()) +
                                       "\nDefault var: " + QString::number(defect("C").var()) +
                                       "\n\nManifested in next cars:" + hystoryChecking("C"));
    } else {
        ui->DefectInformation->setText("Type D. Light defect."
                                       "\nDefault chance: " + QString::number(defect("D").chance()) +
                                       "\nDefault var: " + QString::number(defect("D").var()) +
                                       "\n\nManifested in next cars:" + hystoryChecking("D"));
    }
}

QString MainWindow::hystoryChecking(const QString type)
{
    QString hystoryInfo;
    defect temp(type);
    int counter = 0;
    for(int i = 0; i < autoList.size(); i++) {
        for(int j = 0; j < autoList[i].hystory.size(); j++) {
            if(autoList[i].hystory[j].Defect.type() == temp.type()) { counter++; }
        }
        hystoryInfo = hystoryInfo + "\n" + autoList[i].model() + " " + autoList[i].manufacturer() + " " + QString::number(counter);
        counter = 0;
    }
    return hystoryInfo;
}


void MainWindow::on_AutoList_itemSelectionChanged()
{
    const int i = ui->AutoList->currentRow();
    ui->SettedAuto->setText(autoList[i].model());
}




void MainWindow::on_AutoList_itemDoubleClicked(QListWidgetItem *item)
{
    item = new QListWidgetItem;
    const int i = ui->AutoList->currentRow();
    ui->DefectInformation->setText("MODEL: " + autoList[i].model() +
                                   "\nMANUFACTURER: " + autoList[i].manufacturer() +
                                   "\nYEAR: " + QString::number(autoList[i].year()) +
                                   "\nMILEAGE: " + QString::number(autoList[i].miliage()) +
                                   "\nHYSTORY: " + autoList[i].hystoryInString());

}
