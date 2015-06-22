# ServerDemon
This is done on ubuntu system
Download and uncompress the directory
Navigate into the folder

Compile the File server.c using gcc compiler using the following command
$gcc server.c -lpthread -o ServerDaemon
Please  run the shell script server.sh on Ubuntu
$sh server.sh


Then for client programe run
$python client.py <IP> <Port>
example if your are running on the same system
$python client.py 127.0.0.1 8787

you can type
GETMESSAGE 
#to get randome message and 
BYE
#to terminate connection
~               
