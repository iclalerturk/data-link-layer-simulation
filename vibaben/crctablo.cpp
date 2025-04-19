#include "crctablo.h"
#include "ui_crctablo.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QFont>
#include <QLabel>


CrcTablo::CrcTablo(const std::vector<std::string>& frames, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CrcTablo)
    , frameList(frames)
{
    ui->setupUi(this);

    // Stil sadece bu pencereye uygulansın diye isim veriyoruz
    this->setObjectName("CrcTablo");
    this->setStyleSheet("QDialog#CrcTablo { background-color: #b3e2f4; }");

    // Label'lar (örn. başlıklar varsa) mavi yazı
    for (QLabel* label : this->findChildren<QLabel*>()) {
        label->setStyleSheet("color: #0d47a1; font-weight: bold; font-size: 14px;");
    }

    // Tablomuzu oluşturalım
    table = new QTableWidget(this);
    table->setColumnCount(2);
    table->setHorizontalHeaderLabels(QStringList() << "Frame" << "CRC");

    // Başlık stilleri
    table->horizontalHeader()->setStyleSheet(
        "QHeaderView::section {"
        "    font-size: 12pt;"
        "    font-weight: bold;"
        "    background-color: #1746A2;"
        "    color: white;"
        "    padding: 5px;"
        "    border: 1px solid #ddd;"
        "}"
        );

    table->verticalHeader()->setStyleSheet(
        "QHeaderView::section {"
        "    font-size: 11pt;"
        "    background-color: #e3f2fd;"
        "    color: #0d47a1;"
        "    padding: 2px;"
        "    border: 1px solid #ccc;"
        "}"
        );

    // İçerik hücre stili — siyah yazı
    table->setStyleSheet(
        "QTableWidget { background-color: white; color: black; font-size: 12pt; }"
        "QTableWidget::item:selected { background-color: #bbdefb; }"
        );

    table->setColumnWidth(0, 700);
    table->setColumnWidth(1, 250);
    table->setRowCount(frames.size());

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

        QString crc = QString::fromStdString(crcStr);
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(frames[i])));
        table->setItem(i, 1, new QTableWidgetItem(crc));
    }

    // Buton tasarımı
    ui->pushButton->setStyleSheet(
        "QPushButton {"
        " background-color: #1746A2;"
        " color: white;"
        " font-size: 20px;"
        " border-radius: 20px;"
        " padding: 8px 16px;"
        " }"
        "QPushButton:hover {"
        " background-color: #3567d1;"
        " }"
        );

    // Layout oluştur ve widget'ları sırayla ekle
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(table);
    layout->addWidget(ui->pushButton);

    this->setLayout(layout);
}

CrcTablo::~CrcTablo()
{
    delete ui;
}

void CrcTablo::on_pushButton_clicked()
{
    hide();
    checksum = new Checksum(frameList, crcList, this);
    checksum->show();
}
