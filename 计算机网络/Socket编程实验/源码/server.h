#ifndef SERVER_H
#define SERVER_H

#include<iostream>
#include<string>
#include<cstdio>
#include<fstream>
#include<thread>
#include<exception>
#include<winsock.h>
#include<sstream>

#include"mainwindow.h"

#pragma comment(lib, "ws2_32.lib")

using namespace std;


class MainWindow;
class server {
private:
    static void getfilename(string* filename, string recvbuf, int length);
    static int  sendfile(string filename,SOCKET clientsock);
public:
    static bool serverstate;//服务器的开关状态
    static SOCKET serversocket;//服务器的套接字
    static string homepath;//服务器的虚拟地址
    int port;//套接字的绑定端口号
    u_long serveraddr;//服务器的绑定地址
    static MainWindow* mainwindowp;  //窗口指针


     void set_server_ip(string ip);//设置服务器的ip；
     void set_server_port(int port);//设置服务器的port
     void set_server_path(string path);//设置服务器的虚拟路径


    u_long Blockmode;//阻塞模式
    static int connectnum;//已连接数量
    int Maxconnum;//最大连接数量
    thread* serverthread;//服务器主线程


    bool startup();//设置服务器的开关状态

    void shutdown();//关闭服务器

    bool input_server_set();

    bool Winsock_server_init();//服务器初始化包括绑定listen等
    static void  acceptclient();//接受客户端的请求
    static void recvmessage(SOCKET clientsock, sockaddr_in clientaddr);
    server(MainWindow *w);

};
#endif // SERVER_H


