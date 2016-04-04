#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <string>
#include "c150exceptions.h"
#include "declarations.h"
#include "functiondeclaration.h"
#include "typedeclaration.h"
using namespace std;

void 
generateAdditionalTypeFiles (FILE *additionalTypeHeader, FILE *additionalTypeFunc, Declarations parseTree);
void
structTypeHandler (FILE *additionalTypeHeader, FILE *additionalTypeFunc, TypeDeclaration* typep);
void 
arrayTypeHandler (FILE *additionalTypeHeader, FILE *additionalTypeFunc, TypeDeclaration* typep);
string
buildSendFunction(string sendFunctionName, string arg_or_member, string socket);
string
buildReadFunction (string readFunctionName, string socket);
string
buildArrayFunctionType (TypeDeclaration* typep);
string
buildArrayArgType (TypeDeclaration* typep);
string 
getSendFunctionName (TypeDeclaration* typep);
string 
getReadFunctionName (TypeDeclaration* typep);
string
getFileBasename (const char *filename);
vector<string> 
&split(const string &s, char delim, vector<string> &elems);
vector<string> 
split(const string &s, char delim);
string 
fileheaders(string fileBasename);
string
headerFileheaders ();

int 
main(int argc, char const *argv[])
{
	int argnum;

    //
    // Check argument count
    //
    if (argc < 2) {
      fprintf(stderr, "Syntax: %s  idlfile1 [idlfile...]*\n", argv[0]);
      exit (8);
    };

  	for (argnum = 1; argnum < argc; argnum ++) {
    	//string fileBasename = getFileBasename(argv[argnum]);
    	//cout << "basename is " << fileBasename << endl;
    	//cout << "commonheader is " << fileheaders(fileBasename) << endl;
    
		//
		// Open the file
		//
		ifstream idlFile(argv[argnum]);        // open

		if (!idlFile.is_open()) {
			stringstream ss;
			ss << "Could not open IDL file: " << argv[argnum];
			throw C150Exception(ss.str());
		}

		Declarations parseTree(idlFile);

		string headerFileName = "additionalTypeHeader.h";
		string functionFileName = "additionalTypeFunc.cpp";

		string fileBasename = getFileBasename(argv[argnum]);
		string functionFileHeader = fileheaders(fileBasename);
		functionFileHeader = "#include \"" + headerFileName + "\"\n" + functionFileHeader;
		string headFileheaders = headerFileheaders();

		FILE* additionalTypeHeader = fopen(headerFileName.c_str(), "w+");
		FILE* additionalTypeFunc = fopen(functionFileName.c_str(), "w+");

		fprintf(additionalTypeHeader, "%s\n", headFileheaders.c_str());
		fprintf(additionalTypeFunc, "%s\n", functionFileHeader.c_str());

		generateAdditionalTypeFiles(additionalTypeHeader, additionalTypeFunc, parseTree);
		
		fprintf(additionalTypeHeader, "%s\n", "#endif");
		fclose(additionalTypeHeader);
		fclose(additionalTypeFunc);

    }
    return 0;
}

// generate additional helper functions for array and strcut type
void 
generateAdditionalTypeFiles (FILE *additionalTypeHeader, FILE *additionalTypeFunc, Declarations parseTree) {
	std::map<std::string, TypeDeclaration*>::iterator iter;

    TypeDeclaration *typep;

    for (iter = parseTree.types.begin(); iter != parseTree.types.end(); ++iter) {
        
        typep = iter->second;
        
        if(typep->isStruct()) {
            structTypeHandler(additionalTypeHeader, additionalTypeFunc, typep);
        } else if(typep->isArray()) {
            arrayTypeHandler(additionalTypeHeader, additionalTypeFunc, typep);
        }
    }
}

