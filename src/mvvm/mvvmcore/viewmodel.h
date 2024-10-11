#ifndef VIEWMODEL_H
#define VIEWMODEL_H

class Model;
#define CALL_MODEL(CLASS_NAME) static_cast<CLASS_NAME *>(getModel())

class ViewModel
{
public:
    ViewModel();

public:
    void addModel(Model* model);
    Model* getModel();

private:
    Model* m_pModel = nullptr;
};

#endif // VIEWMODEL_H
