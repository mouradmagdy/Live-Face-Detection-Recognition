#ifndef FILESHELPER_H
#define FILESHELPER_H

#include <opencv2/core.hpp>
#include <filesystem>
#include<iostream>
#include <fstream>
#include<string>
#include<vector>
using namespace std;
using namespace cv;
class FilesHelper
{
public:
    FilesHelper();
    static void writeToFile(Mat eigen,const std::string& filename);
    static void writeMeanToFile(Mat Mean,const std::string& filename);
    static Mat readMatrixFromFile(const std::string& filename);
    static Mat readMeanFromFile(const std::string& filename);
    static void writeWeights(vector<string>& _trainFacesID,Mat weights,bool isLive);
    static Mat readWeights(int noOfFaces,vector<string>& loadedFaceID,bool isLive);
};

#endif // FILESHELPER_H
