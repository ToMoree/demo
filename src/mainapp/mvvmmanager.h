#ifndef MVVMMANAGER_H
#define MVVMMANAGER_H

#include <QQmlContext>
#include "modeldatatransfer.h"

class Model;
class ViewModel;
class ModelDataTransfer;

class  MvvmManager
{
public:
    MvvmManager();
    ~MvvmManager();

public:
    bool InitViewModes(QQmlContext* rootContex);

private:
    bool AddViewMode(Model* model, ViewModel* viewmodel);

private:
    ModelDataTransfer* m_pModelDataTransfer = {};
};

#endif // MVVMMANAGER_H
