#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX 256   /*Maximum size of any array*/
/*proto types for my commands functions*/
void str_token(char *input, char **name_in, int size);
void pwd_new(void);
void echo_new (char **name);
void cd_new(char **name);

int main(void)
{
	/* name used to save every name in the commands arguments */
    char **name = (char **) malloc(MAX * sizeof(char *));
	/* message used to save the input from the user */
    char message[MAX];
	/* The exit_ms is used to compare with the message entered from user to exit*/
    char exit_ms[MAX] = "exit";
    char Match = 0;


    while (1) {
	printf("Ana Fel ALforma Alnharda > ");
	fgets(message, MAX, stdin);

	for (char i = 0; i < 4; i++) {
	    if (message[i] == exit_ms[i]) {
		Match++;
	    }
	}
        /*if user entred exit command*/
	if (Match == 4) {
	    printf("skt al slama\n");
	    break;
	} else {
	    Match = 0;
	}

	printf("You said : %s\n", message);
	    /*call the function that will divide the full string into tokens*/
	str_token(message, name, MAX);
         /*if user entred echo command*/
	if (strcmp(name[0], "echo") == 0) {
	    echo_new(name);
	}/*if user entred pwd command*/ 
	else if (strcmp(name[0], "pwd") == 0) {
	    pwd_new();
	} /*if user entred cd command*/
	else if (strcmp(name[0], "cd") == 0) {
	   cd_new(name);
	}
	/*free the allocated memory*/
	for (int i = 0; i < MAX && name[i] != NULL; i++) {
	    free(name[i]);
	}
    }

    free(name);			/* free the array itself */

    return 0;
}

/* Function responsible for diving iny string into tokens using the special delimiter */

void str_token(char *input, char **name_in, int size)
{
    int i = 0;
    char *token = strtok(input, " ");

    while (token != NULL && i < size) {
	name_in[i] = strdup(token);
	token = strtok(NULL, " ");
	i++;
    }

    // Make sure the remaining array will be filled with NULL
    for (; i < size; i++) {
	name_in[i] = NULL;
    }
}

/* Function responsible for excute the pwd command */

void pwd_new(void){
    char cwd[MAX];
	if (getcwd(cwd, sizeof(cwd)) == NULL) {
    printf("getcwd() error");
	}
	else {
		printf("current working directory: %s\n", cwd);
	    }
}

/* Function responsible for excute the echo command */

void echo_new (char **name){
    char j = 1;
	while (name[j] != NULL) {
	printf("%s ", name[j]);
	j++;
	}

	if (j == 1) {
	    printf("\n");
	    }
}

/* Function responsible for excute the cd command */

void cd_new(char **name){
    name[1][strlen(name[1]) - 1] = 0;
	if (chdir(name[1]) == 0) {
	printf("directory changed\n");
   } else {
		printf("error in changing directory\n");
	    }
}
