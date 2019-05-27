BASE_NAME=kernel

TOPDIR     = ../..
SYSDIR     = $(TOPDIR)/sys
KERNELDIR  = $(SYSDIR)/kernel
STDCDIR    = $(KERNELDIR)/libstdc
HDR_DIRS  += $(KERNELDIR)/include

include $(TOPDIR)/common.mk

INCLUDE   = $(addprefix -I, $(HDR_DIRS))
CFLAGS   += -g -std=gnu99 -ffreestanding -O2 -Wall -Wextra $(INCLUDE)
CXXFLAGS += -g -std=gnu++17 -ffreestanding -O2 -Wall -Wextra \
            -fno-exceptions -fno-rtti $(INCLUDE)
ASFLAGS  += $(INCLUDE) -ffreestanding -O2 -Wall -Wextra



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

LIBS=

LDLIBS  = -lgcc $(LIBS:lib%=-l%)
LDFLAGS = -T kernel.ld -ffreestanding -O2 -nostdlib $(addprefix -L, $(LIBS))

.PHONY: default all clean cleanall $(BASE_NAME)

default all: $(BASE_NAME)

clean:
	$(RM) $(BASE_NAME).bin $(BUILT_OBJS)
	
cleanall: clean all

$(BASE_NAME): $(BASE_NAME).bin

$(BASE_NAME).bin: $(LINKED_OBJS) $(LIBS)
	$(LD) $(LDFLAGS) $(LDLIBS) -o $@ $(LINKED_OBJS)

$(LIBS):
	$(MAKE) -C $@

include $(TOPDIR)/rules.mk
include rules.mk
