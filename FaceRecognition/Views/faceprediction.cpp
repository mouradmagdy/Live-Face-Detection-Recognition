#include "faceprediction.h"
#include "ui_faceprediction.h"

FacePrediction::FacePrediction(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FacePrediction)
{
    ui->setupUi(this);
    facePredictionController = new FacePredictionController();
}

FacePrediction::~FacePrediction()
{
    delete ui;
}

void FacePrediction::on_uploadBtn_clicked()
{
    img = facePredictionController->uploadImg();
    img = img.scaled(ui->inputLbl->size(),Qt::IgnoreAspectRatio);
    ui->inputLbl->setPixmap(img);
}


void FacePrediction::on_detectBtn_clicked()
{
   ui->outputLbl->setText( QString::fromStdString(facePredictionController->predictPerson()));
}

