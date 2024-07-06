
#ifndef SYSTEM_CALLS
#define SYSTEM_CALLS

#include "linked_list.h"
#include "headers.h"

int redirect(char* initial_string,int* stat , char* home_dir , char* prev_path , int* dir_changes , int* past_push, Node*L ,int* system_call_time , char*command ,Que*Q , char* s_inut_string,int ssize );
void system_calls2(char*final_string ,int* stat, char*initial_string,int ssize);
char* system_calls(char*final_string,int* stat , int bg_process , char*initial_string , int*final_time , char*command , Node*L ,int* past_push , int is_piped,int ssize);

#endif

