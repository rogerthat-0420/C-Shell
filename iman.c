#include "headers.h"

char* iman(int* stat,char* inital_cmd,int ssize)
{
    char*final_cmd = strtok_r(inital_cmd , " \t\n" ,&inital_cmd );
    int socket_descriptor;
    char *host = "man.he.net"; 
    struct hostent *server;
    

    server = gethostbyname(host);
    struct sockaddr_in server_addr;
    socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_port = htons(80); 
    if (socket_descriptor < 0) {
        printf("Error Opening Socket!");
        *stat=0;
        return inital_cmd;
    }
    server_addr.sin_family = AF_INET;


    if (server == NULL) {
        printf("Error - Host!");
        *stat=0;
        return inital_cmd;
    }



    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    char* get_request_str;
    if (connect(socket_descriptor, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Error - Could not Connect!");
        *stat=0;
        return inital_cmd;

    }

    get_request_str=(char*)malloc(sizeof(char)*10000); // free k
    int flag;
    snprintf(get_request_str, sizeof(get_request_str), "GET http://man.he.net/?topic=%s&section=all HTTP/1.1\r\nHost: %s\r\n\r\n", final_cmd, host);
    if (send(socket_descriptor, get_request_str, strlen(get_request_str), 0) < 0) {
        printf("Error sending GET Request!");
        *stat=0;
        return inital_cmd;

    }

    char* html_pg_rec;
    flag=0;
    long int data_size_rec;
    html_pg_rec=(char*)malloc(char_s*ssize);
    while ((data_size_rec = recv(socket_descriptor, html_pg_rec, sizeof(html_pg_rec), 0)) > 0) 
    {
        int i; 
        char* result = strstr(html_pg_rec , "NAME\n");
        if(flag ==1)
        {
            char* to_break = strstr(html_pg_rec , "AUTHOR");
            if(to_break!=NULL)
            {
                i = 0;
                while(i < to_break - html_pg_rec)
                {
                    printf("%c", html_pg_rec[i]);
                    i++;
                }
                break;
            }
        }

        if(result!=NULL)
        {
            char* to_break = strstr(result , "AUTHOR");
            flag = 1;
            if(to_break!=NULL)
            {
                i = 0;
                while(i < to_break - result)
                {
                    printf("%c", result[i]);
                    i++;
                }
                break;
            }
            else{
                printf("%s" , result);
            }
        *stat=1;

        }       
    }
    if(!flag)
    {
        printf("ERROR\n\tNo such command\n");
        *stat=0;
    }

    if (data_size_rec < 0) {
        printf("Error - Couldn't Receive response!");
        *stat=0;
        return inital_cmd;
    }
    close(socket_descriptor);

    return inital_cmd;
}
