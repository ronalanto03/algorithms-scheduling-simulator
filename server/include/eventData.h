/**
 * @file eventData.h
 * @brief Declaracion de la clase EventData
 * @author Ronald Sulbaran. ronalanto03@gmail.com.
 */

#ifndef EVENTDATA
#define EVENTDATA



/**
 * @struct EventData
 * @brief Almacenar los datos correspondientes a un evento para enviar a la interfaz(programa hecho en Qt)
 */

struct EventData
{

    //para las variables q se usan para generar los tiempos

    int event;/**< tipo de evento */

    int pid;/**< id del proceso que genero el evento */


    double time;/**< tiempo en el que ocurre el evento*///sDUsedTime

    double arrTime;/**< tiempo de llegada del proceso que genero el evento*/ //sDWaitingTime

    double durationTime;/**< duracion del proceso que genero el evento*///maxUsedTime

    double remainingTime;/**< tiempo restante*///minUsedTime

    double waitingTime;/**< tiempo de espera*/

    double cpuBurstTime;/**< tiempo de rafaga*///maxWaitingTime

    double blockingTime;/**< tiempo de bloqueo*///minWaitingTime

    double quantum;/**< Quantum para en RR*/

    double usedTime;/**< Tiempo de uso*/

    int nT;/**< Numero de veces que el proceso asociado al evento se ha montado en cpu*/

    int nB;/**< Numero de veces que el proceso asociado al evento ha bajado a bloqueado*/

    double allBlockingTime;/**< Tiempo que el proceso ha estado bloqueado desde que inició la simulación*/
};


#endif
