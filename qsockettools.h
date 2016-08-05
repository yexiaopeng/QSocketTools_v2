#ifndef QSOCKETTOOLS_H
#define QSOCKETTOOLS_H


#include <QDialog>
#include<QtNetwork/qtcpsocket.h>
#include <QtNetwork/qudpsocket.h>
#include<QtNetwork/qhostinfo.h>
#include <QtNetwork/qnetworkinterface.h>
//#include<QNetworkInterface>


namespace Ui {
class QSocketTools;
}

class QSocketTools : public QDialog
{
    Q_OBJECT

public:
    explicit QSocketTools(QWidget *parent = 0);
    ~QSocketTools();

private:
    //tcp
    bool isTcpConnectedFlag;
    QTcpSocket * tcpSocket;
    long int receiveNum;
    QString ipAddress;
     quint16 blockSize;
    char SecurityData[32];
    long int receiveCount = 0;
    long int sendCount = 0;

    bool isShowTcpReceiveData;
    bool isShowTcpRecevieData_date;
    bool isShowTcpReceiveDataWithHex;





    //udp





private slots:
    //tcp client
    void on_pb_tcpclient_connect_clicked();

    void on_pb_tcpclient_send_data_clicked();

    void on_pb_tcpclient_clear_send_data_clicked();

    void on_pb_tcpclient_show_receive_data_date_clicked();

    void on_pb_tcpclient_show_receive_data_hex_clicked();

    void on_pb_tcpclient_save_receive_data_clicked();

    void on_pb_tcpclient_pause_receive_data_clicked();

    void on_pb_tcpclient_clear_receive_data_clicked();

    void tcpClient_init();

    void connectToTcpServer();

    void disConnectToTcpServer();

    void connectedTcpServer_cb();

    void disConnectedTcpServer_cb();

    void tcpreadDataReceiveServer_cb();

    //udp
    void on_pb_udp_connect_clicked();

    void on_pb_udp_send_data_clicked();

    void on_pb_udp_clear_send_data_clicked();

    void on_pb_udp_show_receive_data_date_clicked();

    void on_pb_udp_show_receive_data_hex_clicked();

    void on_pb_udp_save_receive_data_clicked();

    void on_pb_udp_pause_receive_data_clicked();

    void on_pb_udp_clear_receive_data_clicked();

    void on_pb_clearReceiveCount_clicked();

    void on_pb_clearSendCount_clicked();

private:
    Ui::QSocketTools *ui;
};

#endif // QSOCKETTOOLS_H
