#include "headers.h"

void print_directory(int d,int* state,int ssize, int f, char *str, char *required_file, int *increment, char *stored_part , char*og_directory)
{

    struct dirent ** directory_info_array;
    int f_stat; 
    int i;
    // printf("%s\n",str);
    DIR *directory = opendir(str);
    if (directory == NULL)
    {
        printf("No such directory exists.");
        return;
    }
    f_stat = scandir(str, &directory_info_array, NULL, alphasort);
    i=0;
    while(i<f_stat)
    {
        char* concatenated_string;
        char* recursive_new_dir;
        concatenated_string=(char*)malloc(char_s*ssize);
        strcpy(concatenated_string, str); 
        if (str[strlen(str) - 1] != '/') 
        {
            strcat(concatenated_string, "/"); 
        }
        strcat(concatenated_string, directory_info_array[i]->d_name);        
        recursive_new_dir=(char*)malloc(char_s*ssize);
        if (strlen(directory_info_array[i]->d_name)>0 && directory_info_array[i]->d_name[0] != '.')
        {
            char* curr_directory;
            struct stat detail_file;
            curr_directory=(char*)malloc(char_s*ssize);
            if (stat(concatenated_string, &detail_file)== -1)
            {
                continue;
            }
            strcpy(curr_directory, str); 


            if (str[strlen(str) - 1] != '/') 
            {
                strcat(curr_directory, "/"); 
            }

            strcat(curr_directory, directory_info_array[i]->d_name);
            
            strcpy(recursive_new_dir, og_directory); 

            if (og_directory[strlen(og_directory) - 1] != '/') 
            {
                strcat(recursive_new_dir, "/"); 
            }
            f_stat=strncmp(required_file, directory_info_array[i]->d_name, strlen(required_file));
            strcat(recursive_new_dir, directory_info_array[i]->d_name); 
            if (!f_stat)
            {
                if (d == 1 ) 
                {
                    if(S_ISDIR(detail_file.st_mode))
                    {
                            if(directory_info_array[i]->d_name[0] != '.')
                            {
                                printf("\033[34m%s\n\033[0m", curr_directory);
                                (*increment)++;
                                strcpy(stored_part, curr_directory);
                            }
                    }
                }
                else if (f == 1)
                {
                    if(S_ISREG(detail_file.st_mode) )
                    {
                        if(directory_info_array[i]->d_name[strlen(required_file)]=='.')
                        {
                            printf("\033[32m%s\n\033[0m", curr_directory);
                            (*increment)++;
                            strcpy(stored_part, curr_directory);
                        }
                    }
                }
                else if(f==0) 
                {
                    (*increment) += (d == 0 && (directory_info_array[i]->d_name[strlen(required_file)] == '.' || directory_info_array[i]->d_name[strlen(required_file)] == '\0')) ? ((S_ISDIR(detail_file.st_mode)) ? (printf("\033[34m%s\n\033[0m", curr_directory), strcpy(stored_part, curr_directory), 1) : ((S_ISREG(detail_file.st_mode)) ? (printf("\033[32m%s\n\033[0m", curr_directory), strcpy(stored_part, curr_directory), 1) : 0)) : 0;

                }
            }
            if (S_ISDIR(detail_file.st_mode)) 
            {
                if(strlen(directory_info_array[i]->d_name)>0 && directory_info_array[i]->d_name[0] != '.')
                {
                    print_directory(d, state, ssize, f, curr_directory, required_file, increment, stored_part , recursive_new_dir);
                }
            }
        }

        i++;
    }
}

