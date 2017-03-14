#include "settings.h"

settings::settings()
{
    loadSettings();
}

QString settings::getDataDirectory()
{
    return _dataDirectory;
}

void settings::setDataDirectory(QString path)
{
    _dataDirectory = path;
    writeSetting("data/directory", _dataDirectory);
}

QString settings::getLanguage()
{
    return _language;
}

void settings::setLanguage(QString language)
{
    _language = language;
    writeSetting("ui/language", _language);
}

int settings::getIncomingPort()
{
    return _incomingPort;
}

void settings::setIncomingPort(int port)
{
    _incomingPort = port;
    writeSetting("net/incomingPort", _incomingPort);
}

int settings::getWindowWidth()
{
    return _windowWidth;
}

void settings::setWindowWidth(int width)
{
    _windowWidth = width;
    writeSetting("ui/windowWidth", _windowWidth);
}

int settings::getWindowHeight()
{
    return _windowHeight;
}

void settings::setWindowHeight(int height)
{
    _windowHeight = height;
    writeSetting("ui/windowHeight", _windowHeight);
}

int settings::getMaxIncomingConnections()
{
    return _maxIncomingConnections;
}

void settings::setMaxIncomingConnections(int count)
{
    _maxIncomingConnections = count;
    writeSetting("net/maxIncomingConnections", _maxIncomingConnections);
}

int settings::getMaxOutgoingConnections()
{
    return _maxOutgoingConnections;
}

void settings::setMaxOutgoingConnections(int count)
{
    _maxOutgoingConnections = count;
    writeSetting("net/maxOutgoingConnections", _maxOutgoingConnections);
}

void settings::loadSettings()
{
    QSettings settings("Decentralised Project", "dc-gui-qt");
    _dataDirectory = settings.value("data/directory", "data/").toString();
    if(_dataDirectory == "data/")
    {
        QDir dir(".");
        _dataDirectory = dir.absolutePath().append("/").append(_dataDirectory);
    }

    _language = settings.value("ui/language", "English").toString();
    _incomingPort = settings.value("net/incomingPort", 6453).toInt();
    _maxIncomingConnections = settings.value("net/maxIncomingConnections", 8).toInt();
    _maxOutgoingConnections = settings.value("net/maxOutgoingConnections", 8).toInt();
    _windowWidth = settings.value("ui/windowWidth", 0).toInt();
    _windowHeight = settings.value("ui/windowHeight", 0).toInt();
}

void settings::writeSetting(const QString &key, const QVariant &variant)
{
    QSettings settings("Decentralised Project", "dc-gui-qt");
    settings.setValue(key, variant);
}
