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
int area(rectangle r){
  sendFunctionName(RPCPROXYSOCKET, "area");
  sendStruct_rectangle (RPCPROXYSOCKET, r);
  return readintType(RPCPROXYSOCKET);
}
Person findPerson(ThreePeople tp){
  sendFunctionName(RPCPROXYSOCKET, "findPerson");
  sendStruct_ThreePeople (RPCPROXYSOCKET, tp);
  return readStruct_Person(RPCPROXYSOCKET);
}

