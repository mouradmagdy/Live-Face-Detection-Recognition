#ifndef FACEDETECTION_H
#define FACEDETECTION_H

#include<iostream>
#include<opencv2/opencv.hpp>
#include "config.h"

using namespace cv;
using namespace std;

class FaceDetection
{
public:
    FaceDetection();
    FaceDetection(Mat weights,Mat eigenFaces, Mat mean,std::vector <std::string> loadedWeights);

    void liveDetection(Mat& frame);
    void liveDetection2(Mat& frame);

    void detectFaces(Mat faceImage,bool isLive);
    void recognize(bool isLive);
    void projectFace(Mat testVec);
    std::vector <pair<std::string,double>> detectTestData(vector <Mat> testFaces);
    Mat prepareFace(Mat _testImg);
    string getFaceId();
    double getDistance();

private:

    Mat weights,eigenFaces,mean,projectedFace;
    string closetFaceID;
    double closetFaceDist;
    std::vector <std::string> loadedWeights;

};

#endif // FACEDETECTION_H
