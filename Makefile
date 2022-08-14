# CC = gcc
# CFLAGS = -I. -Wall -std=gnu99
# _OBJ = helper.o 
# DEPS = helper.h

# .PHONY: all
# .DEFAULT_GOAL := all

# OBJ_DIR = obj

# OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

# $(OBJ_DIR)/%.o: %.c $(DEPS)
# 	if ! [ -d obj ]; then mkdir -p obj; fi
# 	$(CC) -c $< -o $@ $(CFLAGS)

# server: $(OBJ)
# 	$(CC) server.c $^ -o $@ $(CFLAGS) 

# client: $(OBJ)
# 	$(CC) client.c $^ -o $@ $(CFLAGS) 

# all: server client

# clean:
# 	rm -rf obj
# 	rm server
# 	rm client

CC = c99 
CFLAG = -Wall -lpthread 

all: client server 
	echo "Compile Done."
# %.o: %.c
#     gcc -c -Wall -Werror -o $@ $<

server: server.o helper.o
	gcc -g -o server -std=c99 server.o helper.o

client: client.o helper.o
	gcc -g -o client -std=c99 client.o helper.o


clean:
	rm -f server 
	rm -f client 
	rm -f *.o 
	
.PHONY: all clean 