#ifndef LANGUAGE_CONTROLLER_H
#define LANGUAGE_CONTROLLER_H

#include <QObject>
#include <QTranslator>
#include "enumdef.h"

class LanguageController: public QObject
{
    Q_OBJECT
public:
    static LanguageController* getInstance();
    LanguageController(LanguageController&) = delete;
    LanguageController& operator= (LanguageController&) = delete;

    //load language
    void loadLanguage(ENUMDEF::LANGUAGE type);

private:
    LanguageController(){};
    ~LanguageController();

private:
    QTranslator*  m_translator;
};

#endif // LANGUAGE_CONTROLLER_H
