#include "butonlar.h"
#include "ui_butonlar.h"

Butonlar::Butonlar(const std::vector<std::string>& allFrames, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Butonlar)
{
    ui->setupUi(this);
}

Butonlar::~Butonlar()
{
    delete ui;
}
