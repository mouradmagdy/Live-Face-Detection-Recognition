#ifndef READFILE_H
#define READFILE_H

#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <QDebug>
#include "opencv2/core.hpp"


using namespace std;
using namespace cv;

/*
    @param listFilePath: the path to the file containing the list of faces
    @param facesPath: the vector to store the paths of the faces
    @param facesID: the vector to store the IDs of the faces
    @return: void
    @description: Reads the list of faces from the file

*/

void readList(string& listFilePath, vector<string>& facesPath, vector<string>& facesID)
{
    ifstream file(listFilePath.c_str(), ifstream::in);

    if (!file) {
//        qDebug() << "Fail to open file: " << listFilePath << "\n";
    }

    string line, path, id;
    while (getline(file, line)) {
        stringstream lines(line);
        getline(lines, id, ';');
        getline(lines, path);

        path.erase(remove(path.begin(), path.end(), '\r'), path.end());
        path.erase(remove(path.begin(), path.end(), '\n'), path.end());
        path.erase(remove(path.begin(), path.end(), ' '), path.end());

        facesPath.push_back(path);
        //facesID.push_back(atoi(id.c_str()));
        facesID.push_back(id);
    }
}

/*
    @param noOfFaces: the number of faces to read
    @param loadedFaceID: the vector to store the IDs of the faces
    @return: the matrix containing the faces
    @description: Reads the faces from the file
*/

//read faces in eigenspace that has been trained
Mat readFaces(int noOfFaces, vector<string>& loadedFaceID)
{
    Mat faces = Mat::zeros(noOfFaces, noOfFaces, CV_32FC1);
    string facesDataPath = "/Users/zichun/Documents/Assignment/FaceRecognition/FRG/data/facesdata.txt";
    ifstream readFaces(facesDataPath.c_str(), ifstream::in);

    if (!readFaces) {
        cout << "Fail to open file: " << facesDataPath << endl;
    }

    string line, id;
    loadedFaceID.clear();
    for (int i = 0; i < noOfFaces; i++) {
        getline(readFaces, line);
        stringstream lines(line);
        getline(lines, id, ':');
        loadedFaceID.push_back(id);
        for (int j = 0; j < noOfFaces; j++) {
            string data;
            getline(lines, data, ' ');
            faces.col(i).at<float>(j) = atof(data.c_str());
        }
    }

    readFaces.close();
    //cout << faces.row(14).at<float>(14) << endl;
    return faces;
}

/*
    @param noOfFaces: the number of faces to read
    @param loadedWeights: the vector to store the IDs of the faces
    @return: the matrix containing the weights
    @description: Reads the weights from the file

*/

//read average face of all faces
Mat readMean()
{
    Mat mean = Mat::zeros(10000, 1, CV_32FC1);
    string meanPath = "/Users/zichun/Documents/Assignment/FaceRecognition/FRG/data/mean.txt";
    ifstream readMean(meanPath.c_str(), ifstream::in);

    if (!readMean) {
        cout << "Fail to open file: " << meanPath << endl;
    }

    string line;
    for (int i = 0; i < 1; i++) {
        getline(readMean, line);
        stringstream lines(line);
        for (int j = 0; j < mean.rows; j++) {
            string data;
            getline(lines, data, ' ');
            mean.col(i).at<float>(j) = atof(data.c_str());
        }
    }

    readMean.close();
    //cout << mean.col(0).at<float>(1) << endl;
    return mean;
}

/*
    @param noOfFaces: the number of faces to read
    @param loadedWeights: the vector to store the IDs of the faces
    @return: the matrix containing the weights
    @description: Reads the weights from the file

*/

//read eigenvector
Mat readEigen(int noOfFaces)
{
    Mat eigen = Mat::zeros(noOfFaces, 10000, CV_32FC1);
    string eigenPath = "/Users/zichun/Documents/Assignment/FaceRecognition/FRG/data/eigen.txt";
    ifstream readEigen(eigenPath.c_str(), ifstream::in);

    if (!readEigen) {
        cout << "Fail to open file: " << eigenPath << endl;
    }

    string line;
    for (int i = 0; i < noOfFaces; i++) {
        getline(readEigen, line);
        stringstream lines(line);
        for (int j = 0; j < eigen.cols; j++) {
            string data;
            getline(lines, data, ' ');
            eigen.at<float>(i,j) = atof(data.c_str());
        }
    }

    readEigen.close();
    //cout << eigen.row(14).at<float>(9998) << endl;
    return eigen;
}


#endif // READFILE_H
