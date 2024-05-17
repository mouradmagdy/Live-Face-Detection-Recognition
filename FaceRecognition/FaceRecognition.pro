QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
#CONFIG += link_pkgconfig
#PKGCONFIG += opencv4

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/facepredictioncontroller.cpp \
    Controller/livecameracontroller.cpp \
    Controller/modelpredictioncontroller.cpp \
    Helpers/fileshelper.cpp \
    Helpers/gui_helper.cpp \
    Models/facedetection.cpp \
    Models/fetcher.cpp \
    Models/image.cpp \
    Models/pca.cpp \
    Models/readfile.cpp \
    Views/facedetection2.cpp \
    Views/faceprediction.cpp \
    Views/livecamerawidget.cpp \
    Helpers/basichelpers.cpp \
    Views/modelpredictionwidget.cpp \
    main.cpp \
    Views/mainwindow.cpp \
    config.cpp \

HEADERS += \
    Controller/facepredictioncontroller.h \
    Controller/livecameracontroller.h \
    Controller/modelpredictioncontroller.h \
    Helpers/fileshelper.h \
    Helpers/gui_helper.h \
    Models/facedetection.h \
    Models/fetcher.h \
    Models/image.h \
    Models/pca.h \
    Models/readfile.h \
    Views/facedetection2.h \
    Views/faceprediction.h \
    Views/livecamerawidget.h \
    Views/mainwindow.h \
    Helpers/basichelpers.h \
    Views/modelpredictionwidget.h \
    config.h \

FORMS += \
    Views/facedetection2.ui \
    Views/faceprediction.ui \
    Views/livecamerawidget.ui \
    Views/mainwindow.ui \
    Views/modelpredictionwidget.ui





  INCLUDEPATH += D:\tools\opencv\release\install\include

  LIBS += -LD:\tools\opencv\release\lib\
      -lopencv_calib3d490                 \
      -lopencv_core490                    \
      -lopencv_features2d490              \
      -lopencv_flann490                   \
      -lopencv_highgui490                 \
      -lopencv_imgproc490                 \
      -lopencv_imgcodecs490               \
      -lopencv_photo490                   \
      -lopencv_stitching490               \
      -lopencv_ts490                      \
      -lopencv_video490                   \
      -lopencv_videoio490                 \
      -lopencv_objdetect490               \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
