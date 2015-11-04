//! this code demonstrates how to use knn to predict class label

#include "Predict.h"

int main(){
  Predict p("dict_50.yml","training_set.yml",160,81);
  // specify the path to our bag of word (codebook) model
  // specify the path to our codebook histogram 
  // 160 refers to the total number of instances in the 
  // codebook histogram
  // 81 refers to the total number of features (including class label)
  // in the codebook histogram

  p.getClass("path to predict image folder",62);
  // computes knn to the image specify in the image folder
  // 62 is the name of the image file (62.png here)
  // the output is called prediction.txt
  // it lists all the class label with ascending distance
  // (do note that this is not exactly knn but you can further process
  //  the output prediction on your own)

}

