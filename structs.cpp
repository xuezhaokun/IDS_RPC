// --------------------------------------------------------------
//
//                        strcuts.cpp
//
//        Author: Noah Mendelsohn         
//   
//
//        Trivial implementations of the routines declared
//        in structs.idl. These are for testing: they
//        just print messages.
//
//       Copyright: 2012 Noah Mendelsohn
//     
// --------------------------------------------------------------

// IMPORTANT! WE INCLUDE THE IDL FILE AS IT DEFINES THE INTERFACES
// TO THE FUNCTIONS WE'RE IMPLEMENTING. THIS MAKES SURE THE
// CODE HERE ACTUALLY MATCHES THE REMOTED INTERFACE

#include "structs.idl"
#include "c150debug.h"
#include "atomicSocketUtils.h"
#include <cstring>
using namespace std;

Person findPerson (ThreePeople tp){
	return tp.p1;
}

int area (rectangle r){
	return (r.x * r.y);
}