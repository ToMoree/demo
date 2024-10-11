#ifndef MASTER_CONTROLLER_H
#define MASTER_CONTROLLER_H

#include <QQmlContext>
#include <mutex>
#include "mvvmmanager.h"
class MasterController
{

public:
    MasterController(MasterController&) = delete;
    MasterController& operator= (MasterController&) = delete;
    ~MasterController();

    static MasterController* getInstance();

public :
    bool startUp(QQmlContext* rootContex);

private:
    MasterController(){};
    static std::once_flag m_onceFlag;
    MvvmManager m_mvvmManager;
};


#endif // MASTER_CONTROLLER_H
