#include "Preprocess.h"
#include <string>

Preprocess::Preprocess(string p){
    path = p;
}

void Preprocess::process(int s,string p){
    DIR *dir;
    struct dirent *ent;
    int index = 1;
    //read in all images in a folder
    if((dir=opendir(path.c_str()))!=NULL){
        while((ent=readdir(dir))!=NULL){
            string imgName = ent->d_name;
            //errors that may occur
            if(imgName.compare("..")==0)
                continue;
            else if(imgName.compare(".")==0)
                continue;
            else{
                //process image and store it
                Mat img, gray;
                img = imread(path+"/"+imgName);
                //check image input
                if(img.rows==0 || img.cols==0){
                    cout<<"read image error"<<endl;
                    return;
                }
                //turn image to grayscale
                cvtColor(img, gray, CV_RGB2GRAY);
                Mat output = img_resize(gray,256);
                stringstream ss;
                ss<<p<<"/"<<index<<".png";
                imwrite(ss.str(),output);
                index++;
            }

        }
        closedir(dir);
    }
}


Mat Preprocess::img_resize(Mat& input, int s){
    //initial end to small value, start to big value
    int x_end = -1;
    int y_end = -1;
    int x_start = input.rows+input.cols;
    int y_start = input.rows+input.cols;
    //find starting and ending x y index
    for(int i=0; i<input.rows; i++){
        for(int j=0; j<input.cols; j++){
             unsigned char value = input.at<uchar>(i,j);
            //non-white pixel
            if(value!=255){
                if(i<x_start)
                    x_start = i;
                if(i>x_end)
                    x_end = i;
                if(j<y_start)
                    y_start = j;
                if(j>y_end)
                    y_end = j;
            }
        }
    }
    //resize image to cover 3/4 of s size output image
    int width = y_end-y_start;
    int height = x_end-x_start;
    //get the object part out of the original image
    Mat object = input(Rect(y_start, x_start,width, height));
    Mat object_resize;
    float scale_w = (s*0.75)/width;
    float scale_h = (s*0.75)/height;
    //use the longest axies for resize
    float scale = (scale_w<scale_h) ? scale_w : scale_h;
    resize(object, object_resize, Size((int)width*scale,(int)height*scale));
    //creat a white image of 256 size
    Mat output(s,s,CV_8U);
    output = Scalar(255);
    int x = 0.5*(s - width*scale);
    int y = 0.5*(s-height*scale);
    //copy resized object into the new image
    object_resize.copyTo(output(Rect(x,y,object_resize.cols,object_resize.rows)));
    return output;

}

Preprocess::~Preprocess(){}
