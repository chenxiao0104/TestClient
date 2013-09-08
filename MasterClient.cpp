//
//  MasterClient.cpp
//  TestClient
//
//  Created by rt-build on 7/29/13.
//  Copyright (c) 2013 bupt-bnrc. All rights reserved.
//

#include "MasterClient.h"

using namespace ClientSCTT;

MasterClient::MasterClient(const char* ip,unsigned short port,const char* path,int oper,const char* output,long timeOut):Controller(ip,port,path,oper,timeOut) {
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    buff = new char[_MAX_SIZE+1];
    outputDir = NULL;
    outputDir = new char[strlen(output)+1];
    memcpy(outputDir,output,strlen(output)+1);
}

bool MasterClient::arbiter() {
    signal(SIGPIPE, SIG_IGN);
    const int _FIRSTASK_INTERVAL = 10;
    const int _EACHTIME_INTERVAL = 3;
    printf("[LOG: Send Task REQ]\n");
    sendTaskReq();
    int ret = -1;
    bool testResult = false;
    
    bool isRun = true;
    while(isRun) {
        FD_ZERO(&rdfds);
        FD_SET(getSocket(), &rdfds);
        ret = select(getSocket()+1,&rdfds,NULL,NULL,&tv);
        
        if(ret==-1) {
            printf("[ERROR: select EROR]\n");
        }else if(ret==0) {
            //printf("time out.\n");
        }else {
            isRun = recvMsg(buff);
            if(isRun == false){
                return false;
            }
            cJSON* jsonMsg = cJSON_Parse(buff);
            int type = getMsgType(jsonMsg);
            switch (type) {
                case _MSGTYPE_TASKACK: {
                    
                    isRun = handleTaskAck(jsonMsg);
                    if(isRun) {
                        printf("[LOG: Send Binary READY]\n");
                        sendBinaryReady();
                        printf("[LOG: Send file]\n");
                        usleep(100L);
                        isRun = sendBinary();
                        if(isRun) {
                            printf("[LOG: Send OK]\n"); }
                        else
                            printf("[LOg: Send FAIL]\n");
                    }
                }
                    break;
                  
                case _MSGTYPE_APPRECV: {
                    printf("[LOG: Recv Binary ACK]\n");
                    isRun = handleBinaryAck(jsonMsg);
                    if(isRun) {
                        sleep(_FIRSTASK_INTERVAL);
                        isRun = sendStatusReq();
                    }
                }
                    break;
                   
                case _MSGTYPE_STATUSACK: {
                    
                    int newStatus = handleStatusAck(jsonMsg);
                    if(newStatus==_TESTCASE_WAITING || newStatus==_TESTCASE_RUNNING) {
                        if(newStatus==_TESTCASE_WAITING)
                            printf("[LOG: Task is WAITING]\n");
                        else
                            printf("[LOG: Task RUNNING]\n");
                        
                        isRun = true;
                        sleep(_EACHTIME_INTERVAL);
                        isRun = sendStatusReq();
                    }else if(newStatus==_TESTCASE_FINISH) {
                        isRun = true;
                        printf("[LOG: Test Case FINISH]\n");
                    }else if(newStatus == _TESTCASE_TIMEOUT){
                        printf("[ERROR: Test Case TIME OUT]\n");
                        isRun = false;
                    }else if(newStatus == _TESTCASE_FAIL){
                        printf("[ERROR: Test Case FAIL]\n");
                        isRun = false;
                    }else{
                        isRun = false;
                    }
                }
                    break;
                    
                case _MSGTYPE_TESTRESULT: {
                    printf("[LOG: Recv Test Result]\n");
                    testResult = handleTestResult(jsonMsg);
                    recvOutput(cJSON_GetObjectItem(jsonMsg, "outputSize")->valueint, cJSON_GetObjectItem(jsonMsg, "taskId")->valuestring);
                    isRun = false;
                }
                    break;
                    
                default: break;
            }
            bzero(buff, _MAX_SIZE+1);
        }
    }
    return testResult;
    //printf("[LOG: Bvt Test Over]\n");
}

bool MasterClient::sendBinary() {
    FILE* fp = fopen(getBinaryPath(),"rb");
    if(fp<0) {
        printf("[ERROR: Open Binary FAIL]\n");
        return false;
    }
    fseek(fp, 0, SEEK_END);
    long fileLen = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* buff = new char[fileLen];
    int blockSize = (int)fread(buff,sizeof(char),fileLen,fp);
    if(blockSize<0) {
        fclose(fp);
        return false;
    }
    send(getSocket(),buff,fileLen,0);
    return true;
}

bool MasterClient::recvOutput(int fileSize, const char *taskId){
    if(outputDir==NULL){
        printf("[ERROR: outputdir is WRONG]\n");
        return false;
    }
    char* filePath = new char[100];
    memset(filePath,'\0',100);
    memcpy(filePath,outputDir,strlen(outputDir));
    if(filePath[strlen(filePath)]!='/'){
        strcat(filePath,"/");
    }
    strcat(filePath,taskId);
    strcat(filePath,"_output.txt");
    FILE* fp = fopen(filePath,"wb");
    if(fp<0){
        printf("[ERROR: Open Outputfile FAIL]\n");
        return false;
    }
    int totalSize = 0;
    const int _RECV_SIZE = 4096;
    char* buff = new char[_RECV_SIZE];
    int len;
    while(true) {
        len = (int)recv(getSocket(),buff,_RECV_SIZE,0);
        if(len>0){
            fwrite(buff, sizeof(char), len, fp);
            totalSize += len;
            if(totalSize == fileSize)
                break;
        }else {
            fclose(fp);
            printf("[ERROR: Recv Outputfile FAIL]\n");
            return false;
        }
    }
    printf("[LOG: Recv Outputfile OK]\n");
    fclose(fp);
    printf("[ Client: outputfile.txt: %s ]\n",filePath);
    //printOutput(filePath);
    return true;
}

void MasterClient::printOutput(const char * path) {
    FILE* fp = fopen(path,"rb");
    if(fp<0) {
        printf("[ERROR: Open Outputfile FAIL]\n");
        return;
    }
    const int _READ_SIZE = 1024;
    char* msg = new char[_READ_SIZE];
    printf("\n\t[ *** TEST CASE RESULT *** ]\n");
    while(feof(fp)==0) {
        fgets(msg,_READ_SIZE,fp);
        printf("%s",msg);
        memset(msg,'\0',_READ_SIZE);
    }
}
