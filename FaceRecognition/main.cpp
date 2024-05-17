#include "Views/mainwindow.h"
#include "Models/facedetection.h"
#include "Models/fetcher.h"
#include "Models/pca.h"
#include <filesystem>

#include <QApplication>
#include"Models/readfile.h"

#include <iostream>
#include"Helpers/fileshelper.h"
#include "config.h"



namespace fs = std::filesystem;
map<string,int> idToPerson;
int idx= 0 ;


std::vector<Mat> getFaces(std::string path){
    std::vector<Mat> faces;
    Size targetSize = cv::Size(64,64);
    // Iterate over files in the folder
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            std::string imagePath = entry.path().string();
            Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);

            // Create a path object from the imagePath string
             fs::path filePath(imagePath);
             std::string filename = filePath.filename().string();
             size_t pos = filename.find('-');
             std::string extractedFilename = filename.substr(0, pos);

             std::cout << "Extracted Filename: " << extractedFilename << std::endl;
            if(!idToPerson[extractedFilename]){
                idToPerson[extractedFilename] = idx;
                idx++;
            }
        //    cout<<imagePath<<endl;
            if (!image.empty()) {
                faces.push_back(image);
            }
        }
    }
    for(int i = 0; i < faces.size(); i++) {
        resize(faces[i], faces[i], targetSize);
    }
    for (int i = 0; i < faces.size(); i++) {
        faces[i].convertTo(faces[i],CV_32FC1);
    }
    return faces;
}




int main(int argc, char *argv[])
{
    string classifier = "./Assets/haarcascade_frontalface_alt.xml";

   if(!cascade.load(classifier)){
       qDebug()<< "Error in casscade";
       return 1;
   }
   qDebug()<< "Classifier loaded";


  // Precompute PCA for all dataset
   std::vector<Mat> faces;
   faces = getFaces("./dataset4");
   pcaInstance= _PCA(faces);
   Mat weight = pcaInstance.getWeights();
   vector<string>ids;
   for(auto it = idToPerson.begin(); it != idToPerson.end(); ++it){
         for(int j=0;j<7;j++){
             ids.push_back(it->first);
         }
   }
   labelsSize = ids.size();
   FilesHelper::writeWeights(ids,weight,0);
//////////////

     idx=0;
     idToPerson.clear();
   // Precompute PCA for all dataset
    std::vector<Mat> faces2;
    faces2 = getFaces("./datasetlive");
    pcaInstance2= _PCA(faces2);
    Mat weight2 = pcaInstance2.getWeights();
    vector<string>ids2;
    for(auto it = idToPerson.begin(); it != idToPerson.end(); ++it){
          for(int j=0;j<7;j++){
              ids2.push_back(it->first);
          }
    }
    labelSize2 = ids2.size();
    FilesHelper::writeWeights(ids2,weight2,1);



     QApplication a(argc, argv);
      MainWindow w;
      w.show();
      return a.exec();
     return 0;
}
