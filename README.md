# sketch_object_recognition
Sketch object recognition program written in C++. <br /> <br />
This program partly follows the implementation from this paper: <br /> http://cybertron.cg.tu-berlin.de/eitz/pdf/2012_siggraph_classifysketch.pdf <br /> <br />
To run this program you need to have OpenCV installed on your computer. <br /> <br />

Implementation: <br /> 
1. Input images are processed and resized to a fixed size (Preprocess.cpp) <br /> 
2. Find HoG descriptors of input images (HoG.cpp) <br /> 
3. Compute Bag of Word from HoG descriptors (Dictionary.cpp) <br /> 
4. Compute Historgram of the code book (Quantify.cpp) <br /> 
5. Predict the class label for new input images using k-nearest neighbors algorithm (Predict.cpp)  <br /> 
(under development)
