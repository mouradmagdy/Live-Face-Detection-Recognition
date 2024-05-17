#include "gui_helper.h"

GUI_HELPER::GUI_HELPER() {}

void GUI_HELPER::changeBtnsStyle(QList<QPushButton *> list, QString style)
{
    foreach (QPushButton *btn, list) {
        btn->setStyleSheet(style);
    }
}

void GUI_HELPER::changeBtnStyle(QPushButton *btn, QString style)
{
    btn->setStyleSheet(style);
}
