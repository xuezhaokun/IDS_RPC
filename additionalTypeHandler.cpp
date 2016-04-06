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

void sendStruct_MT(C150StreamSocket *socket, MT structData){
	
}

MT readStruct_MT(C150StreamSocket *socket){
	MT result;
	return result;
}

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

void sendStruct_StructWithArrays(C150StreamSocket *socket, StructWithArrays structData){
	sendintType(socket, structData.aNumber);
	sendArray_Person_10(socket, structData.people);
	
}

StructWithArrays readStruct_StructWithArrays(C150StreamSocket *socket){
	StructWithArrays result;
	result.aNumber = readintType(socket);
	readArray_Person_10(socket, result.people);
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

void readArray_Person_10(C150StreamSocket *socket, Person arrayArg[10]){
	for(int i_0 = 0; i_0 < 10; i_0++){
		arrayArg[i_0] = readStruct_Person(socket);
	}

}

void sendArray_Person_10(C150StreamSocket *socket, Person arrayArg[10]){
	for(int i_0 = 0; i_0 < 10; i_0++){
		sendStruct_Person(socket, arrayArg[i_0]);
	}

}

void readArray_int_100(C150StreamSocket *socket, int arrayArg[100]){
	for(int i_0 = 0; i_0 < 100; i_0++){
		arrayArg[i_0] = readintType(socket);
	}

}

void sendArray_int_100(C150StreamSocket *socket, int arrayArg[100]){
	for(int i_0 = 0; i_0 < 100; i_0++){
		sendintType(socket, arrayArg[i_0]);
	}

}

void readArray_int_10(C150StreamSocket *socket, int arrayArg[10]){
	for(int i_0 = 0; i_0 < 10; i_0++){
		arrayArg[i_0] = readintType(socket);
	}

}

void sendArray_int_10(C150StreamSocket *socket, int arrayArg[10]){
	for(int i_0 = 0; i_0 < 10; i_0++){
		sendintType(socket, arrayArg[i_0]);
	}

}

void readArray_int_10_100(C150StreamSocket *socket, int arrayArg[10][100]){
	for(int i_0 = 0; i_0 < 10; i_0++){
		for(int i_1 = 0; i_1 < 100; i_1++){
			arrayArg[i_0][i_1] = readintType(socket);
		}
	}

}

void sendArray_int_10_100(C150StreamSocket *socket, int arrayArg[10][100]){
	for(int i_0 = 0; i_0 < 10; i_0++){
		for(int i_1 = 0; i_1 < 100; i_1++){
			sendintType(socket, arrayArg[i_0][i_1]);
		}
	}

}

void readArray_int_4(C150StreamSocket *socket, int arrayArg[4]){
	for(int i_0 = 0; i_0 < 4; i_0++){
		arrayArg[i_0] = readintType(socket);
	}

}

void sendArray_int_4(C150StreamSocket *socket, int arrayArg[4]){
	for(int i_0 = 0; i_0 < 4; i_0++){
		sendintType(socket, arrayArg[i_0]);
	}

}

void readArray_int_4_10(C150StreamSocket *socket, int arrayArg[4][10]){
	for(int i_0 = 0; i_0 < 4; i_0++){
		for(int i_1 = 0; i_1 < 10; i_1++){
			arrayArg[i_0][i_1] = readintType(socket);
		}
	}

}

void sendArray_int_4_10(C150StreamSocket *socket, int arrayArg[4][10]){
	for(int i_0 = 0; i_0 < 4; i_0++){
		for(int i_1 = 0; i_1 < 10; i_1++){
			sendintType(socket, arrayArg[i_0][i_1]);
		}
	}

}

void readArray_int_4_10_100(C150StreamSocket *socket, int arrayArg[4][10][100]){
	for(int i_0 = 0; i_0 < 4; i_0++){
		for(int i_1 = 0; i_1 < 10; i_1++){
			for(int i_2 = 0; i_2 < 100; i_2++){
				arrayArg[i_0][i_1][i_2] = readintType(socket);
			}
		}
	}

}

void sendArray_int_4_10_100(C150StreamSocket *socket, int arrayArg[4][10][100]){
	for(int i_0 = 0; i_0 < 4; i_0++){
		for(int i_1 = 0; i_1 < 10; i_1++){
			for(int i_2 = 0; i_2 < 100; i_2++){
				sendintType(socket, arrayArg[i_0][i_1][i_2]);
			}
		}
	}

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

void sendStruct_s(C150StreamSocket *socket, s structData){
	sendArray_int_4(socket, structData.m1);
	sendArray_int_4_10(socket, structData.m2);
	sendArray_int_4_10_100(socket, structData.m3);
	
}

s readStruct_s(C150StreamSocket *socket){
	s result;
	readArray_int_4(socket, result.m1);
	readArray_int_4_10(socket, result.m2);
	readArray_int_4_10_100(socket, result.m3);
	return result;
}

