#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>

#include "updatermodel.h"
#include "updaterviewmodel.h"
#include "version.h"

#define INTSALLER_FILE_NAME "installer.exe"
static const QString PARTIAL_DOWN(".part");

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
    m_fileName = INTSALLER_FILE_NAME;
    /* Set download directory */
    m_downloadDir.setPath(QDir::homePath() + "/Downloads/");


    connect(m_manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(onCheckForUpdatesReply(QNetworkReply *)));
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

void UpdaterModel::startDownload()
{
    //reset ui
    CALL_VIEWMODEL(UpdaterViewModel)->downloadProgress(0);

    /* Configure the network request */
    QNetworkRequest request(downloadUrl());

    request.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::NoLessSafeRedirectPolicy);

 #if (QT_VERSION >= QT_VERSION_CHECK(5, 15, 0))
    /* 5s timeout */
    request.setTransferTimeout(5000);
 #endif

    //necessary?
    request.setRawHeader("User-Agent", APPLICATION_VERSION);

    m_reply = m_manager->get(request);
    m_startTime = QDateTime::currentDateTime().toSecsSinceEpoch();

    /* Ensure that downloads directory exists */
    if (!m_downloadDir.exists())
       m_downloadDir.mkpath(".");

    /* Remove old downloads */
    QFile::remove(m_downloadDir.filePath(m_fileName));
    QFile::remove(m_downloadDir.filePath(m_fileName + PARTIAL_DOWN));

    /* Update UI when download progress changes or download finishes */
    connect(m_reply, SIGNAL(metaDataChanged()), this, SLOT(metaDataChanged()));
    connect(m_reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(updateProgress(qint64, qint64)));
    connect(m_reply, SIGNAL(finished()), this, SLOT(finished()));
}

QString UpdaterModel::url() const
{
    return m_url;
}

void UpdaterModel::setUrl(const QString &url)
{
    m_url = url;
}

QString UpdaterModel::downloadUrl() const
{
    return m_downloadUrl;
}

void UpdaterModel::setDownloadUrl(const QString &downloadUrl)
{
    m_downloadUrl = downloadUrl;
}

void UpdaterModel::onCheckForUpdatesReply(QNetworkReply *reply)
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

    QVariantMap gitRetMap = document.toVariant().toMap();
    if(gitRetMap.value("tag_name").toString() != APPLICATION_VERSION){
        CALL_VIEWMODEL(UpdaterViewModel)->newVersion(gitRetMap.value("tag_name").toString());
        QVariantList assets = gitRetMap.value("assets").toList();
        if(!assets.isEmpty()){
            setDownloadUrl(assets.first().toMap().value("browser_download_url").toString());
        }

    }else{
        //showInfo(qsTr("The current version is already the latest"))
    }
#ifdef UPDATE_FROM_GIT

#else

#endif

}

void UpdaterModel::finished()
{
    //remove partial file if error
    if (m_reply->error() != QNetworkReply::NoError){
       QFile::remove(m_downloadDir.filePath(m_fileName + PARTIAL_DOWN));
       return;
    }

    /* Rename file */
    QFile::rename(m_downloadDir.filePath(m_fileName + PARTIAL_DOWN), m_downloadDir.filePath(m_fileName));

    /* Notify application */
    //emit downloadFinished(m_url, m_downloadDir.filePath(m_fileName));

    /* Install the update */
    m_reply->close();
    installUpdate();
    CALL_VIEWMODEL(UpdaterViewModel)->downloadVisible(false);
    //setVisible(false);
}

void UpdaterModel::metaDataChanged()
{
    QVariant variant = m_reply->header(QNetworkRequest::ContentDispositionHeader);
    if (variant.isValid()){
       QString contentDisposition = QByteArray::fromPercentEncoding(variant.toByteArray()).constData();
       QRegularExpression regExp(R"(filename=(\S+))");
       QRegularExpressionMatch match = regExp.match(contentDisposition);
       if (match.hasMatch()){
          m_fileName = match.captured(1);
          qDebug()<<"metaDataChanged filename ===" <<m_fileName;
       }
    }
}

