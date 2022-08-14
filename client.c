#include "client.h"   

volatile bool progCont;



void sig_handler(int sig){
    progCont = false;
    printf("whatup");
}
// Driver code 
int main() { 
    signal(SIGINT,sig_handler);

    int sockfd; 
    char buffer[MAXLINE]; 
    struct sockaddr_in servaddr; 
    
    
    // Create datagram
    Data *datagram = malloc(sizeof(Data));
    if (datagram == NULL){
        free(datagram);
        return -1;
    }
    memset(datagram,0,sizeof(Data));
    // printf("%zu",sizeof(Data));
    // // Allocate package message
    // char *message = (char *)malloc(MAXLINE*sizeof(char));
    // if (message == NULL){
    //     free(message);
    //     return -1;
    // }
    char message[MAXLINE];
    // char *message = "Helloworld";
    // printf("%zu",sizeof(datagram));
    // printf(sizeof(Data));
    // zero out structure
    // memset(datagram, 0, sizeof(*datagram));

    printf("%zu",sizeof(datagram->version));
    printf("%zu",sizeof(datagram->payload));
    printf("%zu",sizeof(datagram->udp_length));

    InitializeFields(datagram);
    printf("hello\n");
    printf("%d\n",datagram->version);
    printf("%d\n",datagram->payload.lattitude);
    
    structTest();
    printf("%zu",strlen(message));
    // printf("hello2");
    printf("%s\n",*message);
    free(datagram);
    // free(message);
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    memset(&servaddr, 0, sizeof(servaddr)); 
        
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
        
    int n, len; 
        
    sendto(sockfd, (const char *)message, strlen(message), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 
    printf("Hello message sent.\n"); 

    // free(datagram);
    // free(message);        

    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 0, (struct sockaddr *) &servaddr, &len); 
    buffer[n] = '\0'; 
    printf("Server : %s\n", buffer); 
    
    close(sockfd); 
    return 0; 
}


void InitializeFields(Data *dg){
    
    // struct Data *dg = malloc(sizeof(struct Data));
    printf("Do you want to input values or default values? Y/N: ");

    printf("Please enter payload version: ");
    // scanf("%hhu",&dg->version);
    scanf("%"SCNu8, &dg->version); 
    printf("Please enter lattitude: ");
    // dg->payload.lattitude = b;
    scanf("%"SCNi8, &dg->payload.lattitude);
    printf("Please enter longtitude: ");
    scanf("%"SCNi16, &dg->payload.longtitude);
    printf("Please enter eta: ");
    scanf("%"SCNu8, &dg->payload.eta);
    printf("Please enter destination code: ");
    scanf("%3s",&dg->payload.dest);

    // Fill in missing data
    // dg->udp_length = CalcLength();
    // dg->check = CheckSum();
    dg->udp_length = 10;
    dg->check = 10000;

    // printf("%d\n", dg->version);
    // printf("%zu\n", sizeof(dg->version));
    // printf("%s\n", dg->payload.dest);

}

// int SumByte(Data* data)){
//     int sum = 0;
//     sum+=
// }


// char *struct2str(struct Data *dg){
//     // Get length of string to hold struct values
//     size_t len = snprintf(NULL)
//     memcpy

//     char *buffer = new char[MAXLINE];
//     int offset = 0;

//     // Adding header
//     memcpy(buffer+offset, &dg->check,sizeof(dg->check));
//     offset+= sizeof(dg->check);
//     memcpy(buffer+offset, &dg->version,sizeof(dg->version));
//     offset+= sizeof(dg->version);
//     memcpy(buffer+offset, &dg->udp_len,sizeof(dg->udp_len));
//     offset+= sizeof(dg->udp_len);

//     // Adding payload
//     memcpy(buffer+offset, &dg->payload.lattitude,sizeof(dg->payload.lattitude));
//     offset+= sizeof(dg->payload.lattitude);
//     memcpy(buffer+offset, &dg->payload.longtitude,sizeof(dg->payload.longtitude));
//     offset+= sizeof(dg->payload.longtitude);
//     memcpy(buffer+offset, &dg->payload.eta,sizeof(dg->payload.eta));
//     offset+= sizeof(dg->payload.eta);
//     memcpy(buffer+offset, &dg->payload.dest,sizeof(dg->payload.dest));
//     offset+= sizeof(dg->payload.dest);


//     return buffer;
// }