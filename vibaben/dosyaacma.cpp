#include "dosyaacma.h"
#include "ui_dosyaacma.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>
#include <Qscrollarea.h>
#include <QScrollBar>
DosyaAcma::DosyaAcma(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DosyaAcma)
{
    ui->setupUi(this);
    // Create and setup the scroll area
    scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);

    // Create a container widget for the scroll area
    QWidget *scrollContent = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);
    scrollLayout->setAlignment(Qt::AlignTop);
    scrollLayout->setContentsMargins(2, 2, 2, 2);  // Small margins

    // Set the scroll content widget
    scrollArea->setWidget(scrollContent);

    // Add scroll area to frameContainer's layout
    QVBoxLayout *frameLayout = new QVBoxLayout(ui->frameContainer);
    frameLayout->addWidget(scrollArea);
    frameLayout->setContentsMargins(0, 0, 0, 0);  // No margins
    ui->labelAnaVeri->setWordWrap(true);
    ui->labelAnaVeri->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    // Metni HTML olarak ayarlayarak daha iyi kontrol sağlayabilirsiniz

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
    frameEkrani = new FrameEkrani(this);
    frameEkrani->show();
}

std::vector<bool> readFileAsBits(const QString& path) {
    QFile file(path);
    std::vector<bool> bits;

    if (!file.open(QIODevice::ReadOnly)) return bits;

    QByteArray data = file.readAll();
    for (unsigned char byte : data) {
        for (int i = 7; i >= 0; --i) {
            bits.push_back((byte >> i) & 1);
        }
    }

    return bits;
}

void DosyaAcma::showNextFrame()
{

    if (currentFrameIndex >= frames.size()) {
        animTimer->stop();
        ui->labelTitle->setText("✔ Tüm frameler gösterildi.");
        return;
    }


    QString frameStr;
    for (bool bit : frames[currentFrameIndex])
        frameStr += bit ? "1" : "0";

    ui->labelFrame->setText(QString("🧱 Frame %1:\n%2").arg(currentFrameIndex + 1).arg(frameStr));
    currentFrameIndex++;
}

std::vector<std::vector<bool>> splitIntoFrames(const std::vector<bool>& bits, int frameSize = 100) {
    std::vector<std::vector<bool>> frames;
    for (size_t i = 0; i < bits.size(); i += frameSize) {
        std::vector<bool> frame;
        for (size_t j = i; j < i + frameSize && j < bits.size(); ++j)
            frame.push_back(bits[j]);
        while (frame.size() < frameSize)
            frame.push_back(0); // padding
        frames.push_back(frame);
    }
    return frames;
}

// Gerekli değişkenlerin tanımlamaları
QList<QList<bool>> frames;  // Veriyi parçalara ayıran frame listesi
int currentFrameIndex = 0;  // Şu anki frame indeksi
int currentVisualFrameIndex = 0;  // Görsel frame animasyon indeksi
QTimer *animTimer = nullptr;  // Animasyon için zamanlayıcı

QStringList frameStrings;
void DosyaAcma::showNextVisualFrame()
{
    if (currentVisualFrameIndex >= frameStrings.size()) {
        animTimer->stop();
        ui->labelTitle->setText("✔ Tüm frameler animasyonla oluşturuldu.");
        return;
    }

    QString currentFrameText = frameStrings[currentVisualFrameIndex];
    ui->labelFrame->setText(QString("Frame %1:\n%2").arg(currentVisualFrameIndex + 1).arg(currentFrameText));

    // Get the scroll content widget
    QWidget *scrollContent = scrollArea->widget();

    QLabel *lbl = new QLabel(scrollContent);  // Parent is now scrollContent
    lbl->setText(QString("🔹 Frame %1: %2")
                     .arg(currentVisualFrameIndex + 1)
                     .arg(currentFrameText.left(100)));

    lbl->setStyleSheet("background-color: #e1f5fe; border: 1px solid #0288d1; padding: 8px; font-family: monospace; color: black");
    lbl->setAlignment(Qt::AlignLeft);
    lbl->setWordWrap(true);

    // Add to scroll content's layout
    qobject_cast<QVBoxLayout*>(scrollContent->layout())->addWidget(lbl);
    lbl->show();

    // Rest of your animation code remains the same...
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(lbl);
    lbl->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0);

    QPropertyAnimation *fadeAnim = new QPropertyAnimation(opacityEffect, "opacity");
    fadeAnim->setDuration(600);
    fadeAnim->setStartValue(0);
    fadeAnim->setEndValue(1);
    fadeAnim->start(QAbstractAnimation::DeleteWhenStopped);

    QRect endRect = lbl->geometry();
    QRect startRect = endRect;
    startRect.moveLeft(startRect.left() + 200);
    lbl->setGeometry(startRect);

    QPropertyAnimation *slideAnim = new QPropertyAnimation(lbl, "geometry");
    slideAnim->setDuration(600);
    slideAnim->setStartValue(startRect);
    slideAnim->setEndValue(endRect);
    slideAnim->start(QAbstractAnimation::DeleteWhenStopped);

    currentVisualFrameIndex++;

    // Ensure the scroll area scrolls to the newly added item
    // Auto-scroll to bottom
    QTimer::singleShot(100, [this]() {
        if (scrollArea && scrollArea->verticalScrollBar()) {
            scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->maximum());
        }
    });
}
void DosyaAcma::on_pushButton_2_clicked()
{
    auto bits = readFileAsBits(ui->lineEdit_dosyaYolu->text());
    frames = splitIntoFrames(bits, 100);

    frameStrings.clear();
    for (const auto& frame : frames) {
        QString frameStr;
        for (bool bit : frame) {
            frameStr += bit ? "1" : "0";
        }
        frameStrings.append(frameStr);
        currentFrameIndex++;
    }

    ui->labelTitle->setText(QString("Toplam %1 frame oluşturuldu").arg(frames.size()));
    QString allData = frameStrings.join("");
    // Veriyi satırlara bölelim (örneğin her 100 karakterde bir yeni satır)
    QString formattedData;
    int chunkSize = 100; // Her satıra 100 karakter
    for (int i = 0; i < allData.size(); i += chunkSize) {
        formattedData += allData.mid(i, chunkSize) + "\n"; // mid() ile parçaları al
    }

    ui->labelAnaVeri->setText("🧱 Veri Bloğu:\n" + formattedData);

    // Layout kontrolü
    if (!ui->frameContainer->layout()) {
        QVBoxLayout *layout = new QVBoxLayout(ui->frameContainer);
        ui->frameContainer->setLayout(layout);

    }

    // Önceki QLabel'ları sil
    auto children = ui->frameContainer->findChildren<QLabel*>();
    for (QLabel *child : children)
        child->deleteLater();

    currentVisualFrameIndex = 0;

    // Zamanlayıcıyı yeniden başlat
    if (animTimer) {
        animTimer->stop();
        delete animTimer;
        animTimer = nullptr;
    }

    animTimer = new QTimer(this);
    connect(animTimer, &QTimer::timeout, this, &DosyaAcma::showNextVisualFrame);
    animTimer->start(500);
}
