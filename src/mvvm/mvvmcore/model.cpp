#include "model.h"
#include "viewmodel.h"
#include "modeldatatransfer.h"
ModelDataTransfer* Model::m_pModelDataTransfer = nullptr;

Model::Model(QObject *parent):QObject(parent)
{

}

void Model::addViewModel(ViewModel *viewmode)
{
    m_pViewModel = viewmode;
}

void Model::InitConnect()
{
    addWhiteboardDataResponseConnection();
    addModelDataTransferConnection();
}

ViewModel* Model::getViewModel()
{
    return m_pViewModel;
}

void Model::setModelDataTransfer(ModelDataTransfer *transfer)
{
    if(m_pModelDataTransfer != transfer){
        if(m_pModelDataTransfer != nullptr){
            delete  m_pModelDataTransfer;
            m_pModelDataTransfer = transfer;
        }
    }
}

ModelDataTransfer *Model::getModelDataTransfer()
{
    return m_pModelDataTransfer;
}
