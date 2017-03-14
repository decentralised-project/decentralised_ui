#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QDir>

class settings
{
public:
    settings();

    QString getDataDirectory();
    void setDataDirectory(QString path);

    QString getLanguage();
    void setLanguage(QString language);

    int getIncomingPort();
    void setIncomingPort(int port);

    int getMaxIncomingConnections();
    void setMaxIncomingConnections(int count);

    int getMaxOutgoingConnections();
    void setMaxOutgoingConnections(int count);

    int getWindowWidth();
    void setWindowWidth(int width);

    int getWindowHeight();
    void setWindowHeight(int height);

private:
    void loadSettings();
    void writeSetting(const QString &key, const QVariant &variant);

    QString _dataDirectory;
    QString _language;
    int _incomingPort;
    int _windowWidth;
    int _windowHeight;
    int _maxIncomingConnections;
    int _maxOutgoingConnections;
};

#endif // SETTINGS_H
