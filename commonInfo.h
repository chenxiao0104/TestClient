//
//  commonInfo.h
//  internClient01
//
//  Created by ChenXiao on 7/25/13.
//  Copyright (c) 2013 Microsoft. All rights reserved.
//

#ifndef internClient01_commonInfo_h
#define internClient01_commonInfo_h

namespace ClientSCTT {
    //max size buff
    const int _MAX_SIZE = 1024;
    
    //new task
    const int _NEW_TASK = 0;
    
    //msg length
    const int _MSGLEN_ALL = 512;
    const int _MSGLEN_TASKID = 20;
    const int _SOCK_SIZE = 512;
    
    //message content
    const int _MSGINDEX_TASKIDFST = 0;
    const int _MSGINDEX_TASKIDSND = 1;
    const int _MSGINDEX_TASKIDTRD = 2;
    const int _MSGINDEX_MSGTYPE = 3;
    const int _MSGINDEX_DATA = 4;
    
    //msg base value
    const char _BASE_VALUE = 10;
    
    //recv flag
    const int _RECV_SUCCESS = 1;
    const int _RECV_FAIL = 0;
    const int _SEND_READY = 1;
    
    //New Task Request
    const int _NEWTASK_ACCEPT = 1;
    const int _NEWTASK_REFUSE = 0;
    
    //Binary Receive Status
    const int _APPRECV_PERMIT = 1;
    const int _APPRECV_REFUSE = 0;
    
    const int _APPRECV_SUCCESS = 1;
    const int _APPRECV_FAIL  = 0;
    
    //Test Case Result
    const int _TESTRESULT_PASS = 1;
    const int _TESTRESULT_FAIL = 0;
    
    //Analysis Result
    const bool _ANALYSIS_PASS = 1;
    const bool _ANALYSIS_FAIL = 0;
    
    //Message Type
    const int _MSGTYPE_NEWTASK = 3001;
    const int _MSGTYPE_TASKACK = 3002;
    const int _MSGTYPE_APPRECV = 3003;
    const int _MSGTYPE_STATUSREQ = 3004;
    const int _MSGTYPE_STATUSACK = 3005;
    const int _MSGTYPE_TESTRESULT = 3006;
    const int _MSGTYPE_ANALYSIS = 3007;
    const int _MSGTYPE_APPREADY = 3008;
    const int _MSGTYPE_APPSEND = 3009;
    const int _MSGTYPE_APPFINISH = 3010;
    
    //task status
    const int _TESTCASE_WAITING = 4001;
    const int _TESTCASE_RUNNING = 4002;
    const int _TESTCASE_FINISH = 4003;
    const int _TESTCASE_FAIL = 4004;
    const int _TESTCASE_TIMEOUT = 4005;
    
    //Operation Platform
    const int _OPER_IOS = 5001;
    const int _OPER_ANDROID = 5002;
    const int _OPER_WINRTARM7 = 5003;
    const int _OPER_MACI386 = 5004;
    const int _OPER_MACX64 = 5005;
    const int _OPER_LINUXX64 = 5006;
    const int _OPER_LINUXI386 = 5007;
    const int _OPER_BLUEI386 = 5008;
    const int _OPER_BLUEX64 = 5009;
    const int _OPER_WINI386 = 5010;
    const int _OPER_WINRTI386 = 5011;
    const int _OPER_WINRTX64 = 5012;
}

#endif
