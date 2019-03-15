/*
* name: SIMPLE SHELL 
* Author: AHMAD HEGAZY <https://ahegazy.github.io>
* Date: 1/3/2019
* filename: simpleshell.c
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h> /* for interrupts */

/*
	# to view the shell and its childs use this command in your terminal, OR this one :D 
	PID=`pidof simpleshell`
	pstree $PID # will list the process and its childs
	htop -p `pstree -p $PID | perl -ne 'push @t, /\((\d+)\)/g; END { print join ",", @t }'`
*/

/* maximum 100 argument, each of 100 byte*/
#define MAX_ARG_LENGTH 100
#define MAX_ARGS 100

void getCmd(char cmd[MAX_ARGS][MAX_ARG_LENGTH]); /* prompt the user */
void clrCmd(char cmd[MAX_ARGS][MAX_ARG_LENGTH]); /* clear the command array*/
int parseCmd(char cmd[MAX_ARGS][MAX_ARG_LENGTH], char * Parms[MAX_ARGS]); /* parse the command & returns wether to background or no */

void handelChild(int sig); /* handels he child signal SIGCHLD */
void storeLog(int pid, int status); /* store the child status */


int main(){
	int wpid,pid, ret, status;
	char cmd[MAX_ARGS][MAX_ARG_LENGTH]; /* maximum 100 argument, each of 100 byte*/
        char * Parms[MAX_ARGS];
	char background = 0;

	signal(SIGCHLD, handelChild);
	while(1){

		getCmd(cmd);

		if( strcmp( cmd[0], "exit") == 0 ){
			exit(0);
		}else if (strcmp( cmd[0], "cd") == 0){
			if ( chdir(cmd[1]) != 0 ) {
				perror(cmd[1]);
			}
		}else {

			background = parseCmd(cmd, Parms);
		     	if ((pid = fork()) ==-1){
			        perror("Couldn't fork a child process.");
		     	}else if (pid == 0) {
			        ret = execvp(Parms[0], Parms);
				/* Will reach this point only when error happens. */
			        printf("Error Command not found %d.\n", ret);
				exit(0);
			}else{
				if(background == 0){
					/* wait for the child to end, and get the status of its ending*/
		        		wpid = wait(&status); //waitpid(pid,&status,WUNTRACED);//wait(&status); /* if & don't wait. */
						storeLog(wpid, status);
				}
			}
		}
	}
	return 0;

}

void getCmd(char cmd[MAX_ARGS][MAX_ARG_LENGTH]){
	char eol = 0; /* end of line detection char.*/

	/*clear cmd array.*/
	clrCmd(cmd);

        /* get the command.*/
	printf("shell>> ");
        int i = 0;
        do{
                scanf("%s%c", cmd[i],&eol);
                i = i + 1;
        }while( (eol != 0x0a) );
	cmd[i][0] = '\0';
}

void clrCmd(char cmd[MAX_ARGS][MAX_ARG_LENGTH]){
	cmd[0][0] = '\0';
}
void clrParms(char * Parms[MAX_ARGS]){
	int i = 0;
	/* Clear the parameters array by setting the referenced parmaters to NULL*/
	for(i=0 ; i < MAX_ARGS; i = i + 1){
		Parms[i] = NULL;
	}
}

int parseCmd(char cmd[MAX_ARGS][MAX_ARG_LENGTH], char * Parms[MAX_ARGS]){
	int i,bg;
	i = 0;
	bg = 0;
	/* clear Parms */
	clrParms(Parms);
	while((cmd[i][0] != '\0')){
		if(cmd[i][0] == '&'){
			bg = 1;
			break;
		}
		Parms[i] = cmd[i];
		i = i + 1;
	}
	return bg;
}

void handelChild(int sig){	
	int pid;
	int status;
	/* pid = wait(NULL); */
	/* Get the process id of the child/childs.*/
	while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
		storeLog(pid, status);
	}
	signal(SIGCHLD, handelChild); 
}

void storeLog(int pid, int status){	
	FILE *fp;
	fp = fopen("shellLog.txt","a");

	fprintf(fp, "child w/ PID: %d was terminated, its exit code %d.\n", pid, status);
	fclose(fp);
}
