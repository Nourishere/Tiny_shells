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

char buff[MAX_BUF];
char * arr;
int err;
int main(int argc, char* argv[]){
	if(argc > 1){
		printf("Use the shell with no arguments\n");
		return -1;
	}
	else{
		while(1){
			printf("$: ");
			fgets(buff,MAX_BUF,stdin);
			buff[strlen(buff)-1] = 0;
			if(strlen(buff) == 0){
				continue;	
			}
			char ** newarg = parse_input(buff);
			pid_t pid = fork();	
			if(pid > 0){
				/* we are in the parent process */
				int status;
				while (wait(&status)>1){;
					if(WEXITSTATUS(status) == EXIT_STATUS){
						exit(0);
					}
				}		
			}
			else if(pid==0){
				/* we are in the child process */

				if(0 == strcmp(newarg[0],"exit")){
					exit(EXIT_STATUS);
				}
				else if(0 == strcmp(newarg[0],"pwd")){
					my_pwd();
					printf("%s %s %s",newarg[0],newarg[1],newarg[2]);
					free_looped(newarg);
					exit(0);
				}
				else if(0 == strcmp(newarg[0],"cd")){
						my_cd(newarg);
						free_looped(newarg);
						exit(0);
				}
				else if(0 == strcmp(newarg[0],"echo")){
						my_echo(newarg);
						free_looped(newarg);
						exit(0);
				}
				else{
					execvp(newarg[0],newarg);
					printf("Error\n");
					free_looped(newarg);
					exit(-1);
				}
			}
		}
	}

}


char ** parse_input(char * input_buff){
	char **args = malloc(sizeof(char *) * INIT_SIZE);		
	int k = 0, argcount = 0;
	int size = INIT_SIZE; /* The array has an initial INIT_SIZE slots */
	int start;

	while (input_buff[k] != '\0') {
		while(input_buff[k] == ' '){
			k++; /* find start of word */
		}
		start = k;
		/* find end of word */
		for (; input_buff[k] != '\0' && input_buff[k] != ' '; k++) {}
		if ((k-start) > 0){
			char *word = malloc((k - start) + 1); /* plus one for null termination */
			word[k-start] = '\0';	
			strncpy(word,&input_buff[start], k-start);
			if(argcount >= size -1){
				size*=2;
				args = realloc(args,size * sizeof(char *));
			}
			args[argcount++] = word;
		}
	}
	args[argcount] = NULL;
	return args;
}
void free_looped(char ** arr){
int i;
	for(i=0;arr[i];i++)
		free(arr[i]);
	free(arr);

}

/* Built in functions */
void my_pwd(){
	char* p = getcwd(NULL, 0);
	if(NULL == p){
		write(2,"Error using mypwd\n",19);
	}
	else{	
		write(1,p,strlen(p));
		write(1,"\n",1);
	}
}
void my_echo(char** newarg){
	char ** arr2 = newarg;
	int lsize=0;
	while(newarg[lsize] != NULL) lsize++;
	while(--lsize){
		if(write(1,*arr2,strlen(*++arr2)) == -1){
			printf("Error writing\n");
			free_looped(newarg);
			exit(-1);
		}
		else write(1," ",1);
	}
		printf("\n");
}
void my_cd(char** newarg){
	err = chdir(newarg[1]);	
	if (err == -1){
		printf("Error: no such file or directory\n");
		free_looped(newarg);
		exit(-1);
	}
}
