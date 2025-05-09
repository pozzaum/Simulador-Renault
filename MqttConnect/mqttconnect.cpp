#include "mqttconnect.h"

MyMqtt::MyMqtt(QObject *parent)
    : QObject(parent), client(nullptr)
{
    qDebug() << "MyMqtt::MyMqtt - thread:" << QThread::currentThread();
}

void MyMqtt::createClient()
{
    qDebug() << "Criando QMqttClient na thread:" << QThread::currentThread();

    if (client) return; // evitar recriação

    client = new QMqttClient(this); // deve ser criado na thread com QApplication

    connect(client, &QMqttClient::connected, this, [this]() {
        qDebug() << "MQTT conectado!";
        emit connected();

        // Assina o tópico após conexão
        client->subscribe(QMqttTopicFilter("mqtt/comando"));  // ou qualquer outro nome
    });

    connect(client, &QMqttClient::disconnected, this, []() {
        qDebug() << "MQTT desconectado!";
    });

    connect(client, &QMqttClient::errorChanged, this, [](QMqttClient::ClientError error) {
        qDebug() << "Erro MQTT:" << error;
    });


}

void MyMqtt::connectToBroker(const QString &host, quint16 port)
{
    if (!client) {
        qWarning() << "MQTT client não foi inicializado ainda!";
        return;
    }

    qDebug() << "Conectando ao broker MQTT em" << host << "na porta" << port;
    client->setHostname(host);
    client->setPort(port);
    client->connectToHost();
}

void MyMqtt::publishTemperature(double value)
{
    if (!client) {
        qWarning() << "MQTT client não inicializado. publish falhou.";
        return;
    }

    QByteArray payload = QByteArray::number(value);
    QMqttTopicName topic("mqtt/temperatura");
    client->publish(topic, payload);
}
