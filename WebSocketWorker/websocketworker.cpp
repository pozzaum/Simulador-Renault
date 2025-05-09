#include "websocketworker.h"

WebSocketWorker::WebSocketWorker(QObject *parent) : QObject(parent) {}

void WebSocketWorker::start(const QUrl &url) {
    connect(&m_webSocket, &QWebSocket::connected, this, &WebSocketWorker::onConnected);
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &WebSocketWorker::onTextMessageReceived);
    connect(&m_webSocket, &QWebSocket::binaryMessageReceived, this, &WebSocketWorker::onBinaryMessageReceived);
    m_webSocket.open(url);
}

void WebSocketWorker::onConnected() {
    qDebug() << "WebSocket connected";
}

void WebSocketWorker::onTextMessageReceived(const QString &message) {
    emit messageReceived(message);
}

void WebSocketWorker::onBinaryMessageReceived(const QByteArray &message) {
    emit messageReceived(message);
}

void WebSocketWorker::sendBinaMessage(const QByteArray &message){
    m_webSocket.sendBinaryMessage(message);
}
