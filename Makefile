PRGNAME     = ncraft.elf
CC			= gcc

SRCDIR		= ./src ./src/pc
VPATH		= $(SRCDIR)
SRC_C		= $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.c))
SRC_S		= $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.s))
OBJ_C		= $(notdir $(patsubst %.c, %.o, $(SRC_C)))
OBJ_S		= $(notdir $(patsubst %.s, %.o, $(SRC_CP)))
OBJS		= $(OBJ_C) $(OBJ_S)

CFLAGS		= -Os -flto
CFLAGS		+= -Isrc -Isrc/pc

LDFLAGS     = -lc -lgcc -lm -lSDL -lasound -Wl,--as-needed -flto -s

# Rules to make executable
$(PRGNAME): $(OBJS)  
	$(CC) $(CFLAGS) -o $(PRGNAME) $^ $(LDFLAGS)

$(OBJ_C) : %.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<
	
$(OBJ_S) : %.o : %.s
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(PRGNAME) *.o
