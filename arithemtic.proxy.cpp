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
  RPCPROXYSOCKET->write("add", strlen("add")+1); // write function name including null
  uint32_t net_int_x = htonl(x);
  RPCPROXYSOCKET->write((char *) &net_int_x, sizeof(uint32_t));
  uint32_t net_int_y = htonl(y);
  RPCPROXYSOCKET->write((char *) &net_int_y, sizeof(uint32_t));
 
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: add() invocation sent, waiting for response");
  uint32_t net_result;
  RPCPROXYSOCKET->read((char*) &result, sizeof(uint32_t));
  uint32_t host_result = ntohl(net_result);
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: add() successful return from remote call");

  return host_result;
  
}


int subtract(int x, int y) {
  //
  // Send the Remote Call
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: subtract() invoked");
  RPCPROXYSOCKET->write("subtract", strlen("subtract")+1); // write function name including null
  uint32_t net_int_x = htonl(x);
  RPCPROXYSOCKET->write((char *) &net_int_x, sizeof(uint32_t));
  uint32_t net_int_y = htonl(y);
  RPCPROXYSOCKET->write((char *) &net_int_y, sizeof(uint32_t));
 
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: subtract() invocation sent, waiting for response");
  uint32_t net_result;
  RPCPROXYSOCKET->read((char*) &result, sizeof(uint32_t));
  uint32_t host_result = ntohl(net_result);
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: subtract() successful return from remote call");

  return host_result;
}


int multiply(int x, int y) {
  //
  // Send the Remote Call
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: multiply() invoked");
  RPCPROXYSOCKET->write("multiply", strlen("multiply")+1); // write function name including null
  uint32_t net_int_x = htonl(x);
  RPCPROXYSOCKET->write((char *) &net_int_x, sizeof(uint32_t));
  uint32_t net_int_y = htonl(y);
  RPCPROXYSOCKET->write((char *) &net_int_y, sizeof(uint32_t));
 
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: multiply() invocation sent, waiting for response");
  uint32_t net_result;
  RPCPROXYSOCKET->read((char*) &result, sizeof(uint32_t));
  uint32_t host_result = ntohl(net_result);
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: multiply() successful return from remote call");

  return host_result;

}

int divide(int x, int y){
  //
  // Send the Remote Call
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: divide() invoked");
  RPCPROXYSOCKET->write("divide", strlen("divide")+1); // write function name including null
  uint32_t net_int_x = htonl(x);
  RPCPROXYSOCKET->write((char *) &net_int_x, sizeof(uint32_t));
  uint32_t net_int_y = htonl(y);
  RPCPROXYSOCKET->write((char *) &net_int_y, sizeof(uint32_t));
 
  //
  // Read the response
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: divide() invocation sent, waiting for response");
  uint32_t net_result;
  RPCPROXYSOCKET->read((char*) &result, sizeof(uint32_t));
  uint32_t host_result = ntohl(net_result);
  c150debug->printf(C150RPCDEBUG,"arithmetic.proxy.cpp: divide() successful return from remote call");

  return host_result;
}

