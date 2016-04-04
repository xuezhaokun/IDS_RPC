#include "c150debug.h"
#include "rpcproxyhelper.h"
#include "basicTypeHandler.h"
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <fstream>
#include <arpa/inet.h>
using namespace C150NETWORK;
using namespace std;
#include "structs.idl"
#include "additionalTypeHandler.h"

void sendStruct_Person(C150StreamSocket *socket, Person structData){
	sendstringType(socket, structData.firstname);
	sendstringType(socket, structData.lastname);
	sendintType(socket, structData.age);
	
}

Person readStruct_Person(C150StreamSocket *socket){
	Person result;
	result.firstname = readstringType(socket);
	result.lastname = readstringType(socket);
	result.age = readintType(socket);
	return result;
}

void sendStruct_ThreePeople(C150StreamSocket *socket, ThreePeople structData){
	sendStruct_Person(socket, structData.p1);
	sendStruct_Person(socket, structData.p2);
	sendStruct_Person(socket, structData.p3);
	
}

ThreePeople readStruct_ThreePeople(C150StreamSocket *socket){
	ThreePeople result;
	result.p1 = readStruct_Person(socket);
	result.p2 = readStruct_Person(socket);
	result.p3 = readStruct_Person(socket);
	return result;
}

void sendStruct_rectangle(C150StreamSocket *socket, rectangle structData){
	sendintType(socket, structData.x);
	sendintType(socket, structData.y);
	
}

rectangle readStruct_rectangle(C150StreamSocket *socket){
	rectangle result;
	result.x = readintType(socket);
	result.y = readintType(socket);
	return result;
}

