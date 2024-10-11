#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>

#include "updatermodel.h"
#include "updaterviewmodel.h"
#include "version.h"

UpdaterModel::UpdaterModel()
{
    qDebug()<<"QSslSocket="<<QSslSocket::sslLibraryBuildVersionString();
    qDebug() << "OpenSSL支持情况:" << QSslSocket::supportsSsl();

    m_manager = new QNetworkAccessManager();
#ifdef UPDATE_FROM_GIT
    setUrl(QString("https://api.github.com/repos/ToMoree/demo/releases/latest"));
#else
    //server url
#endif
    connect(m_manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(onReply(QNetworkReply *)));
}

UpdaterModel::~UpdaterModel()
{
    if(m_manager != nullptr){
        delete m_manager;
        m_manager = nullptr;
    }
}

UpdaterModel *UpdaterModel::getInstance()
{
    static UpdaterModel* model = new UpdaterModel();
    return model;
}

void UpdaterModel::checkForUpdates()
{
    QNetworkRequest request;

    request.setUrl(url());
    request.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::NoLessSafeRedirectPolicy);

    m_manager->get(request);
}

QString UpdaterModel::url() const
{
    return m_url;
}

void UpdaterModel::setUrl(const QString &url)
{
    m_url = url;
}

void UpdaterModel::onReply(QNetworkReply *reply)
{
    /* Check if we need to redirect */
    QUrl redirect = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    if (!redirect.isEmpty()){
       setUrl(redirect.toString());
       checkForUpdates();
       return;
    }

    /* There was a network error */
    if (reply->error() != QNetworkReply::NoError){
       CALL_VIEWMODEL(UpdaterViewModel)->isUpdateAvailable(false);
       //emit checkingFinished(url());
       return;
    }

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    /* JSON is invalid */
    if (document.isNull()){
       CALL_VIEWMODEL(UpdaterViewModel)->isUpdateAvailable(false);
       //emit checkingFinished(url());
       return;
    }

    QVariantMap gitMap = document.toVariant().toMap();
    qDebug()<<"git tag name ==" <<gitMap.value("tag_name").toString();
    if(gitMap.value("tag_name").toString() != APPLICATION_VERSION){
        CALL_VIEWMODEL(UpdaterViewModel)->newVersion(gitMap.value("tag_name").toString());
    }else{
        //showInfo(qsTr("The current version is already the latest"))
    }
#ifdef UPDATE_FROM_GIT

#else

#endif

}
