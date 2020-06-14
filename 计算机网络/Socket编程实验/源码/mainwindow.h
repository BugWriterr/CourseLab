#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"server.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class server;

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void textBrowser_append(QString s);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    server* myserver;                //保存服务器的指针
    void print(std::string);  //打印接口


private slots:
    void on_textBrowser_append(QString s);

    void on_IP_clicked();

    void on_PORT_clicked();

    void on_PATH_clicked();

    void on_START_clicked();

    void on_EXIT_clicked();

    void on_CLEAR_clicked();



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
