#ifndef MULTSIMDATA_H
#define MULTSIMDATA_H

struct MutlSimData
{

    int algorithm;/**< tipo de algoritmo*/

    double usedTimeAmplitude;/**< amplitud de la clase de tiempo de uso*/

    int usedTimeClasses[10];/**< numero de procesos que hay en cada clase para el tiempo de uso*/

    double waitingTimeAmplitude;/**< amplitud de la clase de tiempo de espera*/

    int waitingTimeClasses[10];/**< numero de procesos que hay en cada clase para el tiempo de espera*/

    double turnAroundTimeAmplitude;/**< amplitud de la clase del turnAround*/

    int turnAroundTimeClasses[10];/**< numero de procesos que hay en cada clase para el turnAround*/

};

#endif // MULTSIMDATA_H
