#include"server.h"

#define maxconnection 120//最多连接120个
#define maxbufsize 1000//设置最大缓冲区长度为10000个字节
#define BUFLEN 1000
#define sendbuflen 100000

using namespace std;

bool server::serverstate = false;
int server::connectnum = 0;
SOCKET server::serversocket = NULL;
string server::homepath = "C:/Users/ypzhang/Desktop/temp/";

MainWindow* server::mainwindowp=nullptr;  //窗口指针
/*
11月28日更改
增加accept非阻塞模式*/

/*
尝试增加GUI
尝试配置homepath
尝试try catch//异常处理机制，，，U盘拔出的情况  和accept过程中socket关闭的情况
增加信号量
try catch*/

bool server::startup() {//服务器开启服务

    serverstate = true;//服务器开启
    serverthread = new thread(acceptclient);//new出来的对象，不会被回收
    //cout << "server start success!" << endl;
    mainwindowp->print("server start success!\n");
    return true;
}

void server::shutdown() {
    if (serverstate) {
        serverstate = false;

        if (serverthread && (*serverthread).joinable())
        {
            closesocket(serversocket);
            (*serverthread).join();
            delete serverthread;
            serverthread = NULL;
        }
       // printf("shutdown wait handler threads ...\n");
        mainwindowp->print("shutdown wait handler threads ...\n");
        while (connectnum > 0);
        WSACleanup();
       // printf("shutdown success\n");
        mainwindowp->print("shutdown success\n");
    }
}

