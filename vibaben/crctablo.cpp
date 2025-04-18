#include "crctablo.h"
#include "ui_crctablo.h"
#include <QVBoxLayout>
CrcTablo::CrcTablo(const std::vector<std::string>& frames, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CrcTablo)
{
    ui->setupUi(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
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

        QString crc = QString::fromStdString(data.substr(data.size() - 16));
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(frames[i])));
        table->setItem(i, 1, new QTableWidgetItem(crc));
    }

    layout->addWidget(table);
}

CrcTablo::~CrcTablo()
{
    delete ui;
}
