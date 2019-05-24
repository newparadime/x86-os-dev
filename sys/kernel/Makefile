BASE_NAME=kernel

TOPDIR  = ../..
SYSDIR  = $(TOPDIR)/sys

include $(TOPDIR)/common.mk

CFLAGS   += -std=gnu99 -ffreestanding -O2 -Wall -Wextra
CXXFLAGS += -std=gnu++17 -ffreestanding -O2 -Wall -Wextra
ASFLAGS  +=

LDLIBS  = -lgcc
LDFLAGS = -T kernel.ld -ffreestanding -O2 -nostdlib

ifeq ($(strip $(CXX_OBJ)),)
	LD=$(CC)
else
	LD=$(CXX)
endif

CRTI_OBJ      = crti.o
CRTBEGIN_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ   := $(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ      = crtn.o


BUILT_OBJS  = $(CRTI_OBJ) $(C_OBJ) $(CXX_OBJ) $(AS_OBJ) $(CRTN_OBJ)
LINKED_OBJS = $(CRTI_OBJ) $(CRTBEGIN_OBJ) \
              $(C_OBJ) $(CXX_OBJ) $(filter-out $(CRTI_OBJ) $(CRTN_OBJ), $(AS_OBJ)) \
              $(CRTEND_OBJ) $(CRTN_OBJ)

.PHONY: default all clean cleanall $(BASE_NAME)

default all: $(BASE_NAME)

clean:
	$(RM) $(BASE_NAME) $(BUILT_OBJS)
	
cleanall: clean all

$(BASE_NAME): $(BASE_NAME).bin

$(BASE_NAME).bin: $(LINKED_OBJS)
	$(LD) $(LDFLAGS) $(LDLIBS) -o $@ $(LINKED_OBJS)

include $(TOPDIR)/rules.mk
include rules.mk
