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
void searchRectangles(rectangle rects[200]){
	sendFunctionName(RPCPROXYSOCKET, "searchRectangles");
	sendArray_rectangle_200 (RPCPROXYSOCKET, rects);
	return readvoidType(RPCPROXYSOCKET);
}
int sqrt(int x, int y){
	sendFunctionName(RPCPROXYSOCKET, "sqrt");
	sendintType (RPCPROXYSOCKET, x);
	sendintType (RPCPROXYSOCKET, y);
	return readintType(RPCPROXYSOCKET);
}
int takesTwoArrays(int x[24], int y[24]){
	sendFunctionName(RPCPROXYSOCKET, "takesTwoArrays");
	sendArray_int_24 (RPCPROXYSOCKET, x);
	sendArray_int_24 (RPCPROXYSOCKET, y);
	return readintType(RPCPROXYSOCKET);
}
