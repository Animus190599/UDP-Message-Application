
#ifndef UDP_HELPER_H
#define UDP_HELPER_H

#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h>
#include <unistd.h> 
#include <inttypes.h>
#include <string.h> 

#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#include <signal.h>

#define PORT     8080 // Port to send data
#define MAXLINE 512 // Max length of buffer

// Payload structure
typedef struct
{
    int8_t lattitude;
    int16_t longtitude;
    uint8_t eta;
    char dest[3];
} Payload;


// Payload header structure    
typedef struct
{
    uint64_t check;
    uint8_t version;
    uint16_t udp_length;
    Payload payload;
} Data;


void struct2str(Data*, char*);
void structTest(void);

#endif