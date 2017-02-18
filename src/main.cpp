#include "mainwindow.h"
#include <QApplication>
#include <QtCore/QSettings>
#include <QtNetwork/QNetworkConfigurationManager>
#include <QtNetwork/QNetworkSession>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QCoreApplication::setOrganizationName("Decentralised Project");
    QCoreApplication::setOrganizationDomain("decentralised-project.org");
    QCoreApplication::setApplicationName("dc-gui-qt");

#ifndef WINDOWS
    QFont font("DejaVu Sans [Qt Embedded]", 9, QFont::Normal, false);
    QApplication::setFont(font);
#endif

    w.show();

    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        QSettings settings;
        settings.beginGroup(QLatin1String("net"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) != QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        QNetworkSession *networkSession = new QNetworkSession(config, &a);
        networkSession->open();
        networkSession->waitForOpened();

        if (networkSession->isOpen()) {
            // Save the used configuration
            QNetworkConfiguration config = networkSession->configuration();
            QString id;
            if (config.type() == QNetworkConfiguration::UserChoice) {
                id = networkSession->sessionProperty(
                        QLatin1String("UserChoiceConfiguration")).toString();
            } else {
                id = config.identifier();
            }

            settings.beginGroup(QLatin1String("net"));
            settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
            settings.endGroup();
        }
    }

    return a.exec();
}
