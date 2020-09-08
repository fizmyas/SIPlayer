#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "strings/strings_mainwindow.h"
#include <QTime>
#include <QMessageBox>

using namespace mainwindowStrings;

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    nextBlockSize(0),
    playerName(""),
    fullMessage(""),
    playerID(0),
    isAnswerInWriting(0),
    isFalstart(false),
    falstart(false)
{
    ui->setupUi(this);
    setWindowTitle(MSG_MAINWINDOW_TITLE());
    playerSocket = new QTcpSocket(this);
    ui->readyToAnswerButton->setDisabled(true);
    ui->sendAnswerButton->setDisabled(true);
    ui->name1_Browser->setStyleSheet("background-color: red");
    ui->name2_Browser->setStyleSheet("background-color: green");
    ui->name3_Browser->setStyleSheet("background-color: yellow");
    ui->name4_Browser->setStyleSheet("background-color: blue");
    clearFields();
}

MainWindow::~MainWindow()
{
    delete  playerSocket;
    delete ui;
}


void MainWindow::on_connectButton_clicked()
{
    clearFields();
    playerName = ui->nameEdit->text();
    if (!playerName.isEmpty())
    {
        playerSocket->connectToHost(ui->ipEdit->text(), ui->portEdit->text().toUInt());
        QObject::connect(playerSocket, SIGNAL(connected()), SLOT(slotConnected()));
        QObject::connect(playerSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
        QObject::connect(playerSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
        sendToServer(MSG_NAME_PREFFIX() + playerName);
    }
    else
    {
        QMessageBox::critical(NULL, MSG_ERROR(), MSG_PLAYER_NAME_NOT_FOUND());
    }
}

void MainWindow::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
            "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                         "The host was not found." :
                         err == QAbstractSocket::RemoteHostClosedError ?
                         "The remote host is closed." :
                         err == QAbstractSocket::ConnectionRefusedError ?
                         "The connection was refused." :
                         QString(playerSocket->errorString())
                        );
        ui->answerServerText->append(strError);
        ui->connectButton->setEnabled(true);
}

void MainWindow::slotConnected()
{
    ui->answerServerText->append("Received the connected() signal");
}

