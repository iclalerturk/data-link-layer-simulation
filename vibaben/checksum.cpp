#include "checksum.h"
#include "ui_checksum.h"
#include <bitset>

Checksum::Checksum(const std::vector<std::string>& frames, const std::vector<std::string>& crcList, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::Checksum)
{
    ui->setupUi(this);

    // CRC'leri QStringList'e dönüştür
    for (const auto& crc : crcList)
        crcQStringList.append(QString::fromStdString(crc));

    // CRC'leri arayüzde listele
    for (const QString& crc : crcQStringList)
        ui->listWidget->addItem("CRC: " + crc);

    startChecksumAnimation();
}

Checksum::~Checksum()
{
    delete ui;
}

void Checksum::startChecksumAnimation()
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Checksum::calculateStep);
    timer->start(1000);  // Her saniyede bir adım
}

void Checksum::calculateStep()
{
    if (currentIndex < crcQStringList.size()) {
        // CRC string'ini al ve binary'ye dönüştür
        std::string crcStr = crcQStringList[currentIndex].toStdString();

        // CRC'yi 16 bitlik bir bitset'e dönüştür
        std::bitset<16> b(crcStr);

        // İlk 8 bit ve son 8 bit parçalara ayır
        std::bitset<8> highByte(b.to_ulong() >> 8); // İlk 8 bit
        std::bitset<8> lowByte(b.to_ulong() & 0xFF); // Son 8 bit

        // Her iki byte'ı toplama işlemi ve toplamı 8 bitlik yapmak için & 0xFF
        checksumBits = std::bitset<8>((checksumBits.to_ulong() + highByte.to_ulong() + lowByte.to_ulong()) & 0xFF);

        // Ekranda adım bilgisini göster
        ui->labelStep->setText(
            QString("Adım %1: + %2 + %3 → Toplam: %4")
                .arg(currentIndex + 1)
                .arg(QString::fromStdString(highByte.to_string()))
                .arg(QString::fromStdString(lowByte.to_string()))
                .arg(QString::fromStdString(checksumBits.to_string()))
            );

        // Görsel efekt (isteğe bağlı)
        ui->labelStep->setStyleSheet("background-color: blue;");
        timer->start(100); // Her 100ms'de bir adım
        QTimer::singleShot(50, [=]() {
            ui->labelStep->setStyleSheet("");
        });


        currentIndex++;
    } else {
        timer->stop();
        std::string hex = toHex(checksumBits.to_ulong());
        ui->labelHex->setText("Checksum (hex): " + QString::fromStdString(hex));
    }
}

// C++-style Hex dönüşümü
std::string Checksum::toHex(unsigned long value)
{
    std::string hex = "";
    const char* hexchars = "0123456789ABCDEF";
    for (int i = 28; i >= 0; i -= 4) {
        hex += hexchars[(value >> i) & 0xF];
    }
    return hex;
}

// Qt-style Hex dönüşümü (isteğe bağlı)
QString Checksum::toHexQt(quint32 value)
{
    return QString::number(value, 16).toUpper().rightJustified(8, '0');
}
