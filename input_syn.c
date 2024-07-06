#include"headers.h"
void input_synthesizer(char* str,int ssize,int* stat,char* home_dir,int* dir_changes,char* prev_path,int flag_bg, char* command, Node* L,int* include_in_history, char* input_string,char* filename,int * final,Que* Q)
{   
    char* semicolon_token = strdup(str);
    while(2)
    {
        if(semicolon_token==NULL)
        {
            break;
        }
        else
        {
            char* w_semicolon_token=strtok_r(semicolon_token,";\n",&semicolon_token);
            if(w_semicolon_token==NULL)
            {
                break;
            }

            char temp_copy[5000];
            
            while(2)
            {
            if(w_semicolon_token==NULL)
            {
                break;
            } 
                char* w_and_token;
                strcpy(temp_copy,w_semicolon_token);
                flag_bg=1;
                w_and_token=strtok_r(w_semicolon_token,"&;",&w_semicolon_token);
                if(w_and_token==NULL)
                {
                    break;
                }
                
                if(strcmp(w_and_token,temp_copy)==0)
                {
                    flag_bg=0;
                }
                
                while(3)
                {
                    int i_j;
                    int is_piped;
                    if(w_and_token==NULL)
                    {
                        break;
                    }
                    is_piped = 0;
                    char* copy_2;
                    for(i_j=0;i_j<strlen(w_and_token);i_j++)
                    {
                        if(w_and_token[i_j]=='|')
                        {
                            is_piped=1;
                            w_and_token = piping(w_and_token ,stat,ssize, home_dir ,prev_path ,dir_changes , final , command, L ,include_in_history ,Q ,  input_string );
                            w_and_token =NULL;
                            break;
                        }
                    }
                    copy_2=(char*)malloc(char_s*ssize);
                    if(w_and_token==NULL)
                    {   
                        break;
                    }
                    copy_2= strdup(w_and_token);
                    strcpy(copy_2,w_and_token);
                    char* final_str;
                    final_str = strtok_r(w_and_token," \t\n;&",&w_and_token);
                    int f_sign=0;
                    if(final_str==NULL)
                    {
                        break;
                    }
                    for(int k=0;k<strlen(w_and_token);k++)
                    {
                        if(w_and_token[k]=='<')
                        {
                            f_sign=1;
                        }
                        if(w_and_token[k]=='>')
                        {
                            f_sign=1;
                        }
                    }
                    if(f_sign)
                    {
                        if(redirect(copy_2  , stat,home_dir , prev_path , dir_changes,include_in_history , L , final , command , Q , input_string,ssize)==0)
                            return ;
                        w_and_token=NULL;
                        break;
                    }
                    else if(strcmp(final_str , "activities")==0)
                    {
                        w_and_token = activities(w_and_token );
                    }
                    else if(strcmp(final_str , "iMan")==0)
                    {
                        w_and_token = iman(stat,w_and_token,ssize);
                    }
                    else if(strcmp(final_str , "fg")==0)
                    {
                        foreground_fn(ssize,w_and_token);
                        w_and_token = NULL ;
                    }
                    else if(strcmp(final_str , "bg")==0)
                    {
                        background_fn(ssize,w_and_token);
                        w_and_token = NULL ;
                    }
                    else if(strcmp(final_str , "pastevents")==0)
                    {
                        w_and_token = pastevents(input_string ,stat,include_in_history , Q ,  w_and_token , home_dir , prev_path , dir_changes , L , final , command );
                    }
                    else if(strcmp(final_str,"warp")==0)
                    {
                        w_and_token = warp(home_dir ,dir_changes , w_and_token , prev_path);
                    }
                    else if(strcmp(final_str , "peek")==0)
                    {
                    w_and_token = peek( home_dir ,w_and_token ,dir_changes,prev_path);
                    }
                    else if(strcmp(final_str , "seek")==0)
                    {
                        w_and_token = seek(home_dir,stat,ssize , w_and_token , dir_changes , prev_path);
                    }
                    else if(strcmp(final_str , "proclore")==0)
                    {
                        w_and_token = proclure(w_and_token , home_dir);
                    }
                    else if(strcmp(final_str , "ping")==0)
                    {
                        w_and_token = ping(stat,w_and_token,ssize);
                    }
                    else if(strcmp(final_str , "neonate")==0)
                    {
                        neonate(stat,w_and_token,ssize);
                        w_and_token =NULL ;
                    }
                    else{
                        f_sign=0;
                        for(int k=0;k<strlen(w_and_token);k++)
                        {
                            if(w_and_token[k]=='<')
                            {
                                f_sign=1;
                            }
                            if(w_and_token[k]=='>')
                            {
                                f_sign=1;
                            }
                        }
                        if(f_sign)
                        {
                            if(redirect(copy_2  , stat,home_dir , prev_path , dir_changes,include_in_history , L , final , command , Q , input_string,ssize)==0)
                                return ;
                            w_and_token=NULL;
                            break;
                        }
                        else{
                        w_and_token = system_calls(final_str , stat,flag_bg , w_and_token ,final , command , L , include_in_history , 0,ssize);
                        }
                    }
                }
            }
        }
        FILE* FilePointer_2 = fopen(filename , "w");
        if(*include_in_history ==1)  
        {
            if(strcmp(show_rear(Q,Q->rear,stat) , input_string)!=0)
            {Q = pastevents_push(Q , input_string,stat);}
        }
        write_to_file(FilePointer_2 , Q,stat);
        fclose(FilePointer_2);
    }

    
}
