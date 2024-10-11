#ifndef UPDATER_MODEL_H
#define UPDATER_MODEL_H

#include "model.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDir>

class UpdaterModel : public Model
{
    Q_OBJECT

public:
     ~UpdaterModel();
     static UpdaterModel* getInstance();

     void checkForUpdates();
     void startDownload();

     QString url() const;
     void setUrl(const QString &url);
     QString downloadUrl() const;
     void setDownloadUrl(const QString &downloadUrl);

private slots:
     void onCheckForUpdatesReply(QNetworkReply *reply);
     void finished();
     void metaDataChanged();
     void openDownload();
     void installUpdate();
     void cancelDownload();
     void saveFile(qint64 received, qint64 total);
     void calculateSizes(qint64 received, qint64 total);
     void updateProgress(qint64 received, qint64 total);
     void calculateTimeRemaining(qint64 received, qint64 total);

private:
    UpdaterModel();

private:
    QString m_url{};
    QString m_downloadUrl{};
    QString m_downloadedFileName{};
    QDir m_downloadDir{};
    uint m_startTime{};
    QString m_fileName{};
    QNetworkAccessManager *m_manager = nullptr;
    QNetworkReply *m_reply = nullptr;
};
#endif // UPDATER_MODEL_H
