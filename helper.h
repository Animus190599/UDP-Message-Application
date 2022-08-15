
#ifndef UDP_HELPER_H
#define UDP_HELPER_H
/*----------------------
 |  Includes
 -----------------------*/
// General lib
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <stdbool.h>
#include <unistd.h> 
#include <inttypes.h>
// Network library
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
// Signal library
#include <signal.h>

/*----------------------
 |  Define values
 -----------------------*/
#define PORT 8080 // Port to send data
#define MAXLINE 200 // Max length of buffer

/*----------------------
 |  Set up structures
 -----------------------*/
// Payload structure
typedef struct
{
    int16_t lattitude;
    int16_t longtitude;
    uint16_t eta;
    char dest[3];
} Payload;


// Payload header structure    
typedef struct
{
    uint64_t check;
    unsigned char version;
    uint16_t udp_length;
    Payload payload;
} Data;

/*----------------------
 |  Function definition
 -----------------------*/
void struct2str(Data*, char*);
void str2struct(Data*, char*);
unsigned short calc_length(Data*);
unsigned short csum_calc(Data*);
bool csum_val(Data*);
bool data_verify(Data*);
bool save2disk(Data *mg, const char*);

#endif