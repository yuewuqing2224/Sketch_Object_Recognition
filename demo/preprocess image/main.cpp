//! this code demonstrates how to preprocess images
//! before using them for later work

#include "Preprocess.h"


int main(){
  Preprocess p("path to your original images folder");  
  // specify the folder to your images

  p.process(256,"path to folder where your want to store the new output images");
  // preprocess all images to standard size (this also center all object into the center)
  // here 256 is the pixel size of the output square matrix, you can use other size

  return 0;
}


