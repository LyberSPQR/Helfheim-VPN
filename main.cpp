#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QMovie>
#include <QWidget>
#include <QVBoxLayout>
#include <QFile>
#include <QFontDatabase>


int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    // Установка значка приложения

    QIcon appIcon(":/resources/resources/icons/icon.png");
    app.setWindowIcon(appIcon);
    //Set Style
    QFile styleSheetFile(":/resources/resources/styles/style2.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    app.setStyleSheet(styleSheet);
    int fontId = QFontDatabase::addApplicationFont("font.ttf");
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(family);



    MainWindow w;


    w.show();

    return app.exec();
}
