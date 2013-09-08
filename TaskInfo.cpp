//
//  TaskInfo.cpp
//  internClient01
//
//  Created by ChenXiao on 7/24/13.
//  Copyright (c) 2013 Microsoft. All rights reserved.
//

#include "TaskInfo.h"

using namespace ClientSCTT;

TaskInfo::TaskInfo() {
    taskId = new char[_MSGLEN_TASKID+1];
    bzero(taskId, _MSGLEN_TASKID+1);
    binaryPath = NULL;
    long now = (long)time(NULL);
    startTime = now;
    lastReqTime = now;
    testStatus = _TESTCASE_WAITING;
    recvFlag = _RECV_FAIL;
    operPlatform = _OPER_WINI386;
}

TaskInfo::TaskInfo(const char* id) {
    taskId = new char[_MSGLEN_ALL];
    bzero(taskId, _MSGLEN_ALL);
    int size = (int)strlen(id);
    binaryPath = new char[size+1];
    memcpy(binaryPath, id, size);
    binaryPath[size] = '\0';
    long now = (long)time(NULL);
    startTime = now;
    lastReqTime = now;
    testStatus = _TESTCASE_WAITING;
    recvFlag = _RECV_FAIL;
    operPlatform = _OPER_WINI386;
}

void TaskInfo::setTaskId(const char* id) {
    memcpy(taskId,id,_MSGLEN_ALL);
}


void TaskInfo::setBinaryPath(const char* path) {
    int len = (int)strlen(path);
    binaryPath = new char[len+1];
    memcpy(binaryPath,path,len);
    binaryPath[len] = '\0';
}

void TaskInfo::setStartTime(long timeStamp) {
    startTime = timeStamp;
}

void TaskInfo::setLastReqTime(long timeStamp) {
    lastReqTime = timeStamp;
}

void TaskInfo::setTestStatus(int newStatus) {
    testStatus = newStatus;
}

void TaskInfo::setRecvFlag(bool flag) {
    recvFlag = flag;
}

void TaskInfo::setOperPlatform(int oper) {
    operPlatform = oper;
}

char* TaskInfo::getTaskId() {
    return taskId;
}

char* TaskInfo::getBinaryPath() {
    return binaryPath;
}

long TaskInfo::getStartTime() {
    return startTime;
}

long TaskInfo::getLastReqTime() {
    return lastReqTime;
}

int TaskInfo::getTestStatus() {
    return testStatus;
}

bool TaskInfo::getRecvFlag() {
    return recvFlag;
}

int TaskInfo::getOperPlatform() {
    return operPlatform;
}
