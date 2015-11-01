#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/nonfree/features2d.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;


class Dictionary
{
    public:
        Dictionary();
        Dictionary(int s); //s is the number of words that we want to have
        void KCluster(Mat& featuresUnclustered, string p); //compute the knn cluster
        virtual ~Dictionary();

    private:
        int dictionarySize;

};

#endif // DICTIONARY_H
