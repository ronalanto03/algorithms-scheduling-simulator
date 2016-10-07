#ifndef BASEALGORITHM_H
#define BASEALGORITHM_H
#include<iqueue.h>
#include<CompleteProcess.h>
#include<eventData.h>
#include<finalsocket.h>

class BaseAlgorithm
{
protected:

    /**
     * @struct CmpLessB
     * @brief Estructura para hacer la comparacion de menor que en la Cola de bloqueado.
     */
    struct CmpLessB
    {
          bool operator () (CompleteProcess & __x , CompleteProcess & __y) const
          {
             return __x.getBlockingTime() < __y.getBlockingTime();
          }
    };


    /**
     * @struct CmpGreaterOrEqualB
     * @brief Estructura para hacer la comparacion de mayor o igual que en la Cola de bloqueado.
     */
    struct CmpGreaterOrEqualB
    {
          bool operator () (CompleteProcess & __x,  CompleteProcess & __y) const
          {
             return __x.getBlockingTime() >= __y.getBlockingTime();
          }
    };


    /**
     * @struct CmpLessR
     * @brief Estructura para hacer la comparacion de menor que en la Cola de listo.
     */
    struct CmpLessR
    {
          bool operator () (CompleteProcess & __x , CompleteProcess & __y) const
          {
             return __x.getCpuBurstTime() < __y.getCpuBurstTime();
          }
    };


    /**
     * @struct CmpGreaterOrEqualR
     * @brief Estructura para hacer la comparacion de mayor o igual que en la Cola de listo.
     */
    struct CmpGreaterOrEqualR
    {
          bool operator () (CompleteProcess & __x,  CompleteProcess & __y) const
          {
             return __x.getCpuBurstTime() >= __y.getCpuBurstTime();
          }
    };

    IQueue* priorityBlockQueue;

    IQueue* readyQueue;

    int numOfProcesses;

    BaseProcess* baseProcess;

    struct EventData eventData;

    int nSocket;

    bool connected;




public:
    BaseAlgorithm();

    BaseAlgorithm(IQueue & _priorityBlockQueue, IQueue& _readyQueue,\
                  int _numOfProcesses, BaseProcess & _baseProcess, struct EventData _eventData,int _nSocket,bool _connected);

    void writeEventInfo(double time, int event,const CompleteProcess p,SharedSimulation & _ss);


};

#endif // BASEALGORITHM_H
