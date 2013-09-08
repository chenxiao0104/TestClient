//
//  Controller.h
//  TestClient
//
//  Created by ChenXiao on 7/29/13.
//  Copyright (c) 2013 Microsoft. All rights reserved.
//

#ifndef __TestClient__Controller__
#define __TestClient__Controller__

#include "commonHeader.h"
#include "time.h"
#include "NetMgnt.h"
#include "TaskInfo.h"
#include "HandleMsg.h"
#include "ClientCom.h"

namespace ClientSCTT {
    /*
     * super class
     * handle overall process of the communication
     */
    
    class Controller {
        
    private:
        NetMgnt* netMgnt;
        TaskInfo* taskInfo;
        HandleMsg* handleMsg;
        long threshold;
        
    public:
        Controller(const char*, unsigned short, const char*,int,long);
        int getSocket();
        char* getTaskId();
        int getMsgType(cJSON*);
        bool connectServer();
        bool sendTaskReq();
        bool sendBinaryReady();
        bool sendStatusReq();
        //bool sendAnalysis(char);
        bool handleTaskAck(cJSON*);
        bool handleBinaryAck(cJSON*);
        int handleStatusAck(cJSON*);
        bool handleTestResult(cJSON*);
        bool recvMsg(char*);
        char* getBinaryPath();
        bool isTimeOut(long, long);
        void closeAll();
        virtual bool sendBinary(const char*) { return false; }
        //virtual bool init(int argc, const char * argv[]) { return true; }
        virtual bool arbiter() { return false; }
        virtual ~Controller();
    };
    
}


#endif /* defined(__TestClient__Controller__) */
