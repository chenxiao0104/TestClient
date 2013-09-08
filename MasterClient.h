//
//  MasterClient.h
//  TestClient
//
//  Created by rt-build on 7/29/13.
//  Copyright (c) 2013 bupt-bnrc. All rights reserved.
//

#ifndef __TestClient__MasterClient__
#define __TestClient__MasterClient__

#include "commonHeader.h"
#include "Controller.h"
#include "commonInfo.h"
#include <signal.h>

namespace ClientSCTT {

    class MasterClient : public Controller{
    
    private:
        fd_set rdfds;
        struct timeval tv;
        char* buff;
        //std::string serverIp;
        //unsigned short serverPort;
        char* outputDir;
        long timeOut;
        int operPlatform;
        //char* outputDir;
        
        
    public:
        MasterClient(const char*, unsigned short, const char*,int,const char*,long);
        //bool init(int argc,const char* paras[]);
        bool sendBinary();
        bool recvOutput(int,const char*);
        void printOutput(const char*);
        bool arbiter();
    
    };
    
}

#endif /* defined(__TestClient__MasterClient__) */
