CC = c99 
CFLAGS = -Wall  

all: client server 
	echo "Compile Done."

server: server.o 
	gcc -o server -std=c99 server.o 

client: client.o 
	gcc -o client -std=c99 client.o 


clean:
	rm -f server client 
	rm -f *.o 
	
.PHONY: all clean 