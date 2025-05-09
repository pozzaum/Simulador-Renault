#ifndef WEBSOCKETWORKER_H
#define WEBSOCKETWORKER_H

#include <QObject>
#include <QWebSocket>
#include <iostream>

class WebSocketWorker : public QObject {
    Q_OBJECT
public:
    explicit WebSocketWorker(QObject *parent = nullptr);
    void start(const QUrl &url);
    void sendBinaMessage(const QByteArray &message);
signals:
    void messageReceived(const QString &message);
    void binaryReceived(const QByteArray &message);
public slots:
    void onConnected();
    void onTextMessageReceived(const QString &message);
    void onBinaryMessageReceived(const QByteArray &message);
private:
    QWebSocket m_webSocket;
};

#endif // WEBSOCKETWORKER_H
