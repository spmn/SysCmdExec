# This file demonstrates how to compile the SysCmdExec project on Linux.
#
# To compile SysCmdExec do:
#
# make SYSCMDEXEC
#

GPP = g++
GCC = gcc
OUTFILE = "./SysCmdExec.so"

COMPILE_FLAGS = -m32 -fPIC -c -O3 -w -DLINUX -DHAVE_STDINT_H -DHAVE_ALLOCA_H -I./sdk/amx

all: SYSCMDEXEC

clean:
	-rm -f *~ *.o *.so

SYSCMDEXEC: clean
	$(GPP) $(COMPILE_FLAGS) ./sdk/*.cpp
	$(GPP) $(COMPILE_FLAGS) *.cpp
	$(GPP) -m32 -O2 -fshort-wchar -shared -o $(OUTFILE) *.o