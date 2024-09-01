#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QMouseEvent>
#include <QPoint>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_checkBox_stateChanged(int state);


    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

public slots:
      void remainingTimeCounter();
      void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
private:
    Ui::MainWindow *ui;
    QProcess *openvpn_process;
    QProcess *ckclient_process;
    QPoint m_dragStartPosition;
};

#endif // MAINWINDOW_H
