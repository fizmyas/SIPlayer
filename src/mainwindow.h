#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtNetwork>
#include <QTcpSocket>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connectButton_clicked();

    void slotReadyRead   ();
    void slotError       (QAbstractSocket::SocketError err);
    void slotConnected   ();

    void on_exitButton_clicked();

    void on_readyToAnswerButton_clicked();

    void on_sendAnswerButton_clicked();

    void on_disconnectButton_clicked();

    void timeoutFalstart();

private:
    Ui::MainWindow *ui;
    void sendToServer(QString data);
    QTcpSocket *playerSocket;
    quint16 nextBlockSize;
    QString playerName;
    QString fullMessage;
    unsigned int playerID;
    int isAnswerInWriting;
    bool isFalstart; // игра с фальстартами или без
    bool falstart; // произошёл ли фальстарт
    QTimer falstartTimer;

    void clearFields();
};
#endif // MAINWINDOW_H
