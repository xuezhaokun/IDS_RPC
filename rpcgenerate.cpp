#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include "c150exceptions.h"
#include "declarations.h"
#include "functiondeclaration.h"
#include "typedeclaration.h"
using namespace std;

vector<string> 
&split(const string &s, char delim, vector<string> &elems);
vector<string> 
split(const string &s, char delim);
string
getFileBasename (const char *filename);
string 
fileheaders(string fileBasename);
void
structTypeHandler (TypeDeclaration* typep);
string
buildSendFunction(string sendFunctionName, string parameters, string socket);
string
buildReadFunction (string readFunctionName, string socket);
string 
getSendFunctionName (TypeDeclaration* typep);
string 
getReadFunctionName (TypeDeclaration* typep);

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
    	string fileBasename = getFileBasename(argv[argnum]);
    	cout << "basename is " << fileBasename << endl;
    	cout << "commonheader is " << fileheaders(fileBasename) << endl;
    }
    //FILE* additionalTypeHeader = fopen("additionalTypeHeader.h").c_str(), "w+");
    //FILE* additionalTypeFunc = fopen("additionalTypeFunc.cpp").c_str(), "w+");

    return 0;
}

string 
getFileBasename (const char *filename){
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
fileheaders(string fileBasename) {
    string header = "";
    header.append("#include \"c150debug.h\"\n")
          .append("#include \"rpcproxyhelper.h\"\n")
       	  .append("#include \"atomicSocketUtils.h\"\n") 
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

void
structTypeHandler (TypeDeclaration* typep) {
	unsigned memberNum;
	FILE* additionalTypeHeader = fopen("additionalTypeHeader.h", "w+");
	FILE* additionalTypeFunc = fopen("additionalTypeFunc.cpp", "w+");
	string tyName = typep -> getName();
	string readFunctionName = getSendFunctionName(typep);
	string sendFunctionName = getReadFunctionName(typep);
	string readStructPrototype = tyName + " " + readFunctionName + "(C150StreamSocket *socket)";
	string sendStructPrototype = "void " + sendFunctionName + "(" + tyName + "structData, C150StreamSocket *socket)";
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

	sendFunction += "}\n";
	readFunction += "\t return result;\n}\n";
	// write to handler function file
	fprintf(additionalTypeFunc, "%s;\n", sendFunction.c_str());
	fprintf(additionalTypeFunc, "%s;\n", readFunction.c_str());
	fclose(additionalTypeHeader);
	fclose(additionalTypeFunc);
}


string
buildSendFunction(string sendFunctionName, string arg_or_member, string socket) {
	string sendFunction = sendFunctionName + "(";
	if (sendFunction == "sendvoidType") {
		sendFunction += socket + ");\n";
	} else {
		sendFunction += arg_or_member + ", " + socket + ");\n";
	}
	return sendFunction;
}

string
buildReadFunction (string readFunctionName, string socket){
	string readFunction = readFunctionName + "(" + socket +");\n";
	return readFunction;
}

string 
getSendFunctionName (TypeDeclaration* typep) {
	string sendFunctionName = "send";
	string tyName = typep -> getName();
	if (typep -> isStruct()) {
		sendFunctionName += "Struct" + tyName;
	} else {
		sendFunctionName += tyName + "Type";
	}
	return tyName;
}

string 
getReadFunctionName (TypeDeclaration* typep) {
	string readFunctionName = "read";
	string tyName = typep -> getName();
	if (typep -> isStruct()) {
		readFunctionName += "Struct" + tyName;
	} else {
		readFunctionName += tyName + "Type";
	}
	return tyName;
}