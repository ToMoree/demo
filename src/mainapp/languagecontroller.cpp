#include <QCoreApplication>

#include "languagecontroller.h"


void LanguageController::loadLanguage(ENUMDEF::LANGUAGE type)
{
    qApp->removeTranslator(m_translator);
    QString languagePath = ":/qm/";
    if(type == ENUMDEF::LANGUAGE_EN){
        languagePath = languagePath + "en_US.qm";

    } else if (type == ENUMDEF::LANGUAGE_ZH){
        languagePath = languagePath + "zh_CN.qm";
    }

    if(m_translator->load(languagePath)){
        qApp->installTranslator(m_translator);
    }else{
        qDebug()<<"load language file error";
    }
}

LanguageController::~LanguageController()
{
    if(m_translator != nullptr){
        delete  m_translator;
        m_translator = nullptr;
    }
}
