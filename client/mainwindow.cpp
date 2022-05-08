#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qtcpsocket.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    QObject::connect(socket, SIGNAL(connected()),this, SLOT(onSocketConnected()));
    QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));

    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(onTemperatureReadyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onConnexionButtonClicked() // La fonction sert à se connecter au serveur quand l'utilisateur click sur le bouton de connexion
{
    QString ip = ui->IPLineEdit->text();      // enregistre l'ip saisit sur la ligneEdit
    QString port = ui->PortLineEdit->text();

    bool ok;

    int portAsInt = port.toInt(&ok);
    if(ok)
    {
        socket->connectToHost(ip, portAsInt);
    }
}

void MainWindow::onSocketConnected() // La fonction affiche à l'utilisateur s'il est connecté
{
    ui->ConnexionStatusLabel->setText("Status de connexion : connecté");
}

void MainWindow::onSocketDisconnected() //La  fonction affiche à l'utilisateur s'il est déconnecté
{
    ui->ConnexionStatusLabel->setText("Status de connexion : déconnecté");
}


void MainWindow::onCelsiusButtonClicked() // La  fonction va vérifier si le user est connecté et envoyé le message souhaité pour le celius au serveur
{
    if(socket->state() == QTcpSocket::ConnectedState)
    {

        socket->write("Td03?\n");
    }
}
void MainWindow::onFahrenheitButtonClicked() // La  fonction va vérifier si le user est connecté et envoyé le message souhaité pour le fahrenheit au serveur
{
    if(socket->state() == QTcpSocket::ConnectedState)
    {
        socket->write("Tf03?\n");
    }
}
void MainWindow::onHygrometrieButtonClicked() // La  fonction va vérifier si le user est connecté et envoyé le message souhaité pour le hygrométrie au serveur
{
    if(socket->state() == QTcpSocket::ConnectedState)
    {
        socket->write("Hr03?\n");
    }
}

void MainWindow::onTemperatureReadyRead() // La fonction vérifie les informations envoyés par le serveur pui vérifie si c'est un td , un tf et hr et va afficher le résultat au bonne endroit
{

    QByteArray data = socket->read(socket->bytesAvailable());
    QString donnees(data);



    if(donnees.data()[0] == 'T' && donnees.data()[1] == 'd' ) // vérifie si les données commence par un Td si oui il affiche dans le bon label la données
    {
        ui->CelsiusLabel->setText(""+donnees+" °C");
    }
    else if(donnees.data()[0] =='T' && donnees.data()[1] =='f') // vérifie si les données commence par un Tf si oui il affiche dans le bon label la données
    {
        ui->FahrenheitLabel->setText(""+donnees+" F");
    }
    else if(donnees.data()[0] =='H' && donnees.data()[1] == 'r') // vérifie si les données commence par un Hr si oui il affiche dans le bon label la données
    {
        ui->HygrometrieLabel->setText(""+donnees+" %");
    }
}



