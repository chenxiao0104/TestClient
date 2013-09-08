//
//  HandleMsg.cpp
//  TestClient
//
//  Created by ChenXiao on 7/26/13.
//  Copyright (c) 2013 Microsoft. All rights reserved.
//

#include "HandleMsg.h"

using namespace ClientSCTT;

// new task request message
char* HandleMsg::createTaskReqMsg(int oper) {
    
    cJSON *jsonMsg = cJSON_CreateObject();
    cJSON_AddStringToObject(jsonMsg, "taskId", "0_0_0_0");
    cJSON_AddNumberToObject(jsonMsg, "msgType", _MSGTYPE_NEWTASK);
    cJSON_AddNumberToObject(jsonMsg, "operPlatform", oper);
    char* msg = cJSON_PrintUnformatted(jsonMsg);
    return msg;
}

// ready to send binary message
char* HandleMsg::createAppReadyMsg(const char* id) {
    cJSON *jsonMsg = cJSON_CreateObject();
    cJSON_AddStringToObject(jsonMsg, "taskId", id);
    cJSON_AddNumberToObject(jsonMsg, "msgType", _MSGTYPE_APPREADY);
    char* msg = cJSON_PrintUnformatted(jsonMsg);
    return msg;
}

// task status request message
char* HandleMsg::createTaskStatusReqMsg(const char* id) {
    cJSON *jsonMsg = cJSON_CreateObject();
    cJSON_AddStringToObject(jsonMsg, "taskId", id);
    cJSON_AddNumberToObject(jsonMsg, "msgType", _MSGTYPE_STATUSREQ);
    char* msg = cJSON_PrintUnformatted(jsonMsg);
    return msg;
}

// parse message type
int HandleMsg::parseMsgType(cJSON* jsonMsg) {
    //cJSON *jsonMsg = cJSON_Parse(msg);
    int msgType = cJSON_GetObjectItem(jsonMsg, "msgType")->valueint;
    return msgType;
}

// parse new task request ack
char* HandleMsg::parseTaskReqAck(cJSON* jsonMsg) {
    //cJSON *jsonMsg = cJSON_Parse(msg);
    int reqStatus = cJSON_GetObjectItem(jsonMsg, "reqStatus")->valueint;
    if(reqStatus==_NEWTASK_ACCEPT){
        char* taskId = cJSON_GetObjectItem(jsonMsg, "taskId")->valuestring;
        return taskId;
    }else if(reqStatus==_NEWTASK_REFUSE){
        return NULL;
    }else
        return NULL;
}

// parse app recv ready
int HandleMsg::parseAppRecvReady(cJSON* jsonMsg){
    //cJSON *jsonMsg = cJSON_Parse(msg);
    int recvAccept = cJSON_GetObjectItem(jsonMsg, "recvAccept")->valueint;
    return recvAccept;
}

// parse the result of binary send ack
int HandleMsg::parseAppSndAck(cJSON* jsonMsg) {
    //cJSON *jsonMsg = cJSON_Parse(msg);
    int recvStatus = cJSON_GetObjectItem(jsonMsg, "recvStatus")->valueint;
    return recvStatus;
}

// parse task status request ack
int HandleMsg::parseTaskStatusReqAck(cJSON* jsonMsg) {
    //cJSON *jsonMsg = cJSON_Parse(msg);
    int taskStatus = cJSON_GetObjectItem(jsonMsg, "taskStatus")->valueint;
    return taskStatus;
}

// parse test result
int HandleMsg::parseTestResultMsg(cJSON* jsonMsg) {
    //cJSON *jsonMsg = cJSON_Parse(msg);
    int testResult = cJSON_GetObjectItem(jsonMsg, "testResult")->valueint;
    char* outputPath = cJSON_GetObjectItem(jsonMsg, "outputPath")->valuestring;
    char* detailPath = cJSON_GetObjectItem(jsonMsg, "detailPath")->valuestring;
    printf("[ Server: outputfile.txt: %s ]\n",outputPath);
    printf("[ Server: detail.xml:     %s ]\n",detailPath);
    return testResult;
}
