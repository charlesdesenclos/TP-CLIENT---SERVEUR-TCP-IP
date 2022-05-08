#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtcpsocket.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QTcpSocket * socket;


public slots:



    void onConnexionButtonClicked();
    void onSocketConnected();
    void onSocketDisconnected();
    void onCelsiusButtonClicked();
    void onFahrenheitButtonClicked();
    void onHygrometrieButtonClicked();

    void onTemperatureReadyRead();

};





#endif // MAINWINDOW_H
