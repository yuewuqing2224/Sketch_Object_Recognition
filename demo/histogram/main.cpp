//! this code demonstrates how to create codebook histogram
//! of images 

#include "Quantify.h"

int main(){
  Mat total;
  Quantify q("dict_50.yml",256,20,80,4,2);
  // load the saved bag of word model 
  // specify the same parameters for computing HoG
  // this should be the same as the one used for bag of word model

  total.push_back(q.feature_hist("path to your image folder",1,80));
  // compute histogram of codebook for images in the image folder
  // the image starts with 1.png and continues to 80.png
  total.push_back(q.feature_hist("path to your other image folder",1,80));
  // you can compute for multiple folders (each folder refer to one class of images)

  Mat classLabel(total.rows,1,CV_64F);
  for(int i=0; i<total.rows; i++){
    if(i<80)
        classLabel.at<double>(i,0) = 1;
    else if(i<160)
        classLabel.at<double>(i,0) = 2;
  }
  hconcat(total, classLabel, total);
  // add the class label to the codebook historgram
  // this format is the one used for knn predicting function

  FileStorage fs("training_set.yml", FileStorage::WRITE);
  fs << "histogram" << total;
  fs.release();
  // save the codebook histogram 
  // knn predicting function will use this one

  return 0;
}

