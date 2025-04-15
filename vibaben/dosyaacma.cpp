#include "dosyaacma.h"
#include "ui_dosyaacma.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

DosyaAcma::DosyaAcma(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DosyaAcma)
{
    ui->setupUi(this);

}

DosyaAcma::~DosyaAcma()
{
    delete ui;
}

void DosyaAcma::on_btn_dosyaAc_clicked()
{
    QString dosyaYolu = QFileDialog::getOpenFileName(this, "Dosya Seç", "", "Tüm Dosyalar (*.*)");
    if (!dosyaYolu.isEmpty()) {
        ui->lineEdit_dosyaYolu->setText(dosyaYolu);

        QFile dosya(dosyaYolu);
        if (dosya.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&dosya);
            QString icerik = stream.readAll();
            dosya.close();

            // İsteğe bağlı: içeriği QLabel ya da başka widget’a yazdırabilirsin
            QMessageBox::information(this, "Dosya İçeriği", icerik.left(1000)); // sadece ilk 1000 karakteri göster
        }
    }
}


void DosyaAcma::on_pushButton_clicked()
{
    hide();
    frameEkrani =new FrameEkrani(this);
    frameEkrani->show();
}

