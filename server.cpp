#include "server.h"

Server::Server(QObject *parent)
    : QObject{parent}
{
    client = NULL;
    server = new QTcpServer;

    connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    server->listen(QHostAddress::Any,8888);
}

Server::~Server()
{
    server->close();
    if(client != NULL)
    {
        client->close();
    }
    server->deleteLater();
}

void Server::acceptConnection()
{
    client = server->nextPendingConnection();
    connect(client,SIGNAL(readyRead()),this,SLOT(startRead()));

}
void Server::startRead(){

  QTcpSocket *socket = (QTcpSocket* ) QObject::sender();

  if ( socket->canReadLine() )
  {
      QStringList tokens = QString( socket->readLine() ).split( QRegularExpression( "[ \r\n][ \r\n]*" ) );
          if (tokens[1].split("/")[1] == "api")
          {
              if ( tokens[0] == "PUT" )
              {
                handlePutApi(socket,tokens[1]);
              }
              if ( tokens[0] == "GET" )
              {
                handleGetApi(socket,tokens[1]);
              }
          }
          socket->close();
          if ( socket->state() == QTcpSocket::UnconnectedState )
          {
              delete socket;
          }
  }
}

void Server::handleGetApi(QTcpSocket *socket,QString request)
{
    QString route = request.split("?")[0];
    QString params = request.split("?")[1];

    qDebug() << "You tried accessing: " + route + " with Params: " + params;
    QTextStream os( socket );
    os.setAutoDetectUnicode( true );
    os << "HTTP/1.0 200 Ok\r\n"
    "Content-Type: text/html; charset=\"utf-8\"\r\n"
    "\r\n"
    "<h1>Hallo Get!</h1>\n"
    << QDateTime::currentDateTime().toString() << "\n";

}

void Server::handlePutApi(QTcpSocket *socket, QString request)
{
    QString route = request.split("?")[0];
    QString params = request.split("?")[1];

    qDebug() << "You tried accessing: " + route + " with Params: " + params;
    QTextStream os( socket );
    os.setAutoDetectUnicode( true );
    os << "HTTP/1.0 200 Ok\r\n"
    "Content-Type: text/html; charset=\"utf-8\"\r\n"
    "\r\n"
    "<h1>Hallo Put!</h1>\n"
    << QDateTime::currentDateTime().toString() << "\n";

}

