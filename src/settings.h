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
};

#endif // SETTINGS_H
