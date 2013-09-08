//
//  ClientCom.h
//  TestClient
//
//  Created by ChenXiao on 7/29/13.
//  Copyright (c) 2013 Microsoft. All rights reserved.
//

#ifndef __TestClient__ClientCom__
#define __TestClient__ClientCom__

#include "commonHeader.h"
#include <signal.h>
#include "NetMgnt.h"

namespace ClientSCTT {
    /*
     * extends from class NetMgnt,
     * handle socket in oper Linux & Mac
     */
    class ClientCom : public NetMgnt {
        
    private:
        int clientSocket;
        struct sockaddr_in serverAddr,localAddr;
        char* serverIp;
        unsigned short portNum;
        
    public:
        ClientCom(const char*, unsigned short);
        virtual ~ClientCom();
        bool createConnect();
        bool sendMsg(const char*);
        bool recvMsg(char*);
        
    };
}

#endif /* defined(__TestClient__ClientCom__) */
