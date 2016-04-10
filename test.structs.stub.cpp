void __area(rectangle r){
	int result = area(r);
	sendintType (RPCSTUBSOCKET, result);
}
void __findPerson(ThreePeople tp){
	Person result = findPerson(tp);
	sendStruct_Person (RPCSTUBSOCKET, result);
}
