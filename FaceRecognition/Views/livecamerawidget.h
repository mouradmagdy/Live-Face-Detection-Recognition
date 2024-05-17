#ifndef LIVECAMERAWIDGET_H
#define LIVECAMERAWIDGET_H

#include <opencv2/videoio.hpp>
#include "Controller/livecameracontroller.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QMessageBox>
#include <QWidget>

namespace Ui {
class LiveCameraWidget;
}

class LiveCameraWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LiveCameraWidget(QWidget *parent = nullptr);
    ~LiveCameraWidget();

private slots:

    void on_cameraBtn_clicked();

private:
    Ui::LiveCameraWidget *ui;

    bool startRecording = false;
    QGraphicsPixmapItem pixmap;
    cv::VideoCapture video;
    QTimer timer;
    LiveCameraController* liveController;

};

#endif // LIVECAMERAWIDGET_H
