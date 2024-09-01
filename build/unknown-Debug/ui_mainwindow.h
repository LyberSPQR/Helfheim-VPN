/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QCheckBox *checkBox;
    QHBoxLayout *horizontalLayout;
    QLabel *ip;
    QLabel *ip_adress;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *remain_time;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(374, 521);
        MainWindow->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 255, 0);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        checkBox = new QCheckBox(splitter);
        checkBox->setObjectName("checkBox");
        checkBox->setAutoFillBackground(false);
        checkBox->setStyleSheet(QString::fromUtf8("QCheckBox::indicator {\n"
"subcontrol-position: top center;\n"
"    width: 150px;\n"
"    height: 150px;\n"
"}\n"
"\n"
"QCheckBox::indicator:checked {\n"
"    image: url(\":/resources/resources/buttons/button_on.png\");\n"
"}\n"
"\n"
"QCheckBox::indicator:unchecked {\n"
"    image: url(\":/resources/resources/buttons/button_off.png\");\n"
"}\n"
""));
        checkBox->setIconSize(QSize(10, 10));
        splitter->addWidget(checkBox);

        verticalLayout->addWidget(splitter);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        ip = new QLabel(centralwidget);
        ip->setObjectName("ip");
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(11);
        ip->setFont(font);

        horizontalLayout->addWidget(ip);

        ip_adress = new QLabel(centralwidget);
        ip_adress->setObjectName("ip_adress");

        horizontalLayout->addWidget(ip_adress);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QPalette palette;
        label->setPalette(palette);
        QFont font1;
        font1.setPointSize(11);
        label->setFont(font1);

        horizontalLayout_2->addWidget(label);

        remain_time = new QLabel(centralwidget);
        remain_time->setObjectName("remain_time");

        horizontalLayout_2->addWidget(remain_time);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(horizontalLayout_3);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton:hover {\n"
"    background-color: rgba(44, 192, 172, 0.7); \n"
"}"));

        verticalLayout->addWidget(pushButton);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 374, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Helfheim VPN", nullptr));
        checkBox->setText(QString());
        ip->setText(QCoreApplication::translate("MainWindow", "IP adress:", nullptr));
        ip_adress->setText(QCoreApplication::translate("MainWindow", "No connection", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Remaining time:", nullptr));
        remain_time->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "Authentication", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
