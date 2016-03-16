// --------------------------------------------------------------
//
//                        arithmetic.stub.cpp
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
//       arithmetics.idl file. Of course, your rpcgen
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

#include "arithmetic.idl"

#include "rpcstubhelper.h"

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
  


int __add(int x, int y) {

  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.stub.cpp: invoking add()");

  //
  // Send the response to the client
  //
  // If func1 returned something other than void, this is
  // where we'd send the return value back.
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.stub.cpp: returned from  add() -- responding to client");
  int result = add(x, y);
  uint32_t net_result = htonl(result);
  RPCSTUBSOCKET->write((char*) &net_result, sizeof(uint32_t));
  return result;
}

int __subtract(int x, int y) {

  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.stub.cpp: invoking subtract()");

  //
  // Send the response to the client
  //
  // If func2 returned something other than void, this is
  // where we'd send the return value back.
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.stub.cpp: returned from  subtract() -- responding to client");
  int result = subtract(x, y);
  uint32_t net_result = htonl(result);
  RPCSTUBSOCKET->write((char*) &net_result, sizeof(uint32_t));
  return result;
}

int __multiply(int x, int y) {
  //char doneBuffer[5] = "DONE";  // to write magic value DONE + null

  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.stub.cpp: invoking multiply()");
  //multiply(x, y);

  //
  // Send the response to the client
  //
  // If func3 returned something other than void, this is
  // where we'd send the return value back.
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.stub.cpp: returned from  multiply() -- responding to client");
  int result = multiply(x, y);
  uint32_t net_result = htonl(result);
  RPCSTUBSOCKET->write((char*) &net_result, sizeof(uint32_t));
  return result;
}


int __divide(int x, int y) {
  //char doneBuffer[5] = "DONE";  // to write magic value DONE + null

  //
  // Time to actually call the function 
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.stub.cpp: invoking divide()");


  //
  // Send the response to the client
  //
  // If func3 returned something other than void, this is
  // where we'd send the return value back.
  //
  c150debug->printf(C150RPCDEBUG,"arithmetic.stub.cpp: returned from  divide() -- responding to client");
  int result = divide(x, y);
  uint32_t net_result = htonl(result);
  RPCSTUBSOCKET->write((char*) &net_result, sizeof(uint32_t));
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

  c150debug->printf(C150RPCDEBUG,"arithmetic.stub.cpp: received call for nonexistent function %s()",functionName);
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

  //
  // Read the function name from the stream -- note
  // REPLACE THIS WITH YOUR OWN LOGIC DEPENDING ON THE 
  // WIRE FORMAT YOU USE
  //
  getFunctionNameFromStream(functionNameBuffer,sizeof(functionNameBuffer));

  //
  // We've read the function name, call the stub for the right one
  // The stub will invoke the function and send response.
  //

  if (!RPCSTUBSOCKET-> eof()) {
    if (strcmp(functionNameBuffer, "add") == 0) {
      uint32_t net_int_x;
      RPCSTUBSOCKET->read((char*) &net_int_x, sizeof(uint32_t));
      uint32_t host_int_x = ntohl(net_int_x);

      uint32_t net_int_y;
      RPCSTUBSOCKET->read((char*) &net_int_y, sizeof(uint32_t));
      uint32_t host_int_y = ntohl(net_int_y);

      __add(host_int_x, host_int_y);
    } else if (strcmp(functionNameBuffer, "subtract") == 0) {
      uint32_t net_int_x;
      RPCSTUBSOCKET->read((char*) &net_int_x, sizeof(uint32_t));
      uint32_t host_int_x = ntohl(net_int_x);

      uint32_t net_int_y;
      RPCSTUBSOCKET->read((char*) &net_int_y, sizeof(uint32_t));
      uint32_t host_int_y = ntohl(net_int_y);

      __subtract(host_int_x, host_int_y);
    } else if (strcmp(functionNameBuffer, "multiply") == 0) {
      uint32_t net_int_x;
      RPCSTUBSOCKET->read((char*) &net_int_x, sizeof(uint32_t));
      uint32_t host_int_x = ntohl(net_int_x);

      uint32_t net_int_y;
      RPCSTUBSOCKET->read((char*) &net_int_y, sizeof(uint32_t));
      uint32_t host_int_y = ntohl(net_int_y);

      __multiply(host_int_x, host_int_y);
    } else if (strcmp(functionNameBuffer, "divide") == 0) {
      uint32_t net_int_x;
      RPCSTUBSOCKET->read((char*) &net_int_x, sizeof(uint32_t));
      uint32_t host_int_x = ntohl(net_int_x);

      uint32_t net_int_y;
      RPCSTUBSOCKET->read((char*) &net_int_y, sizeof(uint32_t));
      uint32_t host_int_y = ntohl(net_int_y);

      __divide(host_int_x, host_int_y);
    } else {
      __badFunction(functionNameBuffer);
    }
  }
}

 
//
//                   getFunctionNamefromStream
//
//   Helper routine to read function name from the stream. 
//   Note that this code is the same for all stubs, so can be generated
//   as boilerplate.
//
//   Important: this routine must leave the sock open but at EOF
//   when eof is read from client.
//
void getFunctionNameFromStream(char *buffer, unsigned int bufSize) {
  unsigned int i;
  char *bufp;    // next char to read
  bool readnull;
  ssize_t readlen;             // amount of data read from socket
  
  //
  // Read a message from the stream
  // -1 in size below is to leave room for null
  //
  readnull = false;
  bufp = buffer;
  for (i=0; i< bufSize; i++) {
    readlen = RPCSTUBSOCKET-> read(bufp, 1);  // read a byte
    // check for eof or error
    if (readlen == 0) {
      break;
    }
    // check for null and bump buffer pointer
    if (*bufp++ == '\0') {
      readnull = true;
      break;
    }
  }
  
  //
  // With TCP streams, we should never get a 0 length read
  // except with timeouts (which we're not setting in pingstreamserver)
  // or EOF
  //
  if (readlen == 0) {
    c150debug->printf(C150RPCDEBUG,"arithmetic.stub: read zero length message, checking EOF");
    if (RPCSTUBSOCKET-> eof()) {
      c150debug->printf(C150RPCDEBUG,"arithmetic.stub: EOF signaled on input");

    } else {
      throw C150Exception("arithmetic.stub: unexpected zero length read without eof");
    }
  }

  //
  // If we didn't get a null, input message was poorly formatted
  //
  else if(!readnull) 
    throw C150Exception("arithmetic.stub: method name not null terminated or too long");

  
  //
  // Note that eof may be set here for our caller to check
  //

}


