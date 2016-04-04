#ifndef __ADDITIONALTYPE_H_INCLUDED__
#define __ADDITIONALTYPE_H_INCLUDED__
#include <string>
#include "c150streamsocket.h"
using namespace C150NETWORK;
using namespace std;

Person readStruct_Person(C150StreamSocket *socket);
void sendStruct_Person(Person structData, C150StreamSocket *socket);
StructWithArrays readStruct_StructWithArrays(C150StreamSocket *socket);
void sendStruct_StructWithArrays(StructWithArrays structData, C150StreamSocket *socket);
ThreePeople readStruct_ThreePeople(C150StreamSocket *socket);
void sendStruct_ThreePeople(ThreePeople structData, C150StreamSocket *socket);
void readArray_Person_10(Person[10] readArray, C150StreamSocket *socket);
void sendArray_Person_10(Person[10] sendArray, C150StreamSocket *socket);
rectangle readStruct_rectangle(C150StreamSocket *socket);
void sendStruct_rectangle(rectangle structData, C150StreamSocket *socket);
#endif
