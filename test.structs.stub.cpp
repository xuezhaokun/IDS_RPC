void __area(rectangle r){
	int result = area(r);
	sendintType (RPCSTUBSOCKET, result);
}
void __findPerson(ThreePeople tp){
	Person result = findPerson(tp);
	sendStruct_Person (RPCSTUBSOCKET, result);
}
void __searchRectangles(rectangle rects[200]){
	sendvoidType (RPCSTUBSOCKET);
}
void __sqrt(int x, int y){
	int result = sqrt(x, y);
	sendintType (RPCSTUBSOCKET, result);
}
void __takesTwoArrays(int x[24], int y[24]){
	int result = takesTwoArrays(x, y);
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
		if (strcmp(functionName.c_str(), "area") == 0){
			rectangle r = readStruct_rectangle(RPCSTUBSOCKET);
			__area(r);
		} else if (strcmp(functionName.c_str(), "findPerson") == 0){
			ThreePeople tp = readStruct_ThreePeople(RPCSTUBSOCKET);
			__findPerson(tp);
		} else if (strcmp(functionName.c_str(), "searchRectangles") == 0){
			rectangle rects[200];
			readArray_rectangle_200(RPCSTUBSOCKET, rects);
			__searchRectangles(rects);
		} else if (strcmp(functionName.c_str(), "sqrt") == 0){
			int x = readintType(RPCSTUBSOCKET);
			int y = readintType(RPCSTUBSOCKET);
			__sqrt(x, y);
		} else if (strcmp(functionName.c_str(), "takesTwoArrays") == 0){
			int x[24];
			readArray_int_24(RPCSTUBSOCKET, x);
			int y[24];
			readArray_int_24(RPCSTUBSOCKET, y);
			__takesTwoArrays(x, y);
		}  else {
 			__badFunction(functionNameBuffer);
		}
	}
}
