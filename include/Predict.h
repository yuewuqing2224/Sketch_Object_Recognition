#ifndef PREDICT_H
#define PREDICT_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/nonfree/features2d.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

struct Distance{
    double classLabel;
    double dist;
    Distance(double c, double d) : classLabel(c), dist(d) {}
    //override operator
    bool operator < (const Distance& str) const
    {
        return (dist < str.dist);
    }

};


class Predict
{
    public:
        Predict(string p1,string p2, int nInst, int nFea);
        void getClass(string p,int start);
        virtual ~Predict();

    private:
        string modelPath;
        string imgPath;
        string labelPath;
        string instancesPath;
        int numInstance;
        int numFeature;
        Mat instances;
        void readYML();

};

#endif // PREDICT_H
