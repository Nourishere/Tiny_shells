#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUF 1024
#define MAX_ARGS 20
#define INIT_SIZE 4
#define EXIT_STATUS 3

char ** parse_input(char * input_buff);
void free_looped(char ** arr);
void my_pwd(void);
void my_echo(char** newarg);
void my_cd(char** newarg);
