#include <QQmlEngine>

#include "mvvmmanager.h"
#include "model.h"
#include "viewmodel.h"

#include "updater/updaterviewmodel.h"
#include "updater/updatermodel.h"
MvvmManager::MvvmManager()
{

}

MvvmManager::~MvvmManager()
{

}

bool MvvmManager::InitViewModes(QQmlContext* rootContex)
{
    bool bRet = true;
    m_pModelDataTransfer = new ModelDataTransfer();

    //for code auto completion
    qmlRegisterType<QObject>("JustForQml Code Auto Completion.", 1, 0, "DONT_USE_THIS");

    //register type

    //register meta type

    //register context property
    bRet &= AddViewMode(UpdaterModel::getInstance(), UpdaterViewModel::getInstance());
    rootContex->setContextProperty("UpdaterViewModel", UpdaterViewModel::getInstance());

    return bRet;
}

bool MvvmManager::AddViewMode(Model *model, ViewModel *viewmodel)
{
    bool bRet = false;
    if(viewmodel != nullptr && model != nullptr){
        model->setModelDataTransfer(m_pModelDataTransfer);
        // register viewmodel call back
        model->addViewModel(viewmodel);
        // register model call back
        viewmodel->addModel(model);
        // init the signal &slot connect
        model->InitConnect();
        bRet =  true;

    } else {
        //TODO log
    }
    return bRet;
}
