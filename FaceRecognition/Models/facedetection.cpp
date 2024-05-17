#include "facedetection.h"
#include "qdebug.h"

FaceDetection::FaceDetection()
{

}

FaceDetection::FaceDetection(Mat weights,Mat eigenFaces, Mat mean,std::vector <std::string> loadedWeights) {
    this->eigenFaces= eigenFaces;
    this->weights = weights;
    this->mean = mean;
    this->loadedWeights = loadedWeights;
}

/*
    @param frame: the frame to detect faces in
    @return: void
    @description: Detects faces in the frame and draws rectangles around them
*/

void FaceDetection::liveDetection(Mat &frame)
{
    Mat grey;
    cvtColor(frame,grey,COLOR_BGR2GRAY);

    /*
    * Detect faces with the classifier
   */
    detectFaces(frame,1);
    string face = closetFaceID;
    std::vector<Rect> faces;
    cascade.detectMultiScale(grey,faces);
    // Draw rectangles around the faces
    for (int i = 0; i < faces.size(); ++i) {
        rectangle(frame, faces[i], Scalar(255, 0, 0), 2);
        putText(frame, face, Point(faces[i].x, faces[i].y), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);
    }
}

void FaceDetection::liveDetection2(Mat &frame)
{
    Mat grey;
    cvtColor(frame,grey,COLOR_BGR2GRAY);

    /*
    * Detect faces with the classifier
   */
    std::vector<Rect> faces;
    cascade.detectMultiScale(grey,faces);
    // Draw rectangles around the faces
    for (int i = 0; i < faces.size(); ++i) {

          Mat faceROI = grey(faces[i]);
//          std::string faceName = "./Gallery/face" + std::to_string(i) + ".jpg";
//          imwrite(faceName,faceROI);


          double cX,cY;
          cX = (faces[i].x + faces[i].width)/2;
          cY = (faces[i].y + faces[i].height)/2;
          Point center(cX,cY);
          rectangle(frame,faces[i],Scalar(255,0,0),2);
      }
}



/*
    @param faceImage: the image to detect faces in
    @return: void
    @description: Detects faces in the image and returns the grey image
*/

void FaceDetection::detectFaces(Mat faceImage,bool isLive)
{
    Mat grey;
    cvtColor(faceImage, grey, COLOR_BGR2GRAY);

    // Assuming 'cascade' and other necessary variables are already initialized

    // Preprocess the face image if needed
    Mat processedFace = prepareFace(grey);

    // Project the face for recognition
    projectFace(processedFace);

    // Recognize the face
    recognize(isLive);

    // Return the grey image (original image) or you can return any other result as needed
}

/*
    @param faceImage: the image to detect faces in
    @return: void
    @description: Detects faces in the image and returns the grey image
*/


void FaceDetection::recognize(bool isLive)
{

    int minDist = INT_MAX;
    int min_index = -1;
    for (int i =0; i < loadedWeights.size(); i++) {
        Mat src1 = weights.col(i);
        Mat src2 = projectedFace;

        double dist = norm(src1, src2, NORM_L2);
    //    cout << dist << endl ;
        if (dist < minDist) {
            minDist = dist;
            min_index = i;
        }
    }

    this->closetFaceDist = minDist;
    mi = minDist;
    int threshold;
    if(isLive) threshold=2000;
    else threshold = 3500;
    if(minDist>=threshold){
    this->closetFaceID = "Unknown";
    }
    else{
    this->closetFaceID = loadedWeights[min_index];
    }
}

/*
    @param testVec: the image to detect faces in
    @return: void
    @description: Detects faces in the image and returns the grey image
*/

void FaceDetection::projectFace(Mat testVec)
{
    Mat tmpData;
    cout << testVec.type()<<endl;
    cout << mean.type() << endl;
    cout << testVec.rows << "X" << testVec.cols <<endl;
    cout << eigenFaces.rows << "X" << eigenFaces.cols <<endl;
    mean.convertTo(mean,CV_32FC1);
    testVec.convertTo(testVec,CV_32FC1);
    subtract(testVec, mean, tmpData);
    projectedFace = eigenFaces * tmpData;
}

/*
    @param faceROI: the image to detect faces in
    @return: void
    @description: Detects faces in the image and returns the grey image
*/

Mat FaceDetection::prepareFace(Mat faceROI)
{
    Size newSize(64, 64);
    resize(faceROI, faceROI, newSize);
    faceROI = faceROI.reshape(1, (faceROI.rows * faceROI.cols));
   faceROI.convertTo(faceROI,CV_32FC1);
   return faceROI;
}

/*
    @param faceImage: the image to detect faces in
    @return: void
    @description: Detects faces in the image and returns the grey image
*/

string FaceDetection::getFaceId()
{
    return closetFaceID;
}


std::vector <pair<std::string,double>> FaceDetection::detectTestData(vector <Mat> testFaces){
    std::vector <pair<std::string,double>> faceIds;
    for (int i = 0; i < testFaces.size(); i++) {
        Mat face = testFaces[i];
        detectFaces(face,0);
        faceIds.push_back({closetFaceID,mi});
        cout<<closetFaceID<<" "<<mi<<endl;
    }
    return faceIds;
}
