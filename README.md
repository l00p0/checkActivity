# checkActivity
windows user idle timeout indicator console app. Checks if the windows user is afk.


The original use case for this is for a computer that is being controlled remotely by several users.
Different users may want control of the machine but don't want to kick off users if someone else is already using it.

We can signal the fact that the machine is free or busy by modifying a file on a shared drive.
This can be checked by an indicator application that can tell potential users that the machine is free or busy.

In our case the indicator is part of a web-app that will regularly poll the output file and tell users the current state.

In its current form the program will output to a file called freebusy.dat in the current directory. 
This is fine for our current use-case. 
Even if we wanted to monitor several machines we would simply call the exe from several different paths.


e.g. where Z: is mapped network share

    cd Z:\some\path\machine1\
    c:\path\to\exe\checkActivity.exe 

     
     
and poll those locations knowing which machine corresponds to which path.

