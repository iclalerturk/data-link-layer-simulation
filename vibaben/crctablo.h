#ifndef CRCTABLO_H
#define CRCTABLO_H

#include <QDialog>
#include <QTableWidget>
#include "checksum.h"
namespace Ui {
class CrcTablo;
}

class CrcTablo : public QDialog
{
    Q_OBJECT

public:
    explicit CrcTablo(const std::vector<std::string>& frames, QWidget *parent = nullptr);
    ~CrcTablo();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CrcTablo *ui;
    QTableWidget* table;
    Checksum *checksum;
    std::vector<std::string> frameList;
    std::vector<std::string> crcList;
};

#endif // CRCTABLO_H
