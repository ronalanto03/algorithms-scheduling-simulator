/**
 * @file RR.h
 * @brief Declaración de la clase RR.
 * @author Ronald Sulbaran. ronalanto03@gmail.com.
 * @date 01-06-2013
 */



#ifndef RR_H
#define RR_H

#include<CompleteProcess.h>
#include<fifoQueue.h>
#include<priorityQueue.h>
#include<distributions.h>
#include<fstream>
#include<iostream>
#include<iomanip>
#include<cfloat>
#include<eventData.h>
#include<vector>
#include<finaltimes.h>
#include<finalsocket.h>
#include<basealgorithm.h>


/**
 * @class RR
 * @brief Clase para hacer la simulacion del algoritmo RR,
 * escribe en un archivo los resultados de la simulacion.
 */


class RR:public BaseAlgorithm
{
   private:

      PriorityQueue<CompleteProcess,CmpLessB,CmpGreaterOrEqualB> priorityQueue;/**< Cola de procesos bloqueados*/

      FifoQueue<CompleteProcess> readyQueue;/**< Cola de listo para ejecutarse*/




      std::ofstream out;

      double quantum;



   public:

      RR(BaseProcess * _baseProcesses,int _n,double _quantum,int _t):
          BaseAlgorithm(_baseProcesses,_n,_t),
          quantum(_quantum)

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

         size_t processIndex=0;///indica cual es el proximo proceso que llega

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
         CompleteProcess cpuP(baseProcesses[0]);//representa al proceso que esta actualmente ejecutandose

         double averageIoTime=0.0;//tiempo de bloquedo promedio(IO)

         int inIO=0;//numero de veces que llegan procesos a bloqueado

         int inCpu=0;//numero de veces que se ejecutan los procesos

         double turnAround=0.0;

         cpuP.setPid(-1);//no hay nada en la cpu




         while(connected and
               (processIndex<numOfProcesses
                or not(priorityQueue.is_empty())
                or not(readyQueue.is_empty())
                or  cpuP.getPid()!=-1))
         {

#ifdef RR_DEBUG
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

               if((cpuP.getPid()!=-1 ) and cpuP.getCpuBurstTime()<=cpuP.getQuantum())
               {
                  if(((cpuP.getCpuBurstTime() )<=eventToProcessTime))
                  {
                     eventToProcess=3;
                     eventToProcessTime=cpuP.getCpuBurstTime();
                  }
               }
               if(cpuP.getPid()!=-1 and
                     cpuP.getRemainingTime()<= cpuP.getCpuBurstTime()
                     and cpuP.getRemainingTime()<= cpuP.getQuantum() )
               {
                  if((cpuP.getRemainingTime() )<=eventToProcessTime)
                  {
                     eventToProcess=2;
                     eventToProcessTime=(cpuP.getRemainingTime());
                  }
               }


               if(cpuP.getPid()!=-1 and cpuP.getCpuBurstTime()>cpuP.getQuantum())
                  if((cpuP.getQuantum()<=eventToProcessTime))
                  {
                     eventToProcess=1;
                     eventToProcessTime=cpuP.getQuantum();
                  }
               if(processIndex < numOfProcesses and
                     ((((baseProcesses[processIndex].getArrTime()-simulationTime)<=eventToProcessTime))))
               {
                  eventToProcess=0;
                  eventToProcessTime=baseProcesses[processIndex].getArrTime()-simulationTime;
               }

            }//end else





            if(eventToProcess==0)
            {//llega un proceso
               CompleteProcess tmp(baseProcesses[processIndex++]);
               //                    tmp.setCpuBurstTime((double(int(dCpuBurstTime->getVal()*10.0+.5))/10.0));
               tmp.setCpuBurstTime(dCpuBurstTime->getVal());
               if(not readyQueue.is_empty()){
                  readyQueue.decrementTime(eventToProcessTime);
               }

               readyQueue.put(tmp);

               if(not priorityQueue.is_empty())
                  priorityQueue.decrementTime(eventToProcessTime,true);

               if(cpuP.getPid()!=-1){
                  cpuP.setCpuBurstTime(cpuP.getCpuBurstTime()-eventToProcessTime);
                  cpuP.setRemainingTime(cpuP.getRemainingTime()-eventToProcessTime);
                  cpuP.setAverageUsageTime(cpuP.getAverageUsageTime()+eventToProcessTime);
                  cpuP.setQuantum(cpuP.getQuantum()-eventToProcessTime);
               }


               simulationTime+=eventToProcessTime;
               writeEventInfo(simulationTime,eventToProcess,tmp,_ss);
            }


