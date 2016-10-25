#ifndef DATASOCKET1_H
#define DATASOCKET1_H


struct DistributionData{

    DistributionData(){
        t=2;
        left=1;
        right=50;
    }

    short t;/**< Tipo de distribucion.
                1: constante,2: uniforme,3: exponencial,4: normal*/

    double left;/**< Inicio del intervalo de la distribucion asociada*/

    double right;/**< Final del intervalo de la distribucion asociada*/

};

struct DataSocket1{

    DataSocket1(int a){
    algorithm=a;
    quantum=5;
    n=10;
    seed=1;
    }

    short algorithm;/**< Algoritmo a simular.
                        1:FCFS.2:SJF.3:PSJF.4:RR*/

    double quantum;/**< Quantum para el rr*/

    int n;/**< Numero de procesos*/

    DistributionData arrTimeD;/**< Informacion para la distribucion asociada al tiempo de llegada de los procesos*/

    DistributionData durationTimeD;/**< Informacion para la distribucion asociada al tiempo de duracion de los procesos*/

    DistributionData cpuBusrtTimeD;/**< Informacion para la distribucion asociada al tiempo de rafaga de los procesos*/

    DistributionData blockingTimeD;/**< Informacion para la distribucion asociada al tiempo de bloqueo de los procesos*/

    double seed; /**< semilla para el simulador**/

};



/**
 * @struct EventData
 * @brief Almacenar los datos correspondientes a un evento para enviar a la interfaz
 */
#ifndef FINALSOCKET_H

struct FinalSocket{

    //para las variables q se usan para generar los tiempos


    int inCPU;/**< Numero de veces que se uso el cpu */

    int inIO;/**< Numero de veces que pasaron procesos a bloqueado */

    double averageUsedTime;/**< Tiempo de uso*/

    double averageWaitingTime;/**< tiempo de espera*/

    double sDUsedTime;/**< tiempo en el que ocurre el evento*/

    double sDWaitingTime;/**< tiempo de llegada del proceso que genero el evento*/

    double maxUsedTime;/**< duracion del proceso que genero el evento*/

    double minUsedTime;/**< tiempo restante*/

    double maxWaitingTime;/**< tiempo de rafaga*/

    double minWaitingTime;/**< tiempo de bloqueo*/

    double throughPut;

    double simulationTime;

    double turnAround;

    double sDTurnAround;

    double maxTurnAround;

    double minTurnAround;

    double cpuUtil;

    double IOAvgTime;

    FinalSocket(){}

};

#endif



#endif // DATASOCKET1_H
