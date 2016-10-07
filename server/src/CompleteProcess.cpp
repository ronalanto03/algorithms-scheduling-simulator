/**
 * @file CompleteProcess.cpp
 * @brief Definicion de los metodos de la clase CompleteProcess.
 * @author Cesar Vielma & Ronald Sulbaran.ronalanto03@hotmail.com
 * @date 01-07-2013
 */

#include "CompleteProcess.h"

CompleteProcess::CompleteProcess ( ):cpuBurstTime(0.0),blockingTime(0.0),waitingTime(0.0)
{
}


CompleteProcess::CompleteProcess ( BaseProcess & p )
{
	BaseProcess::setPid( p.getPid() );
	BaseProcess::setArrTime( p.getArrTime() );
	BaseProcess::setDurationTime( p.getDurationTime() );
	setRemainingTime( p.getDurationTime() );
    waitingTime=0.0;
    nRunsCPU=0;
    averageUsageTime=0.0;
    cpuBurstTime=0.0;
    blockingTime=0.0;
    quantum=0.0;
    nB=0;
    averageIoTime=0.0;
}


CompleteProcess & CompleteProcess::operator =(CompleteProcess p)
{
    setPid(p.getPid());
    setArrTime(p.getArrTime());
    setDurationTime(p.getDurationTime());
    setCpuBurstTime(p.getCpuBurstTime());
    setBlockingTime(p.getBlockingTime());
    setWaitingTime(p.getWaitingTime());
    setRemainingTime(p.getRemainingTime());
    nRunsCPU=p.nRunsCPU;
    averageUsageTime=p.averageUsageTime;
    quantum=p.quantum;
    nB=p.nB;
    averageIoTime=p.averageIoTime;
    return *this;
}


CompleteProcess::~CompleteProcess ( )
{
}
