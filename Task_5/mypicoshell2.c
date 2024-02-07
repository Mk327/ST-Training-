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
void str_token(char *input, char **name_in);


void pwd_new(void);


void echo_new(char **name);


void cd_new(char **name);


int Num_Of_Tok(char *message);



int main(void) 
{ 
	/*message is the command that the user want and n is the size of message string */ 
	char *message;


	size_t n = 0;

	char s = 1;


	/* The exit_ms is used to compare with the message entered from user to exit */ 
	char exit_ms[MAX] = "exit";


	char Match = 0;




	while (1) {





		printf("Ana Fel ALforma Alnharda > ");


		int size = getline(&message, &n, stdin);
		message[strcspn(message, "\n")] = '\0';

		//message[size - 1] = 0;


		/*if the user just entered the enter button */ 
		if (strlen(message) == 0)


			continue;
		int x = Num_Of_Tok(message);
		/* name used to save every name in the commands arguments
                 * I increment by one to take the null token into consideration */ 
		char **name = (char **) malloc((x+1) * sizeof(char *));


		for (char i = 0; i < 4; i++) {


			if (message[i] == exit_ms[i]) {


				Match++;


			}


		}


		/*if user entred exit command */ 
		if (Match == 4) {


			printf("skt al slama\n");


			break;


		} else {


			Match = 0;


		}





		/*call the function that will divide the full string into tokens */ 
		str_token(message, name);


		/*if user entred echo command */ 
		if (strcmp(name[0], "echo") == 0) {


			echo_new(name);


		}			/*if user entred pwd command */


		else if (strcmp(name[0], "pwd") == 0) {


			pwd_new();


		}			/*if user entred cd command */


		else if (strcmp(name[0], "cd") == 0) {


			cd_new(name);


		}


                /* if user wants external commands */
		else


		{



			pid_t returned_pid = fork();


			if (returned_pid > 0) {

                           /* The parent waits for his child to terminate */
				int wstatus;
				wait(&wstatus);

			} else if (returned_pid == 0) {

				/* the child execute the command */
				name [x] = NULL;		    
				execvp(name[0], name);


				printf  ("Please insert a valid command\n");


				return -1;


			} else {


				printf("ERROR: I could not get a child\n");


			}






		}

		free(message);


		message = NULL ;


		n = 0; 


		/*free the allocated memory */ 
		for (int i = 0; i < MAX && name[i] != NULL; i++) {


			free(name[i]);


		}
		free(name);
	} 






	return 0;


}





/* Function responsible for diving any string into tokens using the special delimiter */ 

void str_token(char *input, char **name_in) 
{ 
	int i = 0;


	char *token = strtok(input, " ");



	while (token != NULL ) {


		name_in[i] = strdup(token);


		token = strtok(NULL, " ");


		i++;


	}



	// Make sure the remaining string will be NULL


	name_in[i] = NULL;
}





/* Function responsible for excute the pwd command */ 

void pwd_new(void) 
{ 

	char cwd[MAX];


	if (getcwd(cwd, sizeof(cwd)) == NULL) {


		printf("getcwd() error");


	}


	else {


		printf("current working directory: %s\n", cwd);


	}


}





/* Function responsible for excute the echo command */ 

void echo_new(char **name) 
{ 

	char j = 1;


	while (name[j] != NULL) {


		printf("%s ", name[j]);


		j++;


	}


	printf("\n");



}





/* Function responsible for excute the cd command */ 

void cd_new(char **name) 
{ 

	name[1][strlen(name[1]) - 1] = 0;


	if (chdir(name[1]) == 0) {


		printf("directory changed\n");


	} else {


		printf("error in changing directory\n");


	}


}

/* Function responsible for counting the number of tokens after parsing*/
int Num_Of_Tok(char *message) 
{ 

	int Token_Num = 0, i = 0;

	char Arg_Flag = 0;

	while (message[i] != '\0')

	{


		while (message[i] == ' ' && message[i] != '\0')

		{

			i++;

		}


		while (message[i] != ' ' && message[i] != '\0')

		{

			if (Arg_Flag == 0)

			{

				Arg_Flag = 1;

			}

			i++;

		}

		if (Arg_Flag == 1)

		{

			Arg_Flag = 0;

			Token_Num++;

		}

		i++;

	}


	return Token_Num;


}


