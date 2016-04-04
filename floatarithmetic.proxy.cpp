// --------------------------------------------------------------
//
//                        floatarithmetic.proxy.cpp
//
//        Author: Noah Mendelsohn         
//   
//       This is a hand-crafted demonstration proxy.
//
//       For your project, your "rpcgen" program will generate
//       proxies like this one automatically from the idl
//       file. Note that this proxy also #includes the 
//       floatarithmetics.idl file. Of course, your rpcgen
//       program will change that, as well as the number
//       of functions generated. More importantly, it will
//       generate code to handle function arguments and
//       return values.
//
//
//
//       Copyright: 2012 Noah Mendelsohn
//     
// --------------------------------------------------------------

// IMPORTANT! WE INCLUDE THE IDL FILE AS IT DEFINES THE INTERFACES
// TO THE FUNCTIONS WE'RE IMPLEMENTING. THIS MAKES SURE THE
// CODE HERE ACTUALLY MATCHES THE REMOTED INTERFACE

#include "floatarithmetic.idl"
#include "rpcproxyhelper.h"
#include "basicTypeHandler.h"

#include <cstdio>
#include <cstring>
#include <arpa/inet.h>
#include "c150debug.h"

using namespace C150NETWORK;  // for all the comp150 utilities 


float add(float x, float y) {
  //
  // Send the Remote Call
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: add() invoked");
  sendFunctionName(RPCPROXYSOCKET, "add");
  sendfloatType(RPCPROXYSOCKET, x);
  sendfloatType(RPCPROXYSOCKET, y);
 
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: add() invocation sent, waiting for response");

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: add() successful return from remote call");

  return readfloatType(RPCPROXYSOCKET);
}


float subtract(float x, float y) {
  //
  // Send the Remote Call
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: subtract() invoked");
  sendFunctionName(RPCPROXYSOCKET, "subtract");
  sendfloatType(RPCPROXYSOCKET, x);
  sendfloatType(RPCPROXYSOCKET, y);
 
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: subtract() invocation sent, waiting for response");

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: subtract() successful return from remote call");

  return readfloatType(RPCPROXYSOCKET);
}


float multiply(float x, float y) {
  //
  // Send the Remote Call
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: multiply() invoked");
  sendFunctionName(RPCPROXYSOCKET, "multiply");
  sendfloatType(RPCPROXYSOCKET, x);
  sendfloatType(RPCPROXYSOCKET, y);
 
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: multiply() invocation sent, waiting for response");

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: multiply() successful return from remote call");

  return readfloatType(RPCPROXYSOCKET);
}

float divide(float x, float y){
  //
  // Send the Remote Call
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: divide() invoked");
  sendFunctionName(RPCPROXYSOCKET, "divide");
  sendfloatType(RPCPROXYSOCKET, x);
  sendfloatType(RPCPROXYSOCKET, y);
 
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: divide() invocation sent, waiting for response");

  c150debug->printf(C150RPCDEBUG,"floatarithmetic.proxy.cpp: divide() successful return from remote call");

  return readfloatType(RPCPROXYSOCKET);
}

