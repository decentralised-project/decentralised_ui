#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    _ui->setupUi(this);

#ifdef MACOSX
    _ui->centralWidget->setStyleSheet("font-size:12pt;");
#endif

    _data = new decentralised_data(this);
    _crypto = new decentralised_crypt(this);
    EC_KEY *instanceKey = _crypto->generate_key_pair();

    QObject::connect(_data, &decentralised_data::dataError,
                     this, &MainWindow::on_connectionEstablished);

    _client = new decentralised_p2p(instanceKey, _crypto, this, _settings.getIncomingPort());

    QObject::connect(_client, &decentralised_p2p::connectionEstablished,
                     this, &MainWindow::on_connectionEstablished);
    QObject::connect(_client, &decentralised_p2p::dataReceived,
                     this, &MainWindow::on_dataReceived);
    QObject::connect(_client, &decentralised_p2p::connectionDropped,
                     this, &MainWindow::on_connectionDropped);
    QObject::connect(_client, &decentralised_p2p::connectionIncoming,
                     this, &MainWindow::on_connectionIncoming);
    QObject::connect(_client, &decentralised_p2p::connectionOutgoing,
                     this, &MainWindow::on_connectionOutgoing);
    QObject::connect(_client, &decentralised_p2p::serverStarted,
                     this, &MainWindow::on_serverStarted);
    QObject::connect(_client, &decentralised_p2p::serverError,
                     this, &MainWindow::on_serverError);
    QObject::connect(_client, &decentralised_p2p::dnsSeedReceived,
                     this, &MainWindow::on_dnsSeedReceived);
    QObject::connect(_client, &decentralised_p2p::dnsSeedError,
                     this, &MainWindow::on_dnsSeedError);
    QObject::connect(_client, &decentralised_p2p::outgoingError,
                     this, &MainWindow::on_outgoing_error);
}

MainWindow::~MainWindow()
{
//    delete _ui;
//    delete _client;
//    delete _data;
}

void MainWindow::show()
{
    int windowWidth = _settings.getWindowWidth();
    int windowHeight = _settings.getWindowHeight();
    if(windowWidth > 0 && windowHeight > 0)
        this->resize(windowWidth, windowHeight);

    QSplitter* splitterMain = this->findChild<QSplitter*>("splitterMain");
    splitterMain->setSizes(QList<int>() << 400 << 100);

    QTextEdit* txtTerminal = this->findChild<QTextEdit*>("txtTerminal");
    txtTerminal->setWordWrapMode(QTextOption::WrapAnywhere);

    QMainWindow::show();

    terminalWrite(tr("Decentralised Core v1.0.0"), "darkgreen");

    const EC_POINT* publicKey = _crypto->get_public_key(_client->GetInstanceKey());
    terminalWrite(tr("Instance key is %1").arg(_crypto->to_base58(publicKey)), NULL);

    _data->initialize(_settings.getDataDirectory());

    QList<dc_host> hosts = _data->getHosts();
    if(hosts.size() == 0)
    {
        terminalWrite(tr("Can't find any previously connected peers, so trying dns seeds."), NULL);
        _client->RequestDnsSeeds();
    }
    else
        terminalWrite(tr("Found %1 previously connected peers to try and reconnect.")
                      .arg(hosts.size()), NULL);

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
    _login = new LoginDialog(_settings.getDataDirectory(), this);
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
    terminalWrite(tr("Recieved data: %1").arg(QString(data)), "darkgreen");
}

void MainWindow::on_connectionEstablished()
{

}

void MainWindow::on_connectionDropped()
{

}

void MainWindow::on_connectionOutgoing()
{
    terminalWrite(tr("Outgoing connection established."), "darkgreen");
}

void MainWindow::on_outgoing_error(QString message)
{
    terminalWrite(tr("Error connecting to peer. %1").arg(message), "darkred");
}

void MainWindow::on_connectionIncoming(dc_peer *peer)
{
    terminalWrite(tr("Incoming connection received from %1.").arg(peer->GetRemoteAddress().toString()), "darkgreen");
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

void MainWindow::on_dataError(QString message)
{
    terminalWrite(tr("Data error. %1:6453").arg(message), "darkred");
}

void MainWindow::on_dnsSeedReceived(QString ip)
{
    terminalWrite(tr("Trying DNS seed at %1").arg(ip), NULL);
    _client->StartOutgoing(ip, 6453);
}

void MainWindow::on_dnsSeedError(QString message)
{
    terminalWrite(tr("DNS error. %1").arg(message), "darkred");
}

void MainWindow::terminalWrite(QString text, QString color)
{
    if(color == NULL)
        color = "#404040";

    QString timeStamp = "[" + QTime::currentTime().toString("HH:mm") + "]";

    QTextEdit* terminal = this->findChild<QTextEdit*>("txtTerminal");
    QString existing = terminal->toHtml();
    terminal->setText(QString("%1<div style=\"color:%2;margin-bottom:5px;\">%3 %4</div>")
                      .arg(existing, color, timeStamp, text));
}

void MainWindow::on_txtInput_returnPressed()
{
    QLineEdit* input = this->findChild<QLineEdit*>("txtInput");
    input->clear();
}
