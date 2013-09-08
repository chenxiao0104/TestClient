TestClient : main.o Controller.o MasterClient.o ClientCom.o HandleMsg.o TaskInfo.o cJSON.o
	g++ -o TestClient main.o Controller.o MasterClient.o ClientCom.o HandleMsg.o TaskInfo.o cJSON.o

main.o : main.cpp
	g++ -c main.cpp
Controller.o : Controller.h Controller.cpp
	g++ -c Controller.cpp
MasterClient.o : MasterClient.h MasterClient.cpp
	g++ -c MasterClient.cpp
ClientCom.o : NetMgnt.h ClientCom.h ClientCom.cpp
	g++ -c ClientCom.cpp
HandleMsg.o : HandleMsg.h HandleMsg.cpp
	g++ -c HandleMsg.cpp
TaskInfo.o : TaskInfo.h TaskInfo.cpp
	g++ -c TaskInfo.cpp
cJSON.o : cJSON.h cJSON.c
	gcc -c cJSON.c
clean : 
	rm -f main.o Controller.o MasterClient.o ClientCom.o HandleMsg.o TaskInfo.o cJSON.o
