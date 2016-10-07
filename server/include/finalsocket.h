/**
 * @file finalsocket.h
 * @brief Declaración de la clase finalsocket.
 * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
 * @date 01-07-2013
 */

#ifndef FINALSOCKET_H
#define FINALSOCKET_H



/**
 * @struct FinalSocket
 * @brief Almacena los datos resultados obtenidos de una simulacion */

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

    double throughPut;/**< numero de procesos que finalizaron/tiempo de simulacion */

    double simulationTime;/**< Tiempo de simulacion*/

    double turnAround;/**< promedio de turn Around*/

    double sDTurnAround;/**< desviacion estadar de turnAround*/

    double maxTurnAround;/** maximo tiempo de turn around*/

    double minTurnAround;/**< minimo tiempo de turnAround */

    double cpuUtil;/**< porcentaje de utilizacion del cpu*/

    double IOAvgTime;/**< Promedio del tiempo de bloqueo de los procesos*/

};





/**
 * @struct SharedSimulation
 * @brief Almacena los resultados obtenidos de una simulacion multiple*/

struct SharedSimulation{

    int n;/**< numero de  procesos para la simulacion */

    int nn;/**< contador para saber cuantas de las simulaciones se han enviado a ejercutar en los hilos*/

    int t;/**< numero del socket*/

    FinalTimes * results[4];/**< se almacena toda la informacion de correspondiente a cada algoritmo*/

    FinalTimes minTimes[4];/**< se almacenan los minimos correspondiente a cada algoritmo para hacer la division por clases*/

    FinalTimes maxTimes[4];/**< se almacenan los maximos correspondiente a cada algoritmo para hacer la division por clases*/

    bool multiple_ini[4];/**< indica cuales algoritmos se estan ejecuatando*/

    bool multiple_fin[4];/**< indica cuales algoritmos terminaron la ejecucion*/

    bool connected;/**< indica que el hay una simulacion multiple siendo ejecutada*/

    SharedSimulation(){
        connected=false;
        for(int i=0;i<4;++i){
            results[i]=NULL;//es la forma de saber si ese algoritmo fue ejecutado o no
            multiple_ini[i]=0;
            multiple_fin[i]=0;
        }
    }

};

#endif // FINALSOCKET_H
