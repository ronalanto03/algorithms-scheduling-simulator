/** @file eventData.h
  * @brief Declaracion de la clase EventData
  * @authors: Cesar Vielma & Ronald Sulbaran
  */


/*@struct EventData
 *@brief Almacenar los datos correspondientes a un evento para enviar a la interfaz
 */
#ifndef EVENTDATA
#define EVENTDATA
#include <iostream>

struct EventData{

    //para las variables q se usan para generar los tiempos


    int event;/**< tipo de evento */

    int pid;/**< id del proceso que genero el evento */




    double time;/**< tiempo en el que ocurre el evento*/ //ds ut

    double arrTime;/**< tiempo de llegada del proceso que genero el evento*/ //ds wt

    double durationTime;/**< duracion del proceso que genero el evento*/ // max ut

    double remainingTime;/**< tiempo restante*/ //min ut

    double waitingTime;/**< tiempo de espera*/

    double cpuBurstTime;/**< tiempo de rafaga*/ //max wt

    double blockingTime;/**< tiempo de bloqueo*/ //min wt

    double quantum;/**< Quantum para en RR*/

    double usedTime;/**< tiempo de uso*/


    int nT;/**< Numero de veces que el proceso asociado al evento se ha montado en cpu*/

    int nB;/**< Numero de veces que el proceso asociado al evento ha bajado a bloqueado*/

    double allBlockingTime;



    void debugger(){

        std::cout<<"event: "<<event<<"\n";
        std::cout<<"Pid  : "<<pid<<"\n";
        std::cout<<"time: "<<time<<"\n";
        std::cout<<"arrTime: "<<arrTime<<"\n";
        std::cout<<"durationt: "<<durationTime<<"\n";
        std::cout<<"remainingt: "<<remainingTime<<"\n";
        std::cout<<"waitingTime: "<<waitingTime<<"\n";
        std::cout<<"cpuburstt: "<<cpuBurstTime<<"\n";
        std::cout<<"blockT: "<<blockingTime<<"\n";
        std::cout<<"usedT: "<<usedTime<<"\n";
        std::cout<<"quantum: "<<quantum<<"\n";

    }
};


#endif
