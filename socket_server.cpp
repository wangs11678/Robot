#include "serial_send.h"
#include "socket_server.h"

void* thread_socket_server(void *arg)
{
	struct sockaddr_in server_addr;  
    int server_socket;  
    int opt = 1;  
     
    bzero(&server_addr, sizeof(server_addr));   
      
    server_addr.sin_family = AF_INET;  
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);  
    server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);  
  
    /* create a socket */  
    server_socket = socket(PF_INET, SOCK_STREAM, 0);  
    if(server_socket < 0)  
    {  
        printf("Socket服务器: Create Socket Failed!");  
        exit(1);  
    }  
   
    /* bind socket to a specified address*/  
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));  
    if(bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)))  
    {  
        printf("Socket服务器: Server Bind Port : %d Failed!", HELLO_WORLD_SERVER_PORT);   
        exit(1);  
    }  
  
    /* listen a socket */  
    if(listen(server_socket, LENGTH_OF_LISTEN_QUEUE))  
    {  
        printf("Socket服务器: Server Listen Failed!");   
        exit(1);  
    }  
      
    /* run server */  
    while(1)   
    {  
        struct sockaddr_in client_addr;  
        int client_socket;        
        socklen_t length;  
        unsigned char buffer[BUFFER_SIZE];  
  
        /* accept socket from client */  
        length = sizeof(client_addr);  
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &length);  
        if(client_socket < 0)  
        {  
            printf("Socket服务器: Server Accept Failed!\n");  
            break;  
        }  
          
        /* receive data from client */  
        while(1)  
        {  
            bzero(buffer, BUFFER_SIZE);  
            length = recv(client_socket, buffer, BUFFER_SIZE, 0);  
            if(length < 0)  
            {  
                printf("Socket服务器: Server Recieve Data Failed!\n");  
                break;  
            }  
              
            if(0xff == buffer[0])  
            {  
                printf("Socket服务器: Quit from client!\n");  
                break;  
            }  
            serial_send(&buffer[0]);  
            printf("%x\n", buffer[0]);  
        }     
          
        close(client_socket);  
    }  
      
    close(server_socket); 
} 
