#ifndef UPDATER_VIEWMODEL_H
#define UPDATER_VIEWMODEL_H
#include <QObject>

#include "viewmodel.h"
#include "stdafx.h"

class UpdaterViewModel : public QObject, public ViewModel
{
    Q_OBJECT
    Q_PROPERTY_AUTO(bool, isUpdateAvailable)
    Q_PROPERTY_AUTO(QString, newVersion)

    Q_PROPERTY_AUTO(bool, downloadVisible)
    Q_PROPERTY_AUTO(float, downloadProgress)


public:
     UpdaterViewModel(QObject *parent = nullptr);
     static UpdaterViewModel* getInstance();

     Q_INVOKABLE void checkForUpdates();
     Q_INVOKABLE void startDownload();

public slots:


signals:


private:

};
#endif // UPDATER_VIEWMODEL_H
