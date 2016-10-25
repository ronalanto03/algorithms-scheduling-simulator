###############################################################################
# @file CMakeLists.txt
# @project server for the simulations of processes
# @brief  CMakeLists.txt principal for  the simulations of processes
# @details this doc contains all requirements needs for the execution
# @author Ronald Sulbaran and Julio Jaimes R, ronaldanto03@gmail.com, carlosjuliojr@hotmail.com
# @date 15/10/2016
###############################################################################

cmake_minimum_required(VERSION 3.5)

project (server_gui)


 # Widgets finds its own dependencies (QtGui and QtCore).
find_package(Qt5Widgets PATHS "/home/julio/Qt/5.6/gcc_64/lib/cmake" REQUIRED)
set (PROJECT server_gui)

add_definitions(-std=c++11 -g)

add_subdirectory(GUI)
add_subdirectory(server)

include_directories(GUI
                    server/include
                    )


add_executable(${PROJECT} main.cpp )
qt5_use_modules(${PROJECT} Widgets)
target_link_libraries(${PROJECT} ser simulatorgui pthread)



