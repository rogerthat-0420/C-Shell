#include "headers.h"

char *peek(char *home_dir, char *rem_token, int *dir_changes, char *prev_path)
{
    char *cwd = getcwd(NULL, 0);
    int f_a = 0;
    int f_other_cmds = 0;
    int f_l = 0;

    while (1)
    {

        char *t = strtok_r(rem_token, " \t\n", &rem_token);
        if (t == NULL)
        {
            if (f_other_cmds)
            {
                chdir(cwd);
                return rem_token;
            }

            char *curr_dir;
            int num_items;
            f_other_cmds = 1;
            curr_dir = (char *)malloc(char_s * 5000); // free k
            struct dirent **dir_str;
            getcwd(curr_dir, 5000);
            num_items = scandir(curr_dir, &dir_str, NULL, alphasort);
            // error handling
            if (num_items < 0)
            {
                printf("Unable to Scan Directory!\n");
                chdir(cwd);
                return rem_token;
            }

            if (f_a)
            {
                if (f_l)
                {
                    DIR *dir = opendir(curr_dir);
                    if (dir == NULL)
                    {
                        printf("Directory doesn't exist! \n");
                        chdir(cwd);

                        return rem_token;
                    }
                    for (int i = 0; i < num_items; i++)
                    {
                        struct stat file_stat;
                        char *path_string; // free k
                        path_string = (char *)malloc(char_s * 10000);
                        snprintf(path_string, 10000, "%s/%s", curr_dir, dir_str[i]->d_name);
                        if (stat(path_string, &file_stat) == -1)
                        {
                            perror("opendir");
                            break;
                        }
                        else
                        {
                            if (S_ISDIR(file_stat.st_mode))
                            {
                                printf("d");
                            }
                            else
                            {
                                printf("-");
                            }

                            if (file_stat.st_mode & S_IRUSR)
                            {
                                printf("r");
                            }
                            else
                            {
                                printf("-");
                            }

                            if (file_stat.st_mode & S_IWUSR)
                            {
                                printf("w");
                            }
                            else
                            {
                                printf("-");
                            }

                            if (file_stat.st_mode & S_IXUSR)
                            {
                                printf("x");
                            }
                            else
                            {
                                printf("-");
                            }

                            if (file_stat.st_mode & S_IRGRP)
                            {
                                printf("r");
                            }
                            else
                            {
                                printf("-");
                            }

                            if (file_stat.st_mode & S_IWGRP)
                            {
                                printf("w");
                            }
                            else
                            {
                                printf("-");
                            }

                            if (file_stat.st_mode & S_IXGRP)
                            {
                                printf("x");
                            }
                            else
                            {
                                printf("-");
                            }

                            if (file_stat.st_mode & S_IROTH)
                            {
                                printf("r");
                            }
                            else
                            {
                                printf("-");
                            }

                            if (file_stat.st_mode & S_IWOTH)
                            {
                                printf("w");
                            }
                            else
                            {
                                printf("-");
                            }

                            if (file_stat.st_mode & S_IXOTH)
                            {
                                printf("x");
                            }
                            else
                            {
                                printf("-");
                            }

                            struct group *group_info = getgrgid(file_stat.st_gid);
                            char time_str[100];
                            struct passwd *user_info = getpwuid(file_stat.st_uid);
                        unsigned long nlink_value;
                        char *user_name = "";
                        char *group_name = "";
                        long size_value;

                        if (user_info != NULL) {
                            user_name = user_info->pw_name;
                        }

                        if (group_info != NULL) {
                            group_name = group_info->gr_name;
                        }

                        if (file_stat.st_nlink >= 0) {
                            nlink_value = (unsigned long)file_stat.st_nlink;
                        } else {
                            nlink_value = 0;   
                        }

                        if (file_stat.st_size >= 0) {
                            size_value = (long)file_stat.st_size;
                        } else {
                            size_value = 0;  
                        }

                        fprintf(stdout, " %2lu %8s %8s %8ld ", nlink_value, user_name, group_name, size_value);


                            strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
                            printf("%s \t", time_str);
                            if (file_stat.st_mode & S_IXUSR)
                                printf("\033[32m%s\033[0m", dir_str[i]->d_name);
                            else if (S_ISDIR(file_stat.st_mode))
                                printf("\033[34m%s\033[0m", dir_str[i]->d_name);
                            else
                            {
                                printf("%s", dir_str[i]->d_name);
                            }
                            printf("\n");
                        }
                    }
                }
                else
                {
                    for (int i = 0; i < num_items; i++)
                    {
                        struct stat file_stat;
                        char path_string[10000];
                        snprintf(path_string, 10000, "%s/%s", curr_dir, dir_str[i]->d_name);
                        if (stat(path_string, &file_stat) == -1)
                        {
                            perror("opendir");
                            break;
                        }
                        else
                        {

                            if (file_stat.st_mode & S_IXUSR)
                            {
                                printf("\033[32m%s\033[0m\n", dir_str[i]->d_name);
                            }
                            else if (S_ISDIR(file_stat.st_mode))
                            {
                                printf("\033[34m%s\033[0m\n", dir_str[i]->d_name);
                            }
                            else
                            {
                                printf("%s\n", dir_str[i]->d_name);
                            }
                        }
                    }
                }
            }
            else
            {
                if (f_l)
                {
                    DIR *dir = opendir(curr_dir);
                    if (dir == NULL)
                    {
                        printf("No such directory exists.\n");
                        chdir(cwd);

                        return rem_token;
                    }
                    for (int i = 0; i < num_items; i++)
                    {
                        if (dir_str[i]->d_name[0] != '.')
                        {

                            struct stat file_stat;
                            char path_string[10000];
                            snprintf(path_string, 10000, "%s/%s", curr_dir, dir_str[i]->d_name);
                            if (stat(path_string, &file_stat) == -1)
                            {
                                perror("opendir");
                                break;
                            }
                            else
                            {
                                if (S_ISDIR(file_stat.st_mode))
                                {
                                    printf("d");
                                }
                                else
                                {
                                    printf("-");
                                }

                                if (file_stat.st_mode & S_IRUSR)
                                {
                                    printf("r");
                                }
                                else
                                {
                                    printf("-");
                                }

                                if (file_stat.st_mode & S_IWUSR)
                                {
                                    printf("w");
                                }
                                else
                                {
                                    printf("-");
                                }

                                if (file_stat.st_mode & S_IXUSR)
                                {
                                    printf("x");
                                }
                                else
                                {
                                    printf("-");
                                }

                                if (file_stat.st_mode & S_IRGRP)
                                {
                                    printf("r");
                                }
                                else
                                {
                                    printf("-");
                                }

                                if (file_stat.st_mode & S_IWGRP)
                                {
                                    printf("w");
                                }
                                else
                                {
                                    printf("-");
                                }

                                if (file_stat.st_mode & S_IXGRP)
                                {
                                    printf("x");
                                }
                                else
                                {
                                    printf("-");
                                }

                                if (file_stat.st_mode & S_IROTH)
                                {
                                    printf("r");
                                }
                                else
                                {
                                    printf("-");
                                }

                                if (file_stat.st_mode & S_IWOTH)
                                {
                                    printf("w");
                                }
                                else
                                {
                                    printf("-");
                                }

                                if (file_stat.st_mode & S_IXOTH)
                                {
                                    printf("x");
                                }
                                else
                                {
                                    printf("-");
                                }

                                struct group *group_info = getgrgid(file_stat.st_gid);
                                char time_str[100];
                                struct passwd *user_info = getpwuid(file_stat.st_uid);
                        unsigned long nlink_value;
                        char *user_name = "";
                        char *group_name = "";
                        long size_value;

                        if (user_info != NULL) {
                            user_name = user_info->pw_name;
                        }

                        if (group_info != NULL) {
                            group_name = group_info->gr_name;
                        }

                        if (file_stat.st_nlink >= 0) {
                            nlink_value = (unsigned long)file_stat.st_nlink;
                        } else {
                            nlink_value = 0;   
                        }

                        if (file_stat.st_size >= 0) {
                            size_value = (long)file_stat.st_size;
                        } else {
                            size_value = 0;  
                        }

                        fprintf(stdout, " %2lu %8s %8s %8ld ", nlink_value, user_name, group_name, size_value);
                                strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
                                printf("%s \t", time_str);
                                if (file_stat.st_mode & S_IXUSR)
                                    printf("\033[32m%s\033[0m", dir_str[i]->d_name);
                                else if (S_ISDIR(file_stat.st_mode))
                                    printf("\033[34m%s\033[0m", dir_str[i]->d_name);
                                else
                                {
                                    printf("%s", dir_str[i]->d_name);
                                }
                                printf("\n");
                            }
                        }
                    }
                }
                else
                {
                    // a=0 l=0
                    for (int i = 0; i < num_items; i++)
                    {
                        if (dir_str[i]->d_name[0] != '.')
                        {

                            struct stat file_stat;
                            char path_string[10000];
                            snprintf(path_string, 10000, "%s/%s", curr_dir, dir_str[i]->d_name);
                            if (stat(path_string, &file_stat) == -1)
                            {
                                perror("opendir");
                                break;
                            }
                            else
                            {

                                if (file_stat.st_mode & S_IXUSR)
                                {
                                    printf("\033[32m%s\033[0m\n", dir_str[i]->d_name);
                                }
                                else if (S_ISDIR(file_stat.st_mode))
                                {
                                    printf("\033[34m%s\033[0m\n", dir_str[i]->d_name);
                                }
                                else
                                {
                                    printf("%s\n", dir_str[i]->d_name);
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            if (strcmp(t, "-l") == 0)
            {
                f_l = 1;
            }
            else if (strcmp(t, "-al") == 0)
            {
                f_a = 1;
                f_l = 1;
            }
            else if (strcmp(t, "-la") == 0)
            {
                f_a = 1;
                f_l = 1;
            }
            else if (strcmp(t, "-a") == 0)
            {
                f_a = 1;
            }
            else
            {

                f_other_cmds = 1;
                // null char*
                if (t == NULL)
                {
                    break;
                }
                char curr_dir[5000];
                getcwd(curr_dir, 5000);

                char new_dir[5000];
                if (t[0] == '~')
                {
                    char *rel_path;
                    rel_path = malloc(sizeof(char) * 5000);

                    int i = 1;

                    while (t[i] != '\0')
                    {
                        rel_path[i - 1] = t[i++];
                    }
                    rel_path[i - 1] = '\0';

                    chdir(home_dir);
                    chdir(rel_path);

                    getcwd(curr_dir, 5000);
                }
                else if (strcmp(t, "-") == 0)
                {
                    if (*dir_changes == 1)
                    {
                        char *temp_string = strdup(prev_path);
                        getcwd(prev_path, 5000);
                        chdir(temp_string);
                        // error handling
                        getcwd(curr_dir, 5000);
                    }
                    else
                    {
                        printf("No previous directory\n");
                    }
                }
                else
                {
                    chdir(t);
                    getcwd(curr_dir, 5000);
                }
                // error handles for chdir

                int num_items;
                struct dirent **dir_str;
                // char curr_dir[5000];
                getcwd(curr_dir, 5000);
                num_items = scandir(curr_dir, &dir_str, NULL, alphasort);
                // error handling

                if (f_a)
                {
                    if (f_l)
                    {
                        DIR *dir = opendir(curr_dir);
                        if (dir == NULL)
                        {
                            printf("No such directory exists.\n");
                            chdir(cwd);

                            return rem_token;
                        }
                        for (int i = 0; i < num_items; i++)
                        {

                            struct stat file_stat;
                            char path_string[10000];
                            snprintf(path_string, 10000, "%s/%s", curr_dir, dir_str[i]->d_name);
                            if (stat(path_string, &file_stat) == -1)
                            {
                                perror("opendir");
                                break;
                            }
                            else
                            {
                                if (S_ISDIR(file_stat.st_mode))
                                {
                                    printf("d");
                                }
                                else
                                {
                                    printf("-");
                                }

                                if (file_stat.st_mode & S_IRUSR)
                                {
                                    printf("r");
                                }
                                else
                                {
                                    printf("-");
                                }

                                if (file_stat.st_mode & S_IWUSR)
                                {
                                    printf("w");
                                }
                                else
                                {
                                    printf("-");
                                }

                                if (file_stat.st_mode & S_IXUSR)
                                {
                                    printf("x");
                                }
                                else
                                {
                                    printf("-");
                                }

                                if (file_stat.st_mode & S_IRGRP)
                                {
                                    printf("r");
                                }
                                else
                                {
                                    printf("-");
                                }

                                if (file_stat.st_mode & S_IWGRP)
                                {
                                    printf("w");
                                }
                                else
                                {
                                    printf("-");
                                }

                                if (file_stat.st_mode & S_IXGRP)
                                {
                                    printf("x");
                                }
                                else
                                {
                                    printf("-");
                                }

                                if (file_stat.st_mode & S_IROTH)
                                {
                                    printf("r");
                                }
                                else
                                {
                                    printf("-");
                                }

                                if (file_stat.st_mode & S_IWOTH)
                                {
                                    printf("w");
                                }
                                else
                                {
                                    printf("-");
                                }

                                if (file_stat.st_mode & S_IXOTH)
                                {
                                    printf("x");
                                }
                                else
                                {
                                    printf("-");
                                }

                                struct group *group_info = getgrgid(file_stat.st_gid);
                                char time_str[100];
                                struct passwd *user_info = getpwuid(file_stat.st_uid);
                        unsigned long nlink_value;
                        char *user_name = "";
                        char *group_name = "";
                        long size_value;

                        if (user_info != NULL) {
                            user_name = user_info->pw_name;
                        }

                        if (group_info != NULL) {
                            group_name = group_info->gr_name;
                        }

                        if (file_stat.st_nlink >= 0) {
                            nlink_value = (unsigned long)file_stat.st_nlink;
                        } else {
                            nlink_value = 0;   
                        }

                        if (file_stat.st_size >= 0) {
                            size_value = (long)file_stat.st_size;
                        } else {
                            size_value = 0;  
                        }

                        fprintf(stdout, " %2lu %8s %8s %8ld ", nlink_value, user_name, group_name, size_value);
                                strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
                                printf("%s \t", time_str);
                                if (file_stat.st_mode & S_IXUSR)
                                    printf("\033[32m%s\033[0m", dir_str[i]->d_name);
                                else if (S_ISDIR(file_stat.st_mode))
                                    printf("\033[34m%s\033[0m", dir_str[i]->d_name);
                                else
                                {
                                    printf("%s", dir_str[i]->d_name);
                                }
                                printf("\n");
                            }
                        }
                    }
                    else
                    {
                        for (int i = 0; i < num_items; i++)
                        {
                            struct stat file_stat;
                            char path_string[10000];
                            snprintf(path_string, 10000, "%s/%s", curr_dir, dir_str[i]->d_name);
                            if (stat(path_string, &file_stat) == -1)
                            {
                                perror("opendir");
                                break;
                            }
                            else
                            {

                                if (file_stat.st_mode & S_IXUSR)
                                {
                                    printf("\033[32m%s\033[0m\n", dir_str[i]->d_name);
                                }
                                else if (S_ISDIR(file_stat.st_mode))
                                {
                                    printf("\033[34m%s\033[0m\n", dir_str[i]->d_name);
                                }
                                else
                                {
                                    printf("%s\n", dir_str[i]->d_name);
                                }
                            }
                        }
                    }
                }
                else
                {
                    if (f_l)
                    {
                        DIR *dir = opendir(curr_dir);
                        if (dir == NULL)
                        {
                            printf("No such directory exists.\n");
                            chdir(cwd);

                            return rem_token;
                        }
                        for (int i = 0; i < num_items; i++)
                        {
                            if (dir_str[i]->d_name[0] != '.')
                            {

                                struct stat file_stat;
                                char path_string[10000];
                                snprintf(path_string, 10000, "%s/%s", curr_dir, dir_str[i]->d_name);
                                if (stat(path_string, &file_stat) == -1)
                                {
                                    perror("opendir");
                                    break;
                                }
                                else
                                {
                                    if (S_ISDIR(file_stat.st_mode))
                                    {
                                        printf("d");
                                    }
                                    else
                                    {
                                        printf("-");
                                    }

                                    if (file_stat.st_mode & S_IRUSR)
                                    {
                                        printf("r");
                                    }
                                    else
                                    {
                                        printf("-");
                                    }

                                    if (file_stat.st_mode & S_IWUSR)
                                    {
                                        printf("w");
                                    }
                                    else
                                    {
                                        printf("-");
                                    }

                                    if (file_stat.st_mode & S_IXUSR)
                                    {
                                        printf("x");
                                    }
                                    else
                                    {
                                        printf("-");
                                    }

                                    if (file_stat.st_mode & S_IRGRP)
                                    {
                                        printf("r");
                                    }
                                    else
                                    {
                                        printf("-");
                                    }

                                    if (file_stat.st_mode & S_IWGRP)
                                    {
                                        printf("w");
                                    }
                                    else
                                    {
                                        printf("-");
                                    }

                                    if (file_stat.st_mode & S_IXGRP)
                                    {
                                        printf("x");
                                    }
                                    else
                                    {
                                        printf("-");
                                    }

                                    if (file_stat.st_mode & S_IROTH)
                                    {
                                        printf("r");
                                    }
                                    else
                                    {
                                        printf("-");
                                    }

                                    if (file_stat.st_mode & S_IWOTH)
                                    {
                                        printf("w");
                                    }
                                    else
                                    {
                                        printf("-");
                                    }

                                    if (file_stat.st_mode & S_IXOTH)
                                    {
                                        printf("x");
                                    }
                                    else
                                    {
                                        printf("-");
                                    }

                                    struct group *group_info = getgrgid(file_stat.st_gid);
                                    char time_str[100];
                                    struct passwd *user_info = getpwuid(file_stat.st_uid);
                       unsigned long nlink_value;
                        char *user_name = "";
                        char *group_name = "";
                        long size_value;

                        if (user_info != NULL) {
                            user_name = user_info->pw_name;
                        }

                        if (group_info != NULL) {
                            group_name = group_info->gr_name;
                        }

                        if (file_stat.st_nlink >= 0) {
                            nlink_value = (unsigned long)file_stat.st_nlink;
                        } else {
                            nlink_value = 0;   
                        }

                        if (file_stat.st_size >= 0) {
                            size_value = (long)file_stat.st_size;
                        } else {
                            size_value = 0;  
                        }

                        fprintf(stdout, " %2lu %8s %8s %8ld ", nlink_value, user_name, group_name, size_value);

                                    strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
                                    printf("%s \t", time_str);
                                    if (file_stat.st_mode & S_IXUSR)
                                        printf("\033[32m%s\033[0m", dir_str[i]->d_name);
                                    else if (S_ISDIR(file_stat.st_mode))
                                        printf("\033[34m%s\033[0m", dir_str[i]->d_name);
                                    else
                                    {
                                        printf("%s", dir_str[i]->d_name);
                                    }
                                    printf("\n");
                                }
                            }
                        }
                    }
                    else
                    {
                        // a=0 l=0
                        for (int i = 0; i < num_items; i++)
                        {
                            if (dir_str[i]->d_name[0] != '.')
                            {

                                struct stat file_stat;
                                char path_string[10000];
                                snprintf(path_string, 10000, "%s/%s", curr_dir, dir_str[i]->d_name);
                                if (stat(path_string, &file_stat) == -1)
                                {
                                    perror("opendir");
                                    break;
                                }
                                else
                                {

                                    if (file_stat.st_mode & S_IXUSR)
                                    {
                                        printf("\033[32m%s\033[0m\n", dir_str[i]->d_name);
                                    }
                                    else if (S_ISDIR(file_stat.st_mode))
                                    {
                                        printf("\033[34m%s\033[0m\n", dir_str[i]->d_name);
                                    }
                                    else
                                    {
                                        printf("%s\n", dir_str[i]->d_name);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } 
    }
    chdir(cwd);
    return rem_token;
}
