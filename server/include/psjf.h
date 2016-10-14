/**
 * @file PSJF.h
 * @brief Declaración de la clase PSJF.
 * @author Ronald Sulbaran. ronalanto03@gmail.com.
 * @date 01-06-2013
 */



#ifndef PSJF_H
#define PSJF_H

#include<basealgorithm.h>

/**
 * @class PSJF
 * @brief Clase para hacer la simulacion del algoritmo PSJF,
 * escribe en un archivo los resultados de la simulacion.
 */


class PSJF: public BaseAlgorithm
{

   public:

      PSJF(BaseProcess * _baseProcesses,int _n,int _t):BaseAlgorithm(_baseProcesses,_n,_t)
      {
         init();
      }

      void init()
      {
         blockingQueue = new PriorityQueue<CompleteProcess,CmpLessB,CmpGreaterOrEqualB>;
         readyQueue = new  PriorityQueue<CompleteProcess, CmpLessR, CmpGreaterOrEqualR>;
      }

      /**
       * Hace la simulacion del algoritmo
       * @param dCpuBurstTime distribucion asociada al tiempo de rafaga
       * @param dCpuBlockingTime distribucion asociada al tiempo de bloqueo
       */
      void simulate(Distribution * dCpuBurstTime,
                    Distribution * dBlockingTime,
                    SharedSimulation & _ss)
      {

         double minimumUsedTime;

         bool equalMinimum=true;

         double maximumUsedTime;

         bool equalMaximum=true;

         cpuP.setPid(-1);//no hay nada en la cpu

         while(connected and
               (processIndex<numOfProcesses or
                not(blockingQueue->is_empty())
                or not(readyQueue->is_empty()) or
                cpuP.getPid()!=-1))
         {




#ifdef PSJF_DEBUG
            if(cpuP.getPid()!=-1 ){
               std::cout<<"ID:"<<cpuP.getPid()<<std::endl;
               std::cout<<"BURSTTIME:"<<cpuP.getCpuBurstTime()<<std::endl;
               std::cout<<"WAITINGTIME:"<<cpuP.getWaitingTime()<<std::endl;
               std::cout<<"REMAININGTIME:"<<cpuP.getRemainingTime()<<std::endl;
               std::cout<<"BLOCKINGTIME:"<<cpuP.getBlockingTime()<<std::endl;

            }
#endif

            if(not(readyQueue->is_empty()) and cpuP.getPid()==-1)
            {
               eventToProcess=5;
               eventToProcessTime=0;
            }

            else
            {
               if(not blockingQueue->is_empty())
               {
                  eventToProcess=4;
                  eventToProcessTime=blockingQueue->watch().getBlockingTime();
               }

               if((cpuP.getPid()!=-1 ))
               {
                  if(eventToProcess==-1 or ((cpuP.getCpuBurstTime() )<=eventToProcessTime))
                  {
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

               if(cpuP.getPid()!=-1 and (!readyQueue->is_empty()))
                  if(readyQueue->watch().getCpuBurstTime()<cpuP.getCpuBurstTime() and \
                        readyQueue->watch().getCpuBurstTime()<eventToProcessTime)
                  {
                     eventToProcessTime=0.0;
                     eventToProcess=1;

                  }

               if(processIndex<numOfProcesses and
                     (((baseProcesses[processIndex].getArrTime()-simulationTime) <= eventToProcessTime)))
               {
                  eventToProcess=0;
                  eventToProcessTime=baseProcesses[processIndex].getArrTime()-simulationTime;
               }

            }//end else



            if(eventToProcess==0)
            {//llega un proceso
               CompleteProcess tmp(baseProcesses[processIndex++]);
               tmp.setCpuBurstTime(dCpuBurstTime->getVal());
               if(not readyQueue->is_empty())
               {
                  readyQueue->decrementTime(eventToProcessTime,false);
               }

               readyQueue->put(tmp);

               if(not blockingQueue->is_empty())
                  blockingQueue->decrementTime(eventToProcessTime,true);

               if(cpuP.getPid()!=-1)
               {
                  cpuP.setCpuBurstTime(cpuP.getCpuBurstTime()-eventToProcessTime);
                  cpuP.setRemainingTime(cpuP.getRemainingTime()-eventToProcessTime);
                  cpuP.setAverageUsageTime(cpuP.getAverageUsageTime()+eventToProcessTime);
               }

               simulationTime+=eventToProcessTime;
               writeEventInfo(simulationTime,eventToProcess,tmp,_ss);
            }


            else if(eventToProcess==1)
            {//de cpu a listo
               readyQueue->put(cpuP);
               writeEventInfo(simulationTime,eventToProcess,cpuP,_ss);
               cpuP.setPid(-1);
            }
            else if(eventToProcess==2)
            {//proceso termina
               if(not readyQueue->is_empty())
                  readyQueue->decrementTime(eventToProcessTime,false);

               if(not blockingQueue->is_empty())
                  blockingQueue->decrementTime(eventToProcessTime,true);

               cpuP.setRemainingTime(0.0);
               cpuP.setCpuBurstTime(0.0);
               cpuP.setBlockingTime(0.0);
               cpuP.setAverageUsageTime(cpuP.getAverageUsageTime()+eventToProcessTime);


               if(equalMinimum)
               {
                  minimumUsedTime = cpuP.getAverageUsageTime()/cpuP.getNRunsCPU();
                  equalMinimum=false;
               }
               else if(cpuP.getAverageUsageTime() < minimumUsedTime)
                  minimumUsedTime = cpuP.getAverageUsageTime()/cpuP.getNRunsCPU();

               if(equalMaximum)
               {
                  maximumUsedTime = cpuP.getAverageUsageTime() / cpuP.getNRunsCPU();
                  equalMaximum=false;
               }
               else if(cpuP.getAverageUsageTime() > maximumUsedTime)
                  maximumUsedTime=cpuP.getAverageUsageTime()/cpuP.getNRunsCPU();

               simulationTime+=eventToProcessTime;
               std::cout<<"Termino el proceso "<<cpuP.getPid();
               std::cout<<" Entradas en cpu "<<cpuP.getNRunsCPU()<<std::endl;
               //out<<"\t time:"<<simulationTime<<std::endl<<std::endl;
               writeEventInfo(simulationTime,eventToProcess,cpuP,_ss);
               averageUsageTime+=cpuP.getAverageUsageTime()/cpuP.getNRunsCPU();
               averageWaitingTime+=cpuP.getWaitingTime();
               averageIoTime+=cpuP.getAverageIoTime()/cpuP.getNB();
               percentage+=cpuP.getDurationTime();
               inIO+=cpuP.getNB();

               cpuP.setPid(-1);//indica que no hay procesos en la cpu
               turnAround+=(simulationTime-cpuP.getArrTime());

               inCpu+=cpuP.getNRunsCPU();

               _ss.results[2][i++]=FinalTimes(cpuP.getAverageUsageTime()/cpuP.getNRunsCPU(),cpuP.getWaitingTime(),simulationTime-cpuP.getArrTime());

            }


            else if(eventToProcess==3)
            {//pasa de cpu a bloqueado
               //cpuP.setBlockingTime((double(int(dBlockingTime->getVal()*10.0+.5))/10.0));
               cpuP.setBlockingTime(dBlockingTime->getVal());
               cpuP.setRemainingTime(cpuP.getRemainingTime() - eventToProcessTime);
               cpuP.setCpuBurstTime(0.0);
               cpuP.setAverageUsageTime(cpuP.getAverageUsageTime() + eventToProcessTime);
               cpuP.setNB(cpuP.getNB() + 1);
               cpuP.setAverageIoTime(cpuP.getAverageIoTime() + cpuP.getBlockingTime());

               if(not blockingQueue->is_empty())
                  blockingQueue->decrementTime(eventToProcessTime,true);

               blockingQueue->put(cpuP);

               if(not readyQueue->is_empty())
                  readyQueue->decrementTime(eventToProcessTime,false);

               simulationTime += eventToProcessTime;//avanza el tiempo de simulacion

               writeEventInfo(simulationTime,eventToProcess,cpuP,_ss);
               cpuP.setPid(-1);
            }

            else if(eventToProcess==4)
            {//bloqueado a listo
               CompleteProcess tmp;
               if(not blockingQueue->is_empty())
               {
                  blockingQueue->decrementTime(eventToProcessTime,true);
                  tmp=blockingQueue->get();
                  tmp.setCpuBurstTime(0.0);
                  if(not readyQueue->is_empty())
                     readyQueue->decrementTime(eventToProcessTime,false);

                  tmp.setCpuBurstTime(dCpuBurstTime->getVal());
                  readyQueue->put(tmp);

               }

               if(cpuP.getPid()!=-1)
               {
                  cpuP.setRemainingTime(cpuP.getRemainingTime()-eventToProcessTime);
                  cpuP.setCpuBurstTime(cpuP.getCpuBurstTime()-eventToProcessTime);
                  cpuP.setAverageUsageTime(cpuP.getAverageUsageTime()+eventToProcessTime);
               }


               simulationTime += eventToProcessTime;//avanza el tiempo de simulacion

               writeEventInfo(simulationTime,eventToProcess,tmp,_ss);


               if(not readyQueue->is_empty() and
                     cpuP.getPid()!=-1 and
                     readyQueue->watch().getCpuBurstTime() < cpuP.getCpuBurstTime())
               {
                  cpuP.setCpuBurstTime(0.0);
               }

            }

            else
            {
               cpuP = readyQueue->get();
               cpuP.setNRunsCPU(cpuP.getNRunsCPU() + 1);
               writeEventInfo(simulationTime,eventToProcess,cpuP,_ss);
            }

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
            fS.maxUsedTime=_ss.results[2][0].averageUsedTime;//maxUsedTime
            fS.minUsedTime=_ss.results[2][0].averageUsedTime;//minUsedTime
            fS.maxWaitingTime=_ss.results[2][0].averageWaitingTime;//maxWaitingTime
            fS.minWaitingTime=_ss.results[2][0].averageWaitingTime;//minWaitingTime
            fS.maxTurnAround=_ss.results[2][0].turnAround;
            fS.minTurnAround=_ss.results[2][0].turnAround;
            fS.turnAround=turnAround/numOfProcesses;

            for (i=0; i<numOfProcesses; i++)
            {

               if(_ss.results[2][i].averageUsedTime>fS.maxUsedTime)//busca el maximo
                  fS.maxUsedTime=_ss.results[2][i].averageUsedTime;

               if(_ss.results[2][i].averageUsedTime<fS.minUsedTime)//busca el minimo
                  fS.minUsedTime=_ss.results[2][i].averageUsedTime;

               if(_ss.results[2][i].averageWaitingTime>fS.maxWaitingTime)//busca el maximo
                  fS.maxWaitingTime=_ss.results[2][i].averageWaitingTime;

               if(_ss.results[2][i].averageWaitingTime<fS.minWaitingTime)//busca el maximo
                  fS.minWaitingTime=_ss.results[2][i].averageWaitingTime;


               if((_ss.results[2][i].turnAround)>fS.maxTurnAround)
                  fS.maxTurnAround=_ss.results[2][i].turnAround;

               if((_ss.results[2][i].turnAround)<fS.minTurnAround)
                  fS.minTurnAround=_ss.results[2][i].turnAround;


               fS.sDUsedTime+=pow(_ss.results[2][i].averageUsedTime-fS.averageUsedTime,2);
               fS.sDWaitingTime+=pow(_ss.results[2][i].averageWaitingTime-fS.averageWaitingTime,2);
               fS.sDTurnAround+=pow(_ss.results[2][i].turnAround-fS.turnAround,2);

            }


            _ss.minTimes[2]=FinalTimes(fS.minUsedTime,fS.minWaitingTime,fS.minTurnAround);

            _ss.maxTimes[2]=FinalTimes(fS.maxUsedTime,fS.maxWaitingTime,fS.maxTurnAround);

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

            _ss.multiple_fin[2]=true;

         }
      }


      ~PSJF()
      {
         delete blockingQueue;
         delete readyQueue;
      }

};



/* PSJF_H */
# endif
