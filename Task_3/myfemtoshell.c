#include <stdio.h>
#include <string.h>//to use strtok function
#include <unistd.h>
#include <stdlib.h>

#define MAX 100 /* Max value of the array */


void str_token(char *input,char **name_in,int size);
char **name=NULL;

int main(void) {
    
     char message[MAX];/* string to print user message */
     char exit_ms[MAX]="exit"; /* strinf to save the exit command */
     char Match =0; /* Var to check if the message is the exit com or not*/
     while (1)
     {
         printf("Ana Fel ALforma Alnharda > ");
         fgets (message,MAX,stdin);
         for (char i =0 ; i<4 ; i++)
         {
             if (message[i] == exit_ms[i])
             {
                 Match++;
             }
            
         }
          if (Match == 4)
             {
                 printf ("skt al slama ");
                 break;
             }
         else 
            {
             Match =0;
            }
         printf ("You said : %s\n",message);
     
        str_token(message,name,MAX);

       if (name[0] == "echo")
       {
      
	       char j =1;
	       while (name[j] != NULL)
               {
		       printf ("%s ",name[j]);
                       j++;
               }

               if (j == 1)
               {
               printf ("\n");
               }
       }

       else if (name[0] == "pwd")
       {
       
        char cwd[MAX];
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf("getcwd() error");
    } else {
        printf("current working directory : %s\n", cwd);
    }


       }
      else if (name [0] == "cd")
      {
      
      
      name [1] [strlen(name[1])- 1] = 0;
       if ( chdir(name [1]) == 0)
       {     
      
      printf ("dirctory changed");
      
      }
       else 
       {
       
	 printf("error in change dirctory" );

       }
       
       
      }
       

for (char k = 0 ; k < MAX && name[k] != NULL ;k++)
    {
    free(name[k]);
    }
      

 
     

     }

  

    return 0;
}




void str_token(char *input,char **name_in,int size)
{

   int i=0;
   char *token= strtok(input," "); // evert sperate name (command or arg ) will be saved in token

   for (;token != NULL && i<size;i++)
   {
   
	   name[i]=strdup(token);
	   token = strtok(NULL," ");
   
   }

   while(i<size)
   {
   
   name[i] = NULL ;// to make sure the remaining arr wiil be filled with NULL
   i++;
   
   }





}







