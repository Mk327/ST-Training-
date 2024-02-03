#include <stdio.h>






int main (int argc , char** argv)
{

        char i =1;
        while (argv[i] != NULL)
	{
	printf ("%s ",argv[i]);
	i++;
	}

if (i == 1) 
{
 printf ("\n");
}

        return 0;






}
