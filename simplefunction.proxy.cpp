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
#include "rpcproxyhelper.h"

void func1(){
	sendFunctionName(RPCPROXYSOCKET, "func1");
	return readvoidType(RPCPROXYSOCKET);
}
void func2(){
	sendFunctionName(RPCPROXYSOCKET, "func2");
	return readvoidType(RPCPROXYSOCKET);
}
void func3(){
	sendFunctionName(RPCPROXYSOCKET, "func3");
	return readvoidType(RPCPROXYSOCKET);
}
