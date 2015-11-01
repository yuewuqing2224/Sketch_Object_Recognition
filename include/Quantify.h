#ifndef QUANTIFY_H
#define QUANTIFY_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/nonfree/features2d.hpp>
#include <iostream>
#include <fstream>
#include "HoG.h"
#include <math.h>

using namespace std;
using namespace cv;

class Quantify
{
    public:
        Quantify();
        Quantify(string p,int ws,int cs,int bs, int nb, int bstr);
        Mat feature_hist(string p,int start,int num);
        virtual ~Quantify();

    private:
        string path;
        int winS;
        int cellS;
        int blockS;
        int nBins;
        int bStr;
        Mat codebook;

        Mat compute_hist(Mat& features);

};

#endif // QUANTIFY_H
