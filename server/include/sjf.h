/**
 * @file sjf.h
 * @brief class SJF.
 * @author Ronald Sulbaran and Julio Jaimes R. ronalanto03@gmail.com, carlosjuliojr@hotmail.com.
 * @date 07-10-2016
 */



#ifndef SJF_H
#define SJF_H

#include<CompleteProcess.h>
#include<priorityQueue.h>
#include<distributions.h>
#include<fstream>
#include<iostream>
#include<iomanip>
#include<climits>
#include<cfloat>
#include<eventData.h>
#include<vector>
#include<finaltimes.h>
#include<finalsocket.h>
#include<basealgorithm.h>


/**
 * @class SJF
 * @brief Class for to do the simulation SJF's algorithm.
 * @details This class inherit of the class BaseAlgorithm.
 */


class SJF : public BaseAlgorithm{
   private:


      PriorityQueue<CompleteProcess,CmpLessB,BaseAlgorithm::CmpGreaterOrEqualB> priorityQueue;/**< Cola de procesos bloqueados*/

      PriorityQueue<CompleteProcess,BaseAlgorithm::CmpLessR,BaseAlgorithm::CmpGreaterOrEqualR> readyQueue;/**< Cola de listo para ejecutarse*/

   //  std::ofstream out;

   public:

      SJF( const BaseProcess * _baseProcesses,const int _n, const int _t): BaseAlgorithm(_baseProcesses,_n,_t)

      {
      }







      /**
       * Hace la simulacion del algoritmo
       * @param dCpuBurstTime distribucion asociada al tiempo de rafaga
       * @param dCpuBlockingTime distribucion asociada al tiempo de bloqueo
       */

