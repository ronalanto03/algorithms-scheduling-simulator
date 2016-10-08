#ifndef BASEALGORITHM_H
#define BASEALGORITHM_H
#include<iqueue.h>
#include<CompleteProcess.h>
#include<eventData.h>
#include<finalsocket.h>
#include<priorityQueue.h>
#include<fifoQueue.h>
#include <unistd.h>
#include<fstream>

class BaseAlgorithm
{

protected:

    /**
     * @struct CmpLessB
     * @brief Structs for to do the comparision of less in the blocking's queue.
     */
    struct CmpLessB
    {
          bool operator () (CompleteProcess & __x , CompleteProcess & __y) const
          {
             return __x.getBlockingTime() < __y.getBlockingTime();
          }
    };


    /**
     * @struct CmpGreaterOrEqualB
     * @brief Structs for to do the comparision of major in the blocking's queue.
     */
    struct CmpGreaterOrEqualB
    {
          bool operator () (CompleteProcess & __x,  CompleteProcess & __y) const
          {
             return __x.getBlockingTime() >= __y.getBlockingTime();
          }
    };


    /**
     * @struct CmpLessR
     * @brief Structs for to do the comparision of less in the ready's queue.
     */
    struct CmpLessR
    {
          bool operator () (CompleteProcess & __x , CompleteProcess & __y) const
          {
             return __x.getCpuBurstTime() < __y.getCpuBurstTime();
          }
    };


    /**
     * @struct CmpGreaterOrEqualR
     * @brief Structs for to do the comparision of major in the ready's queue.
     */
    struct CmpGreaterOrEqualR
    {
          bool operator () (CompleteProcess & __x,  CompleteProcess & __y) const
          {
             return __x.getCpuBurstTime() >= __y.getCpuBurstTime();
          }
    };

    IQueue<CompleteProcess>* priorityQueue;

    IQueue<CompleteProcess>* readyQueue1;

    int numOfProcesses;

    BaseProcess* baseProcesses;

    struct EventData eventData;

    int nSocket;

    bool connected;


public:
    BaseAlgorithm();

    BaseAlgorithm(
                  const  BaseProcess * _baseProcesses,
                  const int _numOfProcesses,
                  const int _nSocket
                  );
    /**
     * Writes in the Socket the events process.
     * @param time. It is the time when the event occurs
     * @param event Type of Event
     * @param p process associated with the event occurred
     */

    void writeEventInfo(const double time,const int event,const CompleteProcess p,SharedSimulation & _ss);


};

#endif // BASEALGORITHM_H
