#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(600, 300);

    gondericiKutusu = new QLabel("📤 Gönderici", this);
    gondericiKutusu->setGeometry(50, 100, 120, 40);

    aliciKutusu = new QLabel("📥 Alıcı", this);
    aliciKutusu->setGeometry(430, 100, 100, 40);

    mektup = new QLabel("📄 Frame", this);
    mektup->setGeometry(70, 160, 80, 40);
    mektup->hide();

    durumEtiketi = new QLabel(this);
    durumEtiketi->setGeometry(180, 220, 250, 30);

    gonderButonu = new QPushButton("Frame Gönder", this);
    gonderButonu->setGeometry(220, 30, 160, 40);
    connect(gonderButonu, &QPushButton::clicked, this, &MainWindow::gonderFrame);

    ackTimer = new QTimer(this);
    connect(ackTimer, &QTimer::timeout, this, &MainWindow::kontrolEt);
}

MainWindow::~MainWindow() {
    delete ui;
}
void MainWindow::frameIlerle() {
    // Henüz kullanılmıyorsa boş bırakabilirsin
}
void MainWindow::gonderFrame() {
    mektup->move(70, 160);
    mektup->show();
    durumEtiketi->setText("📤 Frame gönderiliyor...");

    animasyon = new QPropertyAnimation(mektup, "pos");
    animasyon->setDuration(2000);
    animasyon->setStartValue(QPoint(70, 160));
    animasyon->setEndValue(QPoint(450, 160));
    animasyon->start();

    ackTimer->start(2100);
}

void MainWindow::kontrolEt() {
    ackTimer->stop();

    int rastgele = QRandomGenerator::global()->bounded(100);
    if (rastgele < 10) {
        // Kayboldu
        durumEtiketi->setText("❌ Mektup yolda kayboldu!");
        mektup->hide();
    }
    else if (rastgele < 30) {
        // Bozuldu
        durumEtiketi->setText("⚠ Mektup bozuldu, tekrar gönderilecek.");
        mektup->setText("📄 ❗");
        QTimer::singleShot(1000, this, &MainWindow::gonderFrame);
    }
    else if (rastgele < 45) {
        // ACK kayboldu
        durumEtiketi->setText("🔁 ACK ulaşmadı, tekrar gönderiliyor.");
        QTimer::singleShot(1000, this, &MainWindow::gonderFrame);
    }
    else {
        // Başarıyla ulaştı
        durumEtiketi->setText("✅ Mektup ulaştı, ACK alındı.");
        mektup->setText("📄");
        mektup->hide();
    }
}
