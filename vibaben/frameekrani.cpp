#include "frameekrani.h"
#include "ui_frameekrani.h"


#include <QRandomGenerator>
#include <QMessageBox>

FrameEkrani::FrameEkrani(const std::vector<std::string>& frames, QWidget *parent) :
    QDialog(parent)
    ,
    ui(new Ui::FrameEkrani)
{
    ui->setupUi(this);
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

    headerLabel = new QLabel("🔢 Header", this);
    headerLabel->setGeometry(470, 160, 100, 30);
    headerLabel->hide();

    dataLabel = new QLabel("📦 Data", this);
    dataLabel->setGeometry(470, 200, 100, 30);
    dataLabel->hide();

    trailerLabel = new QLabel("🔚 Trailer", this);
    trailerLabel->setGeometry(470, 240, 100, 30);
    trailerLabel->hide();

    gondericiKutusu = new QLabel("📤 Gönderici", this);
    gondericiKutusu->setGeometry(450, 100, 120, 40);

    aliciKutusu = new QLabel("📥 Alıcı", this);
    aliciKutusu->setGeometry(880, 100, 100, 40);

    mektup = new QLabel("📄 Frame", this);
    mektup->setGeometry(470, 160, 80, 40);
    mektup->hide();

    durumEtiketi = new QLabel(this);
    durumEtiketi->setGeometry(580, 220, 250, 30);

    gonderButonu = new QPushButton("Frame Gönder", this);
    gonderButonu->setGeometry(620, 30, 160, 40);
    connect(gonderButonu, &QPushButton::clicked, this, &FrameEkrani::gonderFrame);

    gonderButonu->setStyleSheet(
        "QPushButton {"
        " background-color: #1746A2;"
        //" color: white;"
        //" font-size: 20px;"
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
    // Konumları sıfırla
    headerLabel->move(470, 160);
    dataLabel->move(470, 200);
    trailerLabel->move(470, 240);

    headerLabel->show();
    dataLabel->show();
    trailerLabel->show();
    QString style = "background-color: white; border: 2px solid #333; border-radius: 10px; padding: 5px;";
    headerLabel->setStyleSheet(style);
    dataLabel->setStyleSheet(style);
    trailerLabel->setStyleSheet(style);

    durumEtiketi->setText("📤 Frame gönderiliyor (Header + Data + Trailer)...");

    headerAnim = new QPropertyAnimation(headerLabel, "pos");
    headerAnim->setDuration(2000);
    headerAnim->setStartValue(QPoint(470, 160));
    headerAnim->setEndValue(QPoint(880, 160));

    dataAnim = new QPropertyAnimation(dataLabel, "pos");
    dataAnim->setDuration(2000);
    dataAnim->setStartValue(QPoint(470, 200));
    dataAnim->setEndValue(QPoint(880, 200));

    trailerAnim = new QPropertyAnimation(trailerLabel, "pos");
    trailerAnim->setDuration(2000);
    trailerAnim->setStartValue(QPoint(470, 240));
    trailerAnim->setEndValue(QPoint(880, 240));

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
    // Henüz kullanılmıyorsa boş bırakabilirsin
}
