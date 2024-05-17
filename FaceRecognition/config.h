#ifndef CONFIG_H
#define CONFIG_H

#include<QString>

#include "Models/pca.h"
#include "opencv2/objdetect.hpp"
extern QString inactiveBtnStyle;
extern QString activeBtnStyle;
extern int labelsSize;
extern int labelSize2;


extern _PCA pcaInstance;
extern CascadeClassifier cascade;
extern double mi;
extern _PCA pcaInstance2;

#endif // CONFIG_H
