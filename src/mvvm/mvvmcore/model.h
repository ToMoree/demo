#ifndef MODEL_H
#define MODEL_H

#include <QObject>

class ViewModel;
class ModelDataTransfer;

#define CALL_VIEWMODEL(CLASS_NAME) static_cast<CLASS_NAME *>(getViewModel())
class  Model : public  QObject
{
    Q_OBJECT
public:
    Model(QObject *parent = nullptr);

public:
    virtual void addViewModel(ViewModel* viewmode);
    virtual void InitConnect();

    static void setModelDataTransfer(ModelDataTransfer *transfer);
    static ModelDataTransfer* getModelDataTransfer();

    ViewModel* getViewModel();

protected:
    virtual void addModelDataTransferConnection(){}
    virtual void addWhiteboardDataResponseConnection(){}

private:
    ViewModel* m_pViewModel = nullptr;
    static ModelDataTransfer* m_pModelDataTransfer;
};



#endif // MODEL_H
