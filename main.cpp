
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


    //Set Style
    QFile styleSheetFile(":/resources/resources/styles/style2.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    app.setStyleSheet(styleSheet);
    // int fontId = QFontDatabase::addApplicationFont("font.ttf");
    // QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
    // QFont font(family);

    QIcon appIcon("D:/src/resources/icons/prog.ico");
    app.setWindowIcon(appIcon);


    MainWindow w;

   w.setFixedSize(280, 410);
    w.show();

    return app.exec();
}
