#include "crctablo.h"
#include "ui_crctablo.h"
#include <QVBoxLayout>

CrcTablo::CrcTablo(const std::vector<std::string>& frames, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CrcTablo)
    , frameList(frames)
{
    ui->setupUi(this);

    table = new QTableWidget(this);
    table->setColumnCount(2);
    table->setHorizontalHeaderLabels(QStringList() << "Frame" << "CRC");
    table->setColumnWidth(0, 700);  // Frame sütunu
    table->setColumnWidth(1, 150);  // CRC sütunu

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
