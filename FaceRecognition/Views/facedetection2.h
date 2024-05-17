#ifndef FACEDETECTION2_H
#define FACEDETECTION2_H

#include <QWidget>
#include "Controller/livecameracontroller.h"
#include "Controller/facepredictioncontroller.h"

namespace Ui {
class FaceDetection2;
}

class FaceDetection2 : public QWidget
{
    Q_OBJECT

public:
    explicit FaceDetection2(QWidget *parent = nullptr);
    ~FaceDetection2();

private slots:
    void on_uploadImgBtn_clicked();

    void on_applyBtn_clicked();

    void on_resetFilterBtn_clicked();

private:
    Ui::FaceDetection2 *ui;
    QPixmap img,imgDetected;
     LiveCameraController* liveController;
     FacePredictionController *facePredictionController;
};

#endif // FACEDETECTION2_H
