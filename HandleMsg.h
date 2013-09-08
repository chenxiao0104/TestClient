//
//  HandleMsg.h
//  TestClient
//
//  Created by ChenXiao on 7/26/13.
//  Copyright (c) 2013 Microsoft. All rights reserved.
//

#ifndef __TestClient__HandleMsg__
#define __TestClient__HandleMsg__

#include "commonHeader.h"

namespace ClientSCTT {
    
    class HandleMsg {
    public:
        HandleMsg() {}
        virtual ~HandleMsg() {}
        char* createTaskReqMsg(int);
        char* createAppReadyMsg(const char*);
        char* createTaskStatusReqMsg(const char*);
        //char* createAnalysisMsg(const char*,const char);
        int parseMsgType(cJSON*);
        char* parseTaskReqAck(cJSON*); //return taskid
        int parseAppRecvReady(cJSON*);
        int parseAppSndAck(cJSON*);
        int parseTaskStatusReqAck(cJSON*);
        int parseTestResultMsg(cJSON*);
    };
}

#endif /* defined(__TestClient__HandleMsg__) */