void MainWindow::slotReadyRead()
{
    fullMessage = "";
    QDataStream in(playerSocket);
    in.setVersion(QDataStream::Qt_4_2);
    for (;;)
    {
        if (!nextBlockSize)
        {
            if (playerSocket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            in >> nextBlockSize;
        }

        if (playerSocket->bytesAvailable() < nextBlockSize)
        {
            break;
        }

        QTime time;
        QString str;
        in >> time >> str;
        //fullMessage += str;
        fullMessage = str;
        ui->answerServerText->append(time.toString() + " " + str);
        nextBlockSize = 0;

        QStringList list = fullMessage.split(":#");
        if (fullMessage.startsWith(MSG_ID_PREFFIX()))
        {
            ui->connectButton->setDisabled(true);
            ui->idEdit->setText(list[1]);
            ui->idEdit->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
            playerID = list[1].toUInt();
        }

        if (fullMessage.startsWith(MSG_NUMBER_PREFFIX()))
        {
            ui->numberEdit->setText(list[1]);
            ui->numberEdit->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        }

        if (fullMessage.startsWith(MSG_THEME_PREFFIX()))
        {
            ui->themeEdit->setText(list[1]);
        }

        if (fullMessage.startsWith(MSG_VALUE_PREFFIX()))
        {
            ui->valueEdit->setText(list[1]);
            ui->valueEdit->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
            ui->queueBrowser->clear();
            ui->readyToAnswerButton->setEnabled(true);
        }

        if (isAnswerInWriting && fullMessage.startsWith(MSG_QUESTION_PREFFIX()))
        {
            ui->textEdit->setText(list[1]);
        }

        if (fullMessage.startsWith(MSG_NAME1_PREFFIX()))
        {
            ui->name1_Browser->setText(list[1]);
            ui->name1_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        }

        if (fullMessage.startsWith(MSG_NAME2_PREFFIX()))
        {
            ui->name2_Browser->setText(list[1]);
            ui->name2_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        }

        if (fullMessage.startsWith(MSG_NAME3_PREFFIX()))
        {
            ui->name3_Browser->setText(list[1]);
            ui->name3_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        }

        if (fullMessage.startsWith(MSG_NAME4_PREFFIX()))
        {
            ui->name4_Browser->setText(list[1]);
            ui->name4_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        }

        if (fullMessage.startsWith(MSG_SUM1_PREFFIX()))
        {
            ui->sum1_Browser->setText(list[1]);
            ui->sum1_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        }

        if (fullMessage.startsWith(MSG_SUM2_PREFFIX()))
        {
            ui->sum2_Browser->setText(list[1]);
            ui->sum2_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        }

        if (fullMessage.startsWith(MSG_SUM3_PREFFIX()))
        {
            ui->sum3_Browser->setText(list[1]);
            ui->sum3_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        }

        if (fullMessage.startsWith(MSG_SUM4_PREFFIX()))
        {
            ui->sum4_Browser->setText(list[1]);
            ui->sum4_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        }

        if(fullMessage.startsWith(MSG_QUEUE_PREFFIX()))
        {
            ui->queueBrowser->setText(list[1]);
            ui->queueBrowser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
            if(list[1].toInt() == 1 && isAnswerInWriting)
            {
                ui->sendAnswerButton->setEnabled(true);
            }
        }

        if (fullMessage.startsWith(MSG_CORRECTNESS_PREFFIX()))
        {
            ui->correctnessBrowser->setText(list[1]);
            ui->correctnessBrowser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
            if (list[1] == MSG_FALSTART())
            {
                falstart = true;
                ui->readyToAnswerButton->setDisabled(true);
            }
        }

        if (fullMessage.startsWith(MSG_TIMEOUT_PREFFIX()))
        {
            ui->readyToAnswerButton->setDisabled(true);
            if (isAnswerInWriting)
            {
                ui->sendAnswerButton->setDisabled(true);
            }
        }

        if (fullMessage.startsWith(MSG_INWRITTING_PREFFIX()))
        {
            isAnswerInWriting = true;
        }

        if (fullMessage.startsWith(MSG_TIME_PREFFIX()))
        {
            ui->correctnessBrowser->setText(MSG_TIME_PREFFIX());
            if (falstart)
            {
                falstartTimer.singleShot(2000, this, SLOT(timeoutFalstart()));
            }
        }

        if (fullMessage.startsWith(MSG_BLOCK_PREFFIX()))
        {
            ui->readyToAnswerButton->setDisabled(true);
            if (isAnswerInWriting)
            {
                ui->sendAnswerButton->setDisabled(true);
            }
        }
    }


}

void MainWindow::sendToServer(QString data)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << quint16(0) << QTime::currentTime() << data;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    playerSocket->write(arrBlock);
}

void MainWindow::on_exitButton_clicked()
{
    playerSocket->disconnectFromHost();
    close();
}

void MainWindow::on_readyToAnswerButton_clicked()
{
    sendToServer(MSG_ID_PREFFIX() + QString::number(playerID));
}

void MainWindow::on_sendAnswerButton_clicked()
{
    sendToServer(MSG_ANSWER_PREFFIX() + ui->answerLine->text());
    ui->answerLine->clear();
}

void MainWindow::on_disconnectButton_clicked()
{
    clearFields();
    playerSocket->disconnectFromHost();
    QFile *playerLog = new QFile("./player.log");
    if (!playerLog->open(QIODevice::Append))
    {
        QMessageBox::critical(NULL, MSG_ERROR(), "Не удалость открыть лог-файл");
    }
    else
    {
        playerLog->write(ui->answerServerText->toPlainText().toUtf8());
        playerLog->close();
        delete playerLog;
    }
    ui->connectButton->setEnabled(true);
}

void MainWindow::timeoutFalstart()
{
    ui->readyToAnswerButton->setEnabled(true);
}

void MainWindow::clearFields()
{
    ui->name1_Browser->clear();
    ui->name2_Browser->clear();
    ui->name3_Browser->clear();
    ui->name4_Browser->clear();
    ui->sum1_Browser->clear();
    ui->sum2_Browser->clear();
    ui->sum3_Browser->clear();
    ui->sum4_Browser->clear();
    ui->answerLine->clear();
    ui->numberEdit->clear();
    ui->themeEdit->clear();
    ui->valueEdit->clear();
    ui->queueBrowser->clear();
    ui->correctnessBrowser->clear();
    ui->textEdit->clear();
}
