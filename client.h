#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H
/*----------------------
 |  Includes
 -----------------------*/
#include "helper.h"
/*----------------------
 |  Global variables
 -----------------------*/
volatile bool progCont;
/*----------------------
 |  Function definition
 -----------------------*/
void InitializeFields(Data*);
void sig_handler(int);

#endif