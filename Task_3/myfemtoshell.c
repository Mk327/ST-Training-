#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX 256

void str_token(char *input, char **name_in, int size);
void pwd_new(void);
void echo_new (char **name);
int main(void)
{
    char **name = (char **) malloc(MAX * sizeof(char *));
    char message[MAX];
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

	if (Match == 4) {
	    printf("skt al slama\n");
	    break;
	} else {
	    Match = 0;
	}

	printf("You said : %s\n", message);
	str_token(message, name, MAX);

	if (strcmp(name[0], "echo") == 0) {
	    echo_new(name);
	} else if (strcmp(name[0], "pwd") == 0) {
	    printf("Before pwd_new\n");
	    pwd_new();
	} else if (strcmp(name[0], "cd") == 0) {
	    name[1][strlen(name[1]) - 1] = 0;
	    if (chdir(name[1]) == 0) {
		printf("directory changed\n");
	    } else {
		printf("error in changing directory\n");
	    }
	}
	// Remember to free the allocated memory
	for (int i = 0; i < MAX && name[i] != NULL; i++) {
	    free(name[i]);
	}
    }

    free(name);			// Don't forget to free the array itself

    return 0;
}

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

void pwd_new(void){
    char cwd[MAX];
	if (getcwd(cwd, sizeof(cwd)) == NULL) {
    printf("getcwd() error");
	} 
	else {
		printf("current working directory: %s\n", cwd);
	    }
}
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
