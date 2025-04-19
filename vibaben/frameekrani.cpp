#include "frameekrani.h"
#include "ui_frameekrani.h"

#include <QRandomGenerator>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <bitset>

FrameEkrani::FrameEkrani(const std::vector<std::string>& frames, QWidget *parent)
    : QDialog(parent), ui(new Ui::FrameEkrani) {
    ui->setupUi(this);
    this->setFixedSize(1024, 600); // Sabit ekran boyutu

    // CRC hesaplama (önceki haliyle aynı)
    std::string generator = "10001000000100001";
    for (int i = 0; i < frames.size(); ++i) {
        std::string data = frames[i] + std::string(16, '0');
        for (int step = 0; step <= data.size() - generator.size(); ++step) {
            if (data[step] == '1') {
                for (int j = 0; j < generator.size(); ++j) {
                    data[step + j] = (data[step + j] == generator[j]) ? '0' : '1';
                }
            }
        }
        std::string crcStr = data.substr(data.size() - 16);
        crcList.push_back(crcStr);
    }

    std::bitset<8> checksumBits;
    for (const std::string& crcStr : crcList) {
        std::bitset<16> b(crcStr);
        std::bitset<8> highByte(b.to_ulong() >> 8);
        std::bitset<8> lowByte(b.to_ulong() & 0xFF);
        checksumBits = std::bitset<8>((checksumBits.to_ulong() + highByte.to_ulong() + lowByte.to_ulong()) & 0xFF);
    }

    int yOrta = height() / 2;
    int startX = 60;
    int endX = 800;

    // Frame parçaları ortadan geçecek
    headerLabel = new QLabel("🔢 Header", this);
    headerLabel->setGeometry(startX, yOrta, 150, 40);
    headerLabel->setAlignment(Qt::AlignCenter);
    headerLabel->hide();

    dataLabel = new QLabel("📦 Data", this);
    dataLabel->setGeometry(startX, yOrta+60, 150, 40);
    dataLabel->setAlignment(Qt::AlignCenter);
    dataLabel->hide();

    trailerLabel = new QLabel("🔚 Trailer", this);
    trailerLabel->setGeometry(startX, yOrta + 120, 150, 40);
    trailerLabel->setAlignment(Qt::AlignCenter);
    trailerLabel->hide();

    // Gönderici ve Alıcı
    gondericiKutusu = new QLabel("📤 Gönderici", this);
    gondericiKutusu->setGeometry(startX, 80, 180, 50);
    gondericiKutusu->setAlignment(Qt::AlignCenter);
    gondericiKutusu->setStyleSheet(
        "font-size: 20px; font-weight: bold; background-color: #D0E7FF; color:#3399FF; "
        "border: 2px solid #3399FF; border-radius: 15px;"
        );

    aliciKutusu = new QLabel("📥 Alıcı", this);
    aliciKutusu->setGeometry(endX, 80, 180, 50);
    aliciKutusu->setAlignment(Qt::AlignCenter);
    aliciKutusu->setStyleSheet(
        "font-size: 20px; font-weight: bold; background-color: #D0E7FF; color:#3399FF; "
        "border: 2px solid #3399FF; border-radius: 15px;"
        );

    // Frame simgesi
    mektup = new QLabel("📄 Frame", this);
    mektup->setGeometry(startX, yOrta - 20, 100, 40);
    mektup->hide();

    // Durum etiketi ekranın altında
    durumEtiketi = new QLabel(this);
    durumEtiketi->setGeometry((width() - 600) / 2, height() - 60, 600, 40);
    durumEtiketi->setAlignment(Qt::AlignCenter);
    durumEtiketi->setStyleSheet("font-size: 16px; color: black; font-weight: bold;");

    // Gönder butonu
    gonderButonu = new QPushButton("📨 Frame Gönder", this);
    gonderButonu->setGeometry((width() - 200) / 2, 20, 200, 40);
    connect(gonderButonu, &QPushButton::clicked, this, &FrameEkrani::gonderFrame);

    gonderButonu->setStyleSheet(
        "QPushButton {"
        " background-color: #1746A2;"
        " color: white;"
        " font-size: 16px;"
        " font-weight: bold;"
        " border-radius: 20px;"
        " }"
        "QPushButton:hover {"
        " background-color: #3567d1;"
        " }"
        );

    ackTimer = new QTimer(this);
    connect(ackTimer, &QTimer::timeout, this, &FrameEkrani::kontrolEt);
}


FrameEkrani::~FrameEkrani() {
    delete ui;
}

void FrameEkrani::gonderFrame() {
    int startX = 100;
    int endX = 700; // Tek bir hedef noktası

    int yKonum = height() / 2;
    int aralik = 150; // Aralarındaki mesafe

    // Başlangıç pozisyonları
    headerLabel->move(startX, yKonum);
    dataLabel->move(startX + aralik, yKonum);
    trailerLabel->move(startX + 2 * aralik, yKonum);

    headerLabel->show();
    dataLabel->show();
    trailerLabel->show();

    QString style = "background-color: white; border: 2px solid #333; border-radius: 10px; padding: 5px;";
    headerLabel->setStyleSheet(style);
    dataLabel->setStyleSheet(style);
    trailerLabel->setStyleSheet(style);

    durumEtiketi->setText("📤 Frame gönderiliyor (Header + Data + Trailer)...");

    // Animasyonla hepsini aynı hızda ve aralıkla taşıyoruz
    headerAnim = new QPropertyAnimation(headerLabel, "pos");
    headerAnim->setDuration(2000);
    headerAnim->setStartValue(QPoint(startX, yKonum));
    headerAnim->setEndValue(QPoint(endX, yKonum));

    dataAnim = new QPropertyAnimation(dataLabel, "pos");
    dataAnim->setDuration(2000);
    dataAnim->setStartValue(QPoint(startX + aralik, yKonum));
    dataAnim->setEndValue(QPoint(endX + aralik, yKonum));

    trailerAnim = new QPropertyAnimation(trailerLabel, "pos");
    trailerAnim->setDuration(2000);
    trailerAnim->setStartValue(QPoint(startX + 2 * aralik, yKonum));
    trailerAnim->setEndValue(QPoint(endX + 2 * aralik, yKonum));

    headerAnim->start();
    dataAnim->start();
    trailerAnim->start();

    ackTimer->start(2100);
}


void FrameEkrani::kontrolEt() {
    ackTimer->stop();
    int rastgele = QRandomGenerator::global()->bounded(100);

    if (rastgele < 10) {
        durumEtiketi->setText("❌ Frame yolda kayboldu!");
        headerLabel->hide();
        dataLabel->hide();
        trailerLabel->hide();
    }
    else if (rastgele < 30) {
        durumEtiketi->setText("⚠ Frame bozuldu, tekrar gönderilecek.");
        dataLabel->setText("📦 ❗");
        QTimer::singleShot(1000, this, &FrameEkrani::gonderFrame);
    }
    else if (rastgele < 45) {
        durumEtiketi->setText("🔁 ACK kayıp, tekrar gönderiliyor.");
        QTimer::singleShot(1000, this, &FrameEkrani::gonderFrame);
    }
    else {
        durumEtiketi->setText("✅ Frame başarıyla ulaştı.");
        headerLabel->hide();
        dataLabel->hide();
        trailerLabel->hide();
    }
}

void FrameEkrani::frameIlerle() {
    // İleride animasyonla frame ilerletmek istersen burayı kullanabilirsin
}
