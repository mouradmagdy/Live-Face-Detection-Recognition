#include "fetcher.h"
#include <filesystem>

namespace fs = std::filesystem;

Fetcher::Fetcher() {}

// cv::Mat Fetcher::fetch(std::string datasetPath)
// {
//     std::vector<cv::Mat> allFaces;

//     // Iterate over folders in the dataset path
//     for (const auto& entry : fs::directory_iterator(datasetPath)) {
//         if (entry.is_directory()) {
//             std::string folderPath = entry.path().string();
//             std::vector<cv::Mat> faces = readImagesFromFolder(folderPath);
//             allFaces.insert(allFaces.end(), faces.begin(), faces.end());
//         }
//     }
//     cv::Mat data = flattenFaces(allFaces);
//     return data;
// }

std::vector<cv::Mat> Fetcher::readImagesFromFolder(const std::string& folderPath, std::vector <std::string>& extractedFilename) {
    std::vector<cv::Mat> faces;

    // Iterate over files in the folder
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            std::string imagePath = entry.path().string();
            cv::Mat image = cv::imread(imagePath);

            fs::path filePath(imagePath);
            std::string filename = filePath.filename().string();
            size_t pos = filename.find('-');
            std::string exFileName = filename.substr(0, pos);
            extractedFilename.push_back(exFileName);
            std::cout<<"extn"<<exFileName<<std::endl;
            image.convertTo(image,CV_32FC1);
            if (!image.empty()) {
                faces.push_back(image);
            }
        }
    }

    return faces;
}

cv::Mat Fetcher::flattenFaces(std::vector<cv::Mat> faces)
{
    cv::Size targetSize = cv::Size(64,64);

    int imgSize = 64*64;

    for(int i = 0; i < faces.size(); i++) {
        resize(faces[i], faces[i], targetSize);
    }

    // Creating the matrix to hold all flattened faces
    cv::Mat allData = cv::Mat::zeros(targetSize.width * targetSize.height,static_cast<int>(faces.size()), CV_32FC1);

    // Copying each flattened image data to a row in all_data
    for(int i = 0; i < faces.size(); i++) {
        cv::Mat tmp;
        faces[i].convertTo(tmp,CV_32FC1);
        tmp.reshape(1,imgSize).copyTo(allData.col(i));
    }
    return allData;
}
