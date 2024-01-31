#include <stdio.h>

#MAX 20 /* Max value of the array */

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
         
     }
    return 0;
}