TARGET = vm_riskxvii

CC = gcc

CFLAGS 	   = -c -O0 -flto -std=c11 -pie -Oz
SRC        = vm_riskxvii.c vm_functions.c helper_functions.c linked_list.c heap.c
OBJ        = $(SRC:.c=.o)

all:$(TARGET)

$(TARGET):$(OBJ)
	$(CC) -o $@ $(OBJ)

.SUFFIXES: .c .o

.c.o:
	 $(CC) $(CFLAGS) $<

run:
	./$(TARGET)

test:
	echo what are we testing?!

clean:
	rm -f *.o *.obj $(TARGET)
