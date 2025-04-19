#include "butonlar.h"
#include "ui_butonlar.h"

Butonlar::Butonlar(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Butonlar)
{
    ui->setupUi(this);
}

Butonlar::~Butonlar()
{
    delete ui;
}
