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

    // Allocate package message
    // char *message = (char *)malloc(MAXLINE*sizeof(char));
    // if (message == NULL){
    //     free(message);
    //     return -1;
    // }
    char message[50];

    // zero out structure
    // memset(datagram, 0, sizeof(*datagram));

    // printf("%zu",sizeof(datagram->version));
    // printf("%zu",sizeof(datagram->payload));
    // printf("%zu",sizeof(datagram->udp_length));

    InitializeFields(datagram);
    printf("hello\n");
    // printf("%d\n",datagram->version);
    // printf("%d\n",datagram->payload.lattitude);
    
    struct2str(datagram, message);
    // printf("%s",message);
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
    
    printf("Do you want to input values or default values? Y/N: ");

    printf("Please enter payload version: ");
    scanf("%"SCNu8, &dg->version); 
    printf("Please enter lattitude: ");
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

}


