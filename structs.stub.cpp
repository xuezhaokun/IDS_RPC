#include "c150debug.h"
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <fstream>
#include <arpa/inet.h>
using namespace std;
using namespace C150NETWORK;
#include "structs.idl"
#include "basicTypeHandler.h"
#include "structs_additionalTypeHandler.h"
#include "rpcstubhelper.h"

void __add(int x, int y){
	int result = add(x, y);
	sendintType (RPCSTUBSOCKET, result);
}
void __area(rectangle r){
	int result = area(r);
	sendintType (RPCSTUBSOCKET, result);
}
void __divide(float x, float y){
	float result = divide(x, y);
	sendfloatType (RPCSTUBSOCKET, result);
}
void __findPerson(ThreePeople tp){
	Person result = findPerson(tp);
	sendStruct_Person (RPCSTUBSOCKET, result);
}
void __multiply(float x, float y){
	float result = multiply(x, y);
	sendfloatType (RPCSTUBSOCKET, result);
}
void __subtract(int x, int y){
	int result = subtract(x, y);
	sendintType (RPCSTUBSOCKET, result);
}
void __badFunction(char *functionName){
	char doneBuffer[5] = "BAD";
	 RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
}
void dispatchFunction() {
	char functionNameBuffer[50];
	string functionName = readFunctionName(RPCSTUBSOCKET, functionNameBuffer, sizeof(functionNameBuffer));
	if (!RPCSTUBSOCKET-> eof()) {
		if (strcmp(functionName.c_str(), "add") == 0){
			int x = readintType(RPCSTUBSOCKET);
			int y = readintType(RPCSTUBSOCKET);
			__add(x, y);
		} else if (strcmp(functionName.c_str(), "area") == 0){
			rectangle r = readStruct_rectangle(RPCSTUBSOCKET);
			__area(r);
		} else if (strcmp(functionName.c_str(), "divide") == 0){
			float x = readfloatType(RPCSTUBSOCKET);
			float y = readfloatType(RPCSTUBSOCKET);
			__divide(x, y);
		} else if (strcmp(functionName.c_str(), "findPerson") == 0){
			ThreePeople tp = readStruct_ThreePeople(RPCSTUBSOCKET);
			__findPerson(tp);
		} else if (strcmp(functionName.c_str(), "multiply") == 0){
			float x = readfloatType(RPCSTUBSOCKET);
			float y = readfloatType(RPCSTUBSOCKET);
			__multiply(x, y);
		} else if (strcmp(functionName.c_str(), "subtract") == 0){
			int x = readintType(RPCSTUBSOCKET);
			int y = readintType(RPCSTUBSOCKET);
			__subtract(x, y);
		}  else {
 			__badFunction(functionNameBuffer);
		}
	}
}
