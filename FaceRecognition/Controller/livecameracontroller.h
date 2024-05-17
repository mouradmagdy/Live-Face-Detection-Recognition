#ifndef LIVECAMERACONTROLLER_H
#define LIVECAMERACONTROLLER_H

#include <opencv2/opencv.hpp>
#include "Helpers/basichelpers.h"
#include "Models/pca.h"
#include "Helpers/fileshelper.h"
#include "Models/facedetection.h"
#include "config.h"

class LiveCameraController
{
public:
    LiveCameraController();
    void predictPerson(Mat& frame);
        void predictPerson2(Mat& frame);
};

#endif // LIVECAMERACONTROLLER_H
