//
//  ClientCom.cpp
//  TestClient
//
//  Created by ChenXiao on 7/29/13.
//  Copyright (c) 2013 Microsoft. All rights reserved.
//

#include "ClientCom.h"

using namespace ClientSCTT;

ClientCom::ClientCom(const char* ip,unsigned short port): NetMgnt() {
    clientSocket = 0;
    int size = (int)strlen(ip);
    serverIp = new char[size+1];
    memcpy(serverIp, ip, size);
    *(serverIp+size) = '\0';
    portNum = port;
}

ClientCom::~ClientCom() {
	delete serverIp;
}

bool ClientCom::createConnect() {
    clientSocket = socket(PF_INET,SOCK_STREAM,0);
    if(clientSocket == -1) return false;
    setSocket(clientSocket);
    bzero(&serverAddr,sizeof(struct sockaddr_in));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(serverIp);
    serverAddr.sin_port = htons(portNum);
    if(-1 == connect(clientSocket,(struct sockaddr*)(&serverAddr),sizeof(struct sockaddr)))
    {
        return false;
    }
    return true;
}

bool ClientCom::sendMsg(const char* msg) {
    char* buff = new char[_SOCK_SIZE];
    memset(buff,'\0',_SOCK_SIZE);
    memcpy(buff,msg,strlen(msg));
    int len = (int)send(clientSocket, buff, _SOCK_SIZE, 0);
    if(len<=0){
        return false;
    }else{
        return true;
    }
}

bool ClientCom::recvMsg(char* buff) {
    int len = (int)recv(clientSocket, buff, _SOCK_SIZE, 0);
    if(len<=0) return false;
    buff[len] = '\0';
    return true;
}
