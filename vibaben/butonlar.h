#ifndef BUTONLAR_H
#define BUTONLAR_H

#include <QDialog>

namespace Ui {
class Butonlar;
}

class Butonlar : public QDialog
{
    Q_OBJECT

public:
    explicit Butonlar(const std::vector<std::string>& allFrames, QWidget *parent = nullptr);
    ~Butonlar();

private:
    Ui::Butonlar *ui;
    std::string frameBits;
    std::vector<std::string> frames;  // tüm frameler (tablo için)
};

#endif // BUTONLAR_H
