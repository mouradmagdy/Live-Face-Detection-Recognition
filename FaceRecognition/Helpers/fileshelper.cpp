#include "fileshelper.h"


FilesHelper::FilesHelper()
{

}


/*
    @param listFilePath: the path to the file containing the list of faces
    @param facesPath: the vector to store the paths of the faces
    @param facesID: the vector to store the IDs of the faces
    @return: void
    @description: Reads the list of faces from the file


*/


void FilesHelper::writeToFile(Mat eigen,const std::string& filename)
{
//    string eigenPath = "./data/eigen.txt";
    ofstream writeEigenFile(filename.c_str(), ofstream::out | ofstream::trunc);
    if (!writeEigenFile) {
        cout << "Fail to open file: " << filename << endl;
    }

    for (int i = 0; i < eigen.rows; i++) {
        for (int j = 0; j < eigen.cols; j++) {
            writeEigenFile << eigen.row(i).at<float>(j);
            writeEigenFile << " ";
        }
        writeEigenFile << "\n";
    }

    writeEigenFile.close();
}

/*
    @param listFilePath: the path to the file containing the list of faces
    @param facesPath: the vector to store the paths of the faces
    @param facesID: the vector to store the IDs of the faces
    @return: void
    @description: Reads the list of faces from the file
*/

void FilesHelper::writeMeanToFile(Mat Mean, const string &filename)
{
    ofstream writeMeanFile(filename.c_str(), ofstream::out | ofstream::trunc);
    if (!writeMeanFile) {
        cout << "Fail to open file: " << filename << endl;
    }

    for (int i = 0; i < Mean.rows; i++) {
        writeMeanFile << Mean.at<float>(i);
        writeMeanFile << " ";
    }

    writeMeanFile.close();
}


/*
    @param listFilePath: the path to the file containing the list of faces
    @param facesPath: the vector to store the paths of the faces
    @param facesID: the vector to store the IDs of the faces
    @return: void
    @description: Reads the list of faces from the file

*/

Mat FilesHelper:: readMatrixFromFile(const std::string& filename) {
    int num;
     Mat eigen;
    if(filename =="./data/eigen.txt" ) {eigen = Mat::zeros(4, 4096, CV_32FC1);num=4; }
    else { eigen = Mat::zeros(1, 4096, CV_32FC1); num=1; }
//    string eigenPath = "./data/eigen.txt";
    ifstream readEigen(filename, ifstream::in);

    if (!readEigen) {
        cout << "Fail to open file: " << filename << endl;
    }

    string line;
    for (int i = 0; i < num; i++) {
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

/*
    @param listFilePath: the path to the file containing the list of faces
    @param facesPath: the vector to store the paths of the faces
    @param facesID: the vector to store the IDs of the faces
    @return: void
    @description: Reads the list of faces from the file


*/

Mat FilesHelper::readMeanFromFile(const string &filename)
{
    Mat mean = Mat::zeros(4096, 1, CV_32FC1);
    ifstream readMean(filename.c_str(), ifstream::in);

       if (!readMean) {
           cout << "Fail to open file: " << filename << endl;
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
       return mean;
}

/*
    @param listFilePath: the path to the file containing the list of faces
    @param facesPath: the vector to store the paths of the faces
    @param facesID: the vector to store the IDs of the faces
    @return: void
    @description: Reads the list of faces from the file
*/


void FilesHelper::writeWeights(vector<string>& _trainFacesID,Mat weights,bool isLive)
{
    string facesDataPath;
    if(isLive) facesDataPath = "./dataset4files/weights.txt";
    else facesDataPath = "./dataset4files/weights2.txt";
    ofstream writeFaceFile(facesDataPath.c_str(), ofstream::out | ofstream::trunc);
    if (!writeFaceFile) {
        cout << "Fail to open file: " << facesDataPath << endl;
    }

    for (int i = 0; i < _trainFacesID.size(); i++) {
        writeFaceFile << _trainFacesID[i] << ":";
        for (int j = 0; j < weights.rows; j++) {
            writeFaceFile << weights.col(i).at<float>(j);
            writeFaceFile << " ";
        }
        writeFaceFile << "\n";
    }

    writeFaceFile.close();
}


/*
    @param noOfFaces: the number of faces to read
    @param loadedFaceID: the vector to store the IDs of the faces
    @return: the matrix containing the weights
    @description: Reads the weights from the file


*/


Mat FilesHelper::readWeights(int noOfFaces,vector<string>& loadedFaceID,bool isLive)
{
    Mat faces = Mat::zeros(noOfFaces, noOfFaces, CV_32FC1);
    string facesDataPath;
    if(isLive)facesDataPath = "./dataset4files/weights.txt";
    else facesDataPath = "./dataset4files/weights2.txt";
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
