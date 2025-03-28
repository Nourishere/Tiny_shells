#include "../builtins.h"
char ** parse_input(char * input_buff);
void free_looped(char ** arr);
void my_pwd(void);
void my_echo(char** newarg);
void my_cd(char** newarg);

char buff[MAX_BUF];
char * arr;
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
			if(0 == strcmp(newarg[0],"exit")){
					exit(EXIT_STATUS);
			}
			else if(0 == strcmp(newarg[0],"pwd")){
					my_pwd();
			}
			else if(0 == strcmp(newarg[0],"cd")){
					my_cd(newarg);
			}
			else if(0 == strcmp(newarg[0],"echo")){
					my_echo(newarg);
			}
			/* If the command is not a built it, fork */
			else{
				pid_t pid = fork();

				if(pid > 0){
					/* we are in the parent process */
					int status;
					if(0 == strcmp(newarg[0],"cd")){
							my_cd(newarg);
					}
					while (wait(&status)>1){;
						if(WEXITSTATUS(status) == EXIT_STATUS){
							exit(0);
						}
					}
				}
				else if(pid==0){
					/* we are in the child process */

						execvp(newarg[0],newarg);
						printf("Error\n");
						exit(-1);

				}
			}
        }
    }
}


