#ifndef SUBSCRIPTIONCONTROLLER_H
#define SUBSCRIPTIONCONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>

class SubscriptionController : public QObject
{
Q_OBJECT

public:
explicit SubscriptionController(QObject *parent = nullptr);

signals:
void trialSuccess(const QString &subId);
void trialFailed(const QString &error);
void configSuccess(const QString &configData);
void configFailed(const QString &error);

public slots:
void requestTrial();
void fetchConfig(const QString &subId);

private:
QNetworkAccessManager *m_networkManager;};
#endif