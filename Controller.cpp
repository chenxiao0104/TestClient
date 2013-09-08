//
//  Controller.cpp
//  TestClient
//
//  Created by ChenXiao on 7/29/13.
//  Copyright (c) 2013 Microsoft. All rights reserved.
//

#include "Controller.h"

using namespace ClientSCTT;

Controller::Controller(const char* ip,unsigned short port,const char* path,int oper,long timeOut) {
    netMgnt = new ClientCom(ip,port);
    taskInfo = new TaskInfo(path);
    taskInfo->setOperPlatform(oper);
    handleMsg = NULL;
    threshold = timeOut;
}

Controller::~Controller() {
	if(netMgnt!=NULL)
		delete netMgnt;
	if(taskInfo!=NULL)
		delete taskInfo;
}

int Controller::getSocket() {
    return netMgnt->getSocket();
}

char* Controller::getTaskId() {
    return taskInfo->getTaskId();
}

int Controller::getMsgType(cJSON* jsonMsg) {
    int type = handleMsg->parseMsgType(jsonMsg);
    return type;
}

bool Controller::connectServer() {
    bool flag = netMgnt->createConnect();
    return flag;
}

bool Controller::sendTaskReq() {
    char* msg = handleMsg->createTaskReqMsg(taskInfo->getOperPlatform());
    bool flag = netMgnt->sendMsg(msg);
    delete msg;
    return flag;
}

bool Controller::sendBinaryReady() {
    char* msg = handleMsg->createAppReadyMsg(taskInfo->getTaskId());
    bool flag = netMgnt->sendMsg(msg);
    delete msg;
    return flag;
}

bool Controller::handleTaskAck(cJSON* jsonMsg) {
    bool flag = false;
    char* taskId = handleMsg->parseTaskReqAck(jsonMsg);
    if(taskId!=NULL) {
        taskInfo->setTaskId(taskId);
        flag = true;
    }else {
        flag = false;
    }
    return flag;
}

bool Controller::handleBinaryAck(cJSON* jsonMsg) {
    char flag = handleMsg->parseAppSndAck(jsonMsg);
    if(flag==_APPRECV_SUCCESS) {
        long timeStamp = (long)time(NULL);
        taskInfo->setStartTime(timeStamp);
        taskInfo->setLastReqTime(timeStamp);
        taskInfo->setTestStatus(_TESTCASE_WAITING);
    }
    return flag;
}

bool Controller::sendStatusReq() {
    char* taskId = taskInfo->getTaskId();
    bool flag = false;
    if(taskId!=NULL) {
        char* msg = handleMsg->createTaskStatusReqMsg(taskId);
        flag = netMgnt->sendMsg(msg);
        delete msg;
    }
    return flag;
}

// parse task status request ack
// judge task is or not time out
int Controller::handleStatusAck(cJSON* jsonMsg) {
    int oldStatus = taskInfo->getTestStatus();
    if(oldStatus == _TESTCASE_FINISH) {
        return _TESTCASE_FINISH;
    }

    int newStatus = handleMsg->parseTaskStatusReqAck(jsonMsg);
    bool isRunning = false;
    long now = (long)time(NULL);
    
    switch (newStatus) {
        case _TESTCASE_WAITING: {
            long lastReq = taskInfo->getLastReqTime();
            isRunning = !isTimeOut(lastReq, now);
            if(isRunning) {
                //taskInfo->setLastReqTime(now);
            }else {
                return _TESTCASE_TIMEOUT;
            }
        }
            break;
            
        case _TESTCASE_RUNNING: {
            if(oldStatus == _TESTCASE_WAITING) {
                taskInfo->setLastReqTime(now);
                taskInfo->setTestStatus(newStatus);
                isRunning = true;
            }else {
                long lastReq = taskInfo->getLastReqTime();
                isRunning = !isTimeOut(lastReq, now);
                if(isRunning) {
                    //taskInfo->setLastReqTime(now);
                }else {
                    return _TESTCASE_TIMEOUT;
                }
            }
        }
            break;
            
        case _TESTCASE_FINISH: {
            taskInfo->setTestStatus(_TESTCASE_FINISH);
            return _TESTCASE_FINISH;
        }
            break;
            
        default:  break;
    }
    
    return newStatus;
}

bool Controller::handleTestResult(cJSON* jsonMsg) {
    int testResult = handleMsg->parseTestResultMsg(jsonMsg);
    if(testResult == _TESTRESULT_PASS){
        printf("[LOG: Test Result PASS]\n");
        return true;
    }else{
        printf("[LOG: Test Result FAIL]\n");
        return false;
    }
}

bool Controller::recvMsg(char* buff) {
    return netMgnt->recvMsg(buff);
}

char* Controller::getBinaryPath() {
    return taskInfo->getBinaryPath();
}

bool Controller::isTimeOut(long lastReq, long now) {
    //const long threshold = 1800L;
    if(now-lastReq > threshold)
        return true;
    else
        return false;
}

/*
bool Controller::sendAnalysis(char result) {
    char* taskId = taskInfo->getTaskId();
    bool flag = false;
    if(taskId!=NULL) {
        char* msg = handleMsg->createAnalysisMsg(taskId, result);
        flag = netMgnt->sendMsg(msg);
        delete msg;
    }
    return flag;
}
*/

void Controller::closeAll() {
    close(getSocket());
}
