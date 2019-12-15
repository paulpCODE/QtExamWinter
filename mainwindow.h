#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include "auto.h"
#include "defect.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    std::vector<Auto> autoList;

private slots:
    void createAutoList();
    void SetDefectInformation(const QString type);
    QString hystoryChecking(const QString type);


    void on_SetTimeButton_clicked();

    void on_DefectList_itemSelectionChanged();

    void on_AutoList_itemSelectionChanged();

    void on_AutoList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
