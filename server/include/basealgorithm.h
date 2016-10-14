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
#include <cfloat>

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

      IQueue<CompleteProcess>* blockingQueue;

      IQueue<CompleteProcess>* readyQueue;

      size_t numOfProcesses;

      const BaseProcess* baseProcesses;

      struct EventData eventData;

      int nSocket;

      bool connected;
      /********************************************************************/

      unsigned i;

      /**
       * It indicates which is the next process that arrives
      */
      size_t processIndex;

      /**
       * time simulation
      */
      double simulationTime;
      /**
       * @brief eventToProcessTime time process to be run
       */

      double eventToProcessTime;

      /**
       * @brief percentage usage percentage
       */

      double percentage;

      /**
       * @brief averageWaitingTime average waiting time
       */
      double averageWaitingTime;

      /**
       * @brief averageUsageTime average using time
       */

      double averageUsageTime;//tiempo de uso promedio

      /**
       * @brief eventToProcess
       * Se usa para saber cual evento es el que debe procesarse primero
       * 1 means that a new process arrives
       * 2 passes a process queue ready to cpu
       * 3 Go from CPU locked
       * 4 passes blocked ready
       * 5 Process ends cpu
       */
      int eventToProcess;

      /**
       * @brief cpuP It represents the process that is currently running
       */
      CompleteProcess cpuP;

      /**
       * @brief averageIoTime Average blocking time (IO)
       */
      double averageIoTime;

      /**
       * @brief inIO number of times arriving blocked processes
       */
      int inIO=0;

      /**
       * @brief inCpu number of times processes run
       */
      int inCpu=0;

      /**
       * @brief turnAround
       */
      double turnAround=0.0;
      /***********************************************************************/

   public:

      BaseAlgorithm();

      BaseAlgorithm(const  BaseProcess * _baseProcesses,
                    const int _numOfProcesses,
                    const int _nSocket
                    );

      void init();

      /**
       * Writes in the Socket the events process.
       * @param[in] time. It is the time when the event occurs
       * @param[in] event Type of Event
       * @param[in] p process associated with the event occurred
       */
      void writeEventInfo(const double time,const int event,const CompleteProcess p,SharedSimulation & _ss);

      ~BaseAlgorithm()
      {
      }

};

#endif // BASEALGORITHM_H
