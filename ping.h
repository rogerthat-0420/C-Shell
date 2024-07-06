#ifndef __PING__
#define __PING__

#include "headers.h"

char* ping(int* stat,char* rest_string,int ssize);
void ctrl_c_handler(int sig);
void ctrl_d_handler(int sig);
void ctrl_z_handler(int sig);


#endif