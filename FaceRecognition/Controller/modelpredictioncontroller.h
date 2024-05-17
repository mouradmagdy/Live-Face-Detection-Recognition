#ifndef MODELPREDICTIONCONTROLLER_H
#define MODELPREDICTIONCONTROLLER_H
#include "Models/image.h"
#include <opencv2/opencv.hpp>
#include "Helpers/basichelpers.h"
#include "Models/pca.h"
#include "Helpers/fileshelper.h"
#include "Models/facedetection.h"
#include "Models/fetcher.h"
#include "config.h"
#include<iostream>
#include <filesystem>
class ModelPredictionController
{
public:
    ModelPredictionController();
    std::vector <Image> imgs;
    std::vector <Mat> allFaces;
    std::vector <std::string> trueLabels;
    std::vector <pair<std::string,double>> predictPersons();
    std::vector <float> TPR;
    std::vector <float> NPR;
    float tp,fp,tn,fn;
    void loadImages(std::string datasetPath);
    void generateModelConfusion( std::vector<pair<std::string,double>> predictions, std::vector<std::string> truePersons);

};

#endif // MODELPREDICTIONCONTROLLER_H
