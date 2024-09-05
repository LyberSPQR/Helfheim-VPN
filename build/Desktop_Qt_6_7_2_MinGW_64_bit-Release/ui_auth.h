/********************************************************************************
** Form generated from reading UI file 'auth.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTH_H
#define UI_AUTH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>

QT_BEGIN_NAMESPACE

class Ui_Auth
{
public:
    QPushButton *pushButton;
    QLabel *label_2;
    QSplitter *splitter;
    QLabel *label;
    QLineEdit *key;
    QSplitter *splitter_3;
    QSplitter *splitter_2;
    QPushButton *pushButton_2;

    void setupUi(QDialog *Auth)
    {
        if (Auth->objectName().isEmpty())
            Auth->setObjectName("Auth");
        Auth->resize(400, 188);
        pushButton = new QPushButton(Auth);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 110, 381, 29));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton:hover {\n"
"    background-color: rgba(44, 192, 172, 0.7); \n"
"}"));
        label_2 = new QLabel(Auth);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(150, 10, 111, 20));
        QFont font;
        font.setPointSize(11);
        label_2->setFont(font);
        splitter = new QSplitter(Auth);
        splitter->setObjectName("splitter");
        splitter->setGeometry(QRect(10, 50, 381, 28));
        splitter->setOrientation(Qt::Orientation::Horizontal);
        label = new QLabel(splitter);
        label->setObjectName("label");
        splitter->addWidget(label);
        key = new QLineEdit(splitter);
        key->setObjectName("key");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(100);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(key->sizePolicy().hasHeightForWidth());
        key->setSizePolicy(sizePolicy);
        splitter->addWidget(key);
        splitter_3 = new QSplitter(Auth);
        splitter_3->setObjectName("splitter_3");
        splitter_3->setGeometry(QRect(370, 10, 25, 55));
        splitter_3->setOrientation(Qt::Orientation::Vertical);
        splitter_2 = new QSplitter(splitter_3);
        splitter_2->setObjectName("splitter_2");
        splitter_2->setOrientation(Qt::Orientation::Vertical);
        pushButton_2 = new QPushButton(splitter_2);
        pushButton_2->setObjectName("pushButton_2");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(25);
        sizePolicy1.setVerticalStretch(25);
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setMinimumSize(QSize(25, 25));
        pushButton_2->setMaximumSize(QSize(25, 25));
        splitter_2->addWidget(pushButton_2);
        splitter_3->addWidget(splitter_2);

        retranslateUi(Auth);

        QMetaObject::connectSlotsByName(Auth);
    } // setupUi

    void retranslateUi(QDialog *Auth)
    {
        Auth->setWindowTitle(QCoreApplication::translate("Auth", "Helfheim VPN", nullptr));
        pushButton->setText(QCoreApplication::translate("Auth", "Verificate", nullptr));
        label_2->setText(QCoreApplication::translate("Auth", "Helfheim VPN", nullptr));
        label->setText(QCoreApplication::translate("Auth", "Key:", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Auth", "\342\234\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Auth: public Ui_Auth {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTH_H
