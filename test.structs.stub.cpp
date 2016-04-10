void __area(rectangle r){
	int result = area(r);
	sendintType (RPCSTUBSOCKET, result);
}
void __findPerson(ThreePeople tp){
	Person result = findPerson(tp);
	sendStruct_Person (RPCSTUBSOCKET, result);
}
void dispatchFunction() {
	char functionNameBuffer[50];
	string functionName = readFunctionName(RPCSTUBSOCKET, functionNameBuffer, sizeof(functionNameBuffer));
	if (!RPCSTUBSOCKET-> eof()) {
	}
}
