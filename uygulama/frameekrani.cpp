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

    headerLabel = new QLabel(" Header", this);
    headerLabel->setGeometry(startX, yOrta, 150, 50);
    headerLabel->setAlignment(Qt::AlignCenter);
    headerLabel->hide();

    dataLabel = new QLabel(this);
    dataLabel->setGeometry(startX, yOrta + 60, 150, 50);
    dataLabel->setAlignment(Qt::AlignCenter);
    dataLabel->hide();

    trailerLabel = new QLabel("🔚 Trailer", this);
    trailerLabel->setGeometry(startX, yOrta + 120, 150, 50);
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

    stuffingLabel = new QLabel(this);
    stuffingLabel->setGeometry(60, 400, 400, 60); // uygun bir yere yerleştir
    stuffingLabel->setStyleSheet("background-color:#F4F4F4; border:1px solid gray; font-size:10px; color:#333;");
    stuffingLabel->setWordWrap(true);
    stuffingLabel->hide(); // başta gizli

}



FrameEkrani::~FrameEkrani() {
    delete ui;
}

// Byte Stuffing
std::string FrameEkrani::applyByteStuffing(const std::string& rawData) {
    std::string stuffed;
    for (unsigned char ch : rawData) {
        if (ch == 0x7E || ch == 0x7D) {
            stuffed += 0x7D;
            stuffed += ch ^ 0x20;
        } else {
            stuffed += ch;
        }
    }
    return stuffed;
}

// Byte Unstuffing
std::string FrameEkrani::removeByteStuffing(const std::string& stuffedData) {
    std::string unstuffed;
    for (size_t i = 0; i < stuffedData.size(); ++i) {
        if (stuffedData[i] == 0x7D && i + 1 < stuffedData.size()) {
            unstuffed += stuffedData[i + 1] ^ 0x20;
            i++;
        } else {
            unstuffed += stuffedData[i];
        }
    }
    return unstuffed;
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

        // Frame parçaları birleştir
        std::string rawData = header[currentFrameIndex] + frameList[currentFrameIndex].toStdString() + crcList[currentFrameIndex];
        std::string stuffedData = applyByteStuffing(rawData);

        // Gösterilecek string hazırla
        QString stuffedStr;
        stuffedStr.clear(); // eğer önceden doldurulmuşsa sıfırla

        for (unsigned char c : stuffedData) {
            stuffedStr += QString::fromStdString(std::bitset<8>(c).to_string()) + "";

        }


        dataLabel->setText("📦 Stuffed Data:\n" + stuffedStr);


        QString headerText = QString::fromStdString(header[currentFrameIndex]);
        headerLabel->setText(" Header\n" + headerText);
        // Trailer içine CRC yaz
        QString crcText = QString::fromStdString(crcList[currentFrameIndex]);

        crcIcerik->setText("CRC:\n" + crcText);
        crcIcerik->show();
        // Frame parça birleşimi (header + data + crc)
        std::string fullFrameRaw = header[currentFrameIndex] + frameList[currentFrameIndex].toStdString() + crcList[currentFrameIndex];

        // Byte Stuffing uygula
        std::string stuffedFrame = applyByteStuffing(fullFrameRaw);


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
        QLabel* checksumFrame = new QLabel(this);
        checksumFrame->setGeometry(100, yKonum + 150, 300, 40);
        checksumFrame->setAlignment(Qt::AlignCenter);
        checksumFrame->setText("🧮 Checksum: 0x" + hexChecksum);
        checksumFrame->setStyleSheet("background-color:white; font-weight:bold; font-size: 14px; border: 2px solid black; border-radius: 10px; color: black;");
        checksumFrame->show();


        QPropertyAnimation* anim = new QPropertyAnimation(checksumFrame, "pos");
        anim->setDuration(2000);
        anim->setStartValue(QPoint(100, yKonum + 150));
        anim->setEndValue(QPoint(700, yKonum + 150));
        anim->start();

        QTimer::singleShot(2100, this, [=]() {
            // 🔧 BOZULMUŞ VERİ ÜZERİNDEN CHECKSUM HESAPLA
            std::vector<std::string> bozukCrcList = crcList;
            std::bitset<8> newChecksum;

            // %5 ihtimalle bir biti boz
            bool bozuldu = QRandomGenerator::global()->bounded(100) < 5;
            if (bozuldu && !bozukCrcList.empty()) {
                int frameIndex = QRandomGenerator::global()->bounded(static_cast<int>(bozukCrcList.size()));
                int bitIndex = QRandomGenerator::global()->bounded(16);
                bozukCrcList[frameIndex][bitIndex] = (bozukCrcList[frameIndex][bitIndex] == '0') ? '1' : '0';
            }

            // Yeni Checksum hesapla
            for (const std::string& crcStr : bozukCrcList) {
                std::bitset<16> b(crcStr);
                std::bitset<8> highByte(b.to_ulong() >> 8);
                std::bitset<8> lowByte(b.to_ulong() & 0xFF);
                newChecksum = std::bitset<8>((newChecksum.to_ulong() + highByte.to_ulong() + lowByte.to_ulong()) & 0xFF);
            }

            QString calculatedChecksum = QString("%1").arg(newChecksum.to_ulong(), 2, 16, QLatin1Char('0')).toUpper();

            if (calculatedChecksum != hexChecksum) {
                durumEtiketi->setText("❌ Checksum uyuşmazlığı tespit edildi!");
                checksumFrame->setStyleSheet("background-color:white; color: black; font-weight:bold;");
            } else {
                durumEtiketi->setText("✅ Checksum başarıyla ulaştı. ACK gönderiliyor...");

                // ✅ SON ACK ANİMASYONU
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
                    durumEtiketi->setText("🎉 Tüm veriler başarıyla iletildi. Transfer tamamlandı!");
                    checksumFrame->hide();
                });
                return;
            }

        });
    }


}
std::string FrameEkrani::extractDataFromUnstuffed(const std::string& unstuffedFrame, int headerLength, int crcLength) {
    if (unstuffedFrame.size() < headerLength + crcLength) return "";

    return unstuffedFrame.substr(headerLength, unstuffedFrame.size() - headerLength - crcLength);
}
std::string FrameEkrani::calculateCRC(const std::string& binaryData) {
    std::string generator = "10001000000100001";
    std::string data = binaryData + std::string(16, '0'); // CRC boşluğu

    for (size_t step = 0; step <= data.size() - generator.size(); ++step) {
        if (data[step] == '1') {
            for (size_t j = 0; j < generator.size(); ++j) {
                data[step + j] = (data[step + j] == generator[j]) ? '0' : '1';
            }
        }
    }

    return data.substr(data.size() - 16);
}


