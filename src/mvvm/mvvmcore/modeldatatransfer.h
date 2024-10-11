#ifndef MODEL_DATA_TRANSFER_H
#define MODEL_DATA_TRANSFER_H

#include <QObject>
#include "enumdef.h"

#define DECLARE_TS_SIGNAL(signal_name, ...) \
    void signal_from_TS_##signal_name(__VA_ARGS__);

class ModelDataTransfer : public  QObject
{
    Q_OBJECT
public:
    ModelDataTransfer(){};

signals:
    DECLARE_TS_SIGNAL(demo, int a, QString b);

};



#endif // MODEL_DATA_TRANSFER_H
