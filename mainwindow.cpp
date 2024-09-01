
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

    // int id = QFontDatabase::addApplicationFont(":/resources/resources/fonts/Yggdrasil.ttf");
    // QString family1 = QFontDatabase::applicationFontFamilies(id).at(0);
    // QFont Yggdrasil(family1);


    int id2 = QFontDatabase::addApplicationFont(":/resources/resources/fonts/norse.bold.otf");
    QString family2 = QFontDatabase::applicationFontFamilies(id2).at(0);
    QFont norse_bold(family2);

    // int id3 = QFontDatabase::addApplicationFont(":/resources/resources/fonts/norse.regular.otf");
    // QString family3 = QFontDatabase::applicationFontFamilies(id3).at(0);
    // QFont norse_regular(family3);

    // int id4 = QFontDatabase::addApplicationFont(":/resources/resources/fonts/odins_regular.ttf");
    // QString family4 = QFontDatabase::applicationFontFamilies(id4).at(0);
    // QFont odins_regular(family4);

    // int id5 = QFontDatabase::addApplicationFont(":/resources/resources/fonts/odins_ragged.ttf");
    // QString family5 = QFontDatabase::applicationFontFamilies(id5).at(0);
    // QFont odins_ragged(family5);

    // int id6 = QFontDatabase::addApplicationFont(":/resources/resources/fonts/2-prong-tree.regular.ttf");
    // QString family6 = QFontDatabase::applicationFontFamilies(id6).at(0);
    // QFont prong_tree(family6);

    // int id7 = QFontDatabase::addApplicationFont(":/resources/resources/fonts/Art Greco.ttf");
    // QString family7 = QFontDatabase::applicationFontFamilies(id7).at(0);
    // QFont Art_Greco(family7);

    ui->program_name->setFont(norse_bold);
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
      authWindow.setFixedSize(450, 190);
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
                QMessageBox::critical(this, "Ошибка", "Линукс-блок запустился");
                openvpn_process = new QProcess(this);
                ckclient_process = new QProcess(this);
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


            QString args = working_dir + "/config.ovpn";
            QString argsCk = "-c ckclient.json -s 191.96.94.211";

            QStringList argsList = args.split(" ", Qt::SkipEmptyParts);
            QStringList argsListCk = argsCk.split(" ", Qt::SkipEmptyParts);

            if (state == Qt::Checked) {


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

                openvpn_process = new QProcess(this);
                ckclient_process = new QProcess(this);

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