void FrameEkrani::kontrolEt() {
    ackTimer->stop();
    int rastgele = QRandomGenerator::global()->bounded(100);

    if (rastgele < 10) {
        durumEtiketi->setText("❌ Frame yolda kayboldu! Yeniden gönderiliyor...");
        QTimer::singleShot(3000, this, &FrameEkrani::gonderFrame);
        return;
    } else if (rastgele < 30) {
        durumEtiketi->setText("⚠ Frame bozuldu!");
        dataLabel->setText("📦 ❗");
        QTimer::singleShot(3000, this, &FrameEkrani::gonderFrame);
        return;
    } else if (rastgele < 45) {
        durumEtiketi->setText("🔁 ACK kayıp, gönderici tekrar bekliyor...");
        QTimer::singleShot(3000, this, &FrameEkrani::gonderFrame);
        return;
    }

    // ✅ Frame'i yeniden oluştur (stuffed haliyle)
    std::string fullFrameRaw = header[currentFrameIndex] + frameList[currentFrameIndex].toStdString() + crcList[currentFrameIndex];
    std::string stuffedFrame = applyByteStuffing(fullFrameRaw);

    // 🧹 Stuffed frame'i unstuff et
    std::string unstuffedFrame = removeByteStuffing(stuffedFrame);

    // 🔍 Header = 16 bit, CRC = 16 bit → aradan sadece DATA'yı ayıkla
    std::string extractedData = extractDataFromUnstuffed(unstuffedFrame, 16, 16);

    // 🔐 Gelen CRC (frame sonunda)
    std::string receivedCRC = unstuffedFrame.substr(unstuffedFrame.size() - 16);

    // 💥 %20 ihtimalle DATA'yı boz
    int bozulmaIhtimali = QRandomGenerator::global()->bounded(100);
    if (bozulmaIhtimali < 20 && !extractedData.empty()) {
        int bitIndex = QRandomGenerator::global()->bounded(static_cast<int>(extractedData.size()));
        extractedData[bitIndex] = (extractedData[bitIndex] == '0') ? '1' : '0';
        durumEtiketi->setText("⚠️ Veri CRC için bozuldu! CRC kontrolü bozuk veriyle yapılacak.");
    }

    // 🧮 CRC yeniden hesapla
    std::string recalculatedCRC = calculateCRC(extractedData);

    if (recalculatedCRC == receivedCRC) {
        // ✅ CRC eşleşti → ACK gönder
        durumEtiketi->setText("✅ Frame başarıyla ulaştı ve CRC eşleşti. ACK gönderiliyor...");

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

            headerLabel->hide();
            dataLabel->hide();
            trailerLabel->hide();
            crcIcerik->hide();

            QTimer::singleShot(1000, this, &FrameEkrani::gonderFrame);
        });
        return;

    } else {
        // ❌ CRC uyuşmadı
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
