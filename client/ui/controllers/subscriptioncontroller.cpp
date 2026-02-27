#include "subscriptioncontroller.h"
#include <QNetworkReply>

SubscriptionController::SubscriptionController(QObject *parent):
QObject(parent), m_networkManager(new QNetworkAccessManager(this)){}

void SubscriptionController::requestTrial()
{emit trialFailed("Not implemented yet");}

void SubscriptionController::fetchConfig(const QString &subId)
{emit configFailed("Not implemented yet");}