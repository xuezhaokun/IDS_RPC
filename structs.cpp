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

#include <string>
#include <cstring>
#include <iostream>
using namespace std;          // for C++ std library
#include "structs.idl"

Person findPerson(ThreePeople tp){
	cout << "returning p1" << endl;
	return tp.p1;
}

int area(rectangle r){
	return (r.x * r.y);
}