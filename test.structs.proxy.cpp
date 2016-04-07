int area(rectangle r){
	sendFunctionName(RPCPROXYSOCKET, "area");
	sendStruct_rectangle (RPCPROXYSOCKET, r);
	return readintType(RPCPROXYSOCKET);
}
Person findPerson(ThreePeople tp){
	sendFunctionName(RPCPROXYSOCKET, "findPerson");
	sendStruct_ThreePeople (RPCPROXYSOCKET, tp);
	return readStruct_Person(RPCPROXYSOCKET);
}
