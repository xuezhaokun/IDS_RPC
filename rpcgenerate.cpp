#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include "c150exceptions.h"
#include "declarations.h"
#include "functiondeclaration.h"
#include "typedeclaration.h"
using namespace std;

void
generateRPCProxy (FILE *proxyFile, Declarations parseTree);
string
getProxyFunctionPrototype (FunctionDeclaration *functionp);
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
buildReadFunction (string readFunctionName, string arg, string socket);
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

		string headerFileName = "additionalTypeHandler.h";
		string functionFileName = "additionalTypeHandler.cpp";
		string proxy = "test.structs.proxy.cpp";

		string fileBasename = getFileBasename(argv[argnum]);
		string functionFileHeader = fileheaders(fileBasename);
		functionFileHeader = functionFileHeader + "#include \"" + headerFileName + "\"\n";
		string headFileheaders = headerFileheaders();

		FILE* additionalTypeHeader = fopen(headerFileName.c_str(), "w+");
		FILE* additionalTypeFunc = fopen(functionFileName.c_str(), "w+");
		FILE* proxyFile = fopen(proxy.c_str(), "w+");

		fprintf(additionalTypeHeader, "%s\n", headFileheaders.c_str());
		fprintf(additionalTypeFunc, "%s\n", functionFileHeader.c_str());

		generateAdditionalTypeFiles(additionalTypeHeader, additionalTypeFunc, parseTree);
		generateRPCProxy(proxyFile, parseTree);

		fprintf(additionalTypeHeader, "%s\n", "#endif");
		fclose(additionalTypeHeader);
		fclose(additionalTypeFunc);
		fclose(proxyFile);

    }
    return 0;
}

void
generateRPCStud (FILE *stubFile, Declarations parseTree) {
	
}

// For each proxy call, send function name first, 
// then iterate all the arguments, and send corresponding type
// Finally read result
void
generateRPCProxy (FILE *proxyFile, Declarations parseTree) {
	unsigned int argnum;
	std::map<std::string, FunctionDeclaration*>::iterator fiter;  
  	FunctionDeclaration *functionp;

  	for (fiter = parseTree.functions.begin(); fiter != parseTree.functions.end(); ++fiter) {

    	functionp = fiter -> second;
    	string functionName = functionp -> getName();
    	ArgumentVector& args = functionp -> getArgumentVector();
    	string functionReturnType = functionp -> getReturnType() -> getName(); 
    	string functionPrototye = getProxyFunctionPrototype(functionp);
    	fprintf(proxyFile, "%s{\n", functionPrototye.c_str());
		// send function name first
		string sendFunctionNameToSub = "sendFunctionName(RPCPROXYSOCKET, \"" + functionName + "\");";
    	fprintf(proxyFile, "\t%s\n", sendFunctionNameToSub.c_str());

    	for(argnum = 0; argnum < args.size(); argnum++) {
      		Arg_or_Member_Declaration* argp = args[argnum];
      		string argName = argp -> getName();
      		string sendArgToSub = getSendFunctionName(argp -> getType()) + " " + "(RPCPROXYSOCKET, " + argName + ");";
      		fprintf(proxyFile, "\t%s\n", sendArgToSub.c_str());
    	}
    	string returnResult = getReadFunctionName(functionp -> getReturnType()) + "(RPCPROXYSOCKET);";
    	fprintf(proxyFile, "\treturn %s\n}\n", returnResult.c_str());
  	} 
}

string
getProxyFunctionPrototype (FunctionDeclaration *functionp) {
	unsigned int argnum;
	string functionPrototye = "";
	string functionName = functionp -> getName();
    ArgumentVector& args = functionp -> getArgumentVector();
   	string functionReturnType = functionp -> getReturnType() -> getName(); 
   	functionPrototye += functionReturnType + " " + functionName + "(";
   	string arguments = "";

   	for(argnum = 0; argnum<args.size(); argnum++) {
      	Arg_or_Member_Declaration* argp = args[argnum];
      	string argName = argp -> getName();
      	string argType = "";
      	
      	if (argp -> getType() -> isArray()) {
      		argType = buildArrayArgType(argp -> getType());
      	} else {
      		argType = argp -> getType() -> getName();
      	}
      	
      	arguments +=  argType + " " + argName + ", ";
    }
    // remove the last ", "
    arguments = arguments.substr(0, arguments.size() - 2);
    functionPrototye += arguments;
    functionPrototye += ")";

	return functionPrototye;
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
	string tyName = typep -> getName();
	
	string readFunctionName = getReadFunctionName(typep);
	string sendFunctionName = getSendFunctionName(typep);

	string readStructPrototype = tyName + " " + readFunctionName + "(C150StreamSocket *socket)";
	string sendStructPrototype = "void " + sendFunctionName + "(C150StreamSocket *socket, " + tyName + " structData)";
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
		readFunctionName = getReadFunctionName(memp -> getType());
		
		if (memp -> getType() -> isArray()){
			string arg = "result." + mempName;
			readFunction += buildReadFunction(readFunctionName, arg, "socket");
		}else{
			readFunction += "result." + mempName + " = " + buildReadFunction(readFunctionName, "socket");
		}
	}

	sendFunction += "\n}\n";
	readFunction += "return result;\n}\n";
	// write to handler function file
	fprintf(additionalTypeFunc, "%s\n", sendFunction.c_str());
	fprintf(additionalTypeFunc, "%s\n", readFunction.c_str());
}

