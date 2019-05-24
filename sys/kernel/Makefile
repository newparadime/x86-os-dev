BASE_NAME=kernel

TOPDIR=../..
SYSDIR=$(TOPDIR)/sys
BOOTDIR=$(SYS)/boot

include $(TOPDIR)/common.mk

C_SRC=$(wildcard *.c)
C_OBJ=$(C_SRC:%.c=%.o)

CXX_SRC=$(wildcard *.cxx)
CXX_OBJ=$(CXX_SRC:%.cxx=%.o)

AS_SRC=$(wildcard *.S)
AS_OBJ=$(AS_SRC:%.S=%.o)

OBJ=$(C_OBJ) $(CXX_OBJ) $(AS_OBJ)

LDLIBS= -lgcc
LDFLAGS= -T kernel.ld -ffreestanding -O2 -nostdlib

CFLAGS+= -std=gnu99 -ffreestanding -O2 -Wall -Wextra
CXXFLAGS+= -std=gnu++17 -ffreestanding -O2 -Wall -Wextra

ifeq ($(strip $(CXX_OBJ)),)
	LD=gcc
else
	LD=g++
endif

.PHONY: default all clean cleanall $(BASE_NAME)

default all: $(BASE_NAME)

clean:
	$(RM) $(BASE_NAME) $(OBJ)
	
cleanall: clean all

$(BASE_NAME): $(BASE_NAME).bin

$(BASE_NAME).bin: $(OBJ)
	$(TARGET)-$(LD) $(LDFLAGS) $(LDLIBS) -o $@ $^

include $(TOPDIR)/rules.mk
include rules.mk
