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
 * class CompleteProcess
 * Representa a un proceso con todos los atributos necesarios para la simulacion.
 */

class CompleteProcess : public BaseProcess
{
   public:

      /**
       * Constructor por defecto
       */
      CompleteProcess ( );


      /**
       * Constructor por copia
       */
      CompleteProcess (const BaseProcess &);


      /**
       * Destructor
       */
      ~CompleteProcess ( );


   private:

      double cpuBurstTime;/**< Tiempo de rafaga*/

      double remainingTime;/**<  Tiempo restante(el q le falta al proceso para terminar su ejecucion)*/

      double blockingTime;/**< Tiempo de bloqueo del proceso*/

      double waitingTime;/**< Tiempo de espera del proceso*/

      double averageUsageTime;/**< Tiempo de uso promedio del proceso*/

      int nRunsCPU;/**< numero de veces que sube el proceso a cpu*/

      double quantum;/**< Quantum de tiempo asigando al proceso(usado para eñ algoritmo de RR)*/

      int nB;/**< numero de veces que baja el proceso a bloqueado*/

      double averageIoTime;/**< Tiempo de blockeo promedio del proceso*/


   public:

      /**
       * Asigna el valor del tiempo de rafaga
       * @param new_var el nuevo valor de cpuBurstTime
       */
      inline void setCpuBurstTime ( double new_var )
      {
         cpuBurstTime = new_var;
      }

      /**
         * Obtiene el valor del tiempo de rafaga
         * @return el valor de cpuBurstTime
       */
      double getCpuBurstTime ( ) const
      {
         return cpuBurstTime;
      }

      /**
       * Asigna el valor del tiempo restante(el q le falta al proceso para terminar su ejecucion)
       * @param new_var el nuevo valor de remainingTime
       */
      void setRemainingTime ( double new_var )
      {
         remainingTime = new_var;
      }

      /**
       * Obtiene el valor de tiempo restante(el q le falta al proceso para terminar su ejecucion)
       * @return el valor de remainingTime
       */
      double getRemainingTime ( ) const
      {
         return remainingTime;
      }

      /**
       * Asigna el valor del tiempo de bloqueo del proceso.
       * @param new_var el nuevo valor de blockingTime
       */
      void setBlockingTime ( double new_var )
      {
         blockingTime = new_var;
      }

      /**
       * Obtiene el valor del tiempo de bloqueo del proceso.
       * @return el valor de blockingTime
       */
      double getBlockingTime ( ) const
      {
         return blockingTime;
      }

      /**
       * Asigna el valor del tiempo de espera del proceso.
       * @param new_var el nuevo valor de waitingTime
       */
      void setWaitingTime ( double new_var )
      {
         waitingTime = new_var;
      }

      /**
       * Obtiene el valor del tiempo de bloqueo del proceso.
       * @return the value of waitingTime
       */
      double getWaitingTime ( ) const
      {
         return waitingTime;
      }

      /**
       * Asigna el valor de numero de veces que entra al cpu.
       * @param new_var el nuevo valor de nRunsCPU
       */
      void setNRunsCPU( int new_var )
      {
         nRunsCPU = new_var;
      }

      /**
       * Obtiene el valor de numero de veces que entra al cpu.
       * @return el valor de nRunsCPU.
       */
      int getNRunsCPU( ) const
      {
         return nRunsCPU;
      }

      /**
       * Asigna le valor del tiempo promedio que el proceso usa el cpu.
       * @param new_var el nuevo valor de averageUsageTime.
       */
      void setAverageUsageTime( double new_var )
      {
         averageUsageTime = new_var;
      }

      /**
       * Obtiene el valor del tiempo promedio que el proceso usa el cpu.
       * @return el valor de averageUsageTime.
       */
      double getAverageUsageTime( ) const
      {
         return averageUsageTime;
      }

      /**
       * Asigna le valor del quantum del proceso.
       * @param new_var el nuevo valor de quantum.
       */
      void setQuantum( double new_var )
      {
         quantum = new_var;
      }

      /**
       * Obtiene el valor del quantum del proceso.
       * @return el valor de quantum.
       */
      double getQuantum( ) const
      {
         return quantum;
      }

      /**
       * Asigna el valor de numero de veces que entra a bloqueado.
       * @param new_var el nuevo valor de nT
       */
      void setNB( int new_var )
      {
         nB = new_var;
      }

      /**
       * Obtiene el valor de numero de veces que entra a bloqueado.
       * @return el valor de nB.
       */
      int getNB( ) const
      {
         return nB;
      }

      /**
       * Asigna le valor del tiempo promedio que el proceso esta bloqueado.
       * @param new_var el nuevo valor de averageIoTime.
       */
      void setAverageIoTime( double new_var )
      {
         averageIoTime = new_var;
      }

      /**
       * Obtiene el valor del tiempo promedio que el proceso esta bloqueado.
       * @return el valor de averageIoTime.
       */
      double getAverageIoTime( ) const
      {
         return averageIoTime;
      }

      /**
       * @brief Asigna un proceso a otro copiando cada uno de sus parámetros.
       */
      CompleteProcess & operator =(CompleteProcess p);

};

#endif // COMPLETEPROCESS_H
