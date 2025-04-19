#include "butonlar.h"
#include "ui_butonlar.h"
#include "framepanel.h"
#include "crctablo.h"
#include "checksum.h"

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

// 1. Buton → FramePanel (animasyonlu CRC adım adım)
void Butonlar::on_pushButton_clicked()
{
    hide();
    framePanel = new FramePanel(frames, this);
    framePanel->show();
    framePanel->startCrcAnimation();
}

<<<<<<< Updated upstream
// 2. Buton → CRC Tablosu
void Butonlar::on_pushButton_2_clicked()
{

    crcTablo = new CrcTablo(frames, this);
    crcTablo->show();
}

// 3. Buton → Doğrudan Checksum
void Butonlar::on_pushButton_3_clicked()
{
    // CRC listesi hesapla
    std::string generator = "10001000000100001";
    std::vector<std::string> crcList;

    for (const auto& frame : frames) {
        std::string data = frame + std::string(16, '0');
        for (size_t step = 0; step <= data.size() - generator.size(); ++step) {
            if (data[step] == '1') {
                for (size_t j = 0; j < generator.size(); ++j) {
                    data[step + j] = (data[step + j] == generator[j]) ? '0' : '1';
                }
            }
        }
        crcList.push_back(data.substr(data.size() - 16));
    }


    checksum = new Checksum(frames, crcList, this);
    checksum->show();
}
=======

void Butonlar::on_pushButton_4_clicked()
{
    frameEkrani = new FrameEkrani(frames, this);
    frameEkrani->show();
    //frameEkrani->startCrcAnimation();
}

>>>>>>> Stashed changes
