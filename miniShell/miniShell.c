//
//  miniShell.c
//  
//	Jordan Coffland
// 	Mohammed Bataineh
//

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>


//Prototypes
char** parse();
void inputR(char** tokens);
void outputR(char** tokens);
bool isBackProcess(char** tokens);

//currently unused. doesnt free properly
void freeTheMemory(char** tokens);

//char* history[25];

int main(){
	//input and prompt buffers
    	char input[256];
    	char cwd[256];
    

	while(1){
        	getcwd(cwd, sizeof(cwd));
        
        	printf("%s> ",cwd);
        	fgets(input,sizeof(input),stdin);    //prompt and get
		//if(input[0] != NULL)
		//	strcpy(history[0], input); //meant to hold job history. Don't know how to make it without it being extremely cumbersome.

        	char** tokens = parse(input);
        

        	if(!strncmp(tokens[0],"exit", 4)){   //Finds if exit is called immediately
			//freeTheMemory(tokens);	//I'm unsure why this isnt working
            		exit(0);
		}

		bool isBackground = isBackProcess(tokens); //checks if the upcoming fork is a background process

		if(!strncmp(tokens[0], "cd", 2))
			chdir(tokens[1]);
	
        	signal(SIGCHLD, SIG_IGN);           //zombie reaper

		int pid = fork();
		if(pid == 0){
            		inputR(tokens);
            		outputR(tokens);
      			execvp(tokens[0],tokens);
			printf("This is not a valid command\n");
			//freeTheMemory(tokens);	//I'm unsure why this isn't working
			return 0;
		}

		else{                                   //changes the waitpid if it's a background process
            		if(isBackground)
                		waitpid(-1, NULL, WNOHANG);
            
           		 else
                		waitpid(-1, NULL, 0);
		}

	}

    return 0; //should never be called
}



char** parse(char* input){
    int i = 0;
    while(input[i]!='\0')    //Had an error with a character called "Line Feed". Couldnt remove it in parse method for some reason
        i++;
    if(i>1)
        input[i-1]='\0';    //sets line feed char to null
    
    i = 0;
    char** tokens = malloc(sizeof(char**)*20);

    tokens[i] = strtok(input, " ");
    
    while(tokens[i]!=NULL){
        char* hold = malloc(sizeof(char*)*50);
        i++;
        hold = strtok(NULL, " ");
        tokens[i] = hold;
    }
    return tokens;
}


void inputR(char** tokens){
    int i = 0;
    while(tokens[i]!=NULL){
        if(!strncmp(tokens[i],"<", 1)){
            //printf("input changed to %s\n",tokens[i+ 1]);
            freopen(tokens[i-1],"r",stdin);
            tokens[i] = NULL;
            tokens[i+1] = NULL;
        }
        i++;
    }
}


    void outputR(char** tokens){
        int i = 0;
        while(tokens[i]!=NULL){
            if(!strncmp(tokens[i],">", 1)){
                //printf("output changed to %s\n",tokens[i+1]);
                freopen(tokens[i+1],"w",stdout);
                tokens[i] = NULL;
                tokens[i+1] = NULL;
            }
            
            i++;
        }
}

bool isBackProcess(char** tokens){
	int flagCheck = 0;
        while(tokens[flagCheck] != NULL)
		flagCheck++;
        
        if(!strncmp(tokens[flagCheck - 1] ,"&", 1)){
		tokens[flagCheck - 1] = NULL;
		return true;
        }
	return false;
}

void freeTheMemory(char** tokens){
	//meant to free the memory
	int count = 0;
	while(tokens[count] != NULL){
		free(tokens[count]);
		count++;
	}

	free(tokens);
}