void  server::acceptclient() {
    SOCKET clientsocket;//客户端通信socket
    sockaddr_in clientaddr;
    int nsize = sizeof(sockaddr_in);//

    int nrc;//记录函数返回值


    while (serverstate) {


        memset(&clientaddr, 0, nsize);
        try {
            clientsocket = accept(serversocket, (SOCKADDR*)&clientaddr, &nsize);
            if (clientsocket == SOCKET_ERROR && serverstate == 0) throw 1;
        }
        catch (int result){
            //cout << "WEB SERVER IS CLOSING..." << endl;
             //mainwindowp->print("WEB SERVER IS CLOSING...\n");
            return;
        }

        if (clientsocket == SOCKET_ERROR) 	continue;
        else {
            //printf("Accepted client:%s:%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));//输出谁连接的用户
            char temp[BUFLEN];
            sprintf(temp, "Accepted client:%s:%d\n",inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port)) ;
            mainwindowp->print(temp);
            connectnum++;
           // cout << "Now connetnum:" << connectnum << endl;
            sprintf(temp, "Now connetnum:%d\n",connectnum) ;
            mainwindowp->print(temp);
            //判断当个数大于最大个数时如何处理
             //创建一个线程处理该客户端
            thread handlethread(recvmessage, clientsocket, clientaddr);
            handlethread.detach();//不管这个线程
        }
    }
}
void server::recvmessage(SOCKET clientsock, sockaddr_in clientaddr) {
    char  recvBuf[BUFLEN];
    int messagelength = 0;//报文长度
    int ret;
    int nrc;//接受函数返回值
    string filename;//文件名
    fd_set set;
    timeval waittime;
    waittime.tv_sec = 1;
    waittime.tv_usec = 0;
    u_long blockMode = 0;
    while (serverstate) {
        /*FD_ZERO(&set);
        FD_SET(clientsock, &set);

        ret = select(0, &set, nullptr, nullptr, &waittime);
        if (ret == 0) {
            //time out
            //closesocket(clientsock);
            //continue;//继续接受消息
            break;//超时退出
        }
        else if (ret > 0) {*/
        /*int rtn;

        if ((rtn = ioctlsocket(clientsock, FIONBIO, &blockMode) == SOCKET_ERROR)) { //FIONBIO：允许或禁止套接口s的非阻塞模式。
            cout << "ioctlsocket() failed with error!\n";
            return;
        }*/
            setsockopt(clientsock, SOL_SOCKET, SO_RCVTIMEO, (char*)&waittime, sizeof(waittime));//设time置超时
            messagelength = recv(clientsock, recvBuf, BUFLEN, NULL);

            if (messagelength == SOCKET_ERROR) {//发生错误
                int nErrCode = WSAGetLastError();//发生的具体错误
                if (WSAEWOULDBLOCK == nErrCode)	//接受数据缓冲区不可用
                {
                    continue;						//继续循环
                }
                /*else if (WSAENETDOWN == nErrCode ||//客户端关闭了连接
                    WSAETIMEDOUT == nErrCode ||
                    WSAECONNRESET == nErrCode)
                {
                    break;							//线程退出
                }*/
            }
            else if (messagelength == 0) break;
            else {//处理报文
                recvBuf[messagelength] = '\0';
                //cout << recvBuf << endl;//输出接收到的报文
                mainwindowp->print(recvBuf);
                getfilename(&filename, recvBuf, messagelength);

                int flag = sendfile(filename, clientsock);
                //if (flag == 0)
                    break;
            }
        //}
    }
    closesocket(clientsock);
    connectnum--;
    //printf(" client:%s:%d leave!\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
    char temp[BUFLEN];
    sprintf(temp, " client:%s:%d leave!\n",inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port)) ;
    mainwindowp->print(temp);
    //cout << "Now:connectnum=" << connectnum << endl;
    sprintf(temp, "Now:connectnum=%d\n",connectnum) ;
    mainwindowp->print(temp);

}
int server::sendfile(string  filename, SOCKET clientsocket) {
    char sendbuf[BUFLEN];
    char constbuf[BUFLEN] = "HELLO,\nYOU ASK NOTHING";
    string sendbuf2;
    int buflength;
    int head_length;
    buflength = strlen(constbuf);
    sockaddr_in clientaddr;//客户地址
    int nsize, nrc;
    nsize = sizeof(SOCKADDR);

    string content = "";//得到文件

    nrc = getpeername(clientsocket, (SOCKADDR*)&clientaddr, &nsize);
    if (filename.size() == 0) {//没有请求文件  路径名为空
        head_length = sprintf(sendbuf, "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: %d\r\n"
            "Connection: close\r\n\r\n", buflength);
        strcat(sendbuf, constbuf);
        send(clientsocket, sendbuf, strlen(sendbuf), 0);
        char temp[BUFLEN];
        sprintf(temp, "CLIENT ASKING NOTHING....\n") ;
        mainwindowp->print(temp);
        return 0;
    }

    else {
        filename = homepath + filename;
        ifstream content_file(filename, ios::binary);//将请求对象打开
        if (content_file.is_open() == 0) {//没有打开的话，发送404
            char temp[BUFLEN];
            sprintf(temp, "From clientIp:%s clientport:%d \n",inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port)) ;
            mainwindowp->print(temp);
            //printf("From clientIp:%s clientport:%d \n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
            //cout << "NOT FOUND THE FILE:" << filename << endl;
             sprintf(temp, "NOT FOUND THE FILE:%s\n",filename.c_str()) ;
             mainwindowp->print(temp);

            strcpy(constbuf, "ERROR:404,FILE NOT FOUND!");
            buflength = strlen(constbuf);
            sprintf(sendbuf, "HTTP/1.1 404 NOT FOUND\r\n"
                "Content-Type : text/plain\r\n"
                "Content-Length: %d\r\n"
                "Connection: close\r\n\r\n", buflength
            );
            strcat(sendbuf, constbuf);
            send(clientsocket, sendbuf, strlen(sendbuf), 0);
            return 0;
        }
        else {//文件已打开，先得到文件的大小，然后发送报文头
            try {//处理简单的异常
               // printf("From clientIp:%s clientport:%d \n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
                char temp[BUFLEN];
                sprintf(temp, "From clientIp:%s clientport:%d \n",inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port)) ;
                mainwindowp->print(temp);
                //cout << "HAVE THE FILE:" << filename << endl;
                 sprintf(temp, "HAVE THE FILE:%s\n",filename.c_str()) ;
                mainwindowp->print(temp);

                streampos filesize = content_file.tellg();
                content_file.seekg(0, ios::end);
                filesize = content_file.tellg() - filesize;//得到了文件大小


                if (content_file.is_open() == 0) {//文件中途被删除或U盘拔出
                    throw 1;
                }
                content_file.seekg(0, ios::beg);

                content.resize(filesize, 0);
                content_file.read((char*)content.c_str(), filesize);//得到了文件
                content_file.close();

                string length = to_string(content.size());
                string head = "HTTP / 1.1 200 OK\r\nContent-Length:";
                head = head + length + "\r\n\r\n";

                //cout << "发送报文：" << endl;
                mainwindowp->print("SEND MESSAGEING：\n");
                //cout << head << "\n" << content << endl;
                //cout << "SENDING NOW..." << endl;
                mainwindowp->print("SENDING NOW...\n");

                send(clientsocket, head.c_str(), head.size(), 0);

                send(clientsocket, content.c_str(), content.length(), 0);
            }
            catch (int result) {
               // cout << "FILE IS LOSING...." << endl;
                mainwindowp->print("FILE IS LOSING....\n");
                return 0;
            }


            //尝试循环发送
            //内容在content中
        /*	int i = 0;
            if (content.size() > sendbuflen) {
                while (i < content.size() - sendbuflen) {
                    sendbuf2 = content.substr(i, i + sendbuflen);
                    send(clientsocket, sendbuf2.c_str(), sendbuflen, 0);
                    sendbuf2.clear();
                    i += sendbuflen;
                }
            }
            sendbuf2 = content.substr(i, content.end()-content.begin());
            send(clientsocket, sendbuf2.c_str(), sendbuf2.length(), 0);*/

            //cout << "SEND OVER!\n";
             mainwindowp->print("SEND OVER!\n");
            return 1;
        }

    }
}

