void __area(rectangle r){
	int result = area(r);
	sendintType (RPCSTUBSOCKET, result);
}
void __findPerson(ThreePeople tp){
	Person result = findPerson(tp);
	sendStruct_Person (RPCSTUBSOCKET, result);
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
		}  else {
 			__badFunction(functionNameBuffer);
		}
	}
}
