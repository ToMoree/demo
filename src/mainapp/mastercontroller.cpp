#include "mastercontroller.h"

// 静态成员初始化
std::once_flag MasterController::m_onceFlag;

MasterController::~MasterController()
{

}

MasterController *MasterController::getInstance()
{
    static MasterController* instance;
    std::call_once(m_onceFlag, []() {
        instance = new MasterController();
    });
    return instance;
}


bool MasterController::startUp(QQmlContext* rootContex)
{
    bool ret;
    //初始化database
    //初始化language
    //版本检测逻辑
    //获取启动类型：登陆 or 更新
    //自检
    //初始化mvvm
    ret &= m_mvvmManager.InitViewModes(rootContex);
    //进入主界面
    return true;
}
