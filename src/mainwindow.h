#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopServices>
#include <QUrl>
#include <QSettings>
#include <QTime>
#include <logindialog.h>
#include <aboutdialog.h>
#include <decentralised_p2p.h>
#include <stdlib.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void show();
    void resizeEvent(QResizeEvent* event);

private slots:
    void on_actionExit_triggered();

    void on_actionLogin_triggered();

    void on_actionAbout_Decentralised_triggered();

    void on_actionDecentralised_Website_triggered();

    void on_dataReceived(QByteArray data);

    void on_connectionEstablished();

    void on_connectionDropped();

private:

    void terminalWrite(QString text, QString color);

    Ui::MainWindow *ui;
    LoginDialog* login;
    AboutDialog* about;
    decentralised_p2p* client;
};

#endif // MAINWINDOW_H
