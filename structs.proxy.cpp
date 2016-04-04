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


#include "rpcproxyhelper.h"
#include "basicTypeHandler.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include "c150debug.h"

using namespace std; 
using namespace C150NETWORK;  // for all the comp150 utilities 
#include "structs.idl"
#include "additionalTypeHandler.h"

Person findPerson(ThreePeople tp) {
  //
  // Send the Remote Call
  //
  c150debug->printf(C150RPCDEBUG,"structs.proxy.cpp: add() invoked");
  sendFunctionName(RPCPROXYSOCKET, "findPerson");
  
  /*
  // send p1
  sendstringType(RPCPROXYSOCKET, tp.p1.firstname);
  sendstringType(RPCPROXYSOCKET, tp.p1.lastname);
  sendintType(RPCPROXYSOCKET, tp.p1.age);
  // send p2
  sendstringType(RPCPROXYSOCKET, tp.p2.firstname);
  sendstringType(RPCPROXYSOCKET, tp.p2.lastname);
  sendintType(RPCPROXYSOCKET, tp.p2.age);
  // send p3
  sendstringType(RPCPROXYSOCKET, tp.p3.firstname);
  sendstringType(RPCPROXYSOCKET, tp.p3.lastname);
  sendintType(RPCPROXYSOCKET, tp.p3.age);
  */

  sendStruct_ThreePeople(RPCPROXYSOCKET, tp);

  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"structs.proxy.cpp: add() invocation sent, waiting for response");

  c150debug->printf(C150RPCDEBUG,"structs.proxy.cpp: add() successful return from remote call");
  Person result;
  /*result.firstname = readstringType(RPCPROXYSOCKET);
  result.lastname = readstringType(RPCPROXYSOCKET);
  result.age = readintType(RPCPROXYSOCKET);*/
  result = readStruct_Person(RPCPROXYSOCKET);
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
  /*sendintType(RPCPROXYSOCKET, r.x);
  sendintType(RPCPROXYSOCKET, r.y);*/
  sendStruct_rectangle(RPCPROXYSOCKET, r);
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"structs.proxy.cpp: subtract() invocation sent, waiting for response");

  c150debug->printf(C150RPCDEBUG,"structs.proxy.cpp: subtract() successful return from remote call");

  return readintType(RPCPROXYSOCKET);
}
