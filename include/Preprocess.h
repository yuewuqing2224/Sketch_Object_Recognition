#ifndef PREPROCESS_H
#define PREPROCESS_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/nonfree/features2d.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>

using namespace std;
using namespace cv;

class Preprocess
{
    public:
        Preprocess(string p); //p is the path to the image folder
        void process(int s, string p); //s is the size of the image that we want to have, p is the save path
        virtual ~Preprocess();

    private:
        string path;
        Mat img_resize(Mat& input, int s);
};

#endif // PREPROCESS_H
