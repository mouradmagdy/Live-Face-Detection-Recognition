#include "facepredictioncontroller.h"


FacePredictionController::FacePredictionController() {
    img = new Image();
}

QPixmap FacePredictionController::uploadImg() {

    QString path = BasicHelpers::openFile(); // Opens a file dialog to select an image file
    if(!path.isEmpty()){
        //        delete img; // Deletes any previous image
        img = new Image(path.toStdString()); // Loads the image from the selected path
        if(!img->isEmpty()){ // Checks if the image is successfully loaded
            return BasicHelpers::convertMatToPixmap(img->getOriginalImg()); // Converts the image to QPixmap
        }
    }
    return BasicHelpers::convertMatToPixmap(Mat::zeros(1,1,CV_8UC1)); // Returns a blank QPixmap if image loading fails
}




string FacePredictionController::predictPerson()
{
         Mat eigens= pcaInstance.getEigenvectors();
         Mat meanRead= pcaInstance.getAverage();
         vector<string>loadedWeights;
         Mat _= FilesHelper::readWeights(labelsSize,loadedWeights,0);
         Mat w = pcaInstance.getWeights();
         Mat image = img->getOriginalImg();
         FaceDetection hello(w,eigens,meanRead,loadedWeights);
         hello.detectFaces(image,0);
         return hello.getFaceId();
}

Mat FacePredictionController::detectFace()
{

}
