#include "framepanel.h"
#include "ui_framepanel.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QFont>

FramePanel::FramePanel(const std::vector<std::string>& allFrames, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FramePanel)
    , frameBits(allFrames[0])
    , frames(allFrames)
    , step(0)
{
    ui->setupUi(this);

    // Arka plan rengi - soft mavi
    this->setObjectName("FramePanel");
    this->setStyleSheet("QDialog#FramePanel { background-color: #e3f2fd; }");

    // Ana layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(15);

    // Frame verisini gösteren etiket
    frameLabel = new QLabel(QString::fromStdString("Frame: " + frameBits));
    frameLabel->setStyleSheet("font-weight: bold; font-size: 16px; color: #0d47a1; padding: 4px;");
    layout->addWidget(frameLabel);

    // CRC animasyonu için gösterim alanı (mavi tonlarda)
    crcAnimLabel = new QLabel();
    crcAnimLabel->setStyleSheet(
        "font-family: Consolas; font-size: 16px; color: #1565c0;"
        "background-color: white; padding: 10px; border-radius: 10px;"
        "border: 1px solid #bbdefb;"
        );
    crcAnimLabel->setWordWrap(true);
    layout->addWidget(crcAnimLabel);

    // CRC sonucunu gösteren etiket (mavi ton)
    crcResultLabel = new QLabel("CRC: ?");
    crcResultLabel->setStyleSheet("font-weight: bold; font-size: 16px; color: #0d47a1; padding: 4px;");
    layout->addWidget(crcResultLabel);

    // Geri dön butonu (mavi tema)
    QPushButton* backButton = new QPushButton("🔙 Geri Dön");
    backButton->setStyleSheet(
        "background-color: #64b5f6; color: white; padding: 10px; font-size: 14px;"
        "border: none; border-radius: 8px;"
        );
    layout->addWidget(backButton);
    connect(backButton, &QPushButton::clicked, this, &FramePanel::close);

    // Zamanlayıcı kur
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FramePanel::nextStep);

    // CRC datasını ve generator'ü başlat
    generator = "10001000000100001";  // 17 bit CRC-16 generator
    data = frameBits + std::string(16, '0');

    updateDisplay();
}

FramePanel::~FramePanel()
{
    delete ui;
}

void FramePanel::startCrcAnimation() {
    step = 0;
    data = frameBits + std::string(16, '0');
    crcResultLabel->setText("CRC: ?");
    updateDisplay();
    timer->start(250);  // 250 ms adım süresi
}

void FramePanel::nextStep() {
    if (step > data.size() - generator.size()) {
        timer->stop();
        QString crc = QString::fromStdString(data.substr(data.size() - 16));
        crcResultLabel->setText("CRC: " + crc);

        // CRC tablo penceresini aç
        crcTablo = new CrcTablo(frames, this);
        this->hide();
        crcTablo->show();
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
    QString html = "<code style='font-size: 17px; letter-spacing: 1px;'>";
    for (int i = 0; i < data.size(); ++i) {
        if (i >= step && i < step + generator.size())
            html += "<span style='color: #6a1b9a; font-weight: bold;'>" + QString(data[i]) + "</span>"; // sadece XOR kısmı mor
        else
            html += QString(data[i]);
    }
    html += "</code>";
    crcAnimLabel->setText(html);
}
