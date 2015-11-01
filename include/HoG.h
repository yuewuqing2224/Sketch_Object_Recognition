#ifndef HOG_H
#define HOG_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/nonfree/features2d.hpp>
#include <iostream>
#include <fstream>
#include <string>

using namespace cv;
using namespace std;

class HoG
{
    public:
        HoG();
        HoG(string p); //default one
        //ws -- window size
        //cs -- cell size
        //bs -- block size
        //nb -- number of bins
        //bstr -- block strike
        HoG(string p,int ws,int cs,int bs,int nb,int bstr);
        Mat compute(int start, int num); //compute all the features starting from start image till num of images is read
        virtual ~HoG();

    private:
        HOGDescriptor hog;
        int winS;
        int cellS;
        int blockS;
        int nBins;
        int bStr;
        string path;
        Mat input;
        Mat new_input;

        Mat getHoG(const Mat& img);
        Mat deleteZeros(const Mat& features);

};

#endif // HOG_H
