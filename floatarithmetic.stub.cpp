// --------------------------------------------------------------
//
//                        floatarithmetic.stub.cpp
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
//       floatarithmetics.idl file. Of course, your rpcgen
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

#include "floatarithmetic.idl"
#include "rpcstubhelper.h"
#include "basicTypeHandler.h"

#include <cstdio>
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
  


float __add(float x, float y) {

  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: invoking add()");

  //
  // Send the response to the client
  //
  // If func1 returned something other than void, this is
  // where we'd send the return value back.
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: returned from  add() -- responding to client");
  float result = add(x, y);
  sendFloatType(RPCSTUBSOCKET, result);
  return result;
}

float __subtract(float x, float y) {

  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: invoking subtract()");

  //
  // Send the response to the client
  //
  // If func2 returned something other than void, this is
  // where we'd send the return value back.
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: returned from  subtract() -- responding to client");
  float result = subtract(x, y);
  sendFloatType(RPCSTUBSOCKET, result);
  return result;
}

float __multiply(float x, float y) {
  //char doneBuffer[5] = "DONE";  // to write magic value DONE + null

  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: invoking multiply()");
  //multiply(x, y);

  //
  // Send the response to the client
  //
  // If func3 returned something other than void, this is
  // where we'd send the return value back.
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: returned from  multiply() -- responding to client");
  float result = multiply(x, y);
  sendFloatType(RPCSTUBSOCKET, result);
  return result;
}


float __divide(float x, float y) {
  //char doneBuffer[5] = "DONE";  // to write magic value DONE + null

  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: invoking divide()");


  //
  // Send the response to the client
  //
  // If func3 returned something other than void, this is
  // where we'd send the return value back.
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: returned from  divide() -- responding to client");
  float result = divide(x, y);
  sendFloatType(RPCSTUBSOCKET, result);
  return result;
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

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.stub.cpp: received call for nonexistent function %s()",functionName);
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
    if (strcmp(functionName.c_str(), "add") == 0) {
      float host_float_x = readFloatType(RPCSTUBSOCKET);
      float host_float_y = readFloatType(RPCSTUBSOCKET);

      __add(host_float_x, host_float_y);
    } else if (strcmp(functionName.c_str(), "subtract") == 0) {
      float host_float_x = readFloatType(RPCSTUBSOCKET);
      float host_float_y = readFloatType(RPCSTUBSOCKET);

      __subtract(host_float_x, host_float_y);
    } else if (strcmp(functionName.c_str(), "multiply") == 0) {
      float host_float_x = readFloatType(RPCSTUBSOCKET);
      float host_float_y = readFloatType(RPCSTUBSOCKET);

      __multiply(host_float_x, host_float_y);
    } else if (strcmp(functionName.c_str(), "divide") == 0) {
      float host_float_x = readFloatType(RPCSTUBSOCKET);
      float host_float_y = readFloatType(RPCSTUBSOCKET);

      __divide(host_float_x, host_float_y);
    } else {
      __badFunction(functionNameBuffer);
    }
  }
}


