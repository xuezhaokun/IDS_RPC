#ifndef __ADDITIONALTYPE_H_INCLUDED__
#define __ADDITIONALTYPE_H_INCLUDED__
#include <string>
#include "c150streamsocket.h"
using namespace C150NETWORK;
using namespace std;

Person readStruct_Person(C150StreamSocket *socket);
void sendStruct_Person(C150StreamSocket *socket, Person structData);
ThreePeople readStruct_ThreePeople(C150StreamSocket *socket);
void sendStruct_ThreePeople(C150StreamSocket *socket, ThreePeople structData);
rectangle readStruct_rectangle(C150StreamSocket *socket);
void sendStruct_rectangle(C150StreamSocket *socket, rectangle structData);
#endif
