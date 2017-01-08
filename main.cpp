#include "socket_server.h"
#include "sift_bow_svm.h"
#include "clientVedio.h"

int main(int argc, char **argv)  
{  
    pthread_t id1, id2, id3;
    int ret; 
    
    //接受服务器信息，并向小车发送命令
	ret = pthread_create(&id1, NULL, thread_socket_server, NULL);
	if(ret != 0){
		printf("serial_send pthread create error\n");
		exit(1);
	}	
	//发送花卉识别结果到服务器
	ret = pthread_create(&id2, NULL, thread_bow_sendResult, NULL);
	if(ret != 0){
		printf("bow_sendResult pthread create error\n");
		exit(1);
	}
	//打开摄像头，发送视频到服务器
	ret = pthread_create(&id3, NULL, thread_openCamera, NULL);
	if(ret != 0){
		printf("openCamera pthread create error\n");
		exit(1);
	}
	
	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
	pthread_join(id3, NULL);
	
    return 0;  
} 