      void simulate(Distribution * dCpuBurstTime,Distribution * dBlockingTime,SharedSimulation & _ss)
      {

         unsigned i=0;

         int processIndex=0;///indica cual es el proximo proceso que llega

         double simulationTime=0.0;///tiempo de simulacion

         double eventToProcessTime=DBL_MAX;//tiempo de proceso que se va a ejecutar

         double percentage=0.0;//porcejentaje de uso

         double averageWaitingTime=0.0;//tiempo de espera promedio

         double averageUsageTime=0.0;//tiempo de uso promedio

         int eventToProcess=-1;//se usa para saber cual evento es el que debe procesarse primero,1 significa que llega un nuevo proceso,2 pasa un proceso de la cola de listo al cpu, 3 Pasa del CPU a bloqueado, 4 pasa de bloqueado a listo,5 Proceso de cpu termina

         double minimumUsedTime;
         bool equalMinimum=true;

         double maximumUsedTime;

         bool equalMaximum=true;

         CompleteProcess cpuP(BaseAlgorithm::baseProcesses[0]);//representa al proceso que esta actualmente ejecutandose

         double averageIoTime=0.0;//tiempo de bloquedo promedio(IO)

         int inIO=0;//numero de veces que llegan procesos a bloqueado

         int inCpu=0;//numero de veces que se ejecutan los procesos

         double turnAround=0.0;


         cpuP.setPid(-1);//no hay nada en la cpu




         while(connected and
               ( processIndex<numOfProcesses or
                 not(priorityQueue.is_empty()) or
                 not(readyQueue.is_empty()) or
                 cpuP.getPid()!=-1))
         {

#ifdef SJF_DEBUG
            if(cpuP.getPid()!=-1 )
            {
               std::cout<<"ID:"<<cpuP.getPid()<<std::endl;
               std::cout<<"BURSTTIME:"<<cpuP.getCpuBurstTime()<<std::endl;
               std::cout<<"WAITINGTIME:"<<cpuP.getWaitingTime()<<std::endl;
               std::cout<<"REMAININGTIME:"<<cpuP.getRemainingTime()<<std::endl;
               std::cout<<"BLOCKINGTIME:"<<cpuP.getBlockingTime()<<std::endl;

            }
#endif

            if(not(readyQueue.is_empty()) and cpuP.getPid()==-1)
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

               if((cpuP.getPid()!=-1 ))
               {
                  if(eventToProcess==-1 or ((cpuP.getCpuBurstTime() )<=eventToProcessTime))
                  {
                     eventToProcess=3;
                     eventToProcessTime=cpuP.getCpuBurstTime();
                     eventToProcess=3;
                     eventToProcessTime=cpuP.getCpuBurstTime();
                  }
               }
               if((cpuP.getPid()!=-1 and cpuP.getRemainingTime()<= cpuP.getCpuBurstTime() ))
               {
                  if((cpuP.getRemainingTime() )<=eventToProcessTime)
                  {
                     eventToProcess=2;
                     eventToProcessTime=(cpuP.getRemainingTime());
                  }
               }

               if(processIndex<numOfProcesses and
                     (((baseProcesses[processIndex].getArrTime()-simulationTime)<=eventToProcessTime)))
               {
                  eventToProcess=1;
                  eventToProcessTime=baseProcesses[processIndex].getArrTime()-simulationTime;
               }

            }//end else


            if(eventToProcess == 1)
            {//llega un proceso
               CompleteProcess tmp(baseProcesses[processIndex++]);
               tmp.setCpuBurstTime(dCpuBurstTime->getVal());
               if(not readyQueue.is_empty()){
                  readyQueue.decrementTime(eventToProcessTime,false);
               }

               readyQueue.put(tmp);

               if(not priorityQueue.is_empty())
                  priorityQueue.decrementTime(eventToProcessTime,true);

               if(cpuP.getPid() != -1)
               {
                  cpuP.setCpuBurstTime(cpuP.getCpuBurstTime()-eventToProcessTime);
                  cpuP.setRemainingTime(cpuP.getRemainingTime()-eventToProcessTime);
                  cpuP.setAverageUsageTime(cpuP.getAverageUsageTime()+eventToProcessTime);
               }


               simulationTime+=eventToProcessTime;
               writeEventInfo(simulationTime,eventToProcess,tmp,_ss);
            }

            else if(eventToProcess==2)
            {//proceso termina
               if(not readyQueue.is_empty())
                  readyQueue.decrementTime(eventToProcessTime,false);

               if(not priorityQueue.is_empty())
                  priorityQueue.decrementTime(eventToProcessTime,true);

               cpuP.setRemainingTime(0.0);
               cpuP.setCpuBurstTime(0.0);
               cpuP.setBlockingTime(0.0);
               cpuP.setAverageUsageTime(cpuP.getAverageUsageTime()+eventToProcessTime);


               if(equalMinimum)
               {
                  minimumUsedTime=cpuP.getAverageUsageTime()/cpuP.getNRunsCPU();
                  equalMinimum=false;
               }
               else if(cpuP.getAverageUsageTime()<minimumUsedTime)
                  minimumUsedTime=cpuP.getAverageUsageTime()/cpuP.getNRunsCPU();

               if(equalMaximum)
               {
                  maximumUsedTime=cpuP.getAverageUsageTime()/cpuP.getNRunsCPU();
                  equalMaximum=false;
               }
               else if(cpuP.getAverageUsageTime()>maximumUsedTime)
                  maximumUsedTime=cpuP.getAverageUsageTime()/cpuP.getNRunsCPU();

               simulationTime+=eventToProcessTime;
               writeEventInfo(simulationTime,eventToProcess,cpuP,_ss);
               averageUsageTime+=cpuP.getAverageUsageTime()/cpuP.getNRunsCPU();
               averageWaitingTime+=cpuP.getWaitingTime();
               percentage+=cpuP.getDurationTime();
               averageIoTime+=cpuP.getAverageIoTime()/cpuP.getNB();
               inIO+=cpuP.getNB();

               cpuP.setPid(-1);//indica que no hay procesos en la cpu
               turnAround+=(simulationTime-cpuP.getArrTime());

               inCpu+=cpuP.getNRunsCPU();

               _ss.results[1][i++]=FinalTimes(cpuP.getAverageUsageTime()/cpuP.getNRunsCPU(),cpuP.getWaitingTime(),simulationTime-cpuP.getArrTime());

            }


            else if(eventToProcess==3)
            {//pasa de cpu a bloqueado
               cpuP.setBlockingTime(dBlockingTime->getVal());
               cpuP.setRemainingTime(cpuP.getRemainingTime()-eventToProcessTime);
               cpuP.setCpuBurstTime(0.0);
               cpuP.setAverageUsageTime(cpuP.getAverageUsageTime()+eventToProcessTime);
               cpuP.setNB(cpuP.getNB()+1);
               cpuP.setAverageIoTime(cpuP.getAverageIoTime()+cpuP.getBlockingTime());

               if(not priorityQueue.is_empty())
                  priorityQueue.decrementTime(eventToProcessTime,true);

               priorityQueue.put(cpuP);

               if(not readyQueue.is_empty())
                  readyQueue.decrementTime(eventToProcessTime,false);

               simulationTime+=eventToProcessTime;//avanza el tiempo de simulacion

               writeEventInfo(simulationTime,eventToProcess,cpuP,_ss);
               cpuP.setPid(-1);
            }

            else if(eventToProcess==4)
            {//bloqueado a listo
               CompleteProcess tmp;
               if(not priorityQueue.is_empty())
               {
                  priorityQueue.decrementTime(eventToProcessTime,true);
                  tmp=priorityQueue.get();
                  tmp.setCpuBurstTime(0.0);
                  if(not readyQueue.is_empty())
                     readyQueue.decrementTime(eventToProcessTime,false);

                  tmp.setCpuBurstTime(dCpuBurstTime->getVal());
                  readyQueue.put(tmp);

               }

               if(cpuP.getPid()!=-1)
               {
                  cpuP.setRemainingTime(cpuP.getRemainingTime()-eventToProcessTime);
                  cpuP.setCpuBurstTime(cpuP.getCpuBurstTime()-eventToProcessTime);
                  cpuP.setAverageUsageTime(cpuP.getAverageUsageTime()+eventToProcessTime);
               }


               simulationTime+=eventToProcessTime;//avanza el tiempo de simulacion

               writeEventInfo(simulationTime,eventToProcess,tmp,_ss);

            }

            else
            {
               cpuP=readyQueue.get();

               cpuP.setNRunsCPU(cpuP.getNRunsCPU()+1);
               writeEventInfo(simulationTime,eventToProcess,cpuP,_ss);

            }


            eventToProcess=-1;
            eventToProcessTime=DBL_MAX;
         }


