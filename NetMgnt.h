//
//  NetMgnt.h
//  TestClient
//
//  Created by ChenXiao on 7/29/13.
//  Copyright (c) 2013 Microsoft. All rights reserved.
//

#ifndef TestClient_NetMgnt_h
#define TestClient_NetMgnt_h

namespace ClientSCTT {
    /*
     * super class
     * manage socket: create socket, send, recv
     */
    class NetMgnt {
    private:
        int clientSock;
    public:
        NetMgnt() { clientSock=-1; }
        virtual ~NetMgnt() {}
        void setSocket(int sock) { clientSock=sock; }
        int getSocket() { return clientSock; };
        virtual bool createConnect() { return false; }
        virtual bool sendMsg(const char* msg) { return false; }
        virtual bool recvMsg(char*) { return false; }
    };
}

#endif