// handle struct
void
structTypeHandler (FILE *additionalTypeHeader, FILE *additionalTypeFunc, TypeDeclaration* typep) {
	unsigned memberNum;
	//FILE* additionalTypeHeader = fopen("additionalTypeHeader.h", "w+");
	//FILE* additionalTypeFunc = fopen("additionalTypeFunc.cpp", "w+");
	string tyName = typep -> getName();
	
	string readFunctionName = getReadFunctionName(typep);
	string sendFunctionName = getSendFunctionName(typep);

	string readStructPrototype = tyName + " " + readFunctionName + "(C150StreamSocket *socket)";
	string sendStructPrototype = "void " + sendFunctionName + "(" + tyName + " structData, C150StreamSocket *socket)";
	// write to handler header file
	fprintf(additionalTypeHeader, "%s;\n", readStructPrototype.c_str());
	fprintf(additionalTypeHeader, "%s;\n", sendStructPrototype.c_str());
	// write to handler function file
	string readFunction = readStructPrototype + "{\n\t";
	string sendFunction = sendStructPrototype + "{\n\t";
	readFunction = readFunction + tyName + " result;\n\t";

	vector<Arg_or_Member_Declaration *>& members = typep -> getStructMembers();
	for(memberNum=0; memberNum < members.size();memberNum++) {
		Arg_or_Member_Declaration* memp = members[memberNum];
		string mempName = memp -> getName();
		string mempType = memp -> getType() -> getName();

		// send function
		sendFunctionName = getSendFunctionName(memp -> getType());
		string sendParam = "structData." + mempName;
		sendFunction += buildSendFunction(sendFunctionName, sendParam, "socket");

		//read function

		readFunction += "result." + mempName + " = ";
		readFunctionName = getReadFunctionName(memp -> getType());
		readFunction += buildReadFunction(readFunctionName, "socket");
	}

	sendFunction += "\n}\n";
	readFunction += "return result;\n}\n";
	// write to handler function file
	fprintf(additionalTypeFunc, "%s\n", sendFunction.c_str());
	fprintf(additionalTypeFunc, "%s\n", readFunction.c_str());
	//fclose(additionalTypeHeader);
	//fclose(additionalTypeFunc);
}

// handle array type
void 
arrayTypeHandler (FILE *additionalTypeHeader, FILE *additionalTypeFunc, TypeDeclaration* typep) {
	//unsigned memberNum;
	//FILE* additionalTypeHeader = fopen("additionalTypeHeader.h", "w+");
	//FILE* additionalTypeFunc = fopen("additionalTypeFunc.cpp", "w+");
	string tyName = typep -> getName();
	string readFunctionName = getReadFunctionName(typep);
	string sendFunctionName = getSendFunctionName(typep);
	string arrayArg = buildArrayArgType(typep);

	string readArrayPrototype = "void " + readFunctionName + "(" + arrayArg + " readArray, C150StreamSocket *socket)";
	string sendArrayPrototype = "void " + sendFunctionName + "(" + arrayArg + " sendArray, C150StreamSocket *socket)";
	// write to handler header file
	fprintf(additionalTypeHeader, "%s;\n", readArrayPrototype.c_str());
	fprintf(additionalTypeHeader, "%s;\n", sendArrayPrototype.c_str());
	// write to handler function file
	string readFunction = readArrayPrototype + "{\n\t";
	string sendFunction = sendArrayPrototype + "{\n\t";

	TypeDeclaration* temp = typep;
	int loop_counter = 0;
	string readItemIter = "";
	string sendItemIter = "";

	while (temp -> isArray()) {
		int bound = temp -> getArrayBound();

		string iterVar = "i_" + to_string(loop_counter);
		readFunction = readFunction + "for(int " + iterVar + 
						" = 0; " + iterVar + " < " + to_string(bound) + 
						"; " + iterVar + "++){\n\t\t";

		sendFunction = sendFunction + "for(int " + iterVar + 
						" = 0; " + iterVar + " < " + to_string(bound) + 
						"; " + iterVar + "++){\n\t\t";
		readItemIter = readItemIter + "[" + iterVar + "]";
		sendItemIter = sendItemIter + "[" + iterVar + "]";
		temp = temp -> getArrayMemberType();
		loop_counter++;
	}
	readItemIter = "readArray" + readItemIter;
	sendItemIter = "sendArray" + sendItemIter;

	string readArrayElementName = getReadFunctionName(temp);
	string sendArrayElementName = getSendFunctionName(temp);

	readFunction = readFunction + readItemIter + " = " + buildReadFunction(readArrayElementName, "socket");
	sendFunction = sendFunction + buildSendFunction(sendArrayElementName, sendItemIter, "socket");

	readFunction = readFunction + "}\n";
	sendFunction = sendFunction + "}\n";

	fprintf(additionalTypeFunc, "%s}\n", readFunction.c_str());
	fprintf(additionalTypeFunc, "%s}\n", sendFunction.c_str());
	
	//fclose(additionalTypeHeader);
	//fclose(additionalTypeFunc);
}

