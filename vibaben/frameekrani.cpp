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
    : QDialog(parent), ui(new Ui::FrameEkrani), currentFrameIndex(0) {
    ui->setupUi(this);
    this->setFixedSize(1024, 600);

#include <bitset>  // bunu unutma

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

        QString fullFrame = QString::fromStdString(frames[i]);
        frameList.append(fullFrame);

        std::bitset<16> binaryHeader(i);
        header.push_back(binaryHeader.to_string());

    }


    std::bitset<8> checksumBits;
    for (const std::string& crcStr : crcList) {
        std::bitset<16> b(crcStr);
        std::bitset<8> highByte(b.to_ulong() >> 8);
        std::bitset<8> lowByte(b.to_ulong() & 0xFF);
        checksumBits = std::bitset<8>((checksumBits.to_ulong() + highByte.to_ulong() + lowByte.to_ulong()) & 0xFF);
    }

    hexChecksum = QString("%1").arg(checksumBits.to_ulong(), 2, 16, QLatin1Char('0')).toUpper();
    checksumHexLabel = new QLabel("Checksum (hex): 0x" + hexChecksum, this);
    checksumHexLabel->setGeometry(820, 100, 300, 30);
    checksumHexLabel->setStyleSheet("color: green; font-weight: bold;");
    checksumHexLabel->show();

    int yOrta = height() / 2;
    int startX = 60;
    int endX = 800;

    headerLabel = new QLabel("🔢 Header", this);
    headerLabel->setGeometry(startX, yOrta, 150, 40);
    headerLabel->setAlignment(Qt::AlignCenter);
    headerLabel->hide();

    dataLabel = new QLabel(this);
    dataLabel->setGeometry(startX, yOrta + 60, 150, 40);
    dataLabel->setAlignment(Qt::AlignCenter);
    dataLabel->hide();

    trailerLabel = new QLabel("🔚 Trailer", this);
    trailerLabel->setGeometry(startX, yOrta + 120, 150, 40);
    trailerLabel->setAlignment(Qt::AlignCenter);
    trailerLabel->hide();

    // CRC içeriği Trailer kutusunun içinde
    crcIcerik = new QLabel(trailerLabel);
    crcIcerik->setGeometry(0, 0, trailerLabel->width(), trailerLabel->height());
    crcIcerik->setAlignment(Qt::AlignCenter);
    crcIcerik->setStyleSheet("color: darkred; font-size: 10px; font-weight: bold;");
    crcIcerik->hide();

    gondericiKutusu = new QLabel("📤 Gönderici", this);
    gondericiKutusu->setGeometry(startX, 80, 180, 50);
    gondericiKutusu->setAlignment(Qt::AlignCenter);
    gondericiKutusu->setStyleSheet("font-size: 20px; font-weight: bold; background-color: #D0E7FF; color:#3399FF; border: 2px solid #3399FF; border-radius: 15px;");

    aliciKutusu = new QLabel("📥 Alıcı", this);
    aliciKutusu->setGeometry(endX, 80, 180, 50);
    aliciKutusu->setAlignment(Qt::AlignCenter);
    aliciKutusu->setStyleSheet("font-size: 20px; font-weight: bold; background-color: #D0E7FF; color:#3399FF; border: 2px solid #3399FF; border-radius: 15px;");

    ackSinyali = new QLabel("✅ ACK", this);
    ackSinyali->setGeometry(aliciKutusu->x(), aliciKutusu->y() + 60, 100, 40);
    ackSinyali->setAlignment(Qt::AlignCenter);
    ackSinyali->setStyleSheet("background-color: lightgreen; border: 2px solid green; border-radius: 10px; font-weight: bold;");
    ackSinyali->hide();

    mektup = new QLabel("📄 Frame", this);
    mektup->setGeometry(startX, yOrta - 20, 100, 40);
    mektup->hide();

    durumEtiketi = new QLabel(this);
    durumEtiketi->setGeometry((width() - 600) / 2, height() - 60, 600, 40);
    durumEtiketi->setAlignment(Qt::AlignCenter);
    durumEtiketi->setStyleSheet("font-size: 16px; color: black; font-weight: bold;");

    gonderButonu = new QPushButton("📨 Frame Gönder", this);
    gonderButonu->setGeometry((width() - 200) / 2, 20, 200, 40);
    connect(gonderButonu, &QPushButton::clicked, this, &FrameEkrani::gonderFrame);
    gonderButonu->setStyleSheet("QPushButton { background-color: #1746A2; color: white; font-size: 16px; font-weight: bold; border-radius: 20px; } QPushButton:hover { background-color: #3567d1; }");

    ackTimer = new QTimer(this);
    connect(ackTimer, &QTimer::timeout, this, &FrameEkrani::kontrolEt);
}

FrameEkrani::~FrameEkrani() {
    delete ui;
}

