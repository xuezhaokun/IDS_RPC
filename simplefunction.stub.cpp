#include "c150debug.h"
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <fstream>
#include <arpa/inet.h>
using namespace std;
using namespace C150NETWORK;
#include "simplefunction.idl"
#include "basicTypeHandler.h"
#include "simplefunction_additionalTypeHandler.h"
#include "rpcstubhelper.h"

void __func1(){
	sendvoidType (RPCSTUBSOCKET);
}
void __func2(){
	sendvoidType (RPCSTUBSOCKET);
}
void __func3(){
	sendvoidType (RPCSTUBSOCKET);
}
void __badFunction(char *functionName){
	char doneBuffer[5] = "BAD";
	 RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
}
void dispatchFunction() {
	char functionNameBuffer[50];
	string functionName = readFunctionName(RPCSTUBSOCKET, functionNameBuffer, sizeof(functionNameBuffer));
	if (!RPCSTUBSOCKET-> eof()) {
		if (strcmp(functionName.c_str(), "func1") == 0){
		__func1();
		} else if (strcmp(functionName.c_str(), "func2") == 0){
		__func2();
		} else if (strcmp(functionName.c_str(), "func3") == 0){
		__func3();
		}  else {
 			__badFunction(functionNameBuffer);
		}
	}
}
