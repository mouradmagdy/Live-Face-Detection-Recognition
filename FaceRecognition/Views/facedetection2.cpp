#include "facedetection2.h"
#include "ui_facedetection2.h"

FaceDetection2::FaceDetection2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FaceDetection2)
{
    ui->setupUi(this);
    liveController = new LiveCameraController();
    facePredictionController = new FacePredictionController();
}

FaceDetection2::~FaceDetection2()
{
    delete ui;
}

void FaceDetection2::on_uploadImgBtn_clicked()
{
    img = facePredictionController->uploadImg();
    img = img.scaled(ui->imageOriginal->size(),Qt::IgnoreAspectRatio);
     ui->imageOriginal->setPixmap(img);
}


void FaceDetection2::on_applyBtn_clicked()
{
    Mat frms = facePredictionController->img->getOriginalImg();
    liveController->predictPerson2(frms);
    imgDetected = BasicHelpers::convertMatToPixmap(frms);
    imgDetected = imgDetected.scaled(ui->imageDetected->size(),Qt::IgnoreAspectRatio);
     ui->imageDetected->setPixmap(imgDetected);
}


void FaceDetection2::on_resetFilterBtn_clicked()
{
   ui->imageDetected->setPixmap(img);
}

