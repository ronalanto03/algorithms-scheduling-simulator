/**
 * @file processGenerator.h
 * @brief Declaracion de la clase ProcessGenerator.
 * @author Ronald Sulbaran. ronalanto03@gmail.com.
 * @date 13-08-2013
 */

#ifndef PROCESS_GENERATOR_H
#define PROCESS_GENERATOR_H

#include"BaseProcess.h"
#include"distributions.h"

/**
 * @class ProcessGenerator
 * @brief Clase que genera los procesos base para iniciar la simulacion.
 */
class ProcessGenerator
{

   private:

      /**
       * Puntero al que s ele dara memoria para almacenar los procesos
       */
      BaseProcess * baseProcesses;

      int nProcs;/**< Numero de procesos*/


   public:

      /**
       * @param _n,numero de procesos a generar
       */
      ProcessGenerator( int _n );

      /**
       * @param Libera la memoria ocupada por los procesos.
       */
      ~ProcessGenerator();

      ///genera los tiempos de llegada y los tiempos que necesita cada proceso para ejecutarse

      /**
       * @brief Genera los procesos necesarios para la simulacion y los almacena en baseProcesses.
       * @param dArrTime,distribucion asociada a los tiempos de llegada.
       * @param dDurationTime,distribucion asociada a los tiempos de duracion.
       */
      void generateTimes(Distribution* dArrTime, Distribution* dDurationTime);

      BaseProcess * getBaseProcess()
      {
         return baseProcesses;
      }

};

#endif
