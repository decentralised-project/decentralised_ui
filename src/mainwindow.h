#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopServices>
#include <QUrl>
#include <QSettings>
#include <QTime>
#include <logindialog.h>
#include <aboutdialog.h>
#include <preferencesdialog.h>
#include <decentralised_data.h>
#include <decentralised_p2p.h>
#include <stdlib.h>
#include "settings.h"

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

    void on_txtInput_returnPressed();

    void on_actionPreferences_triggered();


    void on_dataReceived(QByteArray data);

    void on_connectionEstablished();

    void on_connectionDropped();

    void on_connectionIncoming();

    void on_serverStarted(int port);

    void on_serverError(QString message);

    void on_dataError(QString message);

    void on_dnsSeedReceived(QString ip);

    void on_dnsSeedError(QString message);

private:

    void terminalWrite(QString text, QString color);

    Ui::MainWindow *_ui;
    LoginDialog* _login;
    AboutDialog* _about;
    PreferencesDialog* _preferences;
    decentralised_data* _data;
    decentralised_p2p* _client;
    settings _settings;
};

#endif // MAINWINDOW_H
