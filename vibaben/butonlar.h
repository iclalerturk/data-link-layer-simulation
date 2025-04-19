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
    explicit Butonlar(QWidget *parent = nullptr);
    ~Butonlar();

private:
    Ui::Butonlar *ui;
};

#endif // BUTONLAR_H
