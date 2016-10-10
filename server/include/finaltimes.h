/**
 * @file finaltimes.h
 * @brief Declaración de la clase FifoQueue.
 * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
 * @date 01-07-2013
 */

#ifndef FINALTIMES_H
#define FINALTIMES_H

/**
 * @struct FinalTimes
 * @brief Almacena los datos necesarios para calcular la desviacion, maximo y minimo del tiempo de uso, tiempo de bloqueo y turn Around*/
struct FinalTimes
{

    double averageUsedTime;
    double averageWaitingTime;
    double turnAround;
    FinalTimes():averageUsedTime(0.0), averageWaitingTime(0.0), turnAround(0.0)
    {

    }

    FinalTimes(double a,double b,double c)
    {
        averageUsedTime = a;
        averageWaitingTime = b;
        turnAround = c;
    }
};

#endif // FINALTIMES_H
