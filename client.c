#include "client.h"   

/*----------------------
 |  Main program
 -----------------------*/

int main() { 
    // singal handler for Ctrl+C
    signal(SIGINT,sig_handler);
    //Initialize socket variables
    int sockfd; 
    char buffer[MAXLINE]; 
    // Declare message variable
    char message[MAXLINE];
    struct sockaddr_in servaddr; 
    // Create datagram
    Data *datagram = malloc(sizeof(Data));
    if (datagram == NULL){
        free(datagram);
        return -1;
    }
    // Zero out structure
    memset(datagram,0,sizeof(Data));
    // Initialize datagram
    InitializeFields(datagram);
    // Convert datagram struct to string to send over network
    struct2str(datagram, message);

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
        
    sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 
    printf("Message sent.\n"); 
    // Free allocated memory
    free(datagram);  

    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 
    buffer[n] = '\0'; 
    printf("Server : %s\n", buffer); 
    
    //Close client socket
    close(sockfd); 

    return 0; 
}

/*----------------------
 |  Functions
 -----------------------*/
/** 
 * sig_handler
 *
 * @param sig signal type
 * @return ivoid
 * 
 * handle SIGINT signal
 **/
void sig_handler(int sig){
    progCont = false;
    exit(1);
}

/** 
 * InitializeFields: initialize the payload datagram
 *
 * @param Data struct
 * @return void
 * 
 * Take users input or default value to fill the datagram Data structure
 **/
void InitializeFields(Data *dg){
    
    char ans;
    // User input to generate payload structure
    printf("Do you want to input values or default values? Y/N: ");
    scanf("%c",&ans);
    if (ans == 'Y'|| ans == 'y'){
        *dg = (Data){.version = 1, .payload={.lattitude = 65, .longtitude = 100, .eta = 10, .dest = "abc"}};
    }
    else{
        printf("Please enter payload version: ");
        scanf("%hhu", &dg->version); 
        printf("Please enter lattitude: ");
        scanf("%"SCNi16, &dg->payload.lattitude);
        printf("Please enter longtitude: ");
        scanf("%"SCNi16, &dg->payload.longtitude);
        printf("Please enter eta: ");
        scanf("%"SCNu16, &dg->payload.eta);
        printf("Please enter destination code: ");
        scanf("%3s",&dg->payload.dest);
    }
    // Fill in missing data: Package length and checksum
    dg->udp_length = calc_length(dg);
    dg->check = csum_calc(dg);;

}



