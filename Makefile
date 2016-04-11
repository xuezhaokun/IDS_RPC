# Makefile for COMP 150IDS RPC Samples
#
#    Copyright 2012 - Noah Mendelsohn
#
#
# Useful targets:
#
#
#    pingstreamclient  - demonstration message ping client using TCP streams
#    pingstreamserver  - demonstration message ping server
#    simplefunctionclient - sample RPC client
#    simplefunctionserver - sample RPC server
#    idldeclarationtst      - demonstrates the IDL parsing framework
#
#    clean       - clean out all compiled object and executable files
#    all         - (default target) make sure everything's compiled
#

# Do all C++ compies with g++
CPP = g++

# change following line if your rpgenerate is not in current directory
RPCGEN = ./rpcgenerate

# Where the COMP 150 shared utilities live, including c150ids.a and userports.csv
# Note that environment variable COMP150IDS must be set for this to work!

C150LIB = $(COMP150IDS)/files/c150Utils/
C150AR = $(C150LIB)c150ids.a

# RPC framework is shared archive
C150IDSRPC = $(COMP150IDS)/files/RPC.framework/
C150IDSRPCAR = $(C150IDSRPC)c150idsrpc.a

CPPFLAGS = -g -Wall -Werror -I$(C150IDSRPC) -I$(C150LIB) -std=c++11
# CPPFLAGS = -g -Wall -Werror  -I$(C150LIB)


LDFLAGS = 
INCLUDES = $(C150LIB)c150streamsocket.h $(C150LIB)c150network.h $(C150LIB)c150exceptions.h $(C150LIB)c150debug.h $(C150LIB)c150utility.h $(C150LIB)c150grading.h $(C150IDSRPC)IDLToken.h $(C150IDSRPC)tokenizeddeclarations.h  $(C150IDSRPC)tokenizeddeclaration.h $(C150IDSRPC)declarations.h $(C150IDSRPC)declaration.h $(C150IDSRPC)functiondeclaration.h $(C150IDSRPC)typedeclaration.h $(C150IDSRPC)arg_or_member_declaration.h rpcproxyhelper.h rpcstubhelper.h simplefunction.idl arithmetic.idl floatarithmetic.idl structs.idl 

all: rpcgenerate structsclient structsserver floatarithmeticclient floatarithmeticserver arithmeticclient arithmeticserver pingstreamclient pingstreamserver idldeclarationtst simplefunctionclient simplefunctionserver idl_to_json

########################################################################
#
#     Adaptations of pingclient and pingserver to illustrate
#     use of COMP 150-IDS dgmstreamsocket class (which supports
#     TCP streams as opposed to UDP datagrams)
#
########################################################################

pingstreamclient: pingstreamclient.o  $(C150AR) $(C150IDSRPCAR) $(INCLUDES)
	$(CPP) -o pingstreamclient pingstreamclient.o $(C150AR) $(C150IDSRPCAR) 


pingstreamserver: pingstreamserver.o  $(C150AR) $(C150IDSRPCAR)  $(INCLUDES)
	$(CPP) -o pingstreamserver pingstreamserver.o $(C150AR) $(C150IDSRPCAR) 


########################################################################
#
#          Sample RPC client and server applications
#
#     Demonstrating remote calls to functions as declared in simplefunctions.idl
#
#     The proxies and stubs used here are hand generated, but eventually
#     your rpcgenerate program will (should) generate them automatically
#     from any idl
#
########################################################################

simplefunctionclient: simplefunctionclient.o rpcproxyhelper.o basicTypeHandler.o simplefunction.proxy.o  $(C150AR) $(C150IDSRPCAR)  $(INCLUDES)
	$(CPP) -o simplefunctionclient simplefunctionclient.o rpcproxyhelper.o basicTypeHandler.o simplefunction.proxy.o  $(C150AR) $(C150IDSRPCAR) 

# The following is NOT a mistake. The main program for any of the rpc servers
# is rpcserver.o.  This way, we can make a different one for each set 
# of functions, by linking the right specific stugs (in this case
# simplefunction.stub.o)
simplefunctionserver: simplefunction.stub.o rpcserver.o rpcstubhelper.o basicTypeHandler.o simplefunction.o  $(C150AR) $(C150IDSRPCAR)  $(INCLUDES)
	$(CPP) -o simplefunctionserver rpcserver.o simplefunction.stub.o basicTypeHandler.o simplefunction.o rpcstubhelper.o $(C150AR) $(C150IDSRPCAR) 


arithmeticclient: arithmeticclient.o rpcproxyhelper.o basicTypeHandler.o arithmetic.proxy.o  $(C150AR) $(C150IDSRPCAR)  $(INCLUDES)
	$(CPP) -o arithmeticclient arithmeticclient.o rpcproxyhelper.o basicTypeHandler.o arithmetic.proxy.o  $(C150AR) $(C150IDSRPCAR) 

# The following is NOT a mistake. The main program for any of the rpc servers
# is rpcserver.o.  This way, we can make a different one for each set 
# of functions, by linking the right specific stugs (in this case
# simplefunction.stub.o)
arithmeticserver: arithmetic.stub.o rpcserver.o rpcstubhelper.o basicTypeHandler.o arithmetic.o  $(C150AR) $(C150IDSRPCAR)  $(INCLUDES)
	$(CPP) -o arithmeticserver rpcserver.o arithmetic.stub.o basicTypeHandler.o arithmetic.o rpcstubhelper.o $(C150AR) $(C150IDSRPCAR) 


