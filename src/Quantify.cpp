#include "Quantify.h"

using namespace std;
using namespace cv;


Quantify::Quantify(){
    cout<<"please provide codebook path"<<endl;
}

Quantify::Quantify(string p,int ws,int cs,int bs, int nb, int bstr){
    path = p;
    winS = ws;
    cellS = cs;
    blockS = bs;
    nBins = nb;
    bStr = bstr;
    //read in codebook
    FileStorage fs(path, FileStorage::READ);
	fs["vocabulary"] >> codebook;
	fs.release();
}

Mat Quantify::feature_hist(string p,int start,int num){

     HoG hog = HoG(p,winS,cellS,blockS,nBins,bStr);
     Mat word_hists;
     //get code book hist
     for(int i=start; i<start+num; i++){
        Mat features = hog.compute(i,1);
        word_hists.push_back(compute_hist(features));
     }

     return word_hists;
}

Mat Quantify::compute_hist(Mat& features){

    Mat word_dist(1,codebook.rows,CV_64F);
    word_dist = Scalar(0);
    //soft kernel codebook
    double sigma = 0.2;
    //compute historgram
    for(int i=0; i<features.rows;i++){
        Mat feature_dist(1,codebook.rows,CV_64F); //single feature historgram
        feature_dist = Scalar(0);
        double sum_total = 0;
        //historgram vector
        for(int j=0; j<codebook.rows;j++){
            //check dimension
            if(codebook.cols!=features.cols){
                cout<<"dimension error"<<endl;
            }

            double sum = 0;

            for(int z=0; z<features.cols; z++){
                double f = features.at<float>(i,z);
                double c = codebook.at<float>(j,z);
                double diff = abs(f-c);
                sum = sum + pow(diff,2);
            }

            double gk = exp(-sqrt(sum)/(2*pow(sigma,2)));
            sum_total = sum_total + gk;
            feature_dist.at<double>(0,j) = gk;
        }
        //normalize the feature_dist historgram and add it to word_dist
        for(int z=0; z<feature_dist.cols; z++){
            double value = feature_dist.at<double>(0,z)/sum_total;
            word_dist.at<double>(0,z) = word_dist.at<double>(0,z) + value;
        }
    }
    //normalize the whole word_dist by the number of descriptors
    int numDescrip = features.rows;
    for(int i=0; i<word_dist.cols; i++){
        word_dist.at<double>(0,i) = word_dist.at<double>(0,i)/numDescrip;
    }

    return word_dist;
}

Quantify::~Quantify(){}
