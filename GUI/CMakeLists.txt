###############################################################################
# @file CMakeLists.txt
# @project server for the simulations of processes
# @brief  CMakeLists.txt principal for  the simulations of processes
# @details this doc contains all requirements needs for the execution
# @author Ronald Sulbaran and Julio Jaimes R, ronaldanto03@gmail.com, carlosjuliojr@hotmail.com
# @date 15/10/2016
###############################################################################
cmake_minimum_required(VERSION 3.5)

project (simulatorgui)
set (PROJECT simulatorgui)


find_package(Qt5Widgets PATHS "/home/julio/Qt/5.6/gcc_64/lib/cmake" REQUIRED)
add_definitions(-std=c++11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
qt5_add_resources(IMAGES_RES images.qrc)

#qt5_wrap_ui(ABOUT_DIALOG_UI_H aboutdialog.ui)
#qt5_wrap_cpp(ABOUT_DIALOG_UI_MOC aboutdialog.h)

#qt5_wrap_ui(DATA_WINDOW_UI_H datawindow.ui)
#qt5_wrap_cpp(DATA_WINDOW_UI_MOC datawindow.h)


#qt5_wrap_ui(GRAPH_DIALOG_UI_H graphdialog.ui)
#qt5_wrap_cpp(GRAPH_DIALOG_UI_MOC graphdialog.h)

#qt5_wrap_ui(GRAPH_WINDOW_UI_H graphswindow.ui)
#qt5_wrap_cpp(GRAPH_WINDOW_UI_MOC graphswindow.h)

#qt5_wrap_ui(MAIN_WINDOW_UI_H mainwindow.ui)
#qt5_wrap_cpp(MAIN_WINDOW_UI_MOC mainwindow.h)

#qt5_wrap_ui(PAINT_WINDOW_UI_H paintwindow.ui)
#qt5_wrap_cpp(PAINT_WINDOW_UI_MOC paintwindow.h)

#qt5_wrap_ui(PROCESS_PROPERTIES_DIALOG_UI_H processpropertiesdialog.ui)
#qt5_wrap_cpp(PROCESS_PROPERTIES_DIALOG_UI_MOC processpropertiesdialog.h)


#qt5_wrap_ui(QUEUE_DIALOG_UI_H queuedialog.ui)
#qt5_wrap_cpp(QUEUE_DIALOG_UI_MOC queuedialog.h)

#qt5_wrap_ui(SETTINGS_DIALOG_UI_H settingsdialog.ui)
#qt5_wrap_cpp(SETTINGS_DIALOG_UI_MOC settingsdialog.h)

set(ExecutableName Gui)
#set(GuilibSrc
#        CMakeLists.txt

#aboutdialog.cpp
#aboutdialog.h

#DataSocket1.h

#datawindow.cpp
#datawindow.h

#eventData.h

#graphdialog.cpp
#graphdialog.h

#graphswindow.cpp
#graphswindow.h

#mainwindow.cpp
#mainwindow.h

#multSimData.h

#mylabel.cpp
#mylabel.h

#paintwindow.cpp
#paintwindow.h

#processpropertiesdialog.cpp
#processpropertiesdialog.h
#qrc_images.cpp

#queuedialog.cpp
#queuedialog.h

#settingsdialog.cpp
#settingsdialog.h

#threadsocket.cpp
#threadsocket.h

#threadsocketvs.cpp
#threadsocketvs.h

#uiprocess.h

#   )

file(GLOB_RECURSE COMMON_SOURCE  "*.h" "*.cpp")
#message(0)
include_directories(${PROJECT_BINARY_DIR})
include_directories(.)
add_library(${PROJECT} STATIC ${COMMON_SOURCE} ${IMAGES_RES})
qt5_use_modules(${PROJECT} Widgets)

