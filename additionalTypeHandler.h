#ifndef __ADDITIONALTYPE_H_INCLUDED__
#define __ADDITIONALTYPE_H_INCLUDED__
#include <string>
#include "c150streamsocket.h"
using namespace C150NETWORK;
using namespace std;

MT readStruct_MT(C150StreamSocket *socket);
void sendStruct_MT(C150StreamSocket *socket, MT structData);
Person readStruct_Person(C150StreamSocket *socket);
void sendStruct_Person(C150StreamSocket *socket, Person structData);
StructWithArrays readStruct_StructWithArrays(C150StreamSocket *socket);
void sendStruct_StructWithArrays(C150StreamSocket *socket, StructWithArrays structData);
ThreePeople readStruct_ThreePeople(C150StreamSocket *socket);
void sendStruct_ThreePeople(C150StreamSocket *socket, ThreePeople structData);
void readArray_Person_10(C150StreamSocket *socket, Person arrayArg[10]);
void sendArray_Person_10(C150StreamSocket *socket, Person arrayArg[10]);
void readArray_int_100(C150StreamSocket *socket, int arrayArg[100]);
void sendArray_int_100(C150StreamSocket *socket, int arrayArg[100]);
void readArray_int_10(C150StreamSocket *socket, int arrayArg[10]);
void sendArray_int_10(C150StreamSocket *socket, int arrayArg[10]);
void readArray_int_10_100(C150StreamSocket *socket, int arrayArg[10][100]);
void sendArray_int_10_100(C150StreamSocket *socket, int arrayArg[10][100]);
void readArray_int_4(C150StreamSocket *socket, int arrayArg[4]);
void sendArray_int_4(C150StreamSocket *socket, int arrayArg[4]);
void readArray_int_4_10(C150StreamSocket *socket, int arrayArg[4][10]);
void sendArray_int_4_10(C150StreamSocket *socket, int arrayArg[4][10]);
void readArray_int_4_10_100(C150StreamSocket *socket, int arrayArg[4][10][100]);
void sendArray_int_4_10_100(C150StreamSocket *socket, int arrayArg[4][10][100]);
rectangle readStruct_rectangle(C150StreamSocket *socket);
void sendStruct_rectangle(C150StreamSocket *socket, rectangle structData);
s readStruct_s(C150StreamSocket *socket);
void sendStruct_s(C150StreamSocket *socket, s structData);
#endif
