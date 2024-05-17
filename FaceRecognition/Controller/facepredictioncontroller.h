#ifndef FACEPREDICTIONCONTROLLER_H
#define FACEPREDICTIONCONTROLLER_H
#include "Models/image.h"
#include <opencv2/opencv.hpp>
#include "Helpers/basichelpers.h"
#include "Models/pca.h"
#include "Helpers/fileshelper.h"
#include "Models/facedetection.h"
#include "config.h"

class FacePredictionController
{
public:
    FacePredictionController();
    Image* img;
    QPixmap uploadImg();
    string predictPerson();
    Mat detectFace();



};

#endif // FACEPREDICTIONCONTROLLER_H
