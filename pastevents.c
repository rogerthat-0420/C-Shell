#include "headers.h"
extern Node* head_node;

char* replaceSubstring(char *str,int* stat ,const char *to_be,  char *to)
{
    int old_length;
    char *pos = strstr(str, to_be);
    int replace_len;
    int ssize=5000;
    int to_length;

    if (pos != NULL) {
        int old_length = strlen(to_be);
        int c;
        int replace_len = strlen(pos + old_length);
        int to_length = strlen(to);
        c=0; 
        memmove(pos + to_length, pos + old_length, replace_len + 1);
        int i;
        memcpy(pos, to, to_length);
        i=0;
        char*sstring;
        sstring = (char*)calloc(ssize,sizeof(char));
        for(int j=0;j<strlen(to);j++)
        {
            if(to[j]!='\n')
            {
                sstring[c++] = to[j];
            }
        }
        return sstring;
    }
}
char* pastevents(char* input_string,int* stat ,int* put_past ,Que*Q ,  char*ini_string  , char*home_dir , char* prev_path , int* dir_changes , Node*L ,int* system_call_time , char*command)
{
    int check;
    int ssize=5000;
    if(ini_string==NULL)
    {   check=Q->rear;
        *put_past =0;
        while(check>=Q->front)
        {
            printf("%s" , Q->arr[check--]);
        }
        return ini_string;
    }
    while(1)
    {   
        char* final_string = strtok_r(ini_string , " \n\t" , &ini_string );
        if(final_string==NULL)
        {   check=Q->rear;
            *put_past =0;
            while(check>=Q->front)
            {
                printf("%s" , Q->arr[check--]);
            }
            return ini_string;
        }
        else if(strcmp(final_string , "purge")==0)
        {
            *put_past = 0;
            for(int j=0;j>-1;j++)
            {
                if(!IsEmpty(Q,stat))
                { Q=pop(Q,Q->front,stat);}
                else
                {
                    break;
                }
            }
            return ini_string;
        }
        else if(strcmp(final_string , "execute")==0)
        {
            int i;
            char to_convert[50];
            int c;
            int total;
            char* command_number = strtok_r(ini_string , " \n\t" , &ini_string );
            c=0;
            int converted_int;
            for(i=0;i<strlen(command_number);i++)
            {
                if(command_number[i]>='0')
                {
                    if(command_number[i]<='9')
                    {to_convert[c++] = command_number[i];}
                }
            }
            int count;
            converted_int = atoi(to_convert);
            total = Q->rear +1;
            count = converted_int;
            // for(int k=0;k>-1;k++)
            while(1)
            {
                if(count-- >0)
                {total--;}
                else
                {break;}
            }
            
            if(total>=0)
            {   int process_bg;
                if( converted_int<=15)
                {
                    char* change_cmds;
                    change_cmds=(char*)malloc(char_s*ssize);
                    char original_substring[] = "pastevents execute ";
                    strcpy(change_cmds,Q->arr[total]);
                    
                    change_cmds[strlen(change_cmds) -1] = '\0';
                    // printf("%s" , change_cmds);
                    strcat(original_substring , to_convert);
                    // printf("%s\n" , original_substring);
                    process_bg =1;
                    input_string = replaceSubstring(original_substring ,stat,input_string ,  change_cmds);
                    char*temp_copy = change_cmds;
                    // printf("%s" , input_string);



                while(1)
                {
                    // printf("%s\n" , temp_copy);
                    char*w_semicolon = strtok_r(temp_copy , ";\n" , &temp_copy);
                    // printf("%s\n" , w_semicolon);
                    if(w_semicolon==NULL)
                    {
                        break;
                    }
                    while(1)
                    {   
                        char* copy_token ;                    
                        copy_token=strdup(w_semicolon);
                        char*w_and_token = strtok_r(w_semicolon , "&" , &w_semicolon);
                        process_bg=1;
                        if(w_and_token==NULL)
                        {
                            break;
                        }
                        int i_j;
                        if(strcmp(w_and_token ,copy_token )==0)
                        {
                            process_bg = 0;
                        }
                        
                        int is_piped;
                        while(1)
                        {    
                            is_piped = 0;
                            if(w_and_token==NULL)
                            {   
                                break;
                            }
                            i_j =0;
                            for(i_j=0;i_j<strlen(w_and_token);i_j++)
                            {
                                if(w_and_token[i_j]=='|')
                                {
                                    w_and_token = piping(w_and_token ,stat,ssize, home_dir ,prev_path ,dir_changes , system_call_time , command, L ,put_past ,Q , input_string);
                                    is_piped=1;
                                    w_and_token =NULL;
                                    break;
                                }
                            }
                        char* ff;
                        if(w_and_token==NULL)
                        {   
                            break;
                        }
                        ff=(char*)malloc(char_s*ssize); //free k
                        strcpy(ff,w_and_token); 
                        
                        char* final_token = strtok_r( w_and_token, " \t\n" ,&w_and_token );
                        if(final_token==NULL)
                        {
                            break;
                        }
                        int f_sign=0;
                        for(int j=0;j<strlen(w_and_token);j++)
                        {
                            if(w_and_token[j]=='<')
                            {
                                f_sign=1;
                            }
                            if(w_and_token[j]=='>')
                            {
                                f_sign=1;
                            }
                        }
                        if(f_sign)
                        {
                            if(redirect(ff  , stat,home_dir , prev_path , dir_changes,put_past , L , system_call_time , command , Q , input_string,ssize)==0)
                            {
                                return 0;
                            }
                            w_and_token=NULL;                           
                            break;
                        }
                        else if(strncmp(final_token , "iMan",sizeof(final_token))==0)
                        {
                            w_and_token = iman(stat,w_and_token,ssize);
                        }
                        else if(strncmp(final_token , "activities",sizeof(final_token))==0)
                        {
                            w_and_token = activities(w_and_token );

                        }
                        else if(strncmp(final_token , "fg",sizeof(final_token))==0)
                        {
                            foreground_fn(ssize,w_and_token);
                            w_and_token = NULL ;

                        }
                        else if(strncmp(final_token , "bg",sizeof(final_token))==0)
                        {
                            background_fn(ssize,w_and_token);
                            w_and_token = NULL ;

                        }
                        else if(strncmp(final_token,"warp",sizeof(final_token))==0)
                        {
                            w_and_token = warp(home_dir ,dir_changes ,w_and_token ,  prev_path);
                        }
                        else if(strncmp(final_token , "peek",sizeof(final_token))==0)
                        {
                            w_and_token = peek(home_dir, w_and_token ,dir_changes ,prev_path);
                        }
                        else if(strncmp(final_token , "seek",sizeof(final_token))==0)
                        {
                            w_and_token = seek(home_dir,stat,ssize , w_and_token , dir_changes , prev_path);
                        }
                        else if(strncmp(final_token , "proclore",sizeof(final_token))==0)
                        {
                            w_and_token = proclure(w_and_token , home_dir);
                        }
                        else if(strncmp(final_token , "neonate",sizeof(final_token))==0)
                        {
                            neonate(stat,w_and_token,ssize);
                            w_and_token =NULL ;
                        }
                        else if(strncmp(final_token , "ping",sizeof(final_token))==0)
                        {
                            w_and_token = ping(stat,w_and_token,ssize);
                        }
                        else{
                            int f_sign=0;
                            for(int j=0;j<strlen(w_and_token);j++)
                            {
                                if(w_and_token[j]=='<')
                                {
                                    f_sign=1;
                                }
                                if(w_and_token[j]=='>')
                                {
                                    f_sign=1;
                                }
                            }
                            if(f_sign)
                            {
                                if(redirect(ff  , stat,home_dir , prev_path , dir_changes,put_past , L , system_call_time , command , Q , input_string,ssize)==0)
                                {
                                    return 0;
                                }
                                w_and_token=NULL;
                                break;
                            }
                            else
                            {
                                w_and_token = system_calls(final_token , stat,process_bg , w_and_token ,system_call_time , command , L , put_past , 0, ssize);
                            }
                            }
                            }
                            free(copy_token);
                        }
                    }
                }
            } 
            //shalu
            else if(converted_int>15){
                printf("More then 15 events are not stored in database\n");
                *put_past =0;
            }
            else{
                printf("Less Than %d events are executed\n" , converted_int);
                *put_past =0;
            }
            return ini_string;
        }

    }

}