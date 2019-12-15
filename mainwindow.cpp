#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createAutoList();
}

void MainWindow::createAutoList()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(6,10);
    const int autoListSize = dist(gen);
    Auto car;
    for(int i = 0; i < autoListSize; i++) {
        QListWidgetItem *carInfo = new QListWidgetItem;
        car.generateAuto();
        autoList.push_back(car);
        car.clearHystory();
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

}
