// c api
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <assert.h>

// c++ api
#include <string>
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

// opencv api
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/ml/ml.hpp"

//socket api
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/select.h>

//thread api
#include <pthread.h>

using namespace std;
using namespace cv;

#define port  20101
#define ip "192.168.1.114"


const string kVocabularyFile("vocabulary.xml.gz");
const string kBowImageDescriptorsDir("/bagOfWords");
const string kSvmsDirs("/svms");


/****************************socket**************************************/
typedef struct DataPackage
{
	int packageLen;
	int commandNo;
	int deviceNo;
	int messageID;
	float message;
	char* pend;
}DataPackage;

typedef struct PicPackage
{
	int packageLen;
	int commandNo;
	int deviceNo;
	int messageID;
    //char * picture;
	char picture[1000000];
	char* pend;
}PicPackage;


class Params
{
public:
	Params(): wordCount(1000), 
			  detectorType("SIFT"),
			  descriptorType("SIFT"), 
			  matcherType("FlannBased"){ }

	int		wordCount;
	string	detectorType;
	string	descriptorType;
	string	matcherType;
};

void sendResultOrPicture(int sockClient,int cmdNo, int devNo, int msgID, float message, char* picPath, char* end);

Mat BuildVocabulary(const string& databaseDir, 
					const vector<string>& categories, 
					const Ptr<FeatureDetector>& detector, 
					const Ptr<DescriptorExtractor>& extractor,
					int wordCount);
					
void ComputeBowImageDescriptors(const string& databaseDir,
								const vector<string>& categories, 
								const Ptr<FeatureDetector>& detector,
								Ptr<BOWImgDescriptorExtractor>& bowExtractor,
								const string& imageDescriptorsDir,
								map<string, Mat>* samples);
								
void TrainSvm(map<string, Mat>& samples, const string& category, const CvSVMParams& svmParams, CvSVM* svm);

string ClassifyBySvm(const Mat& queryDescriptor, map<string, Mat>& samples, const string& svmDir);

void getdirlist(char *path, vector<string> &dirlist);

void getfilelist(char *path, vector<string> &filelist);

void * thread_result_client(void *);

void* thread_bow_sendResult(void *);
