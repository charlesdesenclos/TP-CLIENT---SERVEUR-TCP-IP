#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtcpsocket.h>
#include <qtcpserver.h>

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
    QTcpServer * server;
    QTcpSocket * clientConnection;

public slots:


    void onServerNewConnection();
    void onClientDisconnected();
    void OnCelsiusReadyRead();

};


#endif // MAINWINDOW_H
