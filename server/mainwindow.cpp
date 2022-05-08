#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->setupUi(this);
    socket = new QTcpSocket(this);

    QObject::connect(socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
    QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));
    QObject::connect(socket, SIGNAL(readyread()), this, SLOT(onSocketReadyRead()));

    server = new QTcpServer(this);
    QObject::connect(server, SIGNAL(newConnection()), this, SLOT(onServerNewConnection()));
    server->listen(QHostAddress::AnyIPv4, 1234);
    QObject::connect(server, SIGNAL(readyRead()), this, SLOT(OnCelsiusReadyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onServerNewConnection()
{
    ui->connectionStatusLabel->setText("Un client s'est connecté");
    QTcpSocket * client = server->nextPendingConnection();
    QObject::connect(client, SIGNAL(readyread()), this, SLOT(onClientReadyRead()));
    QObject::connect(client, SIGNAL(disconnect()), this, SLOT(onClientDisconnected()));
}
void MainWindow::onClientDisconnected()
{
    QTcpSocket * obj = qobject_cast<QTcpSocket*>(sender());
    QObject::connect(obj, SIGNAL(readyread()), this, SLOT(onClientReadyRead()));
    QObject::connect(obj, SIGNAL(disconnect()), this, SLOT(onClientDisconnected()));
    obj->deleteLater();
}
void MainWindow::onClientReadyRead()
{
    QTcpSocket * obj = qobject_cast<QTcpSocket*> (sender () );
    QByteArray data = obj->read(obj->bytesAvailable());
    QString donnees(data);
    donnees.chop(1); //enleve le ?
    if (donnees.data()[0]=='H'&&donnees.data()[1]=='r'){
        int val = rand()%100;
    }
    else if(donnees.data()[0]=='T'&&donnees.data()[1]=='d'|| donnees.data()[1]=='f'){
        int val = (rand() % 56) - 20;
    }
    donnees.prepend (','); //ajoute la virgule
    //obj-ewrite():
}

void MainWindow::OnCelsiusReadyRead()
{
    QString ligne;
    while (clientConnection->canReadLine())
    {
        ligne = clientConnection->readLine();
    }

}