void FrameEkrani::gonderFrame() {
    int yKonum = height() / 2;
    int startX = 100;
    int endX = 700;
    int aralik = 150;

    if (currentFrameIndex < frameList.size()) {
        headerLabel->move(startX, yKonum);
        dataLabel->move(startX + aralik, yKonum);
        trailerLabel->move(startX + 2 * aralik, yKonum);

        headerLabel->show();
        dataLabel->show();
        trailerLabel->show();

        QString style = "background-color: white; border: 2px solid #333; border-radius: 10px; padding: 5px; color:black;";
        headerLabel->setStyleSheet(style);
        dataLabel->setStyleSheet(style);
        trailerLabel->setStyleSheet(style);

        dataLabel->setText("📦 " + frameList[currentFrameIndex]);

        QString headerText = QString::fromStdString(header[currentFrameIndex]);
        headerLabel->setText(" Header\n" + headerText);
        // Trailer içine CRC yaz
        QString crcText = QString::fromStdString(crcList[currentFrameIndex]);

        crcIcerik->setText("CRC:\n" + crcText);
        crcIcerik->show();

        durumEtiketi->setText(QString("📤 Frame %1 gönderiliyor...").arg(currentFrameIndex + 1));

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
    } else {
        QLabel* checksumFrame = new QLabel("🧮 Checksum: 0x" + hexChecksum, this);
        checksumFrame->setGeometry(100, yKonum + 150, 250, 40);
        checksumFrame->setStyleSheet("background-color:white; font-weight:bold;");
        checksumFrame->show();

        QPropertyAnimation* anim = new QPropertyAnimation(checksumFrame, "pos");
        anim->setDuration(2000);
        anim->setStartValue(QPoint(100, yKonum + 150));
        anim->setEndValue(QPoint(700, yKonum + 150));
        anim->start();

        QTimer::singleShot(2100, this, [=]() {
            int r = QRandomGenerator::global()->bounded(100);
            if (r < 5) {
                durumEtiketi->setText("❌ Checksum bozuldu!");
                checksumFrame->setStyleSheet("color: red;");
            } else {
                durumEtiketi->setText("✅ Checksum başarıyla ulaştı.");
            }
            checksumFrame->hide();
        });
    }
}

void FrameEkrani::kontrolEt() {
    ackTimer->stop();
    int rastgele = QRandomGenerator::global()->bounded(100);

    if (rastgele < 10) {
        durumEtiketi->setText("❌ Frame yolda kayboldu!");
        return;
    } else if (rastgele < 30) {
        durumEtiketi->setText("⚠ Frame bozuldu!");
        dataLabel->setText("📦 ❗");
        QTimer::singleShot(1000, this, &FrameEkrani::gonderFrame);
        return;
    } else if (rastgele < 45) {
        durumEtiketi->setText("🔁 ACK kayıp, gönderici tekrar bekliyor...");
        QTimer::singleShot(2000, this, &FrameEkrani::gonderFrame);
        return;
    }

    // ✅ CRC DOĞRULAMA
    QString currentData = frameList[currentFrameIndex];
    QString currentCRC = QString::fromStdString(crcList[currentFrameIndex]);

    std::string data = currentData.toStdString() + std::string(16, '0');
    std::string generator = "10001000000100001";

    for (size_t step = 0; step <= data.size() - generator.size(); ++step) {
        if (data[step] == '1') {
            for (size_t j = 0; j < generator.size(); ++j) {
                data[step + j] = (data[step + j] == generator[j]) ? '0' : '1';
            }
        }
    }

    std::string calculatedCRC = data.substr(data.size() - 16);

    if (calculatedCRC == currentCRC.toStdString()) {
        durumEtiketi->setText("✅ Frame başarıyla ulaştı ve CRC eşleşti. ACK gönderiliyor...");

        // ✅ ACK ANİMASYONU
        int startX = aliciKutusu->x() + aliciKutusu->width() / 2 - ackSinyali->width() / 2;
        int endX = gondericiKutusu->x() + gondericiKutusu->width() / 2 - ackSinyali->width() / 2;
        int yKonum = aliciKutusu->y() + aliciKutusu->height() + 20;

        ackSinyali->move(startX, yKonum);
        ackSinyali->show();

        QPropertyAnimation* ackAnim = new QPropertyAnimation(ackSinyali, "pos");
        ackAnim->setDuration(2000);
        ackAnim->setStartValue(QPoint(startX, yKonum));
        ackAnim->setEndValue(QPoint(endX, yKonum));
        ackAnim->start();

        connect(ackAnim, &QPropertyAnimation::finished, this, [=]() {
            ackSinyali->hide();
            currentFrameIndex++;

            // Görselleri gizle
            headerLabel->hide();
            dataLabel->hide();
            trailerLabel->hide();
            crcIcerik->hide();

            QTimer::singleShot(1000, this, &FrameEkrani::gonderFrame);
        });
        return;

    } else {
        durumEtiketi->setText("❌ CRC uyuşmazlığı tespit edildi! Frame yeniden gönderiliyor.");
        QTimer::singleShot(1000, this, &FrameEkrani::gonderFrame);
        return;
    }
}


void FrameEkrani::frameIlerle() {
    int startX = gondericiKutusu->x() + gondericiKutusu->width() / 2 - mektup->width() / 2;
    int endX = aliciKutusu->x() + aliciKutusu->width() / 2 - mektup->width() / 2;
    int yKonum = gondericiKutusu->y() + gondericiKutusu->height() + 20;

    mektup->move(startX, yKonum);
    mektup->setText(QString("📄 Frame %1").arg(currentFrameIndex + 1));
    mektup->setStyleSheet("font-size: 18px; font-weight: bold;");
    mektup->show();

    QPropertyAnimation* animasyon = new QPropertyAnimation(mektup, "pos");
    animasyon->setDuration(2000);
    animasyon->setStartValue(QPoint(startX, yKonum));
    animasyon->setEndValue(QPoint(endX, yKonum));
    animasyon->start();

    connect(animasyon, &QPropertyAnimation::finished, this, [=]() {
        mektup->hide();
    });
}
