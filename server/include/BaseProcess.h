/**
 * @file BaseProcess.h
 * @brief Declaracion de la clase BaseProcess.
 * @author Ronald Sulbaran. ronalanto03@gmail.com.
 * @date 25-05-2013
 */


#ifndef BASEPROCESS_H
#define BASEPROCESS_H


/**
 * @class BaseProcess
 * @brief Para almacenar un proceso cuando es generado.
 */

class BaseProcess
{
   protected:

      int pid;/**< Id del proceso*/

      double arrTime;/**< Tiempo de llegada del proceso */

      double durationTime;/**< Tiempo de duracion total del proceso */


   public:

      /**
       * Constructor
       */
      BaseProcess ( );

      /**
       * Destructor
       */
      ~BaseProcess ( );



      /**
       * Asigna el valor del Id del proceso
       * @param new_var el nuevo valor de pid
       */
      inline void setPid ( int new_var )
      {
         pid = new_var;
      }


      /**
       * Obtiene el valor de id del proceso
       * @return el valor de pid
       */
      inline int getPid ( ) const
      {
         return pid;
      }

      /**
         * Asigna el valor del tiempo de llegada del proceso
       * @param new_var el nuevo valor de arrTime
       */
      inline void setArrTime ( double new_var )
      {
         arrTime = new_var;
      }

      /**
         * Obtiene el valor del tiempo de llegada del proceso
         * @return el valor de arrTime
       */
      inline double getArrTime ( ) const
      {
         return arrTime;
      }

      /**
         * Asigna el valor del tiempo de duracion total del proceso
       * @param new_var el nuevo valor de durationTime
       */
      inline void setDurationTime ( double new_var )		 {
         durationTime = new_var;
      }

      /**
         * Obtiene el valor de tiempo de duracion total del proceso
         * @return el valor de durationTime
       */
      inline double getDurationTime ( ) const
      {
         return durationTime;
      }

};

#endif // BASEPROCESS_H