void UpdaterModel::openDownload()
{

}

void UpdaterModel::installUpdate()
{

}

void UpdaterModel::cancelDownload()
{

}

/**
 * Writes the downloaded data to the disk
 */
void UpdaterModel::saveFile(qint64 received, qint64 total)
{
    Q_UNUSED(received);
    Q_UNUSED(total);

    /* Check if we need to redirect */
    QUrl url = m_reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    setDownloadUrl(url.toString());
    if (!url.isEmpty()){
       startDownload();
       return;
    }

    /* Save downloaded data to disk */
    QFile file(m_downloadDir.filePath(m_fileName + PARTIAL_DOWN));
    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
       file.write(m_reply->readAll());
       file.close();
    }
}

/**
 * Calculates the appropiate size units (bytes, KB or MB) for the received
 * data and the total download size. Then, this function proceeds to update the
 * dialog controls/UI.
 */
void UpdaterModel::calculateSizes(qint64 received, qint64 total)
{
    QString totalSize;
    QString receivedSize;

    if (total < 1024)
       totalSize = tr("%1 bytes").arg(total);

    else if (total < 1048576)
       totalSize = tr("%1 KB").arg(round(total / 1024));

    else
       totalSize = tr("%1 MB").arg(round(total / 1048576));

    if (received < 1024)
       receivedSize = tr("%1 bytes").arg(received);

    else if (received < 1048576)
       receivedSize = tr("%1 KB").arg(received / 1024);

    else
       receivedSize = tr("%1 MB").arg(received / 1048576);

//    m_ui->downloadLabel->setText(tr("Downloading updates") + " (" + receivedSize + " " + tr("of") + " " + totalSize
//                                 + ")");
}

void UpdaterModel::updateProgress(qint64 received, qint64 total)
{
    if (total > 0){
       CALL_VIEWMODEL(UpdaterViewModel)->downloadProgress(received / total);

       calculateSizes(received, total);
       calculateTimeRemaining(received, total);
       saveFile(received, total);

    }else{
//       m_ui->progressBar->setMinimum(0);
//       m_ui->progressBar->setMaximum(0);
//       m_ui->progressBar->setValue(-1);
//       m_ui->downloadLabel->setText(tr("Downloading Updates") + "...");
//       m_ui->timeLabel->setText(QString("%1: %2").arg(tr("Time Remaining")).arg(tr("Unknown")));
    }
}

/**
 * Uses two time samples (from the current time and a previous sample) to
 * calculate how many bytes have been downloaded.
 *
 * Then, this function proceeds to calculate the appropiate units of time
 * (hours, minutes or seconds) and constructs a user-friendly string, which
 * is displayed in the dialog.
 */
void UpdaterModel::calculateTimeRemaining(qint64 received, qint64 total)
{
    uint difference = QDateTime::currentDateTime().toSecsSinceEpoch() - m_startTime;

    if (difference > 0)
    {
       QString timeString;
       qreal timeRemaining = (total - received) / (received / difference);

       if (timeRemaining > 7200)
       {
          timeRemaining /= 3600;
          int hours = int(timeRemaining + 0.5);

          if (hours > 1)
             timeString = tr("about %1 hours").arg(hours);
          else
             timeString = tr("about one hour");
       }

       else if (timeRemaining > 60)
       {
          timeRemaining /= 60;
          int minutes = int(timeRemaining + 0.5);

          if (minutes > 1)
             timeString = tr("%1 minutes").arg(minutes);
          else
             timeString = tr("1 minute");
       }

       else if (timeRemaining <= 60)
       {
          int seconds = int(timeRemaining + 0.5);

          if (seconds > 1)
             timeString = tr("%1 seconds").arg(seconds);
          else
             timeString = tr("1 second");
       }

       //m_ui->timeLabel->setText(tr("Time remaining") + ": " + timeString);
    }
}