string
buildSendFunction(string sendFunctionName, string arg_or_member, string socket) {
	string sendFunction = sendFunctionName + "(";
	if (sendFunction == "sendvoidType") {
		sendFunction += socket + ");\n\t";
	} else {
		sendFunction += arg_or_member + ", " + socket + ");\n\t";
	}
	return sendFunction;
}

string
buildReadFunction (string readFunctionName, string socket){
	string readFunction = readFunctionName + "(" + socket +");\n\t";
	return readFunction;
}

string
buildArrayFunctionType (TypeDeclaration* typep) {
	string tyName;
	TypeDeclaration* temp;
	while (temp -> isArray()) {
		int bound = temp -> getArrayBound();
		tyName += "_" + to_string(bound);
		temp = temp -> getArrayMemberType();
	}
	tyName = temp -> getName() + tyName;
	return tyName;
}

string
buildArrayArgType (TypeDeclaration* typep) {
	string tyName;
	TypeDeclaration* temp;
	while (temp -> isArray()) {
		int bound = temp -> getArrayBound();
		tyName += "[" + to_string(bound) + "]";
		temp = temp -> getArrayMemberType();
	}
	tyName = temp -> getName() + tyName;
	return tyName;
}

string 
getSendFunctionName (TypeDeclaration* typep) {
	string sendFunctionName = "send";
	string tyName = typep -> getName();
	if (typep -> isStruct()) {
		sendFunctionName += "Struct_" + tyName;
	} else if (typep -> isArray()) {
		tyName = buildArrayFunctionType(typep);
		sendFunctionName += "Array_" + tyName;
	} else {
		sendFunctionName += tyName + "Type";
	}
	return sendFunctionName;
}

string 
getReadFunctionName (TypeDeclaration* typep) {
	string readFunctionName = "read";
	string tyName = typep -> getName();
	if (typep -> isStruct()) {
		readFunctionName += "Struct_" + tyName;
	} else if (typep -> isArray()) {
		tyName = buildArrayFunctionType(typep);
		readFunctionName += "Array_" + tyName;
	} else {
		readFunctionName += tyName + "Type";
	}
	return readFunctionName;
}

string 
getFileBasename (const char *filename) {
	string stringFilename(filename);
 	vector<string> tokens = split(stringFilename, '.');
 	if(tokens.at(1) != "idl"){
 		fprintf(stderr, "Input file type should be .idl, wrong file type: %s\n", filename);
    	exit (0);
    }
	return tokens.at(0);
}

// REFERENCE from StackOverFlow
vector<string> 
&split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
vector<string> 
split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

string 
fileheaders (string fileBasename) {
    string header = "";
    header.append("#include \"c150debug.h\"\n")
          .append("#include \"rpcproxyhelper.h\"\n")
       	  .append("#include \"basicTypeHandler.h\"\n") 
          .append("#include <fstream>\n")
          .append("#include <cstdio>\n")
       	  .append("#include <cstring>\n")
       	  .append("#include <string>\n")
       	  .append("#include <fstream>\n")
       	  .append("#include <arpa/inet.h>\n") 
       	  .append("using namespace C150NETWORK;\n")
       	  .append("using namespace std;\n")
       	  .append("#include \"" + fileBasename + ".idl\"\n");
    return header;
}

string
headerFileheaders () {
	string header = "";
	header.append("#ifndef __ADDITIONALTYPE_H_INCLUDED__\n")
		  .append("#define __ADDITIONALTYPE_H_INCLUDED__\n")
		  .append("#include <string>\n")
		  .append("#include \"c150streamsocket.h\"\n")
       	  .append("using namespace C150NETWORK;\n")
       	  .append("using namespace std;\n");
    return header;
}