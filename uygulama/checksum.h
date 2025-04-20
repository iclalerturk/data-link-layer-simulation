#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <QDialog>
#include <QTimer>
#include <QStringList>
#include <bitset>

namespace Ui {
class Checksum;
}

class Checksum : public QDialog
{
    Q_OBJECT

public:
    explicit Checksum(const std::vector<std::string>& frames, const std::vector<std::string>& crcList, QWidget* parent = nullptr);
    ~Checksum();

private slots:
    void calculateStep();

private:
    Ui::Checksum *ui;
    QTimer* timer;
    QStringList crcQStringList;
    int currentIndex = 0;
    std::bitset<8> checksumBits{0};

    void startChecksumAnimation();
    QString toHexQt(quint32 value); // Qt için
    std::string toHex(unsigned long value); // C++ için
};

#endif // CHECKSUM_H
