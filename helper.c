#include "helper.h"



/** 
 * struct2str: convert struct to string message representation
 *
 * @param Data* datagram struct pointer
 * @param char* message string
 * @return void
 * 
 * Using snprintf, the function convert (bruteforce) the input struct to the message string
 **/
void struct2str(Data *dg, char * str){
 
    int j = snprintf(str, MAXLINE, "%lld,%hhu,%hu,%hd,%hd,%hu,%3s%c",dg->check,
             dg->version, dg->udp_length, dg->payload.lattitude, dg->payload.longtitude,
             dg->payload.eta, dg->payload.dest,'\0');
    // Check for buffer length
    if (j>= MAXLINE){
        perror("Buffer length exceeded; string truncated");
    }
    printf("Entered message: %s\n",str);
}
/** 
 * str2struct: Convert a received message string to defined datagram struct
 *
 * @param Data* datagram struct pointer
 * @param char* message string
 * @return if any return value
 * 
 * Used strtok to split the string and gather information. 
 * Then atoi, strtoll, strtoul were used to convert string to the struct fields's correct data format
 **/
void str2struct(Data *dg, char* str){

    // Split strings---------------------------------
    char *ptr;
    char *a[10];
    unsigned char i = 0;
    // Call strtok to split string by "," 
    ptr = strtok(str,",");
    // strtok needs to be call multiple times
    while(ptr!=NULL){
        a[i]=ptr;
        i++;
        // Set the next starting position for strtok
        ptr = strtok(NULL, ",");
    }

    // Assign values to struct --------------------------
    dg->check = strtoll(a[0], NULL, 10); // Convert string to long long
    dg->version= atoi(a[1]); // Convert string to int
    dg->udp_length = strtoul(a[2],NULL, 10); //// Convert a string to an unsigned long integer.
    dg->payload.lattitude = strtoul(a[3],NULL, 10);
    dg->payload.longtitude = strtoul(a[4],NULL, 10);
    dg->payload.eta = strtoul(a[5],NULL, 10);
    strcpy(dg->payload.dest, a[6]);
}


/** 
 * csum_calc: Calculate checksum using custom algorithm
 *
 * @param Data* datagram struct pointer
 * @return 8 byte checksum data
 * 
 * Calculate checksum of the struct using the address of each field within it.
 * 1. Cast the pointer to the type of the field in the struct
 * 2. Sum the byte within it
 **/
unsigned short csum_calc(Data *dg){

    unsigned short sum = 0;

    // Calculate sum of each field in structure
    unsigned char *p = (unsigned char *)&dg->version;
    for (int i=0; i<sizeof(dg->version); i++) {
        sum += p[i];
    }
    p = (unsigned char *)&dg->udp_length;
    for (int i=0; i<sizeof(dg->udp_length); i++) {
        sum += p[i];
    }
    p = (unsigned char *)&dg->payload.lattitude;
    for (int i=0; i<sizeof(dg->payload.lattitude); i++) {
        sum += p[i];
    }
    p = (unsigned char *)&dg->payload.longtitude;
    for (int i=0; i<sizeof(dg->payload.longtitude); i++) {
        sum += p[i];
    }
    p = (unsigned char *)&dg->payload.eta;
    for (int i=0; i<sizeof(dg->payload.eta); i++) {
        sum += p[i];
    }
    p = (unsigned char *)&dg->payload.dest;
    for (int i=0; i<sizeof(dg->payload.dest); i++) {
        sum += p[i];
    }
    return sum;
}
/** 
 * csum_val: validate received checksum from
 * received message with the csum algorithm
 *
 * @param Data* datagram struct pointer
 * @return bool
 * 
 * Simple if-else statement to validate the received value with the cusom algorithm
 **/
bool csum_val(Data *dg){
    if (dg->check == csum_calc(dg)){
        return true;
    }
    else{return false;}
}

/** 
 * calc_length: Calculate length of udp package (in bytes)
 *
 * @param Data* datagram struct pointer
 * @return total length in bytes
 * 
 * Sum of all size (in bytes) of each field within the payload struct
 **/
unsigned short calc_length(Data *dg){
    unsigned short sum = 0;
    sum+= sizeof(dg->payload.lattitude)+sizeof(dg->payload.longtitude) +
            sizeof(dg->payload.eta)+sizeof(dg->payload.dest);
    return sum;
}
/** 
 * data_verify: Verify data with the given constraints
 *
 * @param Data* datagram struct pointer
 * @return bool
 * 
 * Verify data with the given constraints and print error messages
 **/
bool data_verify(Data *dg){
    bool flag = true;
    if(dg->version>255|| dg->version<0){
        printf("Payload version out of range\n");
        flag = false;
    }
    if(dg->udp_length<0 ||dg->udp_length>65535){
        printf("Payload length out of range\n");
        flag = false; 
    }
    if(dg->payload.lattitude<-90 ||dg->payload.lattitude>90){
        printf("Payload lattitude value out of range\n");
        flag = false; 
    }
    if(dg->payload.longtitude<-180 ||dg->payload.longtitude>180){
        printf("Payload longtitude value out of range\n");
        flag = false; 
    }
    if(dg->payload.eta<=0){
        printf("ETA value incorrect\n");
        flag = false; 
    }

    return flag;

}
/** 
 * save2disk: save function to disk
 *
 * @param Data *datagram struct pointer
 * @param file filename
 * @return success status
 * 
 * Save to disk using file I/O
 **/
bool save2disk(Data *dg, const char *file){
    // foo
}