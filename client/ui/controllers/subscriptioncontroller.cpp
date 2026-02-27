#include "subscriptioncontroller.h"
#include <QNetworkReply>
#include <QUrlQuery>
SubscriptionController::SubscriptionController(QObject *parent):
QObject(parent), m_networkManager(new QNetworkAccessManager(this)){}

void SubscriptionController::requestTrial()
{
    QNetworkRequest request(QUrl("https://api.frkn.org/trial"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject body;
    body["source"] = "Mobile";
    QNetworkReply *reply = m_networkManager->post(request, QJsonDocument(body).toJson());
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(data);
            QJsonObject obj = doc.object();
            if (obj.contains("sub_id")) {
                QString subId = obj["sub_id"].toString();
                emit trialSuccess(subId);
            } else {emit trialFailed("Invalid response: missing sub_id");}
        } else {emit trialFailed(reply->errorString());}
        reply->deleteLater();});
}

void SubscriptionController::fetchConfig(const QString &subId)
{
    QUrl url("https://api.frkn.org/sub");
    QUrlQuery query;
    query.addQueryItem("id", subId);
    query.addQueryItem("format", "txt");
    url.setQuery(query);
    QNetworkRequest request(url);
    QNetworkReply *reply = m_networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QString configData = QString::fromUtf8(reply->readAll());
            emit configSuccess(configData);
        }
        else {emit configFailed(reply->errorString());}
        reply->deleteLater();});
}