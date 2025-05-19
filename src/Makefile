TARGET = newpopbios
OBJS = main.o

INCDIR = ../external/uofwinst/include
CFLAGS = -O2 -G0 -Wall -w -fno-pic
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1
PRX_EXPORTS = exports.exp

LIBDIR = ../external/uofwinst/libs
LDFLAGS = -nostartfiles
LIBS =  -lpspsystemctrl_kernel

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
