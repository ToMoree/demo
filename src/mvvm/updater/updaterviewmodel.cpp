#include "updaterviewmodel.h"
#include "updatermodel.h"

UpdaterViewModel::UpdaterViewModel(QObject *parent)
    :QObject(parent)
{

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
