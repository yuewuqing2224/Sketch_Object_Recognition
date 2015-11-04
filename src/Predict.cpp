#include "Predict.h"
#include "Quantify.h"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

Predict::Predict(string p1, string p2, int nInst, int nFea){
    modelPath = p1;
    instancesPath = p2;
    numInstance = nInst;
    numFeature = nFea;
    readYML(); //read instances from yml file
}

//! predict class label when it's integer
void Predict::getClass(string p,int start){
    imgPath = p;
    //compute code book historgram for the image
    Quantify q(modelPath,256,20,80,4,2);
    Mat image = q.feature_hist(imgPath,start,1);
    //compute knn distance (here we set neighbor = 1)
    vector<Distance> knn;
    for(int i=0; i<instances.rows; i++){
        double sum = 0;
        //compute distance
        for(int j=0; j<image.cols; j++){
            double f = image.at<double>(0,j);
            double c = instances.at<double>(i,j);
            double diff = abs(f-c);
            sum = sum + pow(diff,2);
        }
        //insert the new distance struct
        knn.push_back(Distance(instances.at<double>(i,instances.cols-1),sqrt(sum)));
    }
    //now sort in ascending order
    sort(knn.begin(), knn.end());
    //now save the class label output
    stringstream ss;
    for(int i=0; i<knn.size();i++){
        ss << knn[i].classLabel << endl;
    }
    ofstream myFile;
    myFile.open("prediction.txt");
    myFile << ss.str();
    myFile.close();
    return;
}

//! read from yml file and return Mat type
void Predict::readYML(){
    FileStorage fs(instancesPath, FileStorage::READ);
	fs["feature"] >> instances;
	fs.release();
}

Predict::~Predict(){}
