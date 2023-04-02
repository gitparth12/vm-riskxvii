TARGET = vm_riskxvii

CC = gcc

# CFLAGS     = -c -Wall -Wvla -pie -Oz -Werror -O0 -std=c11
CFLAGS 	   = -c -O0 -flto -std=c11
ASAN_FLAGS = -fsanitize=address
SRC        = vm_riskxvii.c vm_functions.c helper_functions.c linked_list.c heap.c
OBJ        = $(SRC:.c=.o)

all:$(TARGET)

# $(TARGET):$(OBJ)
# 	$(CC) $(ASAN_FLAGS) -o $@ $(OBJ)
$(TARGET):$(OBJ)
	$(CC) -o $@ $(OBJ)

.SUFFIXES: .c .o

# .c.o:
# 	 $(CC) $(CFLAGS) $(ASAN_FLAGS) $<

.c.o:
	 $(CC) $(CFLAGS) $<

run:
	./$(TARGET)

test:
	echo what are we testing?!

clean:
	rm -f *.o *.obj $(TARGET)
