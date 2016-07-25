#include "qsockettools.h"
#include "ui_qsockettools.h"

#include <qdebug.h>

QSocketTools::QSocketTools(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSocketTools)
{
    ui->setupUi(this);

    this->tcpClient_init();
}

QSocketTools::~QSocketTools()
{
    delete ui;
}

void QSocketTools::tcpClient_init()
{

    ui->pb_tcpclient_connect->setStyleSheet("background-color: rgb(216, 106, 98)");


    this->isTcpConnectedFlag = false;


    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
       for (int i = 0; i < ipAddressesList.size(); ++i) {
               if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                   ipAddressesList.at(i).toIPv4Address()) {
                   this->ipAddress = ipAddressesList.at(i).toString();
                   break;
               }
           }

    //default tcp socket param
    ui->le_tcpclient_server_add->setText("127.0.0.1");
    ui->le_tcpclient_server_port->setText("21688");
    ui->le_tcpclient_local_add->setDisabled(true);
    ui->le_tcpclient_local_port->setDisabled(true);


    //new a tcp socket
    this->tcpSocket = new QTcpSocket(this);

    //signal and slot
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(tcpreadDataReceiveServer_cb()));
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(connectedTcpServer_cb()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disConnectedTcpServer_cb()));

    /* receive number */
    this->receiveNum = 0;


    isShowTcpReceiveData = true;
    isShowTcpRecevieData_date = false;
    isShowTcpReceiveDataWithHex = false;

}

void QSocketTools::connectToTcpServer()
{

      blockSize = 0;

      tcpSocket->abort();

      tcpSocket->connectToHost(ui->le_tcpclient_server_add->text(),
                               ui->le_tcpclient_server_port->text().toInt());
}

void QSocketTools::disConnectToTcpServer()
{
    if(this->isTcpConnectedFlag == false){
           return ;
       }

      this->tcpSocket->abort();
}

void QSocketTools::connectedTcpServer_cb()
{
     this->isTcpConnectedFlag = true;

     ui->pb_tcpclient_connect->setStyleSheet("background-color: rgb(133, 190, 127)");
     ui->pb_tcpclient_connect->setText("disconnect");

      ui->le_tcpclient_local_add->setText(ipAddress);
      ui->le_tcpclient_local_port->setText(QString("%1").arg(this->tcpSocket->localPort()));
}

void QSocketTools::disConnectedTcpServer_cb()
{

    this->isTcpConnectedFlag = false;

    ui->pb_tcpclient_connect->setStyleSheet("background-color: rgb(216, 106, 98)");


    ui->pb_tcpclient_connect->setText("connect");
    ui->pb_tcpclient_connect->colorCount();
    ui->le_tcpclient_local_add->setText("");
    ui->le_tcpclient_local_port->setText("");
}

void QSocketTools::tcpreadDataReceiveServer_cb()
{

    if(isShowTcpReceiveData == false){
        QByteArray buffer=tcpSocket->readAll();//clear caches
        return;
    }

    QByteArray buffer=tcpSocket->readAll();
         char *message = buffer.data();
         QString data = QString(QLatin1String(message));
   ui->tb_tcpclient_receivedata->append(data);
}

void QSocketTools::on_pb_tcpclient_connect_clicked()
{
    if(this->isTcpConnectedFlag){
           this->disConnectToTcpServer();
       }else{

           this->connectToTcpServer();
       }
}

void QSocketTools::on_pb_tcpclient_send_data_clicked()
{
    if(this->isTcpConnectedFlag == false){
           return ;
       }

       QString  message;
       message = ui->te_tcpclient_send_data->toPlainText();
       QByteArray bytearray= message.toLocal8Bit();
       char* pstr = (char*)bytearray.data();

       this->tcpSocket->write((const char *)pstr,strlen(pstr));
}

void QSocketTools::on_pb_tcpclient_clear_send_data_clicked()
{
   ui->te_tcpclient_send_data->clear();
 }


void QSocketTools::on_pb_tcpclient_show_receive_data_date_clicked()
{
    if (isShowTcpRecevieData_date == true)
        isShowTcpRecevieData_date = false;
    else
        isShowTcpRecevieData_date = true;
}

void QSocketTools::on_pb_tcpclient_show_receive_data_hex_clicked()
{
    if (isShowTcpReceiveDataWithHex == true)
        isShowTcpReceiveDataWithHex = false;
    else
        isShowTcpReceiveDataWithHex = true;
}

void QSocketTools::on_pb_tcpclient_save_receive_data_clicked()
{

}

void QSocketTools::on_pb_tcpclient_pause_receive_data_clicked()
{
    if(isShowTcpReceiveData == true)
        isShowTcpReceiveData = false;
    else
        isShowTcpReceiveData = true;
}

void QSocketTools::on_pb_tcpclient_clear_receive_data_clicked()
{
    ui->tb_tcpclient_receivedata->clear();
}




/*udp codes*/
void QSocketTools::on_pb_udp_connect_clicked()
{

}

void QSocketTools::on_pb_udp_send_data_clicked()
{

}

void QSocketTools::on_pb_udp_clear_send_data_clicked()
{

}

void QSocketTools::on_pb_udp_show_receive_data_date_clicked()
{

}

void QSocketTools::on_pb_udp_show_receive_data_hex_clicked()
{

}

void QSocketTools::on_pb_udp_save_receive_data_clicked()
{

}

void QSocketTools::on_pb_udp_pause_receive_data_clicked()
{

}

void QSocketTools::on_pb_udp_clear_receive_data_clicked()
{

}