         if(connected)
         {
            FinalSocket fS;
            eventData.event=6;
            (void)write(nSocket, (char *)(&eventData), sizeof(struct EventData));

            fS.averageUsedTime=averageUsageTime/numOfProcesses;
            fS.averageWaitingTime=averageWaitingTime/numOfProcesses;


            fS.sDUsedTime=0;//donde se almacenara la desviacion de tiempo de uso
            fS.sDWaitingTime=0;//donde se almacenara la desviacion de tiempo de espera
            fS.sDTurnAround=0;
            fS.maxUsedTime=_ss.results[1][0].averageUsedTime;//maxUsedTime
            fS.minUsedTime=_ss.results[1][0].averageUsedTime;//minUsedTime
            fS.maxWaitingTime=_ss.results[1][0].averageWaitingTime;//maxWaitingTime
            fS.minWaitingTime=_ss.results[1][0].averageWaitingTime;//minWaitingTime
            fS.maxTurnAround=_ss.results[1][0].turnAround;
            fS.minTurnAround=_ss.results[1][0].turnAround;
            fS.turnAround=turnAround/numOfProcesses;

            for (int i=0; i<numOfProcesses; i++)
            {

               if(_ss.results[1][i].averageUsedTime>fS.maxUsedTime)//busca el maximo
                  fS.maxUsedTime=_ss.results[1][i].averageUsedTime;

               if(_ss.results[1][i].averageUsedTime<fS.minUsedTime)//busca el minimo
                  fS.minUsedTime=_ss.results[1][i].averageUsedTime;

               if(_ss.results[1][i].averageWaitingTime>fS.maxWaitingTime)//busca el maximo
                  fS.maxWaitingTime=_ss.results[1][i].averageWaitingTime;

               if(_ss.results[1][i].averageWaitingTime<fS.minWaitingTime)//busca el maximo
                  fS.minWaitingTime=_ss.results[1][i].averageWaitingTime;


               if((_ss.results[1][i].turnAround)>fS.maxTurnAround)
                  fS.maxTurnAround=_ss.results[1][i].turnAround;

               if((_ss.results[1][i].turnAround)<fS.minTurnAround)
                  fS.minTurnAround=_ss.results[1][i].turnAround;


               fS.sDUsedTime+=pow(_ss.results[1][i].averageUsedTime-fS.averageUsedTime,2);
               fS.sDWaitingTime+=pow(_ss.results[1][i].averageWaitingTime-fS.averageWaitingTime,2);
               fS.sDTurnAround+=pow(_ss.results[1][i].turnAround-fS.turnAround,2);

            }
            _ss.minTimes[1]=FinalTimes(fS.minUsedTime,fS.minWaitingTime,fS.minTurnAround);
            _ss.maxTimes[1]=FinalTimes(fS.maxUsedTime,fS.maxWaitingTime,fS.maxTurnAround);


            fS.sDUsedTime= sqrt(fS.sDUsedTime/numOfProcesses);
            fS.sDWaitingTime= sqrt(fS.sDWaitingTime/numOfProcesses);
            fS.sDTurnAround=sqrt(fS.sDTurnAround/numOfProcesses);

            fS.inCPU=inCpu;
            fS.inIO=inIO;
            fS.throughPut=numOfProcesses/simulationTime;
            fS.simulationTime=simulationTime;
            fS.cpuUtil=percentage/simulationTime;
            fS.IOAvgTime=averageIoTime/numOfProcesses;



            //                std::cout<<"tiempo de uso Media: "<<fS.averageUsedTime;
            //                std::cout<<"tiempo de espera Media: "<<fS.averageWaitingTime;


            //                std::cout<<"tiempo de uso SD: "<<fS.sDUsedTime;//donde se almacenara la desviacion de tiempo de uso
            //                std::cout<<"tiempo de espera SD: "<<fS.sDWaitingTime;//donde se almacenara la desviacion de tiempo de espera

            //                std::cout<<"tiempo de uso Max: "<<fS.maxUsedTime;//maxUsedTime
            //                std::cout<<"tiempo de uso Min: "<<fS.minUsedTime;//minUsedTime
            //                std::cout<<"tiempo de espera Max: "<<fS.maxWaitingTime;//maxWaitingTime
            //                std::cout<<"tiempo de espera Min: "<<fS.minWaitingTime;//minWaitingTime


            (void)write(nSocket, (char *)(&fS), sizeof(struct FinalSocket));
            _ss.multiple_fin[1]=true;

         }








      }


      ~SJF()
      {
     //    out.close();
      }

};



/* SJF_H */
# endif
