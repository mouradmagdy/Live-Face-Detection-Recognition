#include "pca.h"
#include "QDebug"

#define SHOW_IMAGE 0

_PCA::_PCA()
{

}

_PCA::_PCA(vector<Mat> faces){
    getImgSize(faces);
    imgRows = faces[0].rows;
    mergeMatrix(faces);
    getAverageVector();
    subtractMatrix();
    Mat _covarMatrix = (subFacesMatrix.t()) * subFacesMatrix;
    getBestEigenVectors(_covarMatrix,0.9);
    calcWeights();
}

/*
    @param faces: the images to get the size of
    @return: void
    @description: Gets the size of the images

*/

void _PCA:: getImgSize(vector<Mat> faces)
{
    //Dimession of Features
    imgSize = faces[0].rows * faces[0].cols;
    //cout << "Per Image Size is: " << size << endl;
}

/*
    @param faces: the images to merge
    @return: void
    @description: Merges the images into a single matrix
*/

void _PCA::mergeMatrix(vector<Mat> faces)
{
    int col = faces.size();
    allFacesMatrix.create(imgSize, col, CV_32FC1);

    for (int i = 0; i < col; i++) {
        Mat tmpMatrix = allFacesMatrix.col(i);
        //Load grayscale image 0
        Mat tmpImg;
        faces[i].convertTo(tmpImg, CV_32FC1);
        //convert to 1D matrix
        tmpImg.reshape(1, imgSize).copyTo(tmpMatrix);
    }
    //cout << "Merged Matix(Width, Height): " << mergedMatrix.size() << endl;
}


/*
    @return: void
    @description: Gets the average face
*/

void _PCA::getAverageVector()
{
    //To calculate average face, 1 means that the matrix is reduced to a single column.
    //vector is 1D column vector, face is 2D Mat
    Mat face;
    cv::reduce(allFacesMatrix, avgVector, 1, REDUCE_AVG);
}

/*
    @return: void
    @description: Subtracts the average face from all faces
*/

void _PCA::subtractMatrix()
{
    allFacesMatrix.copyTo(subFacesMatrix);
    for (int i = 0; i < subFacesMatrix.cols; i++) {
        subtract(subFacesMatrix.col(i), avgVector, subFacesMatrix.col(i));
    }
}

/*
    @param _covarMatrix: the covariance matrix
    @param threshold: the threshold to reduce the matrix
    @return: void
    @description: Gets the best eigen vectors
*/

void _PCA::getBestEigenVectors(Mat _covarMatrix,float threshold)
{
    //Get all eigenvalues and eigenvectors from covariance matrix
    Mat allEigenValues, allEigenVectors;
    eigen(_covarMatrix, allEigenValues, allEigenVectors);

    // reduce till the threshold
    float sum = 0;
    float totalSum = 0;
    for (int i = 0; i < allEigenValues.rows; i++) {
        totalSum += allEigenValues.at<float>(i, 0);
    }
    for (int i = 0; i < allEigenValues.rows; i++) {
        sum += allEigenValues.at<float>(i, 0);
        if (sum / totalSum >= threshold) {
            qDebug() << "Reached threshold at: " << i<<"\n";
            eigenVector = allEigenVectors.rowRange(0, i + 1);
            break;
        }
    }


    eigenVector = allEigenVectors * (subFacesMatrix.t());
    //Normalize eigenvectors
    for(int i = 0; i < eigenVector.rows; i++ )
    {
        Mat tempVec = eigenVector.row(i);
        normalize(tempVec, tempVec);
    }
}

/*
    @return: Mat
    @description: Returns the eigen faces
*/

Mat _PCA::getFacesMatrix()
{
    return allFacesMatrix;
}

/*
    @return: Mat
    @description: Returns the average face
*/

Mat _PCA::getAverage()
{
    return avgVector;
}

/*
    @return: Mat
    @description: Returns the eigen vectors
*/

Mat _PCA::getEigenvectors()
{
    return eigenVector;
}


/*
    @return: Mat
    @description: Returns the weights
*/

Mat _PCA::getWeights()
{
    return weights;
}

/*
    @return: void
    @description: Calculates the weights
*/

void _PCA::calcWeights()
{

    Mat facesMatrix = getFacesMatrix();
    Mat avg = getAverage();
    Mat eigenVec = getEigenvectors();

    weights.create(facesMatrix.cols, facesMatrix.cols, CV_32FC1);

    for (int i = 0; i < facesMatrix.cols; i++) {
        Mat temp;
        Mat projectFace = weights.col(i);
        subtract(facesMatrix.col(i), avg, temp);
        projectFace = eigenVec * temp;
    }
}

_PCA::~_PCA() {}
