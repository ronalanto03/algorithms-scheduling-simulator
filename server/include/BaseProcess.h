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
      /**
       * Id of the process
       */
      int pid;

      /**
       * Process Arrival Time
       */
      double arrTime;

      /**
       * Total duration of the process
       */
      double durationTime;


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
       * Assigns the value of the process ID
       * @param new_var the new value of pid
       */
      inline void setPid ( int new_var )
      {
         pid = new_var;
      }


      /**
       * Gets the process id
       * @return the value of pid
       */
      inline int getPid ( ) const
      {
         return pid;
      }

      /**
       * Assigns the value of the arrival time of the process
       * @param new_var the new value of arrTime
       */
      inline void setArrTime ( double new_var )
      {
         arrTime = new_var;
      }

      /**
       * Gets the value of the arrival time of the process
       * @return The value of arrTime
       */
      inline double getArrTime ( ) const
      {
         return arrTime;
      }

      /**
       * Assign the value of the duration total process
       * @param new_var the new value of durationTime
       */
      inline void setDurationTime ( double new_var )		 {
         durationTime = new_var;
      }

      /**
       * Gets the value of total duration of the process
       * @return The value of durationTime
       */
      inline double getDurationTime ( ) const
      {
         return durationTime;
      }

};

#endif // BASEPROCESS_H
