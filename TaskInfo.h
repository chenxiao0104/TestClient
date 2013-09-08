//
//  TaskInfo.h
//  internClient01
//
//  Created by ChenXiao on 7/24/13.
//  Copyright (c) 2013 Microsoft. All rights reserved.
//

#ifndef __internClient01__TaskInfo__
#define __internClient01__TaskInfo__

#include "commonHeader.h"
#include <time.h>

namespace ClientSCTT {
    /*
     runtime information of the bvt test case
     */
    class TaskInfo {
    private:
        char* taskId;
        char* binaryPath;
        long startTime;
        long lastReqTime;
        int testStatus;
        bool recvFlag;
        int operPlatform;
        
    public:
        TaskInfo();
        TaskInfo(const char*);
        void setTaskId(const char*);
        void setBinaryPath(const char*);
        void setStartTime(long);
        void setLastReqTime(long);
        void setTestStatus(int);
        void setRecvFlag(bool);
        void setOperPlatform(int);
        
        char* getTaskId();
        char* getBinaryPath();
        long getStartTime();
        long getLastReqTime();
        int getTestStatus();
        bool getRecvFlag();
        int getOperPlatform();
        
    };
}

#endif /* defined(__internClient01__TaskInfo__) */
