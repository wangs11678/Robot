#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>

#include <opencv2/opencv.hpp> 
#include <opencv/highgui.h>

#include <iostream>

#define IP "192.168.1.210"
#define PORT 8885

using namespace std;
using namespace cv; 

void* thread_openCamera(void *);
