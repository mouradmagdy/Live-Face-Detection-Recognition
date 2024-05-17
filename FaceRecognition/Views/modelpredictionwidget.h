#ifndef MODELPREDICTIONWIDGET_H
#define MODELPREDICTIONWIDGET_H

#include <QWidget>
#include "Controller/modelpredictioncontroller.h"

namespace Ui {
class ModelPredictionWidget;
}

class ModelPredictionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModelPredictionWidget(QWidget *parent = nullptr);
    ~ModelPredictionWidget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


private:
    Ui::ModelPredictionWidget *ui;
    QPixmap img;
    ModelPredictionController *modelPredictionController;
};

#endif // MODELPREDICTIONWIDGET_H