            else if(eventToProcess==1)
            {//de cpu a listo
               cpuP.setCpuBurstTime(cpuP.getCpuBurstTime()-eventToProcessTime);
               cpuP.setQuantum(0);
               cpuP.setRemainingTime(cpuP.getRemainingTime()-eventToProcessTime);
               cpuP.setAverageUsageTime(cpuP.getAverageUsageTime()+eventToProcessTime);

               if(not readyQueue.is_empty())
                  readyQueue.decrementTime(eventToProcessTime);

               if(not priorityQueue.is_empty())
                  priorityQueue.decrementTime(eventToProcessTime,true);

               readyQueue.put(cpuP);
               simulationTime += eventToProcessTime;
               writeEventInfo(simulationTime, eventToProcess,cpuP,_ss);
               cpuP.setPid(-1);
            }
            else if(eventToProcess==2)
            {//proceso termina
               if(not readyQueue.is_empty())
                  readyQueue.decrementTime(eventToProcessTime);

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
               else if(cpuP.getAverageUsageTime() > maximumUsedTime)
                  maximumUsedTime = cpuP.getAverageUsageTime()/cpuP.getNRunsCPU();

               simulationTime += eventToProcessTime;
               writeEventInfo(simulationTime,eventToProcess,cpuP,_ss);
               averageUsageTime+=cpuP.getAverageUsageTime()/cpuP.getNRunsCPU();
               averageWaitingTime+=cpuP.getWaitingTime();
               averageIoTime+=cpuP.getAverageIoTime()/cpuP.getNB();
               percentage+=cpuP.getDurationTime();
               inIO+=cpuP.getNB();
               cpuP.setPid(-1);//indica que no hay procesos en la cpu
               turnAround+=(simulationTime-cpuP.getArrTime());

               inCpu+=cpuP.getNRunsCPU();

               _ss.results[3][i++]=FinalTimes(cpuP.getAverageUsageTime()/cpuP.getNRunsCPU(),cpuP.getWaitingTime(),simulationTime-cpuP.getArrTime());

            }


            else if(eventToProcess==3)
            {//pasa de cpu a bloqueado
               //cpuP.setBlockingTime((double(int(dBlockingTime->getVal()*10.0+.5))/10.0));
               cpuP.setBlockingTime(dBlockingTime->getVal());
               cpuP.setRemainingTime(cpuP.getRemainingTime()-eventToProcessTime);
               cpuP.setCpuBurstTime(0.0);
               cpuP.setQuantum(0.0);

               cpuP.setAverageUsageTime(cpuP.getAverageUsageTime()+eventToProcessTime);
               cpuP.setNB(cpuP.getNB()+1);
               cpuP.setAverageIoTime(cpuP.getAverageIoTime()+cpuP.getBlockingTime());

               if(not priorityQueue.is_empty())
                  priorityQueue.decrementTime(eventToProcessTime,true);

               priorityQueue.put(cpuP);

               if(not readyQueue.is_empty())
                  readyQueue.decrementTime(eventToProcessTime);

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
                     readyQueue.decrementTime(eventToProcessTime);

                  tmp.setCpuBurstTime(dCpuBurstTime->getVal());
                  //tmp.setCpuBurstTime((double(int(dCpuBurstTime->getVal()*10.0+.5))/10.0));
                  readyQueue.put(tmp);

               }

               if(cpuP.getPid()!=-1)
               {
                  cpuP.setRemainingTime(cpuP.getRemainingTime()-eventToProcessTime);
                  cpuP.setCpuBurstTime(cpuP.getCpuBurstTime()-eventToProcessTime);
                  cpuP.setAverageUsageTime(cpuP.getAverageUsageTime()+eventToProcessTime);
                  cpuP.setQuantum(cpuP.getQuantum()-eventToProcessTime);
               }

               simulationTime+=eventToProcessTime;//avanza el tiempo de simulacion

