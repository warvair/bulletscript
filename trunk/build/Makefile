# bulletscript library
LIBNAME_S = bulletscript-static.a

LIBNAME_D = bulletscript.so

LIBSRCDIR = ../src

LIBOUTDIR_S = ../lib

LIBOUTDIR_D = ../bin

LIBSRC = $(LIBSRCDIR)/bsAffector.cpp $(LIBSRCDIR)/bsAlloc.cpp $(LIBSRCDIR)/bsBulletLexer.cpp $(LIBSRCDIR)/bsBulletParser.cpp $(LIBSRCDIR)/bsController.cpp $(LIBSRCDIR)/bsControllerDefinition.cpp $(LIBSRCDIR)/bsCore.cpp $(LIBSRCDIR)/bsEmitter.cpp $(LIBSRCDIR)/bsEmitterDefinition.cpp $(LIBSRCDIR)/bsFireType.cpp $(LIBSRCDIR)/bsLog.cpp $(LIBSRCDIR)/bsMachine.cpp $(LIBSRCDIR)/bsObjectDefinition.cpp $(LIBSRCDIR)/bsParseTree.cpp $(LIBSRCDIR)/bsScriptMachine.cpp  $(LIBSRCDIR)/bsScriptVariables.cpp $(LIBSRCDIR)/bsTypeManager.cpp

LIBFILES = $(LIBSRC:.cpp=.o)

# testbed
TESTBEDNAME = testbed

TESTBEDSRCDIR = ../testbed

TESTBEDOUTDIR = ../testbed/bin

TESTBEDSRC = $(TESTBEDSRCDIR)/AreaSystem.cpp $(TESTBEDSRCDIR)/BulletSystem.cpp $(TESTBEDSRCDIR)/Main.cpp $(TESTBEDSRCDIR)/Platform.cpp $(TESTBEDSRCDIR)/RendererGL.cpp $(TESTBEDSRCDIR)/UnitSystem.cpp

TESTBEDFILES = $(TESTBEDSRC:.cpp=.o)

# compiler
CXX = g++

CXXFLAGS = -O2 -I../include

# bulletscript
lib-static: $(LIBFILES)
	$(AR) rcs $(LIBOUTDIR_S)/$(LIBNAME_S) $(LIBFILES)

# need to specify that files are compiled with -fPIC
#lib-shared: $(LIBFILES)
#	$(CXX) -shared -o $(LIBOUTDIR_D)/$(LIBNAME_D) $(LIBFILES)

# testbed
testbed: $(TESTBEDFILES)
	 $(CXX) $(CXXFLAGS) $^ $(LIBOUTDIR_S)/$(LIBNAME_S) -o $(TESTBEDOUTDIR)/$(TESTBEDNAME)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

# cleanup
clean:
	rm -f $(LIBOUTDIR_S)/$(LIBNAME_S)
	rm -f $(LIBSRCDIR)/*.o
	rm -f $(TESTBEDSRCDIR)/*.o


	
