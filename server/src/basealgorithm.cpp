#include "basealgorithm.h"

BaseAlgorithm::BaseAlgorithm()
{

}

BaseAlgorithm::BaseAlgorithm(
                             const BaseProcess * _baseProcess,
                             const int _numOfProcesses,
                             const int _nSocket
                             ):
    numOfProcesses(_numOfProcesses),
    baseProcesses(_baseProcess),
    nSocket(_nSocket),
    connected(true)
{
}

/**
 * Writes in the Socket the events process.
 * @param time. It is the time when the event occurs
 * @param event Type of Event
 * @param p process associated with the event occurred
 */
void BaseAlgorithm::writeEventInfo(const double time, const int event, const CompleteProcess p, SharedSimulation &_ss)
{

    eventData.time =  time;
    eventData.pid =  p.getPid();
    eventData.durationTime = p.getDurationTime();
    eventData.event = event;
    eventData.arrTime = p.getArrTime();
    eventData.remainingTime = p.getRemainingTime();
    eventData.waitingTime = p.getWaitingTime();
    eventData.cpuBurstTime = p.getCpuBurstTime();
    eventData.blockingTime = p.getBlockingTime();
    eventData.usedTime = p.getAverageUsageTime();
    eventData.nB = p.getNB();
    eventData.nT = p.getNRunsCPU();
    eventData.allBlockingTime = p.getAverageIoTime();

    std::ofstream prueba;

    prueba.open("prueba.txt",std::ios_base::out|std::ios_base::app);

    prueba<<eventData.time<<"\t"
          <<eventData.pid<<"\t"
          <<eventData.durationTime<<"\t"
          << eventData.event<<"\t"
          << eventData.arrTime<<"\t"
          << eventData.remainingTime<<"\t"
          <<eventData.waitingTime<<"\t"
          <<eventData.cpuBurstTime<<"\t"
          <<eventData.blockingTime<<"\t"
          << eventData.usedTime<<"\t"
          << eventData.nB<<"\t"
          << eventData.nT<<"\t"
          << eventData.allBlockingTime<<"\t"<<"**********"<<"\n";


        prueba.close();


    int tmpRetVal = write(nSocket, (char *)(&eventData), sizeof(struct EventData));
    (void)tmpRetVal;

    tmpRetVal = read(nSocket, (char *)(&eventData), sizeof(struct EventData));
    (void)tmpRetVal;

    if(eventData.event==-1)
    {
       connected=false;
       _ss.connected=false;
    }
}
