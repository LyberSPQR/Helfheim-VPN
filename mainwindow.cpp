
#include <QFontDatabase>
#include <QApplication>
#include <QFontDatabase>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "auth.h"
#include <iostream>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QFile>
#include <filesystem>
#include <QTimer>
#include <QWindow>
#include <QNetworkInterface>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QtCore>
#include <QtNetwork>
#include <iostream>
# include <winsock.h>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>
#include <thread>

using namespace std;
    namespace fs = std::filesystem;

#if defined Q_OS_WIN
QString osys = "win";
#elif defined(Q_OS_LINUX)
QString osys = "lin";
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
 {
 // ipUpdater = new IpAddressUpdater(this);

    ui->setupUi(this);
    ui->statusbar->setStyleSheet("color: #c1c1c1");
    //QFont font("Arial", 12, QFont::Bold);;
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    this->setWindowFlags(Qt::FramelessWindowHint);

    openvpn_process = nullptr;
    ckclient_process = nullptr;
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::remainingTimeCounter);
    timer->start(600000);

    QTimer *timer_ip = new QTimer(this);
    connect(timer_ip, &QTimer::timeout, this, [this]() {
         current_ip;
        getPublicIpAddress(current_ip);
    });
    timer_ip->start(500);

    // Добавьте следующие строки в ваш конструктор MainWindow для установки mouseTracking для checkBox
    ui->checkBox->setMouseTracking(true);

 ui->checkBox->installEventFilter(this);

    QTimer *delayTimer = new QTimer(this);

    // Подключаем слот для обработки завершения задержки
    connect(delayTimer, &QTimer::timeout, this, [](){
        // Этот код будет выполнен по истечении времени задержки
        qDebug() << "Задержка завершена";
    });

    // Устанавливаем время задержки в 2 секунды (2000 мс)
    delayTimer->setSingleShot(true);

}

MainWindow::~MainWindow() {
    delete ui;

        openvpn_process->kill();
        openvpn_process->waitForFinished();
        delete openvpn_process;
        openvpn_process = nullptr;

        ckclient_process->kill();
        ckclient_process->waitForFinished();
        delete ckclient_process;
        ckclient_process = nullptr;
}

void MainWindow::on_pushButton_clicked() {
    Auth authWindow;
      authWindow.setFixedSize(400, 150);
    authWindow.setModal(true);
    authWindow.exec();

}
void MainWindow::remainingTimeCounter()
{
    std::time_t currentTime = std::time(nullptr);

    QString path = QCoreApplication::applicationFilePath();
    QFileInfo fileInfo(path);
    QString working_dir = fileInfo.absolutePath();
    QString remaining_time_path = working_dir + "/remaining_time.txt";

    QFile file(remaining_time_path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line = in.readLine();
        int remain_time = line.toInt();
        file.close();
        remain_time = (remain_time - currentTime) / 86400;
        ui->remain_time->setText(QString::number(remain_time) + " days");
    }
    // else {
    //     QMessageBox::critical(this, "Ошибка", "Не удалось определить оставшееся время");
    // }
}

void MainWindow::on_pushButton_3_clicked()
{
    this->showMinimized();
}

