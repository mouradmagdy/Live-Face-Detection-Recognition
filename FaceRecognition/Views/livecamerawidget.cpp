#include "livecamerawidget.h"
#include "ui_livecamerawidget.h"

LiveCameraWidget::LiveCameraWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LiveCameraWidget)
{
    ui->setupUi(this);
    liveController = new LiveCameraController();
    ui->liveView->setScene(new QGraphicsScene(this));
}

LiveCameraWidget::~LiveCameraWidget()
{
    delete ui;
}

void LiveCameraWidget::on_cameraBtn_clicked()
{
    if(video.isOpened()){
        ui->cameraBtn->setText("Open");
        video.release();
        ui->liveView->scene()->removeItem(&pixmap);
        ui->liveView->scene()->update();
        return;
    }
    if(!video.open(0))
    {
        QMessageBox::critical(this,
                              "Camera Error",
                              "Make sure you entered a correct camera index,"
                              "<br>or that the camera is not being accessed by another program!");
        return;
    }
    ui->liveView->scene()->addItem(&pixmap);

    ui->cameraBtn->setText("Close");



    cv::Mat frame;
    while(video.isOpened())
    {

        video >> frame;

        if(!frame.empty())
        {
            liveController->predictPerson(frame);

            QImage qimg(frame.data,
                        frame.cols,
                        frame.rows,
                        frame.step,
                        QImage::Format_RGB888);

            pixmap.setPixmap( QPixmap::fromImage(qimg.rgbSwapped()) );
            ui->liveView->fitInView(&pixmap, Qt::KeepAspectRatio);

            timer.setInterval(10000);
        }
        qApp->processEvents();
    }
}

