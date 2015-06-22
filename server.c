/*
    C socket server example, handles multiple clients using threads
    Compile
    gcc server.c -lpthread -o ServerDaemon
*/
 
#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread
#include<fcntl.h>
//the thread function
void *connection_handler(void *);
void rand_string(char *str, size_t size); 
int main(int argc , char *argv[])
{

     pid_t pid;
     pid = fork ( );  
    if (pid == -1)  
        return -1;  
    else if (pid != 0)  
        exit (EXIT_SUCCESS);  



    int socket_desc , client_sock , c;
    int defport=8787;
    struct sockaddr_in server , client;
    if(argc>2){
        if(strcmp(argv[1],"-p")==0){
        printf("Port def");
        defport=atoi(argv[2]);

}
     }
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( defport );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
	pthread_t thread_id;
	
    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Connection accepted");
         
        if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &client_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }
         
        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( thread_id , NULL);
        puts("Handler assigned");
    }
     
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
     
    return 0;
}
 
/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size;
    char message[65] , client_message[15],randmess[52];
/*     
    //Send some messages to the client
    message = "Greetings! I am your connection handler\n";
    write(sock , message , strlen(message));
     
    message = "Now type something and i shall repeat what you type \n";
    write(sock , message , strlen(message));
     */
    //Receive a message from client
    while( (read_size = recv(sock , client_message , 12 , 0)) > 0 )
    {
        //end of string marker
		client_message[read_size] = '\0';
		//Send the message back to client
		if(strcmp(client_message,"GETMESSAGE\n")==0){
              //If the request is "GETMESSAGE\n"
                   strcpy(message,"The message is ");
                  rand_string(randmess,50); 
                   strcat(message,randmess);
                   strcat(message,"\n");
        write(sock ,message, strlen(message));
               
                   }else if(strcmp(client_message,"BYE\n")==0){
              //If the request is "BYE\n"
        write(sock ,client_message, strlen(client_message));
               
                close(sock);
                return 0;
}else{
              //If the request is undefied 

                   strcpy(message,"Bad Requset\n");
                   write(sock ,message, strlen(message));
}
		//clear the message buffer
		memset(client_message, 0, 15);
    }
     
/*    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }*/
         
    return 0;
} 


/* generating random string function definition */

void rand_string(char *str,size_t size){
const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
size_t n; 
    if (size) {
        --size;
        for (n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    
}
 



