/**
 * @file simulator.h
 * @brief Declaración de la clase simulator.
 * @author Ronald Sulbaran. ronalanto03@gmail.com.
 * @date 01-06-2013
 */


#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h> //for threading , link with lpthread


#include <eventData.h>
#include <processGenerator.h>
#include  <finaltimes.h>


#include <fcfs.h>
#include <sjf.h>
#include <psjf.h>
#include <rr.h>


//parametros que se le pasa al thread que maneja una simulacion multiple
struct ThreapParamM
{
      int numOfSimulations;//numero de simulaciones
      int nSocket;//socket asociado al thread que maneja la simulacion multiple
};



static SharedSimulation sS;//parametros usasdos por los threads q ejeuctan distintos algoritmos

static int __ss;


//funcion que ejecutara el hilo
void * connection_handler(void *socket_desc);



/**
 * @class Simulator
 * @brief Clase que hace toda la simulacion,
 */
class Simulator
{

   private:

      int t, n, r, s;

      socklen_t tamNombreRemoto;

      struct sockaddr_in nombreLocal;

      struct sockaddr_in nombreRemoto;


   public:

      enum SIMULATION_TYPE
      {
         ST_FCFS = 1,
         ST_SJF = 2,
         ST_PSJF = 3,
         ST_RR = 4
      };

      Simulator();

      void simulate(int _s);

      ~Simulator();

};



#endif // SIMULATOR_H