// handle array type
void 
arrayTypeHandler (FILE *additionalTypeHeader, FILE *additionalTypeFunc, TypeDeclaration* typep) {
	
	string tyName = typep -> getName();
	string readFunctionName = getReadFunctionName(typep);
	string sendFunctionName = getSendFunctionName(typep);
	string arrayArg = buildArrayArgType(typep);

	string readArrayPrototype = "void " + readFunctionName + "(C150StreamSocket *socket, " + arrayArg + ")";
	string sendArrayPrototype = "void " + sendFunctionName + "(C150StreamSocket *socket, " + arrayArg + ")";
	// write to handler header file
	fprintf(additionalTypeHeader, "%s;\n", readArrayPrototype.c_str());
	fprintf(additionalTypeHeader, "%s;\n", sendArrayPrototype.c_str());
	// write to handler function file
	string readFunction = readArrayPrototype + "{\n";
	string sendFunction = sendArrayPrototype + "{\n";

	TypeDeclaration* temp = typep;
	int loop_counter = 0;
	string readItemIter = "";
	string sendItemIter = "";
	string tabs = "\t";
	string closedCurlyBrackets = "";
	while (temp -> isArray()) {
		int bound = temp -> getArrayBound();
		closedCurlyBrackets = tabs + "}\n" + closedCurlyBrackets;
		string iterVar = "i_" + to_string(loop_counter);
		readFunction = readFunction + tabs + "for(int " + iterVar + 
						" = 0; " + iterVar + " < " + to_string(bound) + 
						"; " + iterVar + "++){\n";

		sendFunction = sendFunction + tabs + "for(int " + iterVar + 
						" = 0; " + iterVar + " < " + to_string(bound) + 
						"; " + iterVar + "++){\n";
		readItemIter = readItemIter + "[" + iterVar + "]";
		sendItemIter = sendItemIter + "[" + iterVar + "]";
		temp = temp -> getArrayMemberType();
		loop_counter++;
		tabs += "\t";
	}
	readItemIter = "arrayArg" + readItemIter;
	sendItemIter = "arrayArg" + sendItemIter;

	string readArrayElementName = getReadFunctionName(temp);
	string sendArrayElementName = getSendFunctionName(temp);

	readFunction +=  tabs + readItemIter + " = " + buildReadFunction(readArrayElementName, "socket");
	sendFunction +=  tabs + buildSendFunction(sendArrayElementName, sendItemIter, "socket");
	
	// erase one tab 
	closedCurlyBrackets.erase(0,1);
	
	readFunction = readFunction + closedCurlyBrackets + "\n";
	sendFunction = sendFunction + closedCurlyBrackets + "\n";

	fprintf(additionalTypeFunc, "%s}\n\n", readFunction.c_str());
	fprintf(additionalTypeFunc, "%s}\n\n", sendFunction.c_str());
}

string
buildSendFunction(string sendFunctionName, string arg_or_member, string socket) {
	string sendFunction = sendFunctionName + "(";
	if (sendFunction == "sendvoidType") {
		sendFunction += socket + ");\n\t";
	} else {
		sendFunction += socket + ", " + arg_or_member + ");\n\t";
	}
	return sendFunction;
}

// for non-array type data
string
buildReadFunction (string readFunctionName, string socket){
	string readFunction = readFunctionName + "(" + socket +");\n\t";
	return readFunction;
}

// for arrays
string
buildReadFunction (string readFunctionName, string arg, string socket){
	string readFunction = readFunctionName + "(" + socket + ", " + arg +");\n\t";
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
	string tyName = "";
	TypeDeclaration* temp;
	while (temp -> isArray()) {
		int bound = temp -> getArrayBound();
		tyName += "[" + to_string(bound) + "]";
		temp = temp -> getArrayMemberType();
	}
	tyName = temp -> getName() + " arrayArg" + tyName;
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