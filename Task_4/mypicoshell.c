#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256   /*Maximum size of any array*/
/*proto types for my commands functions*/ 
void str_token(char *input, char **name_in, int size);




	/*message is the command that the user want and n is the size of message string */ 
	char *message;
    
    
	/* name used to save every name in the commands arguments */ 
    char **name = (char **) malloc(MAX * sizeof(char *));
    
	/* The exit_ms is used to compare with the message entered from user to exit */ 
    char exit_ms[MAX] = "exit";
    
    
	
	
	
	
	    /*if the user just entered the enter button */ 
	    if (strlen(message) == 0)
	    
	
	    
		
	    
	
	
	    /*if user entred exit command */ 
	    if (Match == 4) {
	    
	    
	
	    
	
	
	
	    /*call the function that will divide the full string into tokens */ 
	    str_token(message, name, MAX);
	
	    /*if user entred echo command */ 
	    if (strcmp(name[0], "echo") == 0) {
	    
	
	
	else if (strcmp(name[0], "pwd") == 0) {
	    
	
	
	else if (strcmp(name[0], "cd") == 0) {
	    
	
	
	else
	    
	    
	    
		
		
		    ("PARENT: My PID = %d,  I have a new child and his PID = %d\n",
		     
		
	    
		
			getpid(), 
		
		    // getchar();
		    
		
		    ("I am not in the mode of execution. Exec failed\n");
		
	    
		
	    
	    
	    
	    
	    
	
	    /*free the allocated memory */ 
	    for (int i = 0; i < MAX && name[i] != NULL; i++) {
	    
    
    



/* Function responsible for diving iny string into tokens using the special delimiter */ 

    
    
	
	
	
    
    
	// Make sure the remaining array will be filled with NULL
	for (; i < size; i++) {
	
    



/* Function responsible for excute the pwd command */ 

{
    
    
	
    
    
    else {
	
    



/* Function responsible for excute the echo command */ 

{
    
    
	
	
    
    



/* Function responsible for excute the cd command */ 

{
    
    
	
    
	
    


