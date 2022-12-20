#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QRegularExpression>
#include <QDateTime>

#include <QTcpServer>
#include <QTcpSocket>

#define MAXCLIENT 2

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
            ~Server();

public slots:
    void acceptConnection();
    void startRead();
    void handleGetApi(QTcpSocket*,QString);
    void handlePutApi(QTcpSocket*,QString);
private:
    QTcpServer *server;
    QTcpSocket *client;

};

#endif // SERVER_H
