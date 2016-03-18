#ifndef __ATOMICSOCKETUTILS_H__
#define __ATOMICSOCKETUTILS_H__

#include <cstring>
#include "c150streamsocket.h"

using namespace C150NETWORK;

using namespace std;

void sendStringType (C150StreamSocket *socket, string stringData);
string readStringType (C150StreamSocket *socket);

void sendIntType (C150StreamSocket *socket, int intData);
int readIntType (C150StreamSocket *socket);

void sendVoidType (C150StreamSocket *socket);
void readVoidType (C150StreamSocket *socket);

void sendFloatType (C150StreamSocket *socket, float floatData);
float readFloatType (C150StreamSocket *socket);

void sendFunctionName (C150StreamSocket *socket, const char  *functionName);
string readFunctionName(C150StreamSocket *socket, char *buffer, unsigned int bufSize);
#endif