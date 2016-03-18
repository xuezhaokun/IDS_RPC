// --------------------------------------------------------------
//
//                        arithmetic.proxy.cpp
//
//        Author: Noah Mendelsohn         
//   
//       This is a hand-crafted demonstration proxy.
//
//       For your project, your "rpcgen" program will generate
//       proxies like this one automatically from the idl
//       file. Note that this proxy also #includes the 
//       arithmetics.idl file. Of course, your rpcgen
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

#include "arithmetic.idl"
#include "rpcproxyhelper.h"
#include "atomicSocketUtils.h"

#include <cstdio>
#include <cstring>
#include <arpa/inet.h>
#include "c150debug.h"

using namespace C150NETWORK;  // for all the comp150 utilities 


int add(int x, int y) {
  //
  // Send the Remote Call
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: add() invoked");
  sendFunctionName(RPCPROXYSOCKET, "add");
  sendIntType(RPCPROXYSOCKET, x);
  sendIntType(RPCPROXYSOCKET, y);
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: add() invocation sent, waiting for response");
  
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: add() successful return from remote call");

  return readIntType(RPCPROXYSOCKET);
  
}


int subtract(int x, int y) {
  //
  // Send the Remote Call
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: subtract() invoked");
  sendFunctionName(RPCPROXYSOCKET, "subtract");
  sendIntType(RPCPROXYSOCKET, x);
  sendIntType(RPCPROXYSOCKET, y);
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: subtract() invocation sent, waiting for response");
  
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: subtract() successful return from remote call");

  return readIntType(RPCPROXYSOCKET);
}


int multiply(int x, int y) {
  //
  // Send the Remote Call
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: multiply() invoked");
  sendFunctionName(RPCPROXYSOCKET, "multiply");
  sendIntType(RPCPROXYSOCKET, x);
  sendIntType(RPCPROXYSOCKET, y);
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: multiply() invocation sent, waiting for response");
  
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: multiply() successful return from remote call");

  return readIntType(RPCPROXYSOCKET);

}

int divide(int x, int y){
  //
  // Send the Remote Call
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: divide() invoked");
  sendFunctionName(RPCPROXYSOCKET, "divide");
  sendIntType(RPCPROXYSOCKET, x);
  sendIntType(RPCPROXYSOCKET, y);
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: divide() invocation sent, waiting for response");
  
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: divide() successful return from remote call");

  return readIntType(RPCPROXYSOCKET);
}

