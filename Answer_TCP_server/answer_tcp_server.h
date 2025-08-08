#ifndef ANSWER_TCP_SERVER_H
#define ANSWER_TCP_SERVER_H

#include <QWidget>
#include <QTcpServer>

QT_BEGIN_NAMESPACE
namespace Ui { class Answer_TCP_server; }
QT_END_NAMESPACE

class Answer_TCP_server : public QWidget
{
    Q_OBJECT

public:
    Answer_TCP_server(QWidget *parent = nullptr);
    ~Answer_TCP_server();

public slots:
    void handle();



private:
    Ui::Answer_TCP_server *ui;

    QTcpServer *m_tcpServer;

};
#endif // ANSWER_TCP_SERVER_H