char *seek(char *home_dir,int* state, int ssize, char *rest_string, int *dir_changes, char *prev_path)
{

 int go_away;
    char *n_command;
    int pid_r;
    n_command = (char*)malloc(ssize*char_s); //free k
    go_away =0;
    if(strchr(rest_string , '<') || strchr(rest_string, '>'))
    {
        char* s1;
        s1=(char*)malloc(char_s*ssize); // free k
         
        char* s2;
        s2=(char*)malloc(char_s*ssize); // free k
        strcpy(s1, rest_string);
        char* f_o;
        strcpy(s2,rest_string);
        f_o=(char*)malloc(char_s*ssize); // free k
        char* f_i;
        f_i=(char*)malloc(char_s*ssize); // free k
        
        int conc;
        int incoming;
        conc = 0;
        char*other_f = (char*)calloc(ssize,char_s);
        incoming= 0;
        int flag;
        int i;
        flag =0 ;
        int c;
        while(s1[i]!='\0')
        {
            if (s1[i] == '>' || s1[i] == '<')
            {
                flag =1;
                break;
            }
            n_command[i] = s1[i++]; 
        }
        c=0;
        int t;
        while(s1[i]!='\0')
        {
            other_f[c++] = s1[i++];
        }
        t =0;
        char* token = strtok_r(other_f , " \t\n" , &other_f);
        char* args[10];
        while(token!=NULL)
        {
            args[t++] = token;
            token = strtok_r(other_f , " \t\n" , &other_f);
        }
        int tt=0;
        while(tt<t)
        {
            tt++;
            if (strncmp(args[tt-1], "<", 1) == 0)
            {
                strcpy(f_i ,args[tt]);
                incoming = 1;
            }
            if (strncmp(args[tt-1], ">>", 2) == 0)
            {
                go_away = 1;
                strcpy(f_o , args[tt]);
                conc =1;
            } 
            if (strcmp(args[tt-1], ">") == 0)
            {
                strcpy(f_o , args[tt]);
                go_away = 1;
            }
        }
        if(incoming)
        {
            FILE* input_pointer = fopen(f_i , "r");
            char buffer[10000]; 
            if (input_pointer == NULL) {
                printf("Failed to open the file");
                *state=0;
                return NULL;
            }
            while (fgets(buffer, sizeof(buffer), input_pointer) != NULL) {
                strcat(n_command ,buffer);
            }
            fclose(input_pointer);
        }        
    strcpy(rest_string,n_command);
    }


    int increment = 0;
    int f = 0;
    int d = 0;
    char curr_dir[ssize];
    getcwd(curr_dir , sizeof(ssize));
    int e = 0;
    while (1)
    {
        char *token = strtok_r(rest_string, " \n\t", &rest_string);
        if (token == NULL)
        {
            return rest_string;
        }
        int flag;
        flag=strncmp(token, "-d",2);
        if (flag == 0)
        {
            d = 1;
            if (f == 1)
            {
                printf("Invalid flags!\n");
                return rest_string;
            }
        }
        else if ((strncmp(token, "-f",2)) == 0)
        {
            f = 1;
            if (d == 1)
            {
                printf("Invalid flags!\n");
                return rest_string;
            }
        }
        else if (strncmp(token, "-e",2) == 0)
        {
            e = 1;
        }
        else
        {
            char* stored_part;
            char* s3_dir;
            stored_part=(char*)malloc(char_s*ssize);            
            char *changing_directory = strtok_r(rest_string, " \n\t", &rest_string);
            s3_dir=(char*)malloc(char_s*ssize);
            char *curr_d = getcwd(s3_dir, ssize);
            if (changing_directory == NULL)
            {
                changing_directory = curr_d;
            }
            if (changing_directory[0] == '~')
            {
                int j;
                char *new_directory_home = (char *)calloc(ssize, sizeof(char));
                int i;
                j=0;
                for(i=0;i<strlen(home_dir);i++)
                {
                    new_directory_home[j++] = home_dir[i];
                }
                for(i=1;i<strlen(changing_directory);i++)
                {
                    new_directory_home[j++] = changing_directory[i];
                }
                // printf("%s\n", new_directory_home);
                changing_directory = new_directory_home;
            }
            int err_dir = chdir(changing_directory);
            char*og_directory = strdup(changing_directory);
            strcat(og_directory ,"/");
            int t;
            char final_directory[ssize] ;
            getcwd(final_directory,ssize);
            strcat(og_directory , final_directory);
            print_directory(d,state,ssize, f, final_directory, token, &increment, stored_part , og_directory);
            t = 0;
            if (increment == 0)
            {
                printf("No match found!\n");
                return rest_string;
            }
            if (e == 1)
            {
                if (increment == 1) 
                {
                    struct stat detail_file;
                    int err_dir;
                    DIR *directory = opendir(stored_part);
                    if (stat(stored_part, &detail_file) == -1)
                    {
                        printf("Error: Stat");
                        *state=0;
                        continue;
                    }               
                    if (directory != NULL)
                    {
                        chdir(stored_part);
                        t=1;
                    }
                    else if (S_ISREG(detail_file.st_mode))
                    {
                        FILE *file = fopen(stored_part, "r");
                        ssize_t data_size;
                        char* buffer;
                        if (file == NULL)
                        {
                            printf("Error: Fopen Failed");
                            return rest_string;
                        }
                        buffer=(char*)malloc(char_s*ssize);
                        fread(buffer, 1, sizeof(buffer), file);

                        while (data_size  > 0)
                        {
                            fwrite(buffer, 1, data_size, stdout);
                        }
                        free(buffer);
                    }
                }
                else if (increment == 0)
                {
                    printf("No match found!\n");
                }
            }
            if (t == 0)
                {chdir(curr_d);}
        }
    }
}