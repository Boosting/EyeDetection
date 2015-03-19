//
//  eyeDetection.h
//  EyeDetection
//
//  Created by Jakub Vlk on 19/03/15.
//
//

#ifndef __EyeDetection__eyeDetection__
#define __EyeDetection__eyeDetection__

#include <stdio.h>
#import "opencv2/opencv.hpp"

using namespace std;
using namespace cv;


Mat eyeDetection(Mat &face);
void loadEyeCascade();

#endif /* defined(__EyeDetection__eyeDetection__) */
