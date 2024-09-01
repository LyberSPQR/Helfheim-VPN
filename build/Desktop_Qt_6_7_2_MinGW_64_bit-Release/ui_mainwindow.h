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
#include <QtWidgets/QSpacerItem>
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
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QSplitter *splitter;
    QCheckBox *checkBox;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_10;
    QLabel *ip;
    QLabel *ip_adress;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *remain_time;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(295, 410);
        QFont font;
        font.setFamilies({QString::fromUtf8("ZWAdobeF")});
        MainWindow->setFont(font);
        MainWindow->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        MainWindow->setWindowTitle(QString::fromUtf8("Helfheim VPN"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 255, 0);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(-1, 0, -1, 0);
        horizontalSpacer = new QSpacerItem(25, 25, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        horizontalSpacer_2 = new QSpacerItem(25, 25, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(0, 25));
        label_2->setMaximumSize(QSize(16777215, 50));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setBold(false);
        font1.setKerning(true);
        font1.setStyleStrategy(QFont::PreferAntialias);
        label_2->setFont(font1);
        label_2->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        horizontalLayout_4->addWidget(label_2, 0, Qt::AlignmentFlag::AlignHCenter);

        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setMinimumSize(QSize(25, 25));
        pushButton_3->setMaximumSize(QSize(25, 25));

        horizontalLayout_4->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(25, 25));
        pushButton_2->setMaximumSize(QSize(25, 25));

        horizontalLayout_4->addWidget(pushButton_2);


        verticalLayout_3->addLayout(horizontalLayout_4);

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

        verticalLayout_3->addWidget(splitter);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        verticalLayout_3->addItem(verticalSpacer);


        verticalLayout->addLayout(verticalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_10 = new QSpacerItem(5, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_10);

        ip = new QLabel(centralwidget);
        ip->setObjectName("ip");
        ip->setMaximumSize(QSize(80, 16777215));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI")});
        font2.setPointSize(11);
        ip->setFont(font2);

        horizontalLayout->addWidget(ip, 0, Qt::AlignmentFlag::AlignLeft);

        ip_adress = new QLabel(centralwidget);
        ip_adress->setObjectName("ip_adress");

        horizontalLayout->addWidget(ip_adress, 0, Qt::AlignmentFlag::AlignLeft);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_9 = new QSpacerItem(5, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QPalette palette;
        label->setPalette(palette);
        QFont font3;
        font3.setPointSize(11);
        label->setFont(font3);

        horizontalLayout_2->addWidget(label, 0, Qt::AlignmentFlag::AlignLeft);

        remain_time = new QLabel(centralwidget);
        remain_time->setObjectName("remain_time");

        horizontalLayout_2->addWidget(remain_time);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_8);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(horizontalLayout_3);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setFont(font3);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton:hover {\n"
"    background-color: rgba(44, 192, 172, 0.7); \n"
"}"));

        verticalLayout->addWidget(pushButton);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 295, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        label_2->setText(QCoreApplication::translate("MainWindow", "Helfheim VPN", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        checkBox->setText(QString());
        ip->setText(QCoreApplication::translate("MainWindow", "IP adress:", nullptr));
        ip_adress->setText(QCoreApplication::translate("MainWindow", "No connection", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Remaining time:", nullptr));
        remain_time->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "Authentication", nullptr));
        (void)MainWindow;
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
