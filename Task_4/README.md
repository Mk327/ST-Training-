It's the same as myfemtoshell but the difference is that when the user enters a command
I didn't implement I'll use the execvp function to search for the command in the PATH 
environment and after that execute the command by the child that generated bt fork
and make the parent wait untill the child died 

EX of o/p:

Ana Fel ALforma Alnharda > echo mohamed khaled
You said : echo mohamed khaled
mohamed khaled 
Ana Fel ALforma Alnharda > cd ../
You said : cd ../
directory changed
Ana Fel ALforma Alnharda > ls
You said : ls
PARENT: My PID = 5524,  I have a new child and his PID = 5526
CHILD: My PID = 5526,  My parent PID = 5524
session_4  Task_3  Task_4
Ana Fel ALforma Alnharda >      



