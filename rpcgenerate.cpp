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
