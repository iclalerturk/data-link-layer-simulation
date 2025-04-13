#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QPropertyAnimation>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void gonderFrame();
    void frameIlerle();
    void kontrolEt();

private:
    Ui::MainWindow *ui;

    QLabel *gondericiKutusu;
    QLabel *aliciKutusu;
    QLabel *mektup;
    QLabel *durumEtiketi;
    QPushButton *gonderButonu;

    QTimer *ackTimer;
    QPropertyAnimation *animasyon;

    bool ackGeldi;
};
#endif // MAINWINDOW_H
