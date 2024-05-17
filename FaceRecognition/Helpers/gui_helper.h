#ifndef GUI_HELPER_H
#define GUI_HELPER_H

#include "qpushbutton.h"
class GUI_HELPER
{
public:
    GUI_HELPER();
    static void changeBtnsStyle(QList<QPushButton*> list,QString style);
    static void changeBtnStyle(QPushButton* btn,QString style);
};

#endif // GUI_HELPER_H
