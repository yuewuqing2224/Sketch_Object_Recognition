#include "Dictionary.h"


using namespace std;
using namespace cv;

Dictionary::Dictionary()
{
    dictionarySize = 100; //default size
}

Dictionary::Dictionary(int s){
    dictionarySize = s;
}

void Dictionary::KCluster(Mat& featuresUnclustered,string p){


    TermCriteria tc(CV_TERMCRIT_ITER,100,0.001);
    int retries=1;
    int flags=KMEANS_PP_CENTERS;
    BOWKMeansTrainer bowTrainer(dictionarySize,tc,retries,flags);
    cout<<"Computing BoW Using KNN..."<<endl;
    //cluster the feature vectors

	Mat dictionary=bowTrainer.cluster(featuresUnclustered);
	//store the vocabulary
	FileStorage fs(p, FileStorage::WRITE);
	fs << "vocabulary" << dictionary;
	fs.release();

	cout<<"Done"<<endl;

}

Dictionary::~Dictionary(){}
