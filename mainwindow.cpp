#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  getData();
  putData();
}

void MainWindow::on_ConnectpushButton_clicked()
{
   QString ip = ui->IptextEdit->toPlainText();
   ui->label_3->setText(ip);
   //127.0.0.1
   socket->connectToHost(ip,1234);
   if(socket->waitForConnected(3000)){
     qDebug() << "Connected";
 //    emit habilitastart(true);
   //  emit habilitarstop(true);
   }
   else{
     qDebug() << "Disconnected";
     //emit habilitastart(false);
     //emit habilitarstop(false);
}
}
void MainWindow::getData()
{
  QString str;
  QByteArray array;
  QStringList list;
  QDateTime datetime;
  if(socket->isOpen()){
    socket->write("get roles \r\n");
    socket->waitForBytesWritten(3000);
    socket->waitForReadyRead(3000);
    qDebug() << socket->bytesAvailable();
    while(socket->bytesAvailable()){
      str = socket->readLine().replace("\n","").replace("\r","");
      list = str.split(" ");
      if(list.size() == 2){
        datetime.fromString(list.at(0),Qt::ISODate);
        str = list.at(1);
        qDebug() << datetime << ": " << str;
      }
    }
  }
}

MainWindow::~MainWindow()
{
  delete socket;
  delete ui;
}
void MainWindow::putData()
{
    int min,max;
    QDateTime datetime;
    QString str;
    min=ui->MindoubleSpinBox->value();
    max= ui->MaxdoubleSpinBox->value();

    if(min>max || min==max){
        ui->label_3->setText("Error");
        ui->label_4->setText(" ");
    }

    else{
        QString ip = ui->IptextEdit->toPlainText();
        ui->label_3->setText(ip);
        ui->label_4->setText("Ip: ");


    if(socket->isOpen()){
        /*for(int i=0;i<amostras;i++){*/
        datetime = QDateTime::currentDateTime();
        str = "set "+
            datetime.toString(Qt::ISODate)+
            " "+
            QString::number(qrand()%(max-min+1)+min)+"\r\n";

        qDebug() << str;
        socket->write(str.toStdString().c_str());
        socket->waitForBytesWritten(3000);
        ui->DadostextBrowser->append(str);/*}*/
    }}}

void MainWindow::on_Limitesslider_valueChanged(int value)
{
    ui->LimiteslcdNumber->display(value);
}
void MainWindow::timerEvent(QTimerEvent *e){
    putData();
  //qDebug()<<"asdas "<< e->timerId();
}
void MainWindow::on_LimitespushButton_clicked()
{
    int slide;
    slide=ui->Limitesslider->value();
    idTimer=startTimer(slide*1000);
}

void MainWindow::on_StoppushButton_clicked(){
    killTimer(idTimer);
}
