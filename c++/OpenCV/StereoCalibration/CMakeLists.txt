cmake_minimum_required(VERSION 2.6)

PROJECT(StereoCalibration)

FIND_PACKAGE(OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OPENCV_INCLUDE_DIR} )

ADD_EXECUTABLE(StereoCalibration StereoCalibration.cxx)
TARGET_LINK_LIBRARIES(StereoCalibration opencv_core opencv_highgui
opencv_flann opencv_imgproc opencv_highgui opencv_ml opencv_video opencv_objdetect
          opencv_features2d opencv_calib3d opencv_legacy opencv_contrib
)