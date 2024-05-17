#ifndef PCA_H
#define PCA_H

#include <iostream>
#include <vector>
#include <float.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;



/*
    To Apply PCA There are 3 steps:
    1. Standardize the data.
    2. Obtain the Eigenvectors and Eigenvalues from the covariance matrix or correlation matrix, or perform Singular Vector Decomposition.
    3. Sort eigenvalues in descending order and choose the k eigenvectors that correspond to the k largest eigenvalues where k is the number of dimensions of the new feature subspace (k<=d).
*/

class _PCA
{
public:
    _PCA();
    _PCA(vector<Mat> faces);
    Mat getFacesMatrix();
    Mat getAverage();
    Mat getEigenvectors();
    Mat getWeights();
    ~_PCA();

private:
    void getImgSize(vector<Mat> faces);
    void mergeMatrix(vector<Mat> faces);
    void getAverageVector();
    void subtractMatrix();
    void getBestEigenVectors(Mat _covarMatrix,float threshold = 0.90);
    void calcWeights();
    int imgSize = -1;//Dimension of features
    int imgRows = -1;//row# of image
    Mat allFacesMatrix;
    Mat avgVector;
    Mat subFacesMatrix;
    Mat eigenVector;
    Mat weights;
};

#endif // PCA_H
