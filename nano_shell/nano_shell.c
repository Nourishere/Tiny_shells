#include "../builtins.h"

char buff[MAX_BUF];
int envflag=0;
extern int err;
nsh_t local_vars;
int order=0;

int find_var(char* var);
int export_var(char** args);

int main(int argc, char* argv[]){
	if(argc > 1){
		printf("Use the shell with no arguments\n");
		return -1;
	}
	else{
		while(1){
			envflag=0;
			printf("$: ");
			fgets(buff,MAX_BUF,stdin);
			buff[strlen(buff)-1] = 0;
			int i=0;
			while(buff[i++] == ' '){
				}
			if(i-1 == strlen(buff))
				continue;
			else if(strlen(buff) == 0)
				continue;

			char ** newarg = parse_input(buff);
			int j;
			int k;
			for(i=0;newarg[i] != NULL;i++){
				for(j=0;*(newarg[i]+j) != '\0';j++){
					if(*(newarg[i]+j) == '$'){
						envflag =1;
						*(newarg[i]+j) = '\0';
						if((k = find_var((newarg[i]+j+1))) != -1)
							newarg[i] = local_vars.value[k];
					}
					else if(*(newarg[i]+j) == '='){
						envflag =1;
						*(newarg[i]+j) = '\0';
						if((k = find_var(newarg[i])) != -1)
							local_vars.value[k] = newarg[i]+j+1;	
						else{
							local_vars.name[order] = newarg[i];
							local_vars.value[order++] = newarg[i]+j+1;
							local_vars.name[order] = NULL; 
							local_vars.value[order] = NULL;
						}
                    }
					else{
					}
				}
			}
			if(0 == strcmp(newarg[0],"exit")){
					exit(EXIT_STATUS);
			}
			else if(0 == strcmp(newarg[0],"pwd")){
					err = my_pwd();
			}
			else if(0 == strcmp(newarg[0],"export")){
					err = export_var(newarg);

			}
			else if(0 == strcmp(newarg[0],"cd")){
					err = my_cd(newarg);
			}
			else if(0 == strcmp(newarg[0],"echo")){
					err = my_echo(newarg);
			}
			/* If the command is not a built it, fork */
			else if(!envflag){
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
						if(!envflag){
							execvp(newarg[0],newarg);
							printf("Error\n");
							exit(-1);
						}
				}
				else{
					printf("Error forking\n");
				}
			}
			else{}
        }
    }
}
/* Finds a variable in the shell's nsh_t stack.
   Returns the position of variable in the nsh_t stack, and -1 on error.
*/
int find_var(char* var){
	int i;
	for(i=0;local_vars.name[i] != NULL;i++){
		if((strcmp(local_vars.name[i],var) ==0) && local_vars.value[i] != NULL)
			return i;
	}		
	return -1;
}
/* Exports variables to the environment.
   Returns the number of variables exported, and -1 on error.
*/
int export_var(char** args){
	int i,k,f=-1;
	for(i=1;args[i] != NULL;i++){
		if((k=find_var(args[i])) != -1){
			if(setenv(local_vars.name[k], local_vars.value[k],1) == -1){
				printf("Error setting environment variable\n");
				exit(-1);
			}
			f++;	
		}
	}
	return -1;
}
