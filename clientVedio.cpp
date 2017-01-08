#include "clientVedio.h"

void* thread_openCamera(void *)
{
	int err;
 	const int blocksize=28880;
 	//定义包结构  
 	struct recvbuf//包格式  
 	{  
    	char buf[blocksize];//存放数据的变量  
     	int flag;//标志   
     	int num;       
  	}; 
 	struct recvbuf data; 

 	//create udp socket 
  	struct sockaddr_in addrSrv;
	//addrSrv.sin_addr.s_addr=inet_addr("192.168.1.210");
	addrSrv.sin_addr.s_addr=inet_addr(IP);
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(PORT);

	int sockClient=socket(AF_INET,SOCK_DGRAM,0);
	if(-1==sockClient){
		perror("摄像头: Socket创建失败！");
		//exit(-1);
	}
 	int nRecvBuf=1024*1024*10;//接收缓存10M  
 	setsockopt(sockClient,SOL_SOCKET,SO_RCVBUF,(const char*)&nRecvBuf,sizeof(int));
  	//声明IplImage指针  
  	IplImage* pFrame = NULL,*frame_copy=0;  
  
 	//获取摄像头 
  	//CvCapture* pCapture = cvCreateCameraCapture(-1);  
   	CvCapture* capture=NULL;
   	capture = cvCreateCameraCapture(-1);
   	if(!capture){
   		cout<<"摄像头: 打开摄像头失败, 已退出！"<<endl;
   		//exit(-1);
   	} 
   
   	//int peopel_number_count=0;

	while(1){
    	pFrame=cvQueryFrame(capture);  
        //取帧操作  
		//printf("the deeps is %d; the channel is :%d\n",pFrame->depth,pFrame->nChannels);
		if(!pFrame) break;
		if(pFrame)  
    	{ 
			char* img=pFrame->imageData;     //指向该帧的数据矩阵  
            for(int i=0;i<32;i++)                    //640*480*3= 921600 
			{
				for(int k=0;k<blocksize;k++)  
                { 
					data.buf[k]=img[i*blocksize+k];       
				}  
                if(i==31)                         //标识一帧中最后一个数据包             
                {  
					data.flag=2;
					//data.num = peopel_number_count;  //sent the result to the server
				}  
                else  
                {  
					data.flag=1;
                }  
				sendto(sockClient,(char*)(&data),sizeof(data),0,(struct sockaddr*)&addrSrv,sizeof(addrSrv)); 
			}      
			cvReleaseImage( &frame_copy );   // 退出之前结束底层api的捕获操作
			//usleep(2500);
		}
	}
 	close(sockClient);
}
