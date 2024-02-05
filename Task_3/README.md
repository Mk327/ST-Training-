1- myecho.c
It's responsible for printing the argument in the stdout which in our 
case the screen so I used the printf function
EX :  Mohamed Khaled
Mohamed Khaled





2- mypwd.c
It's responsible for get the current working directory so I used getcwd which 
returns non_Null value in success 

EX : /home/mohamed

3- mymv.c

It's responsible for moving a file to a new file even if the new file doesn't exist 
it will create it and put the source file data in it and delete the source file 
the code is same as cp.c except I add the unlink function to delete the source file
EX : input > old_file New_file
     output > old_file will be deleted and it's content will be in new_file


4- myfemtoshell.c

It will implement some built in commands (using tokens from strtok function) 
like discussed above and add new function which is cd that we use for it the 
chdir function 
EX : 
Ana Fel ALforma Alnharda > pwd
You said : pwd

current working directory: /home/public/Task_3
Ana Fel ALforma Alnharda > cd ../
You said : cd ../

directory changed
Ana Fel ALforma Alnharda > echo mohamed khaled
You said : echo mohamed khaled

mohamed khaled
 Ana Fel ALforma Alnharda > exit
skt al slama