floatarithmeticclient: floatarithmeticclient.o rpcproxyhelper.o basicTypeHandler.o floatarithmetic.proxy.o  $(C150AR) $(C150IDSRPCAR)  $(INCLUDES)
	$(CPP) -o floatarithmeticclient floatarithmeticclient.o rpcproxyhelper.o basicTypeHandler.o floatarithmetic.proxy.o  $(C150AR) $(C150IDSRPCAR) 

# The following is NOT a mistake. The main program for any of the rpc servers
# is rpcserver.o.  This way, we can make a different one for each set 
# of functions, by linking the right specific stugs (in this case
# simplefunction.stub.o)
floatarithmeticserver: floatarithmetic.stub.o rpcserver.o rpcstubhelper.o basicTypeHandler.o floatarithmetic.o  $(C150AR) $(C150IDSRPCAR)  $(INCLUDES)
	$(CPP) -o floatarithmeticserver rpcserver.o floatarithmetic.stub.o basicTypeHandler.o floatarithmetic.o rpcstubhelper.o $(C150AR) $(C150IDSRPCAR) 

structsclient: structsclient.o rpcproxyhelper.o basicTypeHandler.o structs_additionalTypeHandler.o structs.proxy.o  $(C150AR) $(C150IDSRPCAR) $(INCLUDES)
	$(CPP) -o structsclient structsclient.o rpcproxyhelper.o basicTypeHandler.o structs_additionalTypeHandler.o structs.proxy.o  $(C150AR) $(C150IDSRPCAR) 

# The following is NOT a mistake. The main program for any of the rpc servers
# is rpcserver.o.  This way, we can make a different one for each set 
# of functions, by linking the right specific stugs (in this case
# simplefunction.stub.o)
structsserver: structs.stub.o rpcserver.o rpcstubhelper.o basicTypeHandler.o structs_additionalTypeHandler.o structs.o  $(C150AR) $(C150IDSRPCAR) $(INCLUDES)
	$(CPP) -o structsserver rpcserver.o structs.stub.o basicTypeHandler.o structs_additionalTypeHandler.o structs.o rpcstubhelper.o $(C150AR) $(C150IDSRPCAR) 


########################################################################
#
#          Generate C++ source from IDL files
#
#     Once you have written an rpcgenerate program, you can uncomment
#     the following two lines to have .cpp generated automatically from idl.
#     (but be sure not to have other .cpp files with the same base name
#     as the idl, e.g. the ones with your functions!)
#
#     The proxies and stubs used here are hand generated, but eventually
#     your rpcgenerate program will (should) generate them automatically
#     from any idl
#
#     WARNING! this may cause your rpcgenerate program to attempt to
#     rebuild supplied samples like simplefunction.proxy.cpp and 
#     simplefunction.stub.cpp. You may want to save backups for comparison.
#
########################################################################

%.proxy.cpp %.stub.cpp:%.idl $(RPCGEN)
	$(RPCGEN) $<

rpcgenerate: rpcgenerate.o $(C150AR) $(C150IDSRPCAR) $(INCLUDES)
	$(CPP) -o rpcgenerate rpcgenerate.o $(C150AR) $(C150IDSRPCAR)
########################################################################
#
#                   idldeclarationtst
#
#     When you write rpcgenerate, you'll want to use the idl
#     parser that's provided for you. This is a demo program
#     you can read and try to see how the parser works.
#
#     NOTE: This program became more or less obsolete in 2016.
#     Prior to then, all  RPC generators were written in C++,
#     there was no idl_to_json program, and this was the main example program
#     students used to learn the IDL parser. It is still maintained
#     in case anyone finds it useful.
#
########################################################################

idldeclarationtst: idldeclarationtst.o $(C150AR) $(C150IDSRPCAR)  $(INCLUDES)
	$(CPP) -o idldeclarationtst idldeclarationtst.o $(C150AR) $(C150IDSRPCAR) 

########################################################################
#
#                   idl_to_json
#
#     This program servers two purposes:
#
#     1) If you are writing your rpc generator in Python or Ruby,
#        this utility will convert .idl files to JSON for you.
#     2) Especially if you are writing rpcgenerate in C++, the
#        source code of idl_to_json.cpp is the best way to learn use
#        the provided .idl parser.
#
########################################################################

idl_to_json: idl_to_json.o $(C150AR) $(C150IDSRPCAR)  $(INCLUDES)
	$(CPP) -o idl_to_json idl_to_json.o $(C150AR) $(C150IDSRPCAR) 

########################################################################
#
#          Generate .json files from .idl files
#
#     This rule allows you to say:
#
#              make demo.json
#
#     if you already have demo.idl
#
########################################################################

%.json:%.idl idl_to_json
	     idl_to_json $< > $@

########################################################################
#
#                   Housekeeping
#
########################################################################


# make .o from .cpp

%.o:%.cpp  $(INCLUDES)
	$(CPP) -c  $(CPPFLAGS) $< 



# clean up everything we build dynamically (probably missing .cpps from .idl)
clean:
	 rm -f rpcgenerate structsclient structsserver floatarithmeticclient floatarithmeticserver arithmeticclient arithmeticserver pingstreamclient pingstreamserver idldeclarationtst idl_to_json simplefunctionclient simplefunctionserver *.o *.json *.pyc


