/**
 * @file fcfs.h
 * @brief Declaración de la clase FCFS.
 * @author Ronald Sulbaran. ronalanto03@gmail.com.
 * @date 01-06-2013
 */



#ifndef FIRST_COME_FIRST_SERVER_H
#define FIRST_COME_FIRST_SERVER_H

#include<CompleteProcess.h>
#include<fifoQueue.h>
#include<priorityQueue.h>
#include<distributions.h>
#include<iostream>
#include<eventData.h>
#include<vector>
#include<finaltimes.h>
#include<finalsocket.h>
#include <unistd.h>
#include<basealgorithm.h>

/**
 * @class FCFS
 * @brief Clase para hacer la simulacion del algoritmo FCFS,
 * escribe en un archivo los resultados de la simulacion.
 */
class FCFS: public BaseAlgorithm
{
   private:


      PriorityQueue<CompleteProcess,CmpLessB,CmpGreaterOrEqualB> priorityQueue;/**< Cola de procesos bloqueados*/

      FifoQueue<CompleteProcess> fifoQueue;/**< Cola de listo para ejecutarse*/


   public:

      FCFS(BaseProcess * _baseProcesses,int _n,int _t): BaseAlgorithm(_baseProcesses,_n,_t)
      {
      }

      /**
         * Hace la simulacion del algoritmo
         * @param dCpuBurstTime distribucion asociada al tiempo de rafaga
         * @param dCpuBlockingTime distribucion asociada al tiempo de bloqueo
         * @param multiple indica si la simulacion pertenece a una simulacion simple o sencilla
         */
      void simulate(Distribution * dCpuBurstTime,
                    Distribution * dBlockingTime,
                    SharedSimulation & _ss)
      {

         unsigned i=0;

         size_t processIndex=0;///indica cual es el proximo proceso que llega

         double simulationTime=0.0;///tiempo de simulacion

         double eventToProcessTime=-1;//tiempo de proceso que se va a ejecutar

         double percentage=0.0;//porcejentaje de uso

         double averageWaitingTime=0.0;//tiempo de espera promedio

         double averageUsageTime=0.0;//tiempo de uso promedio

         /**
          * @brief eventToProcess
          * Se usa para saber cual evento es el que debe procesarse primero
          * 1 significa que llega un nuevo proceso
          * 2 pasa un proceso de la cola de listo al cpu
          * 3 Pasa del CPU a bloqueado
          * 4 pasa de bloqueado a listo
          * 5 Proceso de cpu termina
          */
         int eventToProcess = -1;

         double averageIoTime=0.0;//tiempo de bloquedo promedio(IO)

         int inIO=0;//numero de veces que llegan procesos a bloqueado

         int inCpu=0;//numero de veces que se ejecutan los procesos

         double turnAround=0.0;


         CompleteProcess cpuP(baseProcesses[0]);//representa al proceso que esta actualmente ejecutandose


         cpuP.setPid(-1);//no hay nada en la cpu




         while(connected and
               (processIndex < numOfProcesses
                or not(priorityQueue.is_empty())
                or not(fifoQueue.is_empty())
                or  cpuP.getPid()!=-1))
         {

#ifdef FCFS_DEBUG
            if(cpuP.getPid()!=-1 )
            {
               std::cout<<"ID:"<<cpuP.getPid()<<std::endl;
               std::cout<<"BURSTTIME:"<<cpuP.getCpuBurstTime()<<std::endl;
               std::cout<<"WAITINGTIME:"<<cpuP.getWaitingTime()<<std::endl;
               std::cout<<"REMAININGTIME:"<<cpuP.getRemainingTime()<<std::endl;
               std::cout<<"BLOCKINGTIME:"<<cpuP.getBlockingTime()<<std::endl;
            }
#endif

            if(not(fifoQueue.is_empty()) and cpuP.getPid()==-1)
            {
               eventToProcess=5;
               eventToProcessTime=0;
            }
            else
            {
               if(not priorityQueue.is_empty())
               {
                  eventToProcess=4;
                  eventToProcessTime=priorityQueue.watch().getBlockingTime();
               }

               if((cpuP.getPid()!=-1 and ((cpuP.getCpuBurstTime() )<=eventToProcessTime))or\
                     (eventToProcessTime==-1))
               {
                  eventToProcess=3;
                  eventToProcessTime = cpuP.getCpuBurstTime();
               }

               if((cpuP.getPid()!=-1 and cpuP.getRemainingTime()<= cpuP.getCpuBurstTime() and \
                   (cpuP.getRemainingTime() )<=eventToProcessTime)\
                     or (cpuP.getPid()!=-1 and eventToProcessTime==-1))
               {
                  eventToProcess = 2;
                  eventToProcessTime = (cpuP.getRemainingTime());
               }

               if((((baseProcesses[processIndex].getArrTime() - simulationTime) <=  eventToProcessTime)
                   or eventToProcessTime == -1) and processIndex < numOfProcesses)
               {
                  eventToProcess = 1;
                  eventToProcessTime = baseProcesses[processIndex].getArrTime() - simulationTime;
               }

            }//end else


            if(eventToProcess==1)
            {//llega un proceso
               CompleteProcess tmp(baseProcesses[processIndex++]);

               if(not fifoQueue.is_empty())
               {
                  fifoQueue.decrementTime(eventToProcessTime);
               }

               fifoQueue.put(tmp);

               if(not priorityQueue.is_empty())
               {
                  priorityQueue.decrementTime(eventToProcessTime, true);
               }

               if(cpuP.getPid()!=-1)
               {
                  cpuP.setCpuBurstTime(cpuP.getCpuBurstTime()-eventToProcessTime);
                  cpuP.setRemainingTime(cpuP.getRemainingTime()-eventToProcessTime);
                  cpuP.setAverageUsageTime(cpuP.getAverageUsageTime() +
                                           averageUsageTime+eventToProcessTime);
               }


               simulationTime += eventToProcessTime;
               writeEventInfo(simulationTime, eventToProcess, fifoQueue.watch(), _ss);
            }

            else if(eventToProcess==2)
            {//proceso termina
               if(not fifoQueue.is_empty())
               {
                  fifoQueue.decrementTime(eventToProcessTime);
               }

               if(not priorityQueue.is_empty())
               {
                  priorityQueue.decrementTime(eventToProcessTime,true);
               }

               cpuP.setRemainingTime(0.0);
               cpuP.setCpuBurstTime(0.0);
               cpuP.setBlockingTime(0.0);
               cpuP.setAverageUsageTime(cpuP.getAverageUsageTime() + eventToProcessTime);

               simulationTime += eventToProcessTime;
               writeEventInfo(simulationTime, eventToProcess, cpuP, _ss);
               averageUsageTime += cpuP.getAverageUsageTime()/cpuP.getNRunsCPU();
               averageIoTime += cpuP.getAverageIoTime()/cpuP.getNB();
               inIO += cpuP.getNB();

               averageWaitingTime += cpuP.getWaitingTime();
               percentage += cpuP.getDurationTime();

               turnAround += (simulationTime - cpuP.getArrTime());

               inCpu += cpuP.getNRunsCPU();

               cpuP.setPid(-1);//indica que no hay procesos en la cpu

               _ss.results[0][i++] = FinalTimes(cpuP.getAverageUsageTime()/cpuP.getNRunsCPU(),
                                                cpuP.getWaitingTime(),
                                                simulationTime - cpuP.getArrTime());
            }

            else if(eventToProcess==3)
            {//pasa de cpu a bloqueado
               cpuP.setBlockingTime((double(int(dBlockingTime->getVal()*10.0+.5))/10.0));
               cpuP.setRemainingTime(cpuP.getRemainingTime()-eventToProcessTime);
               cpuP.setCpuBurstTime(0.0);
               cpuP.setAverageUsageTime(cpuP.getAverageUsageTime()+eventToProcessTime);
               cpuP.setNB(cpuP.getNB()+1);
               cpuP.setAverageIoTime(cpuP.getAverageIoTime()+cpuP.getBlockingTime());

               if(not priorityQueue.is_empty())
               {
                  priorityQueue.decrementTime(eventToProcessTime,true);
               }

               priorityQueue.put(cpuP);

               if(not fifoQueue.is_empty())
               {
                  fifoQueue.decrementTime(eventToProcessTime);
               }

               simulationTime += eventToProcessTime;//avanza el tiempo de simulacion

               writeEventInfo(simulationTime,eventToProcess,cpuP,_ss);
               cpuP.setPid(-1);
            }

            else if(eventToProcess==4)
            {//bloqueado a listo
               CompleteProcess tmp;
               if(not priorityQueue.is_empty())
               {
                  priorityQueue.decrementTime(eventToProcessTime, true);
                  tmp = priorityQueue.get();
                  tmp.setCpuBurstTime(0.0);
                  if(not fifoQueue.is_empty())
                  {
                     fifoQueue.decrementTime(eventToProcessTime);
                  }

                  fifoQueue.put(tmp);

               }

               if(cpuP.getPid() != -1)
               {
                  cpuP.setRemainingTime(cpuP.getRemainingTime() - eventToProcessTime);
                  cpuP.setCpuBurstTime(cpuP.getCpuBurstTime() - eventToProcessTime);
                  cpuP.setAverageUsageTime(cpuP.getAverageUsageTime() + eventToProcessTime);
               }


               simulationTime += eventToProcessTime;//avanza el tiempo de simulacion

               writeEventInfo(simulationTime, eventToProcess, tmp, _ss);

            }

            else
            {
               cpuP = fifoQueue.get();
               cpuP.setCpuBurstTime((double(int(dCpuBurstTime->getVal()*10.0+.5))/10.0));

               cpuP.setNRunsCPU(cpuP.getNRunsCPU() + 1);
               writeEventInfo(simulationTime, eventToProcess, cpuP, _ss);
            }

            eventToProcessTime = -1;
         }


         if(connected)
         {
            FinalSocket fS;
            eventData.event = 6;
            int tmpRevVal = write(nSocket, (char *)(&eventData), sizeof(struct EventData));
            (void)tmpRevVal;

            fS.averageUsedTime = averageUsageTime/numOfProcesses;
            fS.averageWaitingTime = averageWaitingTime/numOfProcesses;
            fS.sDUsedTime = 0;//donde se almacenara la desviacion de tiempo de uso
            fS.sDWaitingTime = 0;//donde se almacenara la desviacion de tiempo de espera
            fS.sDTurnAround = 0;
            fS.maxUsedTime = _ss.results[0][0].averageUsedTime;//maxUsedTime
            fS.minUsedTime =_ss.results[0][0].averageUsedTime;//minUsedTime
            fS.maxWaitingTime =_ss.results[0][0].averageWaitingTime;//maxWaitingTime
            fS.minWaitingTime =_ss.results[0][0].averageWaitingTime;//minWaitingTime
            fS.maxTurnAround =_ss.results[0][0].turnAround;
            fS.minTurnAround =_ss.results[0][0].turnAround;
            fS.turnAround = turnAround/numOfProcesses;

            for (size_t i = 0; i < numOfProcesses; i++)
            {
               if(_ss.results[0][i].averageUsedTime>fS.maxUsedTime)//busca el maximo
               {
                  fS.maxUsedTime=_ss.results[0][i].averageUsedTime;
               }

               if(_ss.results[0][i].averageUsedTime<fS.minUsedTime)//busca el minimo
               {
                  fS.minUsedTime=_ss.results[0][i].averageUsedTime;
               }

               if(_ss.results[0][i].averageWaitingTime>fS.maxWaitingTime)//busca el maximo
               {
                  fS.maxWaitingTime=_ss.results[0][i].averageWaitingTime;
               }

               if(_ss.results[0][i].averageWaitingTime<fS.minWaitingTime)//busca el maximo
               {
                  fS.minWaitingTime=_ss.results[0][i].averageWaitingTime;
               }

               if((_ss.results[0][i].turnAround)>fS.maxTurnAround)
               {
                  fS.maxTurnAround=_ss.results[0][i].turnAround;
               }

               if((_ss.results[0][i].turnAround)<fS.minTurnAround)
               {
                  fS.minTurnAround=_ss.results[0][i].turnAround;
               }

               fS.sDUsedTime += pow(_ss.results[0][i].averageUsedTime - fS.averageUsedTime, 2);
               fS.sDWaitingTime += pow(_ss.results[0][i].averageWaitingTime - fS.averageWaitingTime, 2);
               fS.sDTurnAround += pow(_ss.results[0][i].turnAround - fS.turnAround, 2);
            }

            _ss.minTimes[0] = FinalTimes(fS.minUsedTime, fS.minWaitingTime, fS.minTurnAround);

            _ss.maxTimes[0] = FinalTimes(fS.maxUsedTime, fS.maxWaitingTime, fS.maxTurnAround);
            fS.sDUsedTime = sqrt(fS.sDUsedTime/numOfProcesses);
            fS.sDWaitingTime = sqrt(fS.sDWaitingTime/numOfProcesses);
            fS.sDTurnAround = sqrt(fS.sDTurnAround/numOfProcesses);

            fS.inCPU = inCpu;
            fS.inIO = inIO;
            fS.throughPut = numOfProcesses/simulationTime;
            fS.simulationTime = simulationTime;
            fS.cpuUtil = percentage/simulationTime;
            fS.IOAvgTime = averageIoTime/numOfProcesses;

            tmpRevVal = write(nSocket, (char *)(&fS), sizeof(struct FinalSocket));
            (void)tmpRevVal;

            _ss.multiple_fin[0]=true;

         }
      }


      ~FCFS()
      {
      }

};



# endif/* FIRST_COME_FIRST_SERVER_H */
