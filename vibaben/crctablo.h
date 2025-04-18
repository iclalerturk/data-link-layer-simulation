#ifndef CRCTABLO_H
#define CRCTABLO_H

#include <QDialog>
#include <QTableWidget>
namespace Ui {
class CrcTablo;
}

class CrcTablo : public QDialog
{
    Q_OBJECT

public:
    explicit CrcTablo(const std::vector<std::string>& frames, QWidget *parent = nullptr);
    ~CrcTablo();

private:
    Ui::CrcTablo *ui;
    QTableWidget* table;
};

#endif // CRCTABLO_H
