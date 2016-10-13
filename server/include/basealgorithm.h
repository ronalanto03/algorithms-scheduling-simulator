/**
 * @file basealgorithm.h
 * @brief Declaración de la clase FCFS.
 * @author Julio Jaimes. @gmail.com.
 * @date 06-10-2016
 */

#ifndef BASEALGORITHM_H
#define BASEALGORITHM_H

#include <iqueue.h>
#include <CompleteProcess.h>
#include <eventData.h>
#include <finalsocket.h>
#include <priorityQueue.h>
#include <fifoQueue.h>
#include <unistd.h>
#include <fstream>

class BaseAlgorithm
{

   protected:

      /**
       * @struct CmpLessB
       * @brief Structs for to do the comparision of less in the blocking's queue.
       */
      struct CmpLessB
      {
            bool operator () (CompleteProcess& process1 , CompleteProcess& process2) const
            {
               return process1.getBlockingTime() < process2.getBlockingTime();
            }
      };


      /**
       * @struct CmpGreaterOrEqualB
       * @brief Structs for to do the comparision of major in the blocking's queue.
       */
      struct CmpGreaterOrEqualB
      {
            bool operator () (CompleteProcess& process1,  CompleteProcess& process2) const
            {
               return process1.getBlockingTime() >= process2.getBlockingTime();
            }
      };


      /**
       * @struct CmpLessR
       * @brief Structs for to do the comparision of less in the ready's queue.
       */
      struct CmpLessR
      {
            bool operator () (CompleteProcess& process1 , CompleteProcess& process2) const
            {
               return process1.getCpuBurstTime() < process2.getCpuBurstTime();
            }
      };


      /**
       * @struct CmpGreaterOrEqualR
       * @brief Structs for to do the comparision of major in the ready's queue.
       */
      struct CmpGreaterOrEqualR
      {
            bool operator () (CompleteProcess & process1,  CompleteProcess & process2) const
            {
               return process1.getCpuBurstTime() >= process2.getCpuBurstTime();
            }
      };

      IQueue<CompleteProcess>* priorityQueue;

      IQueue<CompleteProcess>* readyQueue1;

      size_t numOfProcesses;

      const BaseProcess* baseProcesses;//Not sure about the const keyword here

      struct EventData eventData;

      int nSocket;

      bool connected;


   public:

      BaseAlgorithm();

      BaseAlgorithm(const  BaseProcess * _baseProcesses,
                    const int _numOfProcesses,
                    const int _nSocket
                    );

      /**
       * Writes in the Socket the events process.
       * @param[in] time. It is the time when the event occurs
       * @param[in] event Type of Event
       * @param[in] p process associated with the event occurred
       */
      void writeEventInfo(const double time,const int event,const CompleteProcess p,SharedSimulation & _ss);


};

#endif // BASEALGORITHM_H
