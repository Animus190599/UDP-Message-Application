// Server side implementation of UDP client-server model 
#include "helper.h"
    

// Payload header structure    
struct Package
{
    uint64_t check;
    uint8_t version;
    uint16_t udp_length;
    // long checksum
    // char version
    // unsigned short length
    // Payload payload
};

// Payload structure
struct Payload
{
    int8_t lattitude;
    int16_t longtitude;
    uint8_t eta;
    char dest[3];
};


// Driver code 
int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Hello from server"; 
    struct sockaddr_in servaddr, cliaddr; 

    // Create datagram
    struct Payload *payload1;
    struct Data *data;
    // User input
        
    // Creating socket that returns a socket descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 

    // Clean bufers    
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
        
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
        
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
        
    int len, n; 
    
    len = sizeof(cliaddr);  //len is value/result 
    
    // Keep listening for data...
    while(1)
    {
        if(n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len)<0)
        {
            perror("receive failed");
            exit(EXIT_FAILURE)
        } 
        buffer[n] = '\0'; 
        printf("Client : %s\n", buffer); 
        sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
        printf("Hello message sent.\n");  
    }
  
        
    return 0; 
}

/* 
Function: checkSum
Descriptions: Return the checksum value of the given data


returns:
 */
#define BLOCK_SIZE 64
 unsigned short CheckSum(unsigned short *datagram, int nbytes){
    register long sum;
    unsigned short oddbytes;

    sum = 0;




 }