#include "butonlar.h"
#include "ui_butonlar.h"
#include "framepanel.h"  // 👈 bu satır şart!


Butonlar::Butonlar(const std::vector<std::string>& allFrames, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Butonlar)
    , frames(allFrames)
{
    ui->setupUi(this);
}

Butonlar::~Butonlar()
{
    delete ui;
}

void Butonlar::on_pushButton_clicked()
{
    hide();
    framePanel = new FramePanel(frames, this);
    framePanel->show();
    framePanel->startCrcAnimation();
}