               writeEventInfo(simulationTime,eventToProcess,tmp,_ss);

            }

            else
            {
               cpuP=readyQueue.get();
               //cpuP.setCpuBurstTime((double(int(dCpuBurstTime->getVal()*10.0+.5))/10.0));
               if(cpuP.getQuantum() == 0)
               {
                  cpuP.setQuantum(quantum);
                  std::cout<<"Quantum "<<cpuP.getQuantum()<<std::endl;
               }
               cpuP.setNRunsCPU(cpuP.getNRunsCPU()+1);
               writeEventInfo(simulationTime,eventToProcess,cpuP,_ss);

            }



            //std::cout<<"EVENT"<<eventToProcess<<std::endl;
            //std::cout<<processIndex<<std::endl;
            //std::cout<<std::setprecision(18)<<simulationTime<<std::endl;
            eventToProcess=-1;
            eventToProcessTime=DBL_MAX;
         }

         if(connected)
         {
            FinalSocket fS;
            eventData.event=6;
            int tmpRevVal = write(nSocket, (char *)(&eventData), sizeof(struct EventData));
            (void)tmpRevVal;

            fS.averageUsedTime=averageUsageTime/numOfProcesses;
            fS.averageWaitingTime=averageWaitingTime/numOfProcesses;


            fS.sDUsedTime=0;//donde se almacenara la desviacion de tiempo de uso
            fS.sDWaitingTime=0;//donde se almacenara la desviacion de tiempo de espera
            fS.sDTurnAround=0;
            fS.maxUsedTime=_ss.results[3][0].averageUsedTime;//maxUsedTime
            fS.minUsedTime=_ss.results[3][0].averageUsedTime;//minUsedTime
            fS.maxWaitingTime=_ss.results[3][0].averageWaitingTime;//maxWaitingTime
            fS.minWaitingTime=_ss.results[3][0].averageWaitingTime;//minWaitingTime
            fS.maxTurnAround=_ss.results[3][0].turnAround;
            fS.minTurnAround=_ss.results[3][0].turnAround;
            fS.turnAround=turnAround/numOfProcesses;

            for (i = 0; i < numOfProcesses; i++)
            {
               if(_ss.results[3][i].averageUsedTime>fS.maxUsedTime)//busca el maximo
                  fS.maxUsedTime=_ss.results[3][i].averageUsedTime;

               if(_ss.results[3][i].averageUsedTime<fS.minUsedTime)//busca el minimo
                  fS.minUsedTime=_ss.results[3][i].averageUsedTime;

               if(_ss.results[3][i].averageWaitingTime>fS.maxWaitingTime)//busca el maximo
                  fS.maxWaitingTime=_ss.results[3][i].averageWaitingTime;

               if(_ss.results[3][i].averageWaitingTime<fS.minWaitingTime)//busca el maximo
                  fS.minWaitingTime=_ss.results[3][i].averageWaitingTime;


               if((_ss.results[3][i].turnAround)>fS.maxTurnAround)
                  fS.maxTurnAround=_ss.results[3][i].turnAround;

               if((_ss.results[3][i].turnAround)<fS.minTurnAround)
                  fS.minTurnAround=_ss.results[3][i].turnAround;


               fS.sDUsedTime+=pow(_ss.results[3][i].averageUsedTime-fS.averageUsedTime,2);
               fS.sDWaitingTime+=pow(_ss.results[3][i].averageWaitingTime-fS.averageWaitingTime,2);
               fS.sDTurnAround+=pow(_ss.results[3][i].turnAround-fS.turnAround,2);

            }

            _ss.minTimes[3]=FinalTimes(fS.minUsedTime,fS.minWaitingTime,fS.minTurnAround);
            _ss.maxTimes[3]=FinalTimes(fS.maxUsedTime,fS.maxWaitingTime,fS.maxTurnAround);

            fS.sDUsedTime= sqrt(fS.sDUsedTime/numOfProcesses);
            fS.sDWaitingTime= sqrt(fS.sDWaitingTime/numOfProcesses);
            fS.sDTurnAround=sqrt(fS.sDTurnAround/numOfProcesses);

            fS.inCPU=inCpu;
            fS.inIO=inIO;
            fS.throughPut=numOfProcesses/simulationTime;
            fS.simulationTime=simulationTime;
            fS.cpuUtil=percentage/simulationTime;
            fS.IOAvgTime=averageIoTime/numOfProcesses;

            tmpRevVal = write(nSocket, (char *)(&fS), sizeof(struct FinalSocket));
            (void)tmpRevVal;
            _ss.multiple_fin[3]=true;

         }

      }


      ~RR()
      {
         out.close();
      }

};



/* RR_H */
# endif
