#include "viewmodel.h"

ViewModel::ViewModel()
{

}

void ViewModel::addModel(Model* model)
{
    m_pModel = model;
}

Model* ViewModel::getModel()
{
    return m_pModel;
}