void server::getfilename(string* filename, string recvbuf, int length) {
    int pos1, pos2, pos3;
    //pos1寻找"/"的位置
    if ((pos1 = recvbuf.find("/", 0)) == string::npos)
    {
        //解析失败，返回默认请求对象
        printf("requestObjectPath fail");
        *filename = "";
    }
    //pos2寻找" "的位置
    pos2 = recvbuf.find(" ", pos1);
    //得到文件路径
    *filename = recvbuf.substr(pos1 + 1, pos2 - pos1 - 1);
    //cout << filename->c_str();
}



bool server::Winsock_server_init() {
    WSADATA wsaData;
    int nrc;//返回值
    nrc = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (nrc) {
       // cout << "Server initialize winsock error!\n";
         mainwindowp->print("Server initialize winsock error!\n");
        return 0;
    }
    if (wsaData.wVersion != 0x0202) {
        //cout << "Server's winsock version error!\n";
         mainwindowp->print("Server's winsock version error!\n");
        WSACleanup();
        return 0;
    }
    //cout << "Server's winsock initialized!\n";
     mainwindowp->print("Server's winsock initialized!\n");

    this->serversocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);//创建服务器socket
    if (serversocket == INVALID_SOCKET) {
        //cout << "Serversocket errror!\n" << endl;
        mainwindowp->print("Serversocket errror!\n");
        WSACleanup();
        return false;
    }

    //cout << "Server socket bind success!\n";
    mainwindowp->print("Server socket bind success!\n");
    sockaddr_in serversockaddr;//服务器地址
    memset(&(serversockaddr), 0, sizeof(serversockaddr));
    serversockaddr.sin_family = PF_INET;
    serversockaddr.sin_port = htons(port);
    serversockaddr.sin_addr.s_addr = htonl(INADDR_ANY);//任意Ip

    nrc = ::bind(serversocket, (LPSOCKADDR)&serversockaddr, sizeof(serversockaddr));//强制类型是必须的

    if (nrc == SOCKET_ERROR) {
      //  cout << "Server socket bind error!\n";
        mainwindowp->print("Server socket bind error!\n\n");
        closesocket(serversocket);
        WSACleanup();
        return 0;
    }

    nrc = listen(serversocket, Maxconnum);//监听客户连接
    if (nrc == SOCKET_ERROR)
    {
        //printf("Server socket listen error!\n");
         mainwindowp->print("Server socket listen error!\n");
        closesocket(serversocket);
        WSACleanup();
        return 0;
    }



    //设置为非阻塞
    /*u_long blockMode = 1;//将srvSock设为非阻塞模式以监听客户连接请求
    int rtn;

    if ((rtn = ioctlsocket(this->serversocket, FIONBIO, &blockMode) == SOCKET_ERROR)) { //FIONBIO：允许或禁止套接口s的非阻塞模式。
        cout << "ioctlsocket() failed with error!\n";
        return -1;
    }
    */



    //printf("Server socket listen success!\n");
     mainwindowp->print("Server socket listen success!\n");
    cout << "server's ip is:" << inet_ntoa(serversockaddr.sin_addr) << "\nserver's port is:" << port << endl;
     char temp[BUFLEN];
     sprintf(temp, "server's ip is:%s\n",inet_ntoa(serversockaddr.sin_addr));
     //mainwindowp->print(temp);
     sprintf(temp, "server's port is:%d\n",port);
     mainwindowp->print(temp);
  //  cout << "server's path is:" << homepath << endl;
    // sprintf(temp, "server's path is:%d\n",port);
    // mainwindowp->print(temp);
    return true;
}

bool server::input_server_set() {
   /* if (serverstate == 0) {
        this->set_server_ip();//提示用户输入ip
        this->set_server_port();//提示用户输入port
        this->set_server_path();//提示用户输入主机虚拟地址
        return true;
    }
    return false;*/
}

void server::set_server_ip(string ip) {
   // cout << "please input the server's IP:\n";
   // cin >> ip;
    server::serveraddr = inet_addr(ip.c_str());
}

void server::set_server_port(int  port) {
   // cout << "please input the server's port:\n";
   server::port=port;
}

void server::set_server_path(string path) {
   // cout << "please input the file's path:" << endl;
   // cin >> this->homepath;
  server::homepath=path;
}

server::server(MainWindow *w) {//构造函数
    serverstate = false;
    serversocket = NULL;
    port = 80;//默认80
    serveraddr = 0;
    Blockmode = 0;
    connectnum = 0;
    Maxconnum = maxconnection;
    serverthread = NULL;
    mainwindowp=w;
}
