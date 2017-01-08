#include <netinet/in.h>      
#include <sys/types.h>      
#include <sys/socket.h>   
#include <sys/stat.h>          
#include <stdlib.h>         
#include <string.h>         
#include <stdio.h>      /*标准输入输出定义*/
#include <unistd.h>     /*Unix 标准函数定义*/
#include <fcntl.h>      /*文件控制定义*/
#include <termios.h>    /*PPSIX 终端控制定义*/
#include <errno.h>      /*错误号定义*/
#include <pthread.h>    /*线程定义*/


#define HELLO_WORLD_SERVER_PORT    8000  
#define LENGTH_OF_LISTEN_QUEUE 20  
#define BUFFER_SIZE 1024 

void* thread_socket_server(void *arg);
