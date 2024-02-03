#include <unistd.h>
#include <stdio.h>





int main(void)
{

    char cwd[150];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
	printf("getcwd() error");
    } else {
	printf("current working directory : %s\n", cwd);
    }

    return 0;
}