void MainWindow::on_pushButton_2_clicked()
{
    this->close();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragStartPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - m_dragStartPosition);
        event->accept();
    }
}
void MainWindow::on_checkBox_stateChanged(int state)
{
    qDebug() << "Start processing";
    auto start = std::chrono::high_resolution_clock::now();
    // Ваша логика

    QString path = QCoreApplication::applicationFilePath();
    QFileInfo fileInfo(path);
    QString working_dir = fileInfo.absolutePath();

    int cnt = 0;
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        if (entry.is_regular_file() && (entry.path().extension() == ".ovpn" || entry.path().extension() == ".json"))
        {
            cnt++;
        }
    }
    std:: cerr << cnt;
    if(cnt == 2){
        ui->statusbar->showMessage("Connecting...");
        if (osys == "lin")
        {
            QString args =/* working_dir +*/ "./config.ovpn";
            QString argsCk = "-c ckclient.json -s 191.96.94.211";

            QStringList argsList = args.split(" ", Qt::SkipEmptyParts);
            QStringList argsListCk = argsCk.split(" ", Qt::SkipEmptyParts);

            if (state == Qt::Checked) {
                if (openvpn_process) {
                    openvpn_process->terminate();
                    if (!openvpn_process->waitForFinished(30)) { // Ждать 3 секунды
                        QProcess::execute("taskkill", QStringList() << "/F" << "/IM" << "openvpn");
                        openvpn_process->kill();
                    }
                    delete openvpn_process;
                    openvpn_process = nullptr;
                }

                // Завершение ckclient_process
                if (ckclient_process) {
                    ckclient_process->terminate();
                    if (!ckclient_process->waitForFinished(30)) { // Ждать 3 секунды
                        QProcess::execute("taskkill", QStringList() << "/F" << "/IM" << "ck-client");
                    }
                    delete ckclient_process; // Освобождаем память
                    ckclient_process = nullptr;
                }

                openvpn_process = new QProcess(this);
                ckclient_process = new QProcess(this);

                // Перенаправление вывода процессов в null
                openvpn_process->setProcessChannelMode(QProcess::MergedChannels);
                openvpn_process->setStandardOutputFile(QByteArray());

                ckclient_process->setProcessChannelMode(QProcess::MergedChannels);
                ckclient_process->setStandardOutputFile(QByteArray());

                ckclient_process->start("./ck-client", argsListCk);
                if (!ckclient_process->waitForStarted()) {
                    QMessageBox::critical(this, "Ошибка", "Обратитесь в службу поддержки.");
                    delete ckclient_process;
                    ckclient_process = nullptr;
                    throw std::runtime_error("Failed to start ck-client process");
                }
                std::this_thread::sleep_for(std::chrono::seconds(1));
                // Запуск процессов
                openvpn_process->start("./openvpn", argsList);
                if (!openvpn_process->waitForStarted()) {
                    QMessageBox::critical(this, "Ошибка", "Обратитесь в службу поддержки.");
                    delete openvpn_process;
                    openvpn_process = nullptr;
                    throw std::runtime_error("Failed to start openvpn process");
                }


                remainingTimeCounter();
                auto end = std::chrono::high_resolution_clock::now();
                qDebug() << "Processing time:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms";
            } else {
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to disable VPN service?", QMessageBox::Yes | QMessageBox::No);

                if (reply == QMessageBox::Yes) {
                    // Завершение openvpn_proces
                    if (openvpn_process) {
                        openvpn_process->terminate();
                        if (!openvpn_process->waitForFinished(30)) { // Ждать 3 секунды
                            QProcess::execute("taskkill", QStringList() << "/F" << "/IM" << "openvpn.exe");
                            openvpn_process->kill();
                        }
                        delete openvpn_process;
                        openvpn_process = nullptr;
                    }
                    // Завершение ckclient_process
                    if (ckclient_process) {
                        ckclient_process->terminate();
                        if (!ckclient_process->waitForFinished(30)) { // Ждать 3 секунды
                            QProcess::execute("taskkill", QStringList() << "/F" << "/IM" << "ck-client.exe");
                        }
                        delete ckclient_process;
                        ckclient_process = nullptr;
                    }
                    // Подключение сигналов для освобождения ресурсов
                    connect(openvpn_process, &QProcess::finished, this, [=]() {
                        qDebug() << "openvpn процесс завершился";
                        openvpn_process->deleteLater();
                    });

                    connect(ckclient_process, &QProcess::finished, this, [=]() {
                        qDebug() << "ckclient процесс завершился";
                        ckclient_process->deleteLater();
                    });


                    ui->ip_adress->setText("No connection");
                    ui->statusbar->showMessage("VPN service is disabled");
                } else {
                    ui->checkBox->setChecked(true);
                }
            }
        }
        else if (osys == "win")
        {

            QString args = working_dir + "/config.ovpn";
            QString argsCk = "-c ckclient.json -s 191.96.94.211";

            QStringList argsList = args.split(" ", Qt::SkipEmptyParts);
            QStringList argsListCk = argsCk.split(" ", Qt::SkipEmptyParts);

            if (state == Qt::Checked) {
                if (openvpn_process) {
                    openvpn_process->terminate();
                    if (!openvpn_process->waitForFinished(30)) { // Ждать 3 секунды
                        QProcess::execute("taskkill", QStringList() << "/F" << "/IM" << "openvpn.exe");
                        openvpn_process->kill();
                    }
                    delete openvpn_process;
                    openvpn_process = nullptr;
                }

                // Завершение ckclient_process
                if (ckclient_process) {
                    ckclient_process->terminate();
                    if (!ckclient_process->waitForFinished(30)) { // Ждать 3 секунды
                        QProcess::execute("taskkill", QStringList() << "/F" << "/IM" << "ck-client.exe");
                    }
                    delete ckclient_process; // Освобождаем память
                    ckclient_process = nullptr;
                }

                openvpn_process = new QProcess(this);
                ckclient_process = new QProcess(this);

                // Перенаправление вывода процессов в null
                openvpn_process->setProcessChannelMode(QProcess::MergedChannels);
                openvpn_process->setStandardOutputFile(QByteArray());

                ckclient_process->setProcessChannelMode(QProcess::MergedChannels);
                ckclient_process->setStandardOutputFile(QByteArray());

                ckclient_process->start("ck-client.exe", argsListCk);
                if (!ckclient_process->waitForStarted()) {
                    QMessageBox::critical(this, "Ошибка", "Обратитесь в службу поддержки.");
                    delete ckclient_process;
                    ckclient_process = nullptr;
                    throw std::runtime_error("Failed to start ck-client process");
                }
 std::this_thread::sleep_for(std::chrono::seconds(1));
                // Запуск процессов
                openvpn_process->start("openvpn.exe", argsList);
                if (!openvpn_process->waitForStarted()) {
                    QMessageBox::critical(this, "Ошибка", "Обратитесь в службу поддержки.");
                    delete openvpn_process;
                    openvpn_process = nullptr;
                    throw std::runtime_error("Failed to start openvpn process");
                }


                remainingTimeCounter();
                auto end = std::chrono::high_resolution_clock::now();
                qDebug() << "Processing time:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms";
            } else {
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to disable VPN service?", QMessageBox::Yes | QMessageBox::No);

                if (reply == QMessageBox::Yes) {
                    // Завершение openvpn_proces
                    if (openvpn_process) {
                        openvpn_process->terminate();
                        if (!openvpn_process->waitForFinished(30)) { // Ждать 3 секунды
                            QProcess::execute("taskkill", QStringList() << "/F" << "/IM" << "openvpn.exe");
                            openvpn_process->kill();
                        }
                        delete openvpn_process;
                        openvpn_process = nullptr;
                    }

                    // Завершение ckclient_process
                    if (ckclient_process) {
                        ckclient_process->terminate();
                        if (!ckclient_process->waitForFinished(30)) { // Ждать 3 секунды
                            QProcess::execute("taskkill", QStringList() << "/F" << "/IM" << "ck-client.exe");
                        }
                        delete ckclient_process;
                        ckclient_process = nullptr;
                    }
                    // Подключение сигналов для освобождения ресурсов
                    connect(openvpn_process, &QProcess::finished, this, [=]() {
                        qDebug() << "openvpn процесс завершился";
                        openvpn_process->deleteLater();
                    });

                    connect(ckclient_process, &QProcess::finished, this, [=]() {
                        qDebug() << "ckclient процесс завершился";
                        ckclient_process->deleteLater();
                    });


                    ui->ip_adress->setText("No connection");
                    ui->statusbar->showMessage("VPN service is disabled");
                } else {
                    ui->checkBox->setChecked(true);
                }
            }
        }
    }
    else
    {
        if(ui->checkBox->isChecked())
        {
            QMessageBox::critical(this, "Ошибка", "Вы не аутентифицированы.");
            ui->checkBox->setCheckState(Qt::Unchecked);
        }
    }
}

