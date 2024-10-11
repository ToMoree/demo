#ifndef UPDATER_MODEL_H
#define UPDATER_MODEL_H

#include "model.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class UpdaterModel : public Model
{
    Q_OBJECT

public:
     ~UpdaterModel();
     static UpdaterModel* getInstance();

     void checkForUpdates();

     QString url() const;
     void setUrl(const QString &url);

private slots:
     void onReply(QNetworkReply *reply);

private:
    UpdaterModel();

private:
    QString m_url{};
    QNetworkAccessManager *m_manager = nullptr;
};
#endif // UPDATER_MODEL_H
