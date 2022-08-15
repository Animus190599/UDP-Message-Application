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