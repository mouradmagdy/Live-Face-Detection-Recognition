#include "modelpredictioncontroller.h"
namespace fs = std::filesystem;
ModelPredictionController::ModelPredictionController() {

}




void ModelPredictionController::loadImages(std::string datasetPath){
        cout<<"ana d5lt";
        std::vector <std::string> trueLabells;
        std::vector<cv::Mat> faces = Fetcher::readImagesFromFolder(datasetPath,trueLabells);
        this->allFaces.insert(allFaces.end(), faces.begin(), faces.end());
        cout<<allFaces.size();
        for(int i=0;i<faces.size();i++){
            imwrite("facebag"+to_string(i)+".png",faces[i]);
        }
        this->trueLabels = trueLabells;

    // std::vector <std::string> files = FilesHelper::getFiles();
    // std::vector <Mat> images;
    // for (int i = 0; i < files.size(); i++)
    // {
    //     Image img(files[i]);
    //     imgs.push_back(img);
    //     images.push_back(img.getOriginalImg())
    // }
}



std::vector <pair<std::string,double>> ModelPredictionController::predictPersons()
{

    std::vector <pair<std::string,double>> faceIds;
    Mat eigens= pcaInstance.getEigenvectors();
    Mat meanRead= pcaInstance.getAverage();
    vector<string>loadedWeights;
    Mat _= FilesHelper::readWeights(labelsSize,loadedWeights,0);
    Mat w = pcaInstance.getWeights();
    FaceDetection hello(w,eigens,meanRead,loadedWeights);
    faceIds = hello.detectTestData(this->allFaces);
    return faceIds;
}


void ModelPredictionController::generateModelConfusion( std::vector<pair<std::string,double>> predictions, std::vector<std::string> truePersons){
    std::vector<float> trueLabels;
    std::vector<float> NPRLIST;
    std::vector<float> TPRLIST;
    std::vector <float>thresholds = {0,120,150,200,250,270,300,330,350,400,440,480,510,520,800,1000,1200,1500,1800,2000,2500};


    for (float threshold : thresholds) {
        float TpCounter = 0, TnCounter = 0, FnCounter = 0, FpCounter = 0;

    for(int i=0; i<predictions.size(); i++){
        if(predictions[i].second>threshold && truePersons[i]==predictions[i].first )
            TpCounter++;

        if(predictions[i].second<threshold && truePersons[i]==predictions[i].first )
            FnCounter++;

        if(predictions[i].second>threshold && truePersons[i]!=predictions[i].first)
            FpCounter++;

        if(predictions[i].second<threshold && truePersons[i]!=predictions[i].first )
            TnCounter++;
    }
    float NPR= FpCounter/(TnCounter+FpCounter);
    float TPR =TpCounter/(TpCounter+FnCounter);
    NPRLIST.push_back(NPR);
    TPRLIST.push_back(TPR);
    }
    this->NPR=NPRLIST;
    this->TPR=TPRLIST;
    float thresooold = 3000;

    float TpCounterr = 0, TnCounterr = 0, FnCounterr = 0, FpCounterr = 0;
    for(int i=0; i<predictions.size(); i++){

        if(predictions[i].second<thresooold && truePersons[i]==predictions[i].first )
            TpCounterr++;

        if(predictions[i].second>thresooold && truePersons[i]==predictions[i].first )
            FnCounterr++;

        if(predictions[i].second<thresooold && truePersons[i]!=predictions[i].first)
            FpCounterr++;

        if(predictions[i].second>thresooold && truePersons[i]!=predictions[i].first )
            TnCounterr++;
    }
    this->fp =FpCounterr;
    this->fn =FnCounterr;
    this->tn =TnCounterr;
    this->tp = TpCounterr;




}


