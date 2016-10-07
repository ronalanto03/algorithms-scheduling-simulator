/**
 * @file processGenerator.cpp
 * @brief Definicion de los metodos de la clase ProcessGenerator.
 * @author Cesar Vielma & Ronald Sulbaran.ronalanto03@hotmail.com
 * @date 13-08-2013
 */

#include<iostream>
#include<processGenerator.h>


ProcessGenerator::ProcessGenerator(int _n)
{
    baseProcesses=new BaseProcess[nProcs=_n];
}

ProcessGenerator::~ProcessGenerator()
{
    delete [] baseProcesses;
}


//genera los tiempos de llegada y los tiempos que necesita cada proceso para ejecutarse
void ProcessGenerator::generateTimes(Distribution * dArrTime, Distribution * dDurationTime)
    {
    baseProcesses[0].setArrTime(0);
//    baseProcesses[0].setDurationTime(double(int(dDurationTime->getVal()*10.0+.5))/10.0);
    baseProcesses[0].setDurationTime(dDurationTime->getVal());

    baseProcesses[0].setPid(1);
   for(int i=1; i<nProcs; i++)
   {
        baseProcesses[i].setArrTime((baseProcesses[i-1].getArrTime()+dArrTime->getVal()));
       // baseProcesses[i].setArrTime(double(int(baseProcesses[i].getArrTime()*10.0+.5))/10.0);
        baseProcesses[i].setDurationTime(dDurationTime->getVal());
//        baseProcesses[i].setDurationTime(double(int(dDurationTime->getVal()*10.0+.5))/10.0);
        baseProcesses[i].setPid(i+1);
	}

}
