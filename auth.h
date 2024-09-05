#ifndef AUTH_H
#define AUTH_H

#include <QDialog>
#include <QTcpSocket>
#include <QTimer>

namespace Ui {
class Auth;
}

class Auth : public QDialog {
    Q_OBJECT

public:
    explicit Auth(QWidget *parent = nullptr);
    ~Auth();

private slots:
    void on_pushButton_clicked();
    void onConnected();
    void onReadyRead();
    void onTimeout();

    void on_pushButton_2_clicked();

private:

    Ui::Auth *ui;
    QTcpSocket *socket;
    QByteArray responseBuffer;
    QTimer timer;
    QString key;


};

#endif // AUTH_H
