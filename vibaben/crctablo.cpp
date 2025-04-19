#include "crctablo.h"
#include "ui_crctablo.h"
#include <QVBoxLayout>
#include <QHeaderView>   // QHeaderView için
#include <QFont>         // QFont için
CrcTablo::CrcTablo(const std::vector<std::string>& frames, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CrcTablo)
    , frameList(frames)
{
    ui->setupUi(this);

    table = new QTableWidget(this);
    table->setColumnCount(2);
    table->setHorizontalHeaderLabels(QStringList() << "Frame" << "CRC");
    table->horizontalHeader()->setStyleSheet(
        "QHeaderView::section {"
        "    font-size: 12pt;"
        "    font-weight: bold;"
        "    background-color: #1746A2;"  // Mavi arka plan
        "    color: white;"               // Beyaz yazı
        "    padding: 5px;"               // İç boşluk
        "    border: 1px solid #ddd;"    // Kenarlık
        "}"
        );
    table->verticalHeader()->setStyleSheet(
        "QHeaderView::section {"
        "    font-size: 12pt;"           // Daha küçük yazı
        "    background-color: #1746A2;" // Açık gri arka plan             // Siyah yazı
        "    padding: 2px;"
        "    border: 1px solid #ccc;"
        "}"
        );
    table->setColumnWidth(0, 700);  // Frame sütunu
    table->setColumnWidth(1, 250);  // CRC sütunu

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
        crcList.push_back(crcStr); // sınıf değişkenine ekle

        QString crc = QString::fromStdString(crcStr);
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(frames[i])));
        table->setItem(i, 1, new QTableWidgetItem(crc));
    }
    ui->pushButton->setStyleSheet(
        "QPushButton {"
        " background-color: #1746A2;"
        //" color: white;"
        " font-size: 20px;"
        " border-radius: 20px;"
        " }"
        "QPushButton:hover {"
        " background-color: #3567d1;"
        " }"
        );
    // Layout oluştur ve widget'ları sırayla ekle
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(table);
    layout->addWidget(ui->pushButton);  // Designer'daki buton

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
