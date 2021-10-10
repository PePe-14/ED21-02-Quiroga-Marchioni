#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include <iostream>

using namespace cv;
using namespace std;

//Image
int main()
{
    string path = "Resources/imagen2.jpg";
    Mat img = imread(path);

    CascadeClassifier faceCascade;
    faceCascade.load("haarcascade_frontalface_default.xml");

    if (faceCascade.empty()) { cout << "no se cargo el archivo" << endl; }

    vector<Rect> faces;
    faceCascade.detectMultiScale(img,faces,1.1,10);

    for (int i = 0; i < faces.size(); i++)
    {
        rectangle(img, faces[i].tl(), faces[i].br(), Scalar(0, 0,255),3);
    }
    
    imshow("Image", img);
    waitKey(0);
}


/*/ Webcam
/int main()
{
  
    VideoCapture cap(0);
    Mat img;

    while (true) {
        
        cap.read(img);

        imshow("Image", img);
        waitKey(1);
    }
}*/