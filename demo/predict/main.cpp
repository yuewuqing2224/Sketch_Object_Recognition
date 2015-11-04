#include "Predict.h"
#include <iostream>
#include <string>

using namespace std;


int main(int argc, char* argv[]){
  if(argc!=3){
    cout<<"Input Argument Error!"<<endl;
    cout<<"Example: ./predict images/Apple 62"<<endl;
    return 0;
  }

  string imgPath = argv[1];
  string number = argv[2];
  int fileIndex = atoi(number.c_str());
  cout<<"Predicting "<<argv[1]<<endl;

  Predict p("dict_50.yml","training_set.yml",500,51);
  p.getClass(imgPath,fileIndex);
  cout<<"Done, saved to prediction.txt"<<endl;

  return 0;
}





