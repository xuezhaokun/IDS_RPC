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

#include "structs.idl"
#include "rpcstubhelper.h"
#include "atomicSocketUtils.h"
#include <cstring>
#include "c150debug.h"

using namespace C150NETWORK;  // for all the comp150 utilities 

void getFunctionNamefromStream();

// ======================================================================
//                             STUBS
//
//    Each of these is generated to match the signature of the 
//    function for which it is a stub. The names are prefixed with "__"
//    to keep them distinct from the actual routines, which we call!
//
//    Note that when functions take arguments, these are the routines
//    that will read them from the input stream. These routines should
//    be generated dynamically from your rpcgen program (and so should the
//    code above).
//
// ======================================================================
  


void __findPerson(ThreePeople tp) {

  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"structs.stub.cpp: invoking findPerson()");

  //
  // Send the response to the client
  //
  // If func1 returned something other than void, this is
  // where we'd send the return value back.
  //
  c150debug->printf(C150RPCDEBUG,"structs.stub.cpp: returned from  findPerson() -- responding to client");
  Person result = findPerson(tp);
  sendStringType(RPCSTUBSOCKET, result.firstname);
  sendStringType(RPCSTUBSOCKET, result.lastname);
  sendIntType(RPCSTUBSOCKET, result.age);
  //sendFloatType(RPCSTUBSOCKET, result);
  //return result;
}

void __area(rectangle r) {

  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"structs.stub.cpp: invoking area()");

  //
  // Send the response to the client
  //
  // If func2 returned something other than void, this is
  // where we'd send the return value back.
  //
  c150debug->printf(C150RPCDEBUG,"structs.stub.cpp: returned from  area() -- responding to client");
  int result = area(r);
  sendIntType(RPCSTUBSOCKET, result);
  //return result;
}


//
//     __badFunction
//
//   Pseudo-stub for missing functions.
//

void __badFunction(char *functionName) {
  char doneBuffer[5] = "BAD";  // to write magic value DONE + null


  //
  // Send the response to the client indicating bad function
  //

  c150debug->printf(C150RPCDEBUG,"structs.stub.cpp: received call for nonexistent function %s()",functionName);
  RPCSTUBSOCKET->write(doneBuffer, strlen(doneBuffer)+1);
}



// ======================================================================
//
//                        COMMON SUPPORT FUNCTIONS
//
// ======================================================================

// forward declaration
void getFunctionNameFromStream(char *buffer, unsigned int bufSize);



//
//                         dispatchFunction()
//
//   Called when we're ready to read a new invocation request from the stream
//

void dispatchFunction() {


  char functionNameBuffer[50];
  string functionName = readFunctionName(RPCSTUBSOCKET, functionNameBuffer, sizeof(functionNameBuffer));
  
  if (!RPCSTUBSOCKET-> eof()) {
    //string functionName = readFunctionName(RPCSTUBSOCKET, functionNameBuffer);
    if (strcmp(functionName.c_str(), "findPerson") == 0) {
      ThreePeople tp;
      People p1;
      People p2;
      People p3;

      p1.firstname = readStringType(RPCSTUBSOCKET);
      p1.lastname = readStringType(RPCSTUBSOCKET);
      p1.age = readIntType(RPCSTUBSOCKET);

      p2.firstname = readStringType(RPCSTUBSOCKET);
      p2.lastname = readStringType(RPCSTUBSOCKET);
      p2.age = readIntType(RPCSTUBSOCKET);

      p3.firstname = readStringType(RPCSTUBSOCKET);
      p3.lastname = readStringType(RPCSTUBSOCKET);
      p3.age = readIntType(RPCSTUBSOCKET);

      tp.p1 = p1;
      tp.p2 = p2;
      tp.p3 = p3;

      __findPerson(tp);
    } else if (strcmp(functionName.c_str(), "area") == 0) {
      rectangle r;
      r.x = readIntType(RPCSTUBSOCKET);
      r.y = readIntType(RPCSTUBSOCKET);

      __area(r);
    } else {
      __badFunction(functionNameBuffer);
    }
  }
}


