// --------------------------------------------------------------
//
//                        structs.proxy.cpp
//
//        Author: Noah Mendelsohn         
//   
//       This is a hand-crafted demonstration proxy.
//
//       For your project, your "rpcgen" program will generate
//       proxies like this one automatically from the idl
//       file. Note that this proxy also #includes the 
//       structss.idl file. Of course, your rpcgen
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

#include "structs.idl"
#include "rpcproxyhelper.h"
#include "atomicSocketUtils.h"

#include <cstdio>
#include <cstring>
#include <arpa/inet.h>
#include "c150debug.h"

using namespace C150NETWORK;  // for all the comp150 utilities 


Person findPerson(ThreePeople tp) {
  //
  // Send the Remote Call
  //
  c150debug->printf(C150RPCDEBUG,"structs.proxy.cpp: add() invoked");
  sendFunctionName(RPCPROXYSOCKET, "findPerson");
  // send p1
  sendStringType(RPCPROXYSOCKET, tp.p1.firstname);
  sendStringType(RPCPROXYSOCKET, tp.p1.lastname);
  sendInrType(RPCPROXYSOCKET, tp.p1.age);
  // send p2
  sendStringType(RPCPROXYSOCKET, tp.p2.firstname);
  sendStringType(RPCPROXYSOCKET, tp.p2.lastname);
  sendInrType(RPCPROXYSOCKET, tp.p2.age);
  // send p3
  sendStringType(RPCPROXYSOCKET, tp.p3.firstname);
  sendStringType(RPCPROXYSOCKET, tp.p3.lastname);
  sendInrType(RPCPROXYSOCKET, tp.p3.age);
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"structs.proxy.cpp: add() invocation sent, waiting for response");

  c150debug->printf(C150RPCDEBUG,"structs.proxy.cpp: add() successful return from remote call");
  People result;
  result.firstname = readStringType(RPCPROXYSOCKET);
  result.lastname = readStringType(RPCPROXYSOCKET);
  result.age = readIntType(RPCPROXYSOCKET);
  //cout << ""
  return result;
  //return readFloatType(RPCPROXYSOCKET);
}


int area(rectangle r) {
  //
  // Send the Remote Call
  //
  c150debug->printf(C150RPCDEBUG,"structs.proxy.cpp: subtract() invoked");
  sendFunctionName(RPCPROXYSOCKET, "area");
  sendIntType(RPCPROXYSOCKET, r.x);
  sendIntType(RPCPROXYSOCKET, r.y);
 
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"structs.proxy.cpp: subtract() invocation sent, waiting for response");

  c150debug->printf(C150RPCDEBUG,"structs.proxy.cpp: subtract() successful return from remote call");

  return readIntType(RPCPROXYSOCKET);
}
