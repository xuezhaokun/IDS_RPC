void sendStruct_Person(Person structData, C150StreamSocket *socket){
	sendstringType(structData.firstname, socket);
	sendstringType(structData.lastname, socket);
	sendintType(structData.age, socket);
	
}

Person readStruct_Person(C150StreamSocket *socket){
	Person result;
	result.firstname = readstringType(socket);
	result.lastname = readstringType(socket);
	result.age = readintType(socket);
	return result;
}

void sendStruct_StructWithArrays(StructWithArrays structData, C150StreamSocket *socket){
	sendintType(structData.aNumber, socket);
	sendArray_Person_10(structData.people, socket);
	
}

StructWithArrays readStruct_StructWithArrays(C150StreamSocket *socket){
	StructWithArrays result;
	result.aNumber = readintType(socket);
	result.people = readArray_Person_10(socket);
	return result;
}

void sendStruct_ThreePeople(ThreePeople structData, C150StreamSocket *socket){
	sendStruct_Person(structData.p1, socket);
	sendStruct_Person(structData.p2, socket);
	sendStruct_Person(structData.p3, socket);
	
}

ThreePeople readStruct_ThreePeople(C150StreamSocket *socket){
	ThreePeople result;
	result.p1 = readStruct_Person(socket);
	result.p2 = readStruct_Person(socket);
	result.p3 = readStruct_Person(socket);
	return result;
}

void readArray_Person_10(Person[10] readArray, C150StreamSocket *socket){
	for(int i_0 = 0; i_0 < 10; i_0++){
		readArray[i_0] = readStruct_Person(socket);
	}
}
void sendArray_Person_10(Person[10] sendArray, C150StreamSocket *socket){
	for(int i_0 = 0; i_0 < 10; i_0++){
		sendStruct_Person(sendArray[i_0], socket);
	}
}
void sendStruct_rectangle(rectangle structData, C150StreamSocket *socket){
	sendintType(structData.x, socket);
	sendintType(structData.y, socket);
	
}

rectangle readStruct_rectangle(C150StreamSocket *socket){
	rectangle result;
	result.x = readintType(socket);
	result.y = readintType(socket);
	return result;
}

