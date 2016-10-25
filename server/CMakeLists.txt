###############################################################################
# @file CMakeLists.txt
# @project server for the simulations of processes
# @brief  CMakeLists.txt principal for  the simulations of processes
# @details this doc contains all requirements needs for the execution
# @author Ronald Sulbaran and Julio Jaimes R, ronaldanto03@gmail.com, carlosjuliojr@hotmail.com
# @date 15/10/2016
###############################################################################

cmake_minimum_required(VERSION 3.5)

#project (server)

add_definitions(-std=c++11)


set(libSrc
   CMakeLists.txt
        include/basealgorithm.h
        include/BaseProcess.h
        include/CompleteProcess.h
        include/distributions.h
        include/finaltimes.h
        include/processGenerator.h
        include/simulator.h
        include/DataSocket1.h
        include/eventData.h
        include/fcfs.h
        include/fifoQueue.h
        include/finalsocket.h
        include/iqueue.h
        include/multSimData.h
        include/node.h
        include/priorityQueue.h
        include/psjf.h
        include/rr.h
        include/serverSock.h
        include/simulator.h
        include/sjf.h
        src/basealgorithm.cpp
        src/BaseProcess.cpp
        src/CompleteProcess.cpp
        src/distributions.cpp
        src/finaltimes.cpp
        src/processGenerator.cpp
        src/simulator.cpp
    #    src/test.cpp
   )

#add_executable(${ExecutableName} ${libSrc} )

#remarks: pthread exists on linux only
#target_link_libraries(${ExecutableName} pthread)

#This file contains all header files
include_directories(include)
add_library(ser STATIC ${libSrc})

