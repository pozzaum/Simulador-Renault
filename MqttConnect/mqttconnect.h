#ifndef MQTTCONNECT_H
#define MQTTCONNECT_H

#pragma once

#include <QObject>
#include <QMqttClient>
#include <QThread>
#include <QDebug>


class MyMqtt : public QObject {
    Q_OBJECT
public:

    explicit MyMqtt(QObject *parent = nullptr);
    void publishTemperature(double value);

public slots:
    void createClient();
    void connectToBroker(const QString &host = "localhost", quint16 port = 1883);


private:
    QMqttClient *client;

signals:
    void connected();
    //void messageReceived(const QString &payload);
};


#endif // MQTTCONNECT_H
