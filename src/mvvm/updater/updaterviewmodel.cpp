#include "updaterviewmodel.h"
#include "updatermodel.h"

UpdaterViewModel::UpdaterViewModel(QObject *parent)
    :QObject(parent)
{
    m_isUpdateAvailable = false;
    m_newVersion = "";
    m_downloadProgress = 0;
    m_downloadVisible = false;
}

UpdaterViewModel *UpdaterViewModel::getInstance()
{
    static UpdaterViewModel* instance = new UpdaterViewModel();
    return instance;
}

void UpdaterViewModel::checkForUpdates()
{
    CALL_MODEL(UpdaterModel)->checkForUpdates();
}

void UpdaterViewModel::startDownload()
{
    CALL_MODEL(UpdaterModel)->startDownload();
}

void UpdaterViewModel::cancelDownload()
{
    CALL_MODEL(UpdaterModel)->cancelDownload();
}