void MainWindow::getPublicIpAddress(QString &current_ip)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    QObject::connect(manager, &QNetworkAccessManager::finished, [this, manager,&current_ip](QNetworkReply *reply) {
        if (reply->error() == QNetworkReply::NoError) {
             current_ip = QString(reply->readAll());
            qDebug() << "My public IP address is: " << current_ip;
                if(current_ip == "191.96.94.211")
                {
                ui->ip_adress->setText(current_ip);
                ui->statusbar->showMessage("VPN service is enable");
                }
            // ui->ip_adress->setText(current_ip);
        } else {
            qDebug() << "Error: " << reply->errorString();
        }
        reply->deleteLater();
        manager->deleteLater();
    });
    QUrl url("https://api.ipify.org");
    QNetworkRequest request(url);
    manager->get(request);
}


bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->checkBox) {
        if (event->type() == QEvent::Enter) {
            onButtonEntered();
        } else if (event->type() == QEvent::Leave) {
            onButtonLeft();
        }
    }
    return false;
}

void MainWindow::onButtonEntered()
{
    ui->checkBox->setStyleSheet("QCheckBox::indicator {"
                                "    subcontrol-position: top center;"
                                "    width: 150px;"
                                "    height: 150px;"
                                "}"
                                "QCheckBox::indicator:checked {"
                                "    image: url(:/resources/resources/buttons/button_on_hover.png);"
                                "}"
                                "QCheckBox::indicator:unchecked {"
                                "    image: url(:/resources/resources/buttons/button_off_hover.png);"
                                "}");
}

void MainWindow::onButtonLeft()
{
    ui->checkBox->setStyleSheet("QCheckBox::indicator {"
                                "    subcontrol-position: top center;"
                                "    width: 150px;"
                                "    height: 150px;"
                                "}"
                                "QCheckBox::indicator:checked {"
                                "    image: url(:/resources/resources/buttons/button_on.png);"
                                "}"
                                "QCheckBox::indicator:unchecked {"
                                "    image: url(:/resources/resources/buttons/button_off.png);"
                                "}");
}
