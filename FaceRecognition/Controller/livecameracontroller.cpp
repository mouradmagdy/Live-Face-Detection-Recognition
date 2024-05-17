#include "livecameracontroller.h"

LiveCameraController::LiveCameraController() {


}

void LiveCameraController::predictPerson(Mat& frame)
{
    Mat eigens = pcaInstance2.getEigenvectors();
    Mat mean = pcaInstance2.getAverage();
    vector<string>loadedWeights;
    Mat _= FilesHelper::readWeights(labelSize2,loadedWeights,1);
    Mat w = pcaInstance2.getWeights();
    FaceDetection detector(w,eigens,mean,loadedWeights);
    detector.liveDetection(frame);

}

void LiveCameraController::predictPerson2(Mat& frame)
{
    Mat eigens = pcaInstance.getEigenvectors();
    Mat mean = pcaInstance.getAverage();
    vector<string>loadedWeights;
    Mat _= FilesHelper::readWeights(labelsSize,loadedWeights,1);
    Mat w = pcaInstance.getWeights();
    FaceDetection detector(w,eigens,mean,loadedWeights);
    detector.liveDetection2(frame);
}
