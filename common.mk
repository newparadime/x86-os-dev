TARGET:=i686-elf
PREFIX:=/usr/local/cross

CC:=$(TARGET)-gcc
CXX:=$(TARGET)-g++
AS:=$(TARGET)-as
LD:=$(TARGET)-ld
AR:=$(TARGET)-ar

C_SRC=$(wildcard *.c)
C_OBJ=$(C_SRC:%.c=%.o)

CXX_SRC=$(wildcard *.cxx)
CXX_OBJ=$(CXX_SRC:%.cxx=%.o)

AS_SRC=$(wildcard *.S)
AS_OBJ=$(AS_SRC:%.S=%.o)

.SECONDARY: %.o

