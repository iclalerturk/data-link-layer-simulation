#include "checksum.h"
#include "ui_checksum.h"
#include <bitset>
#include <QPropertyAnimation>
#include <QPalette>
#include <QTimer>

Checksum::Checksum(const std::vector<std::string>& frames, const std::vector<std::string>& crcList, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::Checksum)
{
    ui->setupUi(this);

    // Arka plan rengi (sayfa)
    this->setObjectName("ChecksumDialog");
    this->setStyleSheet("QDialog#ChecksumDialog { background-color: #e3f2fd; }");

    // Üst başlık label
    ui->label->setStyleSheet(
        "QLabel {"
        "background-color: #1746A2;"
        "border-radius: 20px;"
        "padding: 8px 12px;"
        "color: white;"
        "font-size: 16px;"
        "}"
        );

    // Adım açıklama yazısı
    ui->labelStep->setStyleSheet(
        "color: black;"
        "font-size: 14px;"
        "font-weight: bold;"
        );

    // Hex sonucu
    ui->labelHex->setStyleSheet(
        "color: black; font-weight: bold; font-size: 16px;"
        );

    // Liste görünümü
    ui->listWidget->setStyleSheet(
        "QListWidget {"
        " background-color: white;"
        " color: black;"
        " font-size: 13px;"
        " border-radius: 10px;"
        " padding: 6px;"
        "}"
        "QListWidget::item:selected {"
        " background-color: #bbdefb;"
        " color: black;"
        "}"
        );

    // CRC verilerini listele
    for (const auto& crc : crcList)
        crcQStringList.append(QString::fromStdString(crc));

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
    timer->start(100);  // 1 saniyede bir adım
}

void Checksum::calculateStep()
{
    if (currentIndex < crcQStringList.size()) {
        std::string crcStr = crcQStringList[currentIndex].toStdString();
        std::bitset<16> b(crcStr);

        std::bitset<8> highByte(b.to_ulong() >> 8);
        std::bitset<8> lowByte(b.to_ulong() & 0xFF);

        checksumBits = std::bitset<8>((checksumBits.to_ulong() + highByte.to_ulong() + lowByte.to_ulong()) & 0xFF);

        ui->labelStep->setText(
            QString("Adım %1: + %2 + %3 → Toplam: %4")
                .arg(currentIndex + 1)
                .arg(QString::fromStdString(highByte.to_string()))
                .arg(QString::fromStdString(lowByte.to_string()))
                .arg(QString::fromStdString(checksumBits.to_string()))
            );

        // Animasyon sadece arka plan rengi için çalışacak
        QColor startColor = QColor("#e3f2fd");
        QColor endColor = QColor("#e3f2fd");
        QString baseStyle = "color: black; font-weight: bold; font-size: 14px;";

        QPropertyAnimation* colorAnim = new QPropertyAnimation(this, "dummyProperty");
        colorAnim->setDuration(500);
        colorAnim->setStartValue(0.0);
        colorAnim->setEndValue(1.0);
        colorAnim->setEasingCurve(QEasingCurve::InOutQuad);

        connect(colorAnim, &QPropertyAnimation::valueChanged, [=](const QVariant &value) {
            QColor mixed;
            mixed.setRedF(startColor.redF() + (endColor.redF() - startColor.redF()) * value.toReal());
            mixed.setGreenF(startColor.greenF() + (endColor.greenF() - startColor.greenF()) * value.toReal());
            mixed.setBlueF(startColor.blueF() + (endColor.blueF() - startColor.blueF()) * value.toReal());

            ui->labelStep->setStyleSheet(
                QString("background-color: %1; %2").arg(mixed.name()).arg(baseStyle)
                );
        });

        connect(colorAnim, &QPropertyAnimation::finished, [=]() {
            ui->labelStep->setStyleSheet(
                QString("background-color: %1; %2").arg(startColor.name()).arg(baseStyle)
                );
            colorAnim->deleteLater();
        });

        colorAnim->start();
        currentIndex++;
    } else {
        timer->stop();
        std::string hex = toHex(checksumBits.to_ulong());
        ui->labelHex->setText("Checksum (hex): " + QString::fromStdString(hex));
    }
}

// Hex dönüşüm
std::string Checksum::toHex(unsigned long value)
{
    std::string hex = "";
    const char* hexchars = "0123456789ABCDEF";
    for (int i = 28; i >= 0; i -= 4) {
        hex += hexchars[(value >> i) & 0xF];
    }
    return hex;
}

QString Checksum::toHexQt(quint32 value)
{
    return QString::number(value, 16).toUpper().rightJustified(8, '0');
}
