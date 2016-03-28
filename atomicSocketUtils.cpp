#include "atomicSocketUtils.h"
#include "c150debug.h"
#include "c150streamsocket.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <arpa/inet.h>

using namespace C150NETWORK;
using namespace std;

void sendStringType (C150StreamSocket *socket, string stringData) {
	socket->write(stringData.c_str(), stringData.length() + 1);
}

string readStringType (C150StreamSocket *socket) {
	char readBuffer[512];
	ssize_t readlen; 
	readlen = socket->read(readBuffer, sizeof(readBuffer) - 1);
	readBuffer[readlen] = '\0';
	string stringData(readBuffer);
  cout << "read: " << stringData << endl;
	return stringData;
}

void sendIntType (C150StreamSocket *socket, int intData) {
	uint32_t netIntData = htonl(intData);
    socket->write((char*) &netIntData, sizeof(uint32_t));
}

int readIntType (C150StreamSocket *socket) {
    uint32_t netIntData;
    socket->read((char*) &netIntData, sizeof(uint32_t));
    uint32_t hostIntData = ntohl(netIntData);
    return hostIntData;
}

void sendVoidType (C150StreamSocket *socket) {
	sendIntType(socket, 0);
}

void readVoidType (C150StreamSocket *socket) {
	readIntType(socket);
}

void sendFloatType (C150StreamSocket *socket, float floatData) {
	char floatBuffer[20];
	sprintf(floatBuffer, "%f", floatData);
	socket->write(floatBuffer, 20);
}

float readFloatType (C150StreamSocket *socket) {
	char floatBuffer[20];
	socket->read(floatBuffer, 20);
	float floatData = atof(floatBuffer);
	return floatData;
}

void sendFunctionName (C150StreamSocket *socket, const char  *functionName) {
    socket->write(functionName, strlen(functionName) + 1);
}

string readFunctionName(C150StreamSocket *socket, char *buffer, unsigned int bufSize) {
  	unsigned int i;
 	char *bufp;    // next char to read
  	bool readnull;
  	ssize_t readlen;             // amount of data read from socket
  
  	//
  	// Read a message from the stream
  	// -1 in size below is to leave room for null
  	//
  	readnull = false;
  	bufp = buffer;
  	for (i=0; i< bufSize; i++) {
   		readlen = socket-> read(bufp, 1);  // read a byte
    	// check for eof or error
    	if (readlen == 0) {
      		break;
    	}
    	// check for null and bump buffer pointer
    	if (*bufp++ == '\0') {
     		readnull = true;
      		break;
    	}
  	}
  
  	//
  	// With TCP streams, we should never get a 0 length read
  	// except with timeouts (which we're not setting in pingstreamserver)
  	// or EOF
  	//
  	if (readlen == 0) {
    	c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub: read zero length message, checking EOF");
    	if (socket-> eof()) {
      	c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub: EOF signaled on input");

    	} else {
      	throw C150Exception("floatarithmetic.stub: unexpected zero length read without eof");
    	}
  	}

  	//
  	// If we didn't get a null, input message was poorly formatted
  	//
  	else if(!readnull) 
    	throw C150Exception("floatarithmetic.stub: method name not null terminated or too long");

  
  	//
  	// Note that eof may be set here for our caller to check
  	//
	string functionName(buffer);
	return functionName;
}
