#include "HoG.h"




using namespace cv;
using namespace std;

HoG::HoG(){
    cout<<"Must provide folder path!"<<endl;
    exit(0);
}

HoG::HoG(string p){
    path = p;
    winS = 256;
    cellS = 4;
    blockS = 8;
    nBins = 8;
    bStr = 4;
}

HoG::HoG(string p,int ws,int cs,int bs, int nb, int bstr){
    path = p;
    winS = ws;
    cellS = cs;
    blockS = bs;
    nBins = nb;
    bStr = bstr;
}

//!compute HoG features of all images
//! arguments: start is the starting picture name
//!            num is how many pictures to compute
Mat HoG::compute(int start, int num){

    Mat featuresUnclustered;
    //set up parameters for HoG
    hog.winSize = Size(winS,winS);
	hog.cellSize = Size(cellS,cellS);
	hog.blockSize = Size(blockS,blockS);
    hog.nbins = nBins;
    hog.blockStride=Size(bStr,bStr);


    //get HoG features of all pictures
    for(int i=start; i<start+num; i++){
        //get full path name
        string filePath = path + "/"+ to_string(i) +".png";
        //read in image
        new_input = imread(filePath, CV_LOAD_IMAGE_GRAYSCALE);
        //testing
        if(new_input.rows!=winS || new_input.cols!=winS){
            cout<<"read image error"<<endl;
            cout<<"can't open "<<filePath<<endl;
        }

        //compute HoG + add to features Mat
        featuresUnclustered.push_back(getHoG(new_input));

    }

    //delete all zeros features
    return (deleteZeros(featuresUnclustered));

}


//! compute HoG features of a single image
//! argument: img is the input image
Mat HoG::getHoG(const Mat& img){

    //compute features and store to vector
    vector<float> features;
    hog.compute(img,features);

    //convert it to Mat
    int numF = pow((blockS/cellS),2)*nBins;
    Mat tmp(features.size()/numF , numF , CV_32F);
    for(int i=0;i<features.size();i+=numF){
        for(int j=0; j<numF; j++){
            tmp.at<float>(i/numF,j) = features[i+j];
        }
    }

    return tmp;

}


//! delete all zeros features
//! argument: features is the whole HoG features of all images
Mat HoG::deleteZeros(const Mat& features){

    //reduce dimension
    Mat sum;
    reduce(features, sum, 1, CV_REDUCE_SUM, CV_32F);
    //testing only
    if(sum.rows!=features.rows){
        cout<<"unequal rows deleting zeros"<<endl;
        exit(0);
    }
    //delete zero rows
    Mat non_zero;
    for(int i=0; i<sum.rows; i++){
        if(sum.at<float>(i,0)!=0.0)
            non_zero.push_back(features.row(i));
    }
    //testing only
    if(non_zero.cols!=features.cols){
        cout<<"unequal cols deleting zeros"<<endl;
        exit(0);
    }

    return non_zero;
}

HoG::~HoG(){}
