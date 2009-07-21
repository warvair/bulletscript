# bulletscript library
LIBNAME_S = bulletscript-static.a

LIBNAME_D = bulletscript.so

LIBSRCDIR = ../src

LIBSRC = $(LIBSRCDIR)/bsAbstractSyntaxTree.cpp $(LIBSRCDIR)/bsBulletLexer.cpp $(LIBSRCDIR)/bsScriptMachine.cpp $(LIBSRCDIR)/bsAreaGun.cpp $(LIBSRCDIR)/bsBulletParser.cpp $(LIBSRCDIR)/bsScriptMachine.cpp $(LIBSRCDIR)/bsGun.cpp $(LIBSRCDIR)/bsScriptStructs.cpp $(LIBSRCDIR)/bsBulletGun.cpp $(LIBSRCDIR)/bsGunDefinitions.cpp $(LIBSRCDIR)/bsScriptVariables.cpp

LIBOUTDIR_S = ../lib

LIBOUTDIR_D = ../bin

LIBFILES = $(LIBSRC:.cpp=.o)

# minimal app
MINNAME_S = minimal-static

MINNAME_D = minimal-shared

MINSRCDIR = ../minimal

MINSRC = $(MINSRCDIR)/Main.cpp $(MINSRCDIR)/BulletSystem.cpp

MINOUTDIR = ../minimal/bin

MINFILES = $(MINSRC:.cpp=.o)

# compiler
CXX = g++

CXXFLAGS = -O2 -I../include -g

# bulletscript
lib-static: $(LIBFILES)
	$(AR) rcs $(LIBOUTDIR_S)/$(LIBNAME_S) $(LIBFILES)

# need to specify that files are compiled with -fPIC
#lib-shared: $(LIBFILES)
#	$(CXX) -shared -o $(LIBOUTDIR_D)/$(LIBNAME_D) $(LIBFILES)

# minimal app
minimal-static: $(MINFILES)
	$(CXX) $(CXXFLAGS) $^ $(LIBOUTDIR_S)/bulletscript-static.a -o $(MINOUTDIR)/$(MINNAME_S)

# minimal-shared: $(MINFILES)
# need to specify that files are compiled with -fPIC
	

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

# cleanup
clean:
	rm -f $(LIBOUTDIR_S)/$(LIBNAME_S)
	rm -f $(MINOUTDIR)/$(MINNAME_S)
	rm -f $(LIBSRCDIR)/*.o
	rm -f $(MINSRCDIR)/*.o

	
