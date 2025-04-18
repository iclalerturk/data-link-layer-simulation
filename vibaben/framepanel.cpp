#include "framepanel.h"
#include "ui_framepanel.h"
#include <QVBoxLayout>
#include <QTimer>

FramePanel::FramePanel(const std::vector<std::string>& allFrames, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FramePanel)
    , frameBits(allFrames[0])  // sadece ilk frame ile animasyon yap
    , frames(allFrames)        // tüm frameleri CRC tablosu için sakla
    , step(0)
{
    ui->setupUi(this);

    QVBoxLayout* layout = new QVBoxLayout(this);

    frameLabel = new QLabel(QString::fromStdString("Frame: " + frameBits));
    frameLabel->setStyleSheet("font-family: monospace;");

    crcAnimLabel = new QLabel();
    crcAnimLabel->setStyleSheet("font-family: monospace; color: blue;");

    crcResultLabel = new QLabel("CRC: ?");
    crcResultLabel->setStyleSheet("font-weight: bold;");

    layout->addWidget(frameLabel);
    layout->addWidget(crcAnimLabel);
    layout->addWidget(crcResultLabel);

    // Başlangıç CRC verisi oluştur
    data = frameBits + std::string(16, '0');

    // CRC-16 polynomial: "10001000000100001" örnek
    generator = "10001000000100001";  // 17 bit (CRC-16 için)

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FramePanel::nextStep);
}

FramePanel::~FramePanel()
{
    delete ui;
}

void FramePanel::startCrcAnimation() {
    updateDisplay();
    timer->start(250); // 250 ms per step
}

void FramePanel::nextStep() {
    if (step > data.size() - generator.size()) {
        timer->stop();
        QString crc = QString::fromStdString(data.substr(data.size() - 16));
        crcResultLabel->setText("CRC: " + crc);

        // Yeni CRC Tablosu sayfası aç
        CrcTablo* tablo = new CrcTablo(frames, this);
        this->hide();
        tablo->show();
        return;
    }


    if (data[step] == '1') {
        for (size_t j = 0; j < generator.size(); ++j) {
            data[step + j] = (data[step + j] == generator[j]) ? '0' : '1';
        }
    }

    step++;
    updateDisplay();
}

void FramePanel::updateDisplay() {
    QString html = "<code>";
    for (int i = 0; i < data.size(); ++i) {
        if (i >= step && i < step + generator.size())
            html += "<span style='color: red;'>" + QString(data[i]) + "</span>";
        else
            html += QString(data[i]);
    }
    html += "</code>";
    crcAnimLabel->setText(html);
}
