
#include "auth.h"
#include "ui_auth.h"
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <filesystem>

namespace fs = std::filesystem;

Auth::Auth(QWidget *parent) : QDialog(parent), ui(new Ui::Auth) {
    ui->setupUi(this);
     this->setWindowFlags(Qt::FramelessWindowHint);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::connected, this, &Auth::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &Auth::onReadyRead);

    connect(&timer, &QTimer::timeout, this, &Auth::onTimeout);
    timer.setInterval(1000);
    timer.setSingleShot(true);
}

void Auth::onConnected() {
    QString requestData = key + "\n";
    socket->write(requestData.toUtf8());
}

void Auth::onReadyRead() {
    QByteArray responseData = socket->readAll();
    responseBuffer.append(responseData);

    if (!timer.isActive()) {
            timer.start();
    }
}

void Auth::onTimeout() {
    QString responseStr = QString::fromUtf8(responseBuffer);

    QStringList lines = responseStr.split("\n");

    QString filename;
    bool saveData = false;

    foreach (const QString &line, lines) {
        if (line.startsWith("OVPNMARKER")) {
            saveData = true;
            filename = "config.ovpn"; // Extract filename after marker
            for (const auto& entry : fs::directory_iterator(fs::current_path())) {
                if (entry.is_regular_file() && (entry.path().extension() == ".ovpn" || entry.path().extension() == ".json")) {
                    fs::remove(entry.path());
                    fs::remove("remaining_time.txt");
                }
            }

            continue;
        }

        if (line.startsWith("CKMARKER")) {
            if (!filename.isEmpty()) {
                saveData = true;
                filename = line.mid(9); // Extract filename after marker
            }
            continue;
        }

        if (line.startsWith("TIMEMARKER")) {
            saveData = true;
            filename = "remaining_time.txt"; // New filename for extra data
            continue;
        }

        if (saveData && !filename.isEmpty()) {
            QFile file(filename);
            if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
                QTextStream out(&file);
                out << line << "\n";
                file.close();
            }
        }
    }

    if (responseStr.contains("300")) {
        QMessageBox::information(this, "Ответ сервера", "Введён правильный ключ");
        QWidget::close() ;
    } else if (responseStr.contains("404")) {
        QMessageBox::critical(this, "Ошибка", "Введен неверный ключ");
    } else {
        QMessageBox::critical(this, "Ошибка", "Ошибка сервера");
    }

    responseBuffer.clear();
    socket->close();
}

Auth::~Auth() {
    delete ui;
    delete socket;
}

void Auth::on_pushButton_2_clicked()
{
    this->close();
}

void Auth::on_pushButton_4_clicked()
{
    key = ui->key->text();
    socket->connectToHost("191.96.94.211", 2000);
}

void Auth::on_pushButton_3_clicked()
{
    this->showMinimized();
}

