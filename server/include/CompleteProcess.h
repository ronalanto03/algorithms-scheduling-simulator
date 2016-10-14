/**
 * @file CompleteProcess.h
 * @brief Declaración de la clase CompleteProcess.
 * @author Ronald Sulbaran. ronalanto03@gmail.com.
 * @date 01-07-2013
 */

#ifndef COMPLETEPROCESS_H
#define COMPLETEPROCESS_H
#include "BaseProcess.h"

/**
 * Class Complete Process
 *  represents a process with all the attributes required for the simulation.
 */

class CompleteProcess : public BaseProcess
{
   public:


      /**
       * @brief CompleteProcess
       * Default constructor
       */
      CompleteProcess ( );

      /**
       * @brief CompleteProcess
       * Copy constructor
       */
      CompleteProcess (const BaseProcess &);

      /**
       * destroyer
       */
      ~CompleteProcess ( );


   private:

      /**
       * @brief cpuBurstTime
       * Time rafaga
       */
      double cpuBurstTime;

      /**
       * @brief remainingTime
       * Time left (the q missing from the process to terminate its execution)
       */
      double remainingTime;

      /**
       * @brief blockingTime
       * Lock time process *
       */
      double blockingTime;

      /**
       * @brief waitingTime
       * Time of waiting of the process
       */
      double waitingTime;

      /**
       * @brief averageUsageTime
       * Average usage time of the process
       */
      double averageUsageTime;

      /**
       * @brief nRunsCPU
       * number of times up the process cpu
       */
      int nRunsCPU;

      /**
       * @brief quantum
       * Quantum allotted time to process (used for algorithm RR)
       */
      double quantum;

      /**
       * @brief nB
       * number of times down the process blocked
       */
      int nB;

      /**
       * @brief averageIoTime
       */
      double averageIoTime;/**< Tiempo de blockeo promedio del proceso*/


   public:

      /**
       * Assign the time value rafaga
       * @param new_var the new value of cpuBurstTime
       */
      inline void setCpuBurstTime ( double new_var )
      {
         cpuBurstTime = new_var;
      }

      /**
       * Gets the time value rafaga
       * @return The value of cpuBurstTime
       */
      double getCpuBurstTime ( ) const
      {
         return cpuBurstTime;
      }

      /**
       * Assign the value of the remaining time (q lacks the process to terminate its execution)
       * @param new_var the new value of remainingTime
       */
      void setRemainingTime ( double new_var )
      {
         remainingTime = new_var;
      }

      /**
       * Gets the value of remaining time (q lacks the process to terminate its execution)
       * @return the value of remainingTime
       */
      double getRemainingTime ( ) const
      {
         return remainingTime;
      }

      /**
       * Assign the value of time blocking the process.
       * @param Nnew_var the new value of blockingTime
       */
      void setBlockingTime ( double new_var )
      {
         blockingTime = new_var;
      }

      /**
       * Gets the time value of blocking the process.
       * @return The value of blockingTime
       */
      double getBlockingTime ( ) const
      {
         return blockingTime;
      }

      /**
       * Assign the value of the timeout process.
       * @param New_var the new value of WaitingTime
       */
      void setWaitingTime ( double new_var )
      {
         waitingTime = new_var;
      }

      /**
       * Gets the time value of blocking the process.
       * @return The value of WaitingTime
       */
      double getWaitingTime ( ) const
      {
         return waitingTime;
      }

      /**
       * Assign the value of number of times entering the cpu.
       *@param new_var the new value of nRunsCPU
       */
      void setNRunsCPU( int new_var )
      {
         nRunsCPU = new_var;
      }

      /**
       * Gets the value of number of times entering the cpu.
       * @return The value of nRunsCPU.
       */
      int getNRunsCPU( ) const
      {
         return nRunsCPU;
      }

      /**
       * Assign the value of the average time that the process uses the cpu.
       * @param new_var the new value of averageUsageTime.
       */
      void setAverageUsageTime( double new_var )
      {
         averageUsageTime = new_var;
      }

      /**
       * Gets the value of the average time that the process uses the cpu.
       * @return The value of averageUsageTime.
       */
      double getAverageUsageTime( ) const
      {
         return averageUsageTime;
      }

      /**
       * Assign the value of the quantum of the process.
       * @param New_var the new quantum value.
       */
      void setQuantum( double new_var )
      {
         quantum = new_var;
      }

      /**
       * Gets the value of the quantum of the process.
       * @return The value of quantum.
       */
      double getQuantum( ) const
      {
         return quantum;
      }

      /**
       * Assign the value of number of times entering locked.
       * @param new_var the new value of nT
       */
      void setNB( int new_var )
      {
         nB = new_var;
      }

      /**
       * Gets the value of number of times entering locked.
       * @return The value of nB.
       */
      int getNB( ) const
      {
         return nB;
      }

      /**
       * Assign the value of the average time the process is blocked.
       * @param New_var the new value of averageIoTime.
       */
      void setAverageIoTime( double new_var )
      {
         averageIoTime = new_var;
      }

      /**
       * Gets the value of the average time that the process is blocked.
       * @return The value of averageIoTime.
       */
      double getAverageIoTime( ) const
      {
         return averageIoTime;
      }

      /**
       * @brief Assigns one process to another by copying each of its parameters.
       */
      CompleteProcess & operator =(CompleteProcess p);

};

#endif // COMPLETEPROCESS_H
