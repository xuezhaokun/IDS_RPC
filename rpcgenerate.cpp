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
structTypeHandler (TypeDeclaration* typep, File *additionalTypeHeader, File *additionalTypeFunc);
string
buildSendFunction(string sendFunctionName, string parameters, string socket);
string
buildReadFunction (string readFunctionName, string socket);

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
       	  =----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------.append("#include \"" + fileBasename + ".idl\"\n");
    return header;
}

void
structTypeHandler (TypeDeclaration* typep, File *additionalTypeHeader, File *additionalTypeFunc) {
	unsigned memberNum;
	string tyName = typep -> getName();
	string readFunctionName = "readStruct" + tyName;
	string sendFunctionName = "sendStruct" + tyName;
	string readStructPrototype = tyName + " " + readFunctionName + "(C150StreamSocket *socket)";
	string sendStructPrototype = "void " + sendFunctionName + "(" + tyName + "structData, C150StreamSocket *socket)";
	// write to handler header file
	fprintf(additionalTypeHeader, "%s;\n", readStructPrototype.c_str());
	fprintf(additionalTypeHeader, "%s;\n", sendStructPrototype.c_str());
	// write to handler function file
	string readFunction = readStructPrototype + "{\n\t";
	string sendFunction = sendStructPrototype + "{\n\t";
	readFunction = readFunction + tyName + " result;\n";

	vector<Arg_or_Member_Declaration *>& members = typep -> getStructMembers();
	for(memberNum=0; memberNum < members.size();memberNum++) {
		Arg_or_Member_Declaration* memp = members[memberNum];
		mempName = memp -> getName();
		mempType = memp -> getType() -> getName();
	}
}


string
buildSendFunction(string sendFunctionName, string parameter, string socket) {

}

string
buildReadFunction (string readFunctionName, string socket){
	string readFunction = readFunctionName + "(" + socket +");\n";
	return readFunction;
}



