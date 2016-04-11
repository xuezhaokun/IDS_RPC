// --------------------------------------------------------------
//
//                        structs.stub.cpp
//
//        Author: Noah Mendelsohn         
//   
//       This is a hand-crafted demonstration stub.
//
//       It implements a very simple protocol that works only
//       for functions with no arguments and void return. Invocation
//       requests are just the null terminated function name; 
//       Responses are the null terminated words DONE or BAD.
//       You'll have to do something much more sophisticated
//       for routines that accept and return values. (And you might
//       not want to use nulls as delimiters in your protocol, since
//       some of the values you send might contain them!)
//
//       For your project, your "rpcgen" program will generate
//       stubs like this one automatically from the idl
//       file. Note that this stub also #includes the 
//       structss.idl file. Of course, your rpcgen
//       program will change that, as well as the number
//       of functions generated. More importantly, it will
//       generate code to handle function arguments and
//       return values.
//
//       You can structure your stub however you like. This
//       one relies on the container to loop calling 
//       dispatchFunction() until eof is reached, but you
//       can do it other ways. In general, there needs to
//       be some place where you read the stream to see
//       which function to call; how you do that is up to you.
//
//       Copyright: 2012 Noah Mendelsohn
//
// --------------------------------------------------------------

// IMPORTANT! WE INCLUDE THE IDL FILE AS IT DEFINES THE INTERFACES
// TO THE FUNCTIONS WE'RE IMPLEMENTING. THIS MAKES SURE THE
// CODE HERE ACTUALLY MATCHES THE REMOTED INTERFACE


#include "rpcstubhelper.h"
#include "basicTypeHandler.h"
#include <cstring>
#include <string>
#include "c150debug.h"

using namespace std; 
using namespace C150NETWORK;  // for all the comp150 utilities 

#include "structs.idl"
#include "structs_additionalTypeHandler.h"
void __area(rectangle r){
  int result = area(r);
  sendintType (RPCSTUBSOCKET, result);
}
void __findPerson(ThreePeople tp){
  Person result = findPerson(tp);
  sendStruct_Person (RPCSTUBSOCKET, result);
}
void __searchRectangles(rectangle rects[200]){
  sendvoidType (RPCSTUBSOCKET);
}
void __badFunction(char *functionName){
  char doneBuffer[5] = "BAD";
   RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
}
void dispatchFunction() {
  char functionNameBuffer[50];
  string functionName = readFunctionName(RPCSTUBSOCKET, functionNameBuffer, sizeof(functionNameBuffer));
  if (!RPCSTUBSOCKET-> eof()) {
    if (strcmp(functionName.c_str(), "area") == 0){
      rectangle r = readStruct_rectangle(RPCSTUBSOCKET);
      __area(r);
    } else if (strcmp(functionName.c_str(), "findPerson") == 0){
      ThreePeople tp = readStruct_ThreePeople(RPCSTUBSOCKET);
      __findPerson(tp);
    } else if (strcmp(functionName.c_str(), "searchRectangles") == 0){
      rectangle rects[200];
    readArray_rectangle_200(RPCSTUBSOCKET, rects);
      __searchRectangles(rects);
    }  else {
      __badFunction(functionNameBuffer);
    }
  }
}
