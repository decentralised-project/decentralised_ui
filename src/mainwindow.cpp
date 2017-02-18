#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _client = new decentralised_p2p(0, _settings.getIncomingPort());

    QObject::connect(_client, &decentralised_p2p::connectionEstablished,
                     this, &MainWindow::on_connectionEstablished);
    QObject::connect(_client, &decentralised_p2p::dataReceived,
                     this, &MainWindow::on_dataReceived);
    QObject::connect(_client, &decentralised_p2p::connectionDropped,
                     this, &MainWindow::on_connectionDropped);
    QObject::connect(_client, &decentralised_p2p::connectionIncoming,
                     this, &MainWindow::on_connectionIncoming);
    QObject::connect(_client, &decentralised_p2p::serverStarted,
                     this, &MainWindow::on_serverStarted);
    QObject::connect(_client, &decentralised_p2p::serverError,
                     this, &MainWindow::on_serverError);
}

MainWindow::~MainWindow()
{
    delete _ui;
    delete _client;
}

void MainWindow::show()
{
    int windowWidth = _settings.getWindowWidth();
    int windowHeight = _settings.getWindowHeight();
    if(windowWidth > 0 && windowHeight > 0)
        this->resize(windowWidth, windowHeight);

    QSplitter* splitterMain = this->findChild<QSplitter*>("splitterMain");
    splitterMain->setSizes(QList<int>() << 400 << 100);

    QMainWindow::show();

    terminalWrite(tr("Decentralised Core v1.0.0"), "darkgreen");
    _client->Start();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);

   _settings.setWindowWidth(this->width());
   _settings.setWindowHeight(this->height());
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionLogin_triggered()
{
    _login = new LoginDialog(this);
    _login->show();
}

void MainWindow::on_actionAbout_Decentralised_triggered()
{
    _about = new AboutDialog(this);
    _about->show();
}

void MainWindow::on_actionPreferences_triggered()
{
    _preferences = new PreferencesDialog(this);
    _preferences->show();
}

void MainWindow::on_actionDecentralised_Website_triggered()
{
    QDesktopServices::openUrl(QUrl("http://decentralised-project.org", QUrl::TolerantMode));
}

void MainWindow::on_dataReceived(QByteArray data)
{

}

void MainWindow::on_connectionEstablished()
{

}

void MainWindow::on_connectionDropped()
{

}

void MainWindow::on_connectionIncoming()
{
    terminalWrite(tr("Incoming connection received."), "darkgreen");
}

void MainWindow::on_serverStarted(int port)
{
    terminalWrite(tr("Server started on local port %1 for incoming connections.")
                  .arg(QString::number(port)), NULL);
}

void MainWindow::on_serverError(QString message)
{
    terminalWrite(tr("Server error, incoming connections are disabled. %1").arg(message), "darkred");
}

void MainWindow::terminalWrite(QString text, QString color)
{
    if(color == NULL)
        color = "#404040";

    QString timeStamp = "[" + QTime::currentTime().toString("HH:mm") + "]";

    QLabel* terminal = this->findChild<QLabel*>("txtTerminal");
    QString existing = terminal->text();
    terminal->setText(QString("%1<div style=\"color:%2;margin-bottom:5px;\">%3 %4</div>")
                      .arg(existing, color, timeStamp, text));
}

void MainWindow::on_txtInput_returnPressed()
{
    QLineEdit* input = this->findChild<QLineEdit*>("txtInput");
    input->clear();
}
