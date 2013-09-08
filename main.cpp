//
//  main.cpp
//  TestClient
//
//  Created by ChenXiao on 7/26/13.
//  Copyright (c) 2013 Microsoft. All rights reserved.
//

#include "commonHeader.h"
#include "Controller.h"
#include "MasterClient.h"

using namespace ClientSCTT;
using namespace std;

typedef struct {
    string serverIp;
    unsigned short serverPort;
    string binaryPath;
    string outputDir;
    int operPlatform;
    long timeOut;
} InitInfo;

bool init(int argc, const char **paras,InitInfo&);
int getPlatform(int);
void help();

const int TEST_PASS = 0;
const int TEST_FAIL = -1;
const int PROC_ERROR = -2;

int main(int argc, const char * argv[])
{
    
    if(argc==2 and strcmp(argv[1],"-help")==0) {
        help();
        return PROC_ERROR;
    }
    
    InitInfo initInfo;
    bool f = init(argc,argv,initInfo);
    if(!f) {
        printf("[ERROR: init FAIL]\n");
        return PROC_ERROR;
    }
    const char* serverIp = initInfo.serverIp.data();
    unsigned short serverPort = initInfo.serverPort;
    //const char* binaryPath = initInfo.binaryPath.data();
    const char* binaryPath= "/Users/rt-build/Downloads/bvttest";
    int operPlatform = getPlatform(initInfo.operPlatform);
    const char* outputDir = initInfo.outputDir.data();
    long timeOut = initInfo.timeOut;
    
    Controller *master = new MasterClient(serverIp,serverPort,binaryPath,operPlatform,outputDir,timeOut);
    f = master->connectServer();
    bool returnValue = false;
    if(f) {
        returnValue = master->arbiter();
    }else {
        printf("[EROR: Connect to Server FAIL]\n");
        return PROC_ERROR;
    }
    master->closeAll();
    if(returnValue)
        return TEST_PASS;
    else
        return TEST_FAIL;
}

bool init(int argc, const char **paras,InitInfo& initInfo) {
    /*
     * read config.tx
     * including:
     *    ServerIp
     *    ServerPort
     *    outputDir
     *    operPlatform
     *    timeOut
     */
    ifstream fp("config.txt");
    if(!fp) {
        printf("[ERROR: open config.txt FAIL]\n");
        return false;
    }
    map<string,string> configInfo;
    while(!fp.eof()) {
        string str;
        getline(fp, str);
        int index = (int)str.find('=');
        string key = str.substr(0,index);
        string value = str.substr(index+1,str.length()-index-1);
        configInfo[key] = value;
    }
    fp.close();
    initInfo.serverIp = configInfo["ServerIp"];
    initInfo.serverPort = (unsigned short)atoi(configInfo["ServerPort"].data());
    initInfo.outputDir = configInfo["outputDir"];
    string timeStr = configInfo["timeOut"];
    initInfo.operPlatform = atoi(configInfo["operPlatform"].data());
    
    /* handle parameters */
    initInfo.binaryPath = "";
    for(int i=1;i<argc && i+1<argc;i+=2) {
        if(strcmp(paras[i],"-b")==0) {
            initInfo.binaryPath = string(paras[i+1]);
        }else if(strcmp(paras[i],"-i")==0) {
            initInfo.serverIp = string(paras[i+1]);
        }else if(strcmp(paras[i],"-p")==0) {
            initInfo.serverPort = (unsigned short)atoi(paras[i+1]);
        }else if(strcmp(paras[i],"-s")==0) {
            initInfo.operPlatform = atoi(paras[i+1]);
        }else if(strcmp(paras[i],"-d")==0) {
            initInfo.outputDir = string(paras[i+1]);
        }else if(strcmp(paras[i],"-t")==0) {
            timeStr = string(paras[i+1]);
        }else {
            help();
            return false;
        }
    }
    if(initInfo.binaryPath=="") {
        printf("[ERROR: please input binary PATH: -b path]\n");
        help();
        return false;
    }
    
    /* calculate time out duration */
    int len = (int)timeStr.size();
    char timeType = timeStr[len-1];
    string dura = timeStr.substr(0,len-1);
    switch(timeType) {
        case 's': {
            initInfo.timeOut = (long)atoi(dura.data());
        }break;
        case 'm': {
            initInfo.timeOut = (long)atoi(dura.data())*60;
        }break;
        case 'h': {
            initInfo.timeOut = (long)atoi(dura.data())*3600;
        }break;
        default:{
            initInfo.timeOut = 1800L;
        }break;
    }
    if(initInfo.timeOut<=0) {
        printf("[WARN: timeOut OVERFLOW]\n");
        return false;
    }
    /*
    cout<<initInfo.serverIp<<" "<<initInfo.serverPort<<endl;
    cout<<initInfo.binaryPath<<endl;
    cout<<initInfo.outputDir<<endl;
    cout<<initInfo.operPlatform<<" "<<initInfo.timeOut<<endl;
    */
    return true;
}
int getPlatform(int oper) {
    int operPlatform = -1;
    switch(oper) {
        case 0: { operPlatform =  _OPER_IOS; } break;
        case 1: { operPlatform = _OPER_ANDROID; } break;
        case 2: { operPlatform = _OPER_WINRTARM7; } break;
        case 3: { operPlatform = _OPER_MACI386; } break;
        case 4: { operPlatform = _OPER_MACX64; } break;
        case 5: { operPlatform = _OPER_LINUXX64; } break;
        case 6: { operPlatform = _OPER_LINUXI386; } break;
        case 7: { operPlatform = _OPER_BLUEI386; } break;
        case 8: { operPlatform = _OPER_BLUEX64; } break;
        case 9: { operPlatform = _OPER_WINI386; } break;
        case 10: { operPlatform = _OPER_WINRTI386; } break;
        case 11: { operPlatform = _OPER_WINRTX64; } break;
        default: break;
    }
    return operPlatform;
}

void help() {
    printf("cmd: TestClient -b binaryPath [options]\n");
    printf("[options]:\n");
    printf("-i Server Ip\n");
    printf("-p Server Port\n");
    printf("-d output Dir\n");
    printf("-t time out\n");
    printf("-s operation platform\n");
    printf("[operation platform]:\n");
    printf("0 \tios-armv7\n");
    printf("1 \tandroid-armv6-ndk\n");
    printf("2 \twinrt-armv7\n");
    printf("3 \tmac-i386\n");
    printf("4 \tmac-x86_64\n");
    printf("5 \tlinux-x86_64-glibc\n");
    printf("6 \tlinux-i386-glibc\n");
    printf("7 \tblue-i386\n");
    printf("8 \tblue-x86_64\n");
    printf("9 \twin-i386\n");
    printf("10\twinrt-i386\n");
    printf("11\twinrt-x86_64\n");
}