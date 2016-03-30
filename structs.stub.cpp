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
  cout << "calling __findPerson" << endl;
  Person result = findPerson(tp);
  cout << "result firstname is " << result.age << endl;
  sendStringType(RPCSTUBSOCKET, result.firstname);
  sendStringType(RPCSTUBSOCKET, result.lastname);
  sendIntType(RPCSTUBSOCKET, result.age);
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
      cout << "received findPerson request" << endl;
      ThreePeople tp;
      Person p1;
      Person p2;
      Person p3;

      p1.firstname = readStringType(RPCSTUBSOCKET);
      cout << "p1 firstname: " << p1.firstname << endl;
      p1.lastname = readStringType(RPCSTUBSOCKET);
      cout << "p1 lastname: " << p1.lastname << endl;
      p1.age = readIntType(RPCSTUBSOCKET);
      cout << "p1 age: " << p1.age << endl;
      
      p2.firstname = readStringType(RPCSTUBSOCKET);
      cout << "p2 firstname: " << p2.firstname << endl;
      p2.lastname = readStringType(RPCSTUBSOCKET);
      cout << "p2 lastname: " << p2.lastname << endl;
      p2.age = readIntType(RPCSTUBSOCKET);
      cout << "p2 age: " << p2.age << endl;

      p3.firstname = readStringType(RPCSTUBSOCKET);
      cout << "p3 firstname: " << p3.firstname << endl;
      p3.lastname = readStringType(RPCSTUBSOCKET);
      cout << "p3 lastname: " << p3.lastname << endl;
      p3.age = readIntType(RPCSTUBSOCKET);
      cout << "p3 age: " << p3.age << endl;

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


