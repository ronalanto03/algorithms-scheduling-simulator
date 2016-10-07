/**
 * @file DataSocket1.h
 * @brief Declaracion de las estructuras DistributionData y DataSocket1
 * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
 */

#ifndef DATASOCKET1_H
#define DATASOCKET1_H


/**
 * @struct DistributionData
 * @brief Almacena los parametros de una distribucion
 */
struct DistributionData{

    short t;/**< Tipo de distribucion.
                1: constante,2: uniforme,3: exponencial,4: normal*/

    double left;/**< Inicio del intervalo de la distribucion asociada*/

    double right;/**< Final del intervalo de la distribucion asociada*/

};



/**
 * @struct DataSocket1
 * @brief Almacena los datos necesarios para iniciar una simulacion
 */
struct DataSocket1{

    short algorithm;/**< Algoritmo a simular.
                        1:FCFS.2:SJF.3:PSJF.4:RR*/

    double quantum;/**< Quantum para el rr*/

    int n;/**< Numero de procesos*/

    DistributionData arrTimeD;/**< Informacion para la distribucion asociada al tiempo de llegada de los procesos*/

    DistributionData durationTimeD;/**< Informacion para la distribucion asociada al tiempo de duracion de los procesos*/

    DistributionData cpuBusrtTimeD;/**< Informacion para la distribucion asociada al tiempo de rafaga de los procesos*/

    DistributionData blockingTimeD;/**< Informacion para la distribucion asociada al tiempo de bloqueo de los procesos*/

    double seed;/**< semilla para el simulador **/
};


#endif // DATASOCKET1_H
