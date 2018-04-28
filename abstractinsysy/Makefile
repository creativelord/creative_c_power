CC=gcc
CUR_DIR=.
H_DIR =$(CUR_DIR)
C_DIR= $(CUR_DIR)
O_DIR=$(CUR_DIR)
DEBUG=-g -O2
CFLAGS=${DEBUG} -Wall
RM=rm -rf

CFILES=$(wildcard $(C_DIR)/*.c)
HFILES=$(wildcard $(H_DIR)/*.h)
OFILES=$(patsubst %.c,$(O_DIR)/%.o ,$(CFILES))
TARGET=main
$(TARGET):$(OFILES)
	$(CC) $(CFLAGS) $@ $<

.c.o:
	$(CC) -c $<