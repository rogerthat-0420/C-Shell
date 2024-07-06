#ifndef __NEONATE__
#define __NEONATE__

#include "headers.h"

void die(const char *s);
void disableRawMode();
void enableRawMode();
void neonate(int* stat,char* initial_string,int ssize);



#endif