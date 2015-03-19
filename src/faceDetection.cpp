//
//  faceDetection.cpp
//  EyeDetection
//
//  Created by Jakub Vlk on 19/03/15.
//
//

#include "faceDetection.h"
#import "constants.h"



#if XCODE
string faceCascadeName = "../../../res/haarcascade_frontalface_alt.xml";
#else
string faceCascadeName = "../res/haarcascade_frontalface_alt.xml";
#endif

CascadeClassifier faceCascade;



// private functions
Rect getBiggestFace(vector<Rect> &faces);


Mat faceDetection(Mat &frame)
{
    vector<Rect> faces;
    Mat frame_gray;
    /*eyesCentres.clear();
     irises.clear();
     pupils.clear();*/
    
    // convert from color to grayscale
    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    
    // contrast adjustment using the image's histogram
    equalizeHist( frame_gray, frame_gray );
    
    //Detects objects (faces) of different sizes in the input image. The detected objects are returned as a list of rectangles.
    faceCascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(frame_gray.size().width / 6, frame_gray.size().height / 6) );
    
    if (faces.size() > 0)
    {
        Rect face = getBiggestFace(faces);
        
        Point center( face.x + face.width*0.5, face.y + face.height*0.5 );
        rectangle( frame, Rect(face.x, face.y, face.width, face.height), Scalar( 255, 0, 255 ), 4, 8, 0 );
        
        Mat faceROI = frame_gray( face );
    }
}

void loadFaceCascade()
{
    if( !faceCascade.load( faceCascadeName ) )
    {
        cerr << "Can't load face cascade " + faceCascadeName << endl;
    }
}


Rect getBiggestFace(vector<Rect> &faces)
{
    
    double max = 0;
    int maxIndex = -1;
    
    for (int i = 0; i < faces.size(); ++i)
    {
        int volume = faces[i].size().width * faces[i].size().height;
        if (volume > max)
        {
            max = volume;
            maxIndex = i;
        }
    }
    
    if (maxIndex >= 0)
    {
        return faces[maxIndex];
    }
    else
    {
        return faces[0];
    }
}