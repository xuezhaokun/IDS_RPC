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
#include "rpcproxyhelper.h"

int add(int x, int y){
	sendFunctionName(RPCPROXYSOCKET, "add");
	sendintType (RPCPROXYSOCKET, x);
	sendintType (RPCPROXYSOCKET, y);
	return readintType(RPCPROXYSOCKET);
}
int area(rectangle r){
	sendFunctionName(RPCPROXYSOCKET, "area");
	sendStruct_rectangle (RPCPROXYSOCKET, r);
	return readintType(RPCPROXYSOCKET);
}
float divide(float x, float y){
	sendFunctionName(RPCPROXYSOCKET, "divide");
	sendfloatType (RPCPROXYSOCKET, x);
	sendfloatType (RPCPROXYSOCKET, y);
	return readfloatType(RPCPROXYSOCKET);
}
Person findPerson(ThreePeople tp){
	sendFunctionName(RPCPROXYSOCKET, "findPerson");
	sendStruct_ThreePeople (RPCPROXYSOCKET, tp);
	return readStruct_Person(RPCPROXYSOCKET);
}
int findSecondPersonAge(StructWithArrays persons){
	sendFunctionName(RPCPROXYSOCKET, "findSecondPersonAge");
	sendStruct_StructWithArrays (RPCPROXYSOCKET, persons);
	return readintType(RPCPROXYSOCKET);
}
float multiply(float x, float y){
	sendFunctionName(RPCPROXYSOCKET, "multiply");
	sendfloatType (RPCPROXYSOCKET, x);
	sendfloatType (RPCPROXYSOCKET, y);
	return readfloatType(RPCPROXYSOCKET);
}
rectangle searchRectangles(rectangle rects[4]){
	sendFunctionName(RPCPROXYSOCKET, "searchRectangles");
	sendArray_rectangle_4 (RPCPROXYSOCKET, rects);
	return readStruct_rectangle(RPCPROXYSOCKET);
}
int subtract(int x, int y){
	sendFunctionName(RPCPROXYSOCKET, "subtract");
	sendintType (RPCPROXYSOCKET, x);
	sendintType (RPCPROXYSOCKET, y);
	return readintType(RPCPROXYSOCKET);
}
int sumSm(sm stest){
	sendFunctionName(RPCPROXYSOCKET, "sumSm");
	sendStruct_sm (RPCPROXYSOCKET, stest);
	return readintType(RPCPROXYSOCKET);
}
