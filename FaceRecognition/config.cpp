#include "config.h"




QString inactiveBtnStyle ="\
    QPushButton {\
        background-color: #316669;\
        border: none;\
        border-radius: 6px;\
        color: #EEEEEE;\
        font-size: 14px;\
        font-weight: 500;\
        line-height: 20px;\
        list-style: none;\
        padding: 4px 12px;\
        height: 40px;\
}\
    QPushButton:hover {\
        background-color: rgba(118, 171, 174, 203);\
        text-decoration: none;\
}\
    QPushButton:focus {\
        outline: 1px transparent;\
}";

QString activeBtnStyle = "background-color: #76ABAE;";
int labelsSize;
int labelSize2;
_PCA pcaInstance = _PCA();
CascadeClassifier cascade;
double mi;
_PCA pcaInstance2 = _PCA();
