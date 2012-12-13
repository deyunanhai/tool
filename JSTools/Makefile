SRC_DIR = .
OBJ_DIR = obj
ifeq ($(STATIC),1)
CC = gcc -static
else
CC = gcc
endif
CFILES =
PROG_CFILES = \
	remove_debug.c
INCLUDES =
CFLAGS =  -Wall -Wno-format -O2 -s
CFLAGS += $(INCLUDES)

LDFLAGS = -lpthread -lm

PROG_OBJS = $(addprefix $(OBJ_DIR)/, $(CFILES:.c=.o))
PROGS     = $(addprefix $(OBJ_DIR)/, $(PROG_CFILES:.c=))

all: $(PROGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	if test ! -d $(@D); then rm -rf $(@D); mkdir -p $(@D); fi
	$(CC) -o $@ -c $(CFLAGS) $*.c

$(OBJ_DIR)/%: $(OBJ_DIR)/%.o $(PROG_OBJS)
	$(CC) -o $@ $(CFLAGS) $(PROG_OBJS) $(OBJ_DIR)/$*.o $(LDFLAGS) $(PROG_LIBS)

clean:
	rm -rf $(OBJ_DIR)
