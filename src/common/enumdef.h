#ifndef ENUMDEF_H
#define ENUMDEF_H

#include <QObject>
#include <QQmlEngine>

class ENUMDEF : public QObject
{
    Q_OBJECT
public:
    enum LANGUAGE{
        LANGUAGE_ZH,
        LANGUAGE_EN,
        LANGUAGE_MAX
    };
    Q_ENUM(LANGUAGE);

    /*Call back for qml qmlRegisterSingletonType*/
    static QObject  *callback(QQmlEngine *engine, QJSEngine *scriptEngine){
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)
        return ENUMDEF::getInstance();
    }

private:
    static ENUMDEF* getInstance(){
        static ENUMDEF* enumdef = new ENUMDEF();
        return enumdef;
    }
    explicit ENUMDEF(QObject *parent = nullptr){
        Q_UNUSED(parent)
    };
};

Q_DECLARE_METATYPE(ENUMDEF::LANGUAGE)
#endif // ENUMDEF_H
