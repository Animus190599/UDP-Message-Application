#include "helper.h"


void struct2str(Data *dg, char * buffer){
    // Get length of string to hold struct values
    // size_t len = snprintf(NULL)
    // memcpy
    printf("Hello");
    int j = snprintf(buffer, sizeof(buffer), "%lld,%c,%hu,%hd,%hd,%hu,%3s",dg->check,
             dg->version, dg->udp_length, dg->payload.lattitude, dg->payload.longtitude,
             dg->payload.eta, dg->payload.dest);
    printf("%s",*buffer);
    // char *buffer = malloc(sizeof(char)*100);
    // int offset = 0;

    // printf("hello1");
    // // Adding header
    // memcpy(buffer+offset, &dg->check,sizeof(dg->check));
    // offset+= sizeof(dg->check);
    // memcpy(buffer+offset, &dg->version,sizeof(dg->version));
    // offset+= sizeof(dg->version);
    // memcpy(buffer+offset, &dg->udp_length,sizeof(dg->udp_length));
    // offset+= sizeof(dg->udp_length);
    // fflush(stdout);
    // printf("hello2");
    // // Adding payload
    // memcpy(buffer+offset, &dg->payload.lattitude,sizeof(dg->payload.lattitude));
    // offset+= sizeof(dg->payload.lattitude);
    // memcpy(buffer+offset, &dg->payload.longtitude,sizeof(dg->payload.longtitude));
    // offset+= sizeof(dg->payload.longtitude);
    // memcpy(buffer+offset, &dg->payload.eta,sizeof(dg->payload.eta));
    // offset+= sizeof(dg->payload.eta);
    // memcpy(buffer+offset, &dg->payload.dest,sizeof(dg->payload.dest));
    // offset+= sizeof(dg->payload.dest);
    return buffer;
}
void structTest(void){
    printf("All working fine");
}
