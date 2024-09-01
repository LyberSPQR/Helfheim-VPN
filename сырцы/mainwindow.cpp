
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


    namespace fs = std::filesystem;

#if defined Q_OS_WIN
QString osys = "win";
#elif defined(Q_OS_LINUX)
QString osys = "lin";
#endif

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
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

}

MainWindow::~MainWindow() {
    delete ui;

        openvpn_process->kill();
        openvpn_process->waitForFinished(); // Ждать, пока процесс завершится
        delete openvpn_process;
        openvpn_process = nullptr;

        ckclient_process->kill();
        ckclient_process->waitForFinished(); // Ждать, пока процесс завершится
        delete ckclient_process;
        ckclient_process = nullptr;

}

void MainWindow::on_pushButton_clicked() {
    Auth authWindow;
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
void MainWindow::on_checkBox_stateChanged(int state)
{


    QString path = QCoreApplication::applicationFilePath();
    QFileInfo fileInfo(path);
    QString working_dir = fileInfo.absolutePath();
    // QString command_qs_lin = "openvpn " + working_dir + "/config.ovpn";
    // QByteArray command_lin = command_qs_lin.toUtf8();
    // const char* cStr_lin = command_lin.constData();
    // QString command_qs_win = "openvpn.exe " + working_dir + "/config.ovpn";
    // QByteArray command_win = command_qs_win.toUtf8();
    // const char* cStr_win = command_win.constData();
    int cnt = 0;
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        if (entry.is_regular_file() && (entry.path().extension() == ".ovpn" || entry.path().extension() == ".json"))
        {
            cnt++;
        }
    }
    std:: cerr << cnt;
    if(cnt != 0){
        if (osys == "lin")
        {
            if (state == Qt::Checked)
            {

                 openvpn_process = new QProcess();
                 ckclient_process = new QProcess();
                QString args = working_dir + "/config.ovpn";
                QString argsCk = working_dir + "-c ckclient.json -s 191.96.94.211";
                QStringList argsList = args.split(" ", Qt::SkipEmptyParts);
                QStringList argsListCk = argsCk.split(" ", Qt::SkipEmptyParts);
\

                if (!openvpn_process->startDetached("openvpn", argsList)) {

                    throw std::runtime_error("Failed to start openvpn process");
                    QMessageBox::critical(this, "Ошибка", "Обратитесь в службу поддержки.");
                }

                if (!ckclient_process->startDetached("ck-client",argsListCk)) {
                    throw std::runtime_error("Failed to start ck-client process");
                    QMessageBox::critical(this, "Ошибка", "Обратитесь в службу поддержки.");
                }

                remainingTimeCounter();
                ui->ip_adress->setText("191.96.94.211");
                ui->statusbar->showMessage("VPN service is enable");
            } else {
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to disable VPN service?", QMessageBox::Yes|QMessageBox::No);

                if (reply == QMessageBox::Yes) {
                    if (openvpn_process) {
                        openvpn_process->terminate();
                        openvpn_process->waitForFinished(); // Ждать, пока процесс завершится
                        delete openvpn_process;
                        openvpn_process = nullptr;
                    }

                    if (ckclient_process) {
                        ckclient_process->terminate();
                        ckclient_process->waitForFinished(); // Ждать, пока процесс завершится
                        delete ckclient_process;
                        ckclient_process = nullptr;
                    }
                    ui->ip_adress->setText("No connection");
                    ui->statusbar->showMessage("VPN service is disable");
                } else {
                    ui->checkBox->setChecked(true);
                }
            }
        }
        else if (osys == "win") {
            openvpn_process = new QProcess();
            ckclient_process = new QProcess();

            QString args = working_dir + "/config.ovpn";
            QString argsCk = "-c ckclient.json -s 191.96.94.211";

            QStringList argsList = args.split(" ", Qt::SkipEmptyParts);
            QStringList argsListCk = argsCk.split(" ", Qt::SkipEmptyParts);

            if (state == Qt::Checked) {
                // Перенаправление вывода процессов в null
                openvpn_process->setProcessChannelMode(QProcess::MergedChannels); // Объединяем stdout и stderr
                openvpn_process->setStandardOutputFile(QByteArray()); // Перенаправляем вывод в null

                ckclient_process->setProcessChannelMode(QProcess::MergedChannels);
                ckclient_process->setStandardOutputFile(QByteArray());

                // Запуск процессов
                openvpn_process->start("openvpn.exe", argsList);
                if (!openvpn_process->waitForStarted()) {
                    QMessageBox::critical(this, "Ошибка", "Обратитесь в службу поддержки.");
                    delete openvpn_process;
                    openvpn_process = nullptr;
                    throw std::runtime_error("Failed to start openvpn process");
                }

                ckclient_process->start("ck-client.exe", argsListCk);
                if (!ckclient_process->waitForStarted()) {
                    QMessageBox::critical(this, "Ошибка", "Обратитесь в службу поддержки.");
                    delete ckclient_process;
                    ckclient_process = nullptr;
                    throw std::runtime_error("Failed to start ck-client process");
                }

                remainingTimeCounter();
                ui->ip_adress->setText("191.96.94.211");
                ui->statusbar->showMessage("VPN service is enabled");



            } else {
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to disable VPN service?", QMessageBox::Yes | QMessageBox::No);

                if (reply == QMessageBox::Yes) {
                    // Завершение openvpn_proces
                    if (openvpn_process) {
                        openvpn_process->terminate(); // Попросить завершиться корректно
                        if (!openvpn_process->waitForFinished(30)) { // Ждать до 3 секунд
                            QProcess::execute("taskkill", QStringList() << "/F" << "/IM" << "openvpn.exe");
                            openvpn_process->kill();
                        }
                        delete openvpn_process; // Освобождаем память
                        openvpn_process = nullptr;
                    }

                    // Завершение ckclient_process
                    if (ckclient_process) {
                        ckclient_process->terminate(); // Попросить завершиться корректно
                        if (!ckclient_process->waitForFinished(30)) { // Ждать до 3 секунд
                             QProcess::execute("taskkill", QStringList() << "/F" << "/IM" << "ck-client.exe");
                        }
                        delete ckclient_process; // Освобождаем память
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
                    ui->checkBox->setChecked(true); // Сохраняем состояние
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
