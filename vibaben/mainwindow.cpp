#include "mainwindow.h"
#include "./ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->basla->setStyleSheet(
        "QPushButton {"
         " background-color: #1746A2;"
        //" color: white;"
        //" font-size: 20px;"
        " border-radius: 20px;"
        " }"
        "QPushButton:hover {"
        " background-color: #3567d1;"
        " }"
        );

    ui->label->setStyleSheet(
        "QLabel {"
        "background-color: #1746A2;"     // Açık sarı (isteğe göre değiştirilebilir)
        "border-radius: 20px;"           // Köşeleri yumuşatır
        "padding: 8px 12px;"             // İç boşluk
        "color: #ffffff;"                // Yazı rengi (uyumlu bir kahverengi tonu)
            // Eğik yazı (mizahi alt yazı gibi)
        "}"
        );
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_basla_clicked()
{
    hide();
    dosyaAcma = new DosyaAcma(this);
    dosyaAcma->show();
}


