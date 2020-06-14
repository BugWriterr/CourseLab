#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "server.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
     connect(this,  &MainWindow::textBrowser_append, this, &MainWindow::on_textBrowser_append);//信号槽绑定
     myserver=NULL;
     myserver=new server(this);//定义服务器
     ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_IP_clicked()
{
   QString ip_input =ui->lineEdit_IP->text();
   //修改IP
   myserver->set_server_ip(ip_input.toStdString());
   //显示当前IP
   ui->textBrowser_IP->setText(ip_input);
}



void MainWindow::on_PORT_clicked()
{
    int port = ui->lineEdit_PORT->text().toInt();

    myserver->set_server_port(port);

    QString port_input = QString::number(port);
    ui->textBrowser_PORT->setText(port_input);
}

void MainWindow::on_PATH_clicked()
{
    QString path_input = ui->lineEdit_PATH->text();
    string path = path_input.toStdString();
    myserver->set_server_path(path);

    ui->textBrowser_PATH->setText(path_input);
}

void MainWindow:: on_START_clicked()
{
    if(myserver->Winsock_server_init()){
        myserver->startup();
    }
    else{
        print("ERROR HAPPEND!\n");
    }
}

void MainWindow::on_EXIT_clicked()
{
    print("closing...");
    myserver->shutdown();
    print("EXIT\n");
    on_CLEAR_clicked();
    delete myserver;
}

void MainWindow::on_CLEAR_clicked(){
    ui->textBrowser->clear();
    ui->textBrowser_IP->clear();
    ui->textBrowser_PORT->clear();
    ui->textBrowser_PATH->clear();
}

void MainWindow::print(string s)
{
    emit textBrowser_append(QString::fromStdString(s));
}


void MainWindow::on_textBrowser_append(QString s)
{
    ui->textBrowser->append(s);
}




