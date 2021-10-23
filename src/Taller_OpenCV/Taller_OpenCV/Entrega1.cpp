#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int main()
{
    string path = "Resources/imagen1.jpg";
    Mat img = imread(path);
    
    CascadeClassifier faceCascade;
    faceCascade.load("haarcascade_frontalface_default.xml");

    vector<Rect> faces;
    faceCascade.detectMultiScale(img,faces,1.1,10);

    for (int i = 0; i < faces.size(); i++)
    {
        rectangle(img, faces[i].tl(), faces[i].br(), Scalar(0, 0,255),3);
    }
    
    imshow("Image", img);
    waitKey(0);
}
