// Server side implementation of UDP client-server model 
#include "server.h"
    

/*----------------------
 |  Main program
 -----------------------*/
int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Message received"; 
    struct sockaddr_in servaddr, cliaddr; 
        
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
    
    // Listening to incoming packages
    while(1){
        printf("Waiting for data...");
        fflush(stdout);
        n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                    MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                    &len); 
        buffer[n] = '\0'; 
        printf("Client : %s\n", buffer); 
        unpack_data(buffer);
        sendto(sockfd, (const char *)hello, strlen(hello),  
            MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
                len); 
        printf("Message unpacked and verified by server.\n");  
    }
        
  
        
    return 0; 
}
/*----------------------
 |  Functions
 -----------------------*/
/** 
 * unpack_data: This function unpacks and validates incoming data
 *
 * @param *str Message received from the client
 * @return int
 * 
 * This function will unpack the string message into a struct. Then, it will:
 * 1. Validate checksum
 * 2. Validate supported version
 * 3. Validate data range
 * 4. Save message to disk
 **/
int unpack_data(char *str){
    // Allocate data for struct---------------------
    Data *datagram = malloc(sizeof(Data));
    if (datagram == NULL){
        free(datagram);
        return -1;
    }
    // Zero out structure---------------------------
    memset(datagram,0,sizeof(Data));

    // Unpack payload--------------------------------
    str2struct(datagram, str);

    // Validate checksum----------------------------
    if(csum_val(datagram)){
        printf("Checksum: Correct\n");
    }
    else{
        printf("Checksum: Error. Data corrupted\n");
    }
    // Check supported payload version--------------
    if(datagram->version==1){
        printf("Payload version: Supported\n");
    }
    else{
        printf("Payload version: Unsupported\n");
    }
    // Verify all data to be within constraints-----
    if (data_verify(datagram)){
        printf("All data verified\n");
    }

    // Save data to disk----------------------------
    save2disk(datagram, "homework.txt");
    printf("Saved to disk\n");
    // Free allocated memory------------------------
    free(datagram);
    return 0;
}