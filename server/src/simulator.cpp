#include"../include/simulator.h"
#include<iostream>
#include"../include/eventData.h"
#include"../include/fcfs.h"
#include"../include/sjf.h"
#include"../include/psjf.h"
#include"../include/rr.h"
#include"../include/processGenerator.h"
#include"../include/DataSocket1.h"
#include"../include/multSimData.h"
/**
 * This will handle connection for each client
 * */





//numero de algoritmos que se van ejecutar
void * mulAlgorithmFunct(void * _n)
{
   (void)_n;//unused parameter, @TODO this should be removed in the future

   bool con=true;

   sleep(1);

   do
   {
      con = true;
      for(int i = 0; i < 4; ++i)
      {
         if(sS.multiple_ini[i])
         {
            con = con and (sS.multiple_ini[i] != sS.multiple_fin[i]);
            std::cerr<<i<<std::endl;
         }
      }
      if(!sS.connected)
      {
         return NULL;
      }

      std::cerr<<"Esperando ...\n";
   }
   while(con);

   FinalTimes min, max;//tiempo minimo

   int i;
   for( i = 0; i <  4; ++i)
   {
      if(sS.multiple_fin[i]){
         min = sS.minTimes[i];
         max = sS.maxTimes[i];
      }
   }

   //    for( i=0;i<4;++i){
   //        if(sS.minTimes[i].averageUsedTime<min.averageUsedTime)
   //            min.averageUsedTime=sS.minTimes[i].averageUsedTime;

   //        if(sS.minTimes[i].averageWaitingTime<min.averageWaitingTime)
   //            min.averageWaitingTime=sS.minTimes[i].averageWaitingTime;

   //        if(sS.minTimes[i].turnAround<min.turnAround)
   //            min.turnAround=sS.minTimes[i].turnAround;

   //        if(sS.maxTimes[i].averageUsedTime>max.averageUsedTime)
   //            max.averageUsedTime=sS.maxTimes[i].averageUsedTime;

   //        if(sS.maxTimes[i].averageWaitingTime"max.averageWaitingTime)
   //            max.averageWaitingTime=sS.maxTimes[i].averageWaitingTime;

   //        if(sS.maxTimes[i].turnAround<max.turnAround)
   //            max.turnAround=sS.maxTimes[i].turnAround;

   //    }



   //hacer el procesamiento de la division de clases aqui

   MutlSimData mSD;

   for( int k = 0; k < 4;  k++)
   {
      //        if(sS.multiple_ini[k]){
      mSD.usedTimeAmplitude=max.averageUsedTime/sS.n;
      mSD.waitingTimeAmplitude=max.averageWaitingTime/sS.n;
      mSD.turnAroundTimeAmplitude=max.turnAround/sS.n;

      std::cerr<<"Amplitud used time "<<mSD.usedTimeAmplitude<<std::endl;
      std::cerr<<"Amplitud waiting time "<<mSD.waitingTimeAmplitude<<std::endl;
      std::cerr<<"Amplitud turnAround time "<<mSD.turnAroundTimeAmplitude<<std::endl;

      for( i = 0; i < sS.n; ++i)
      {
         for( int j = 1; j <= 10; ++j)
         {
            if(sS.results[k][i].averageUsedTime >= mSD.usedTimeAmplitude*(j-1)
                  and sS.results[k][i].averageUsedTime < mSD.usedTimeAmplitude*j)
            {
               mSD.usedTimeClasses[j-1]++;
            }

            if(sS.results[k][i].averageWaitingTime >= mSD.waitingTimeAmplitude*(j-1)
                  and sS.results[k][i].averageWaitingTime < mSD.waitingTimeAmplitude*j)
            {
               mSD.waitingTimeClasses[j-1]++;
            }

            if(sS.results[k][i].turnAround >= mSD.turnAroundTimeAmplitude*(j-1)
                  and sS.results[k][i].turnAround < mSD.turnAroundTimeAmplitude*j)
            {
               mSD.turnAroundTimeClasses[j-1]++;
            }
         }
      }

      mSD.algorithm = k + 1;


      int p;
      int tmpRetVal = write(sS.t, (char *)(&mSD), sizeof(struct MutlSimData));
      tmpRetVal = read(sS.t, (char *)(&p), sizeof(int));
      (void)tmpRetVal;

      std::cerr<<"Recibido "<<p<<std::endl;
   }

   for( i = 0; i < 4; ++i)
   {
      sS.multiple_ini[i]=false;
      sS.multiple_fin[i]=false;
   }
   close(sS.t);
   return NULL;
}

void * connection_handler(void *socket_desc)
{

   int t = *(int*)socket_desc;
   std::cout<<"Entro al thread "<<t<<std::endl;
   struct DataSocket1 dataSocket1;
   struct ThreapParamM tPM;//para guardar el numero de simulaciones y el numero del socket
   int tmpRetVal = read(t, (char *)(&dataSocket1), sizeof(struct DataSocket1));
   (void)tmpRetVal;
   pthread_t multipleAlgorithm;


   std::cout<<"Configuraciones:"<<std::endl;
   std::cout<<"Algorithm: "<<dataSocket1.algorithm<<std::endl;
   std::cout<<"N: "<<dataSocket1.n<<std::endl<<std::endl;


   if(dataSocket1.algorithm==-1)
   {
      std::cout<<"Terminating the server\n";
      close(__ss);
      return NULL;
   }

   //    if(dataSocket1.algorithm==1){
   sS.results[0]=new FinalTimes[dataSocket1.n];
   //    }
   //    else if(dataSocket1.algorithm==2){
   sS.results[1]=new FinalTimes[dataSocket1.n];
   //
   //    }
   //    else if(dataSocket1.algorithm==3){
   sS.results[2]=new FinalTimes[dataSocket1.n];

   //    }
   //    else if(dataSocket1.algorithm==4){
   sS.results[3]=new FinalTimes[dataSocket1.n];




   if(dataSocket1.algorithm >= 5)
   {
      sS.connected = true;
      sS.nn = dataSocket1.algorithm-4;
      sS.n = dataSocket1.n;
      sS.t = t;

      if( pthread_create( &multipleAlgorithm, NULL ,  mulAlgorithmFunct , (void*) &tPM) < 0)
      {
         perror("could not create thread");
         return NULL;
      }
      return NULL;

   }



   if(sS.nn > 0)
   {
      if(dataSocket1.algorithm == 1)
      {
         sS.multiple_ini[0] = true;
      }
      else if(dataSocket1.algorithm == 2)
      {
         sS.multiple_ini[1] = true;
      }
      else if(dataSocket1.algorithm == 3)
      {
         sS.multiple_ini[2] = true;
      }
      else if(dataSocket1.algorithm == 4)
      {
         sS.multiple_ini[3] = true;

      }
      sS.nn--;
   }

   Distribution* dArrTime = NULL;
   Distribution* dDurationTime = NULL;

   Distribution* dCpuBurstTime = NULL;
   Distribution* dBlockingTime = NULL;

   ProcessGenerator p(dataSocket1.n);



   //seleccionar la distribucion para el tiempo de llegada
   //1 constante,2 uniforme,3 exponencial,4 normal
   switch(dataSocket1.arrTimeD.t)
   {
      case 1:
      {
         dArrTime=new Distribution(Distribution::constant,dataSocket1.arrTimeD.left,0,dataSocket1.seed);
         break;
      }

      case 2:
      {
         dArrTime=new Distribution(Distribution::uniform,dataSocket1.arrTimeD.left,dataSocket1.arrTimeD.right,dataSocket1.seed);
         break;
      }

      case 3:
      {
         dArrTime=new Distribution(Distribution::exponential,dataSocket1.arrTimeD.left,dataSocket1.arrTimeD.right,dataSocket1.seed);
         break;
      }

      case 4:
      {
         dArrTime=new Distribution(Distribution::normal,dataSocket1.arrTimeD.left,dataSocket1.arrTimeD.right,dataSocket1.seed);
         break;
      }
   }


   //seleccionar la distribucion para el tiempo de duracion
   //1 constante,2 uniforme,3 exponencial,4 normal
   switch(dataSocket1.durationTimeD.t)
   {
      case 1:
      {
         dDurationTime=new Distribution(Distribution::constant,dataSocket1.durationTimeD.left,0,dataSocket1.seed);
         break;
      }

      case 2:
      {
         dDurationTime=new Distribution(Distribution::uniform,dataSocket1.durationTimeD.left,dataSocket1.durationTimeD.right,dataSocket1.seed);
         break;
      }

      case 3:
      {
         dDurationTime=new Distribution(Distribution::exponential,dataSocket1.durationTimeD.left,dataSocket1.durationTimeD.right,dataSocket1.seed);
         break;
      }

      case 4:
      {
         dDurationTime=new Distribution(Distribution::normal,dataSocket1.durationTimeD.left,dataSocket1.durationTimeD.right,dataSocket1.seed);
         break;
      }
   }


   //seleccionar la distribucion para el tiempo de bloqueo
   //1 constante,2 uniforme,3 exponencial,4 normal
   switch(dataSocket1.blockingTimeD.t)
   {
      case 1:
      {
         dBlockingTime=new Distribution(Distribution::constant,dataSocket1.blockingTimeD.left,dataSocket1.blockingTimeD.right,dataSocket1.seed);
         break;
      }

      case 2:
      {
         dBlockingTime=new Distribution(Distribution::uniform,dataSocket1.blockingTimeD.left,dataSocket1.blockingTimeD.right,dataSocket1.seed);
         break;
      }

      case 3:
      {
         dBlockingTime=new Distribution(Distribution::exponential,dataSocket1.blockingTimeD.left,dataSocket1.blockingTimeD.right,dataSocket1.seed);
         break;
      }

      case 4:
      {
         dBlockingTime=new Distribution(Distribution::normal,dataSocket1.blockingTimeD.left,dataSocket1.blockingTimeD.right,dataSocket1.seed);
         break;
      }
   }



   //seleccionar la distribucion para el tiempo de rafaga
   //1 constante,2 uniforme,3 exponencial,4 normal
   switch(dataSocket1.cpuBusrtTimeD.t){
      case 1:
      {
         dCpuBurstTime=new Distribution(Distribution::constant,dataSocket1.cpuBusrtTimeD.left,0,dataSocket1.seed);
         break;
      }

      case 2:
      {
         dCpuBurstTime=new Distribution(Distribution::uniform,dataSocket1.cpuBusrtTimeD.left,dataSocket1.cpuBusrtTimeD.right,dataSocket1.seed);
         break;
      }

      case 3:
      {
         dCpuBurstTime=new Distribution(Distribution::exponential,dataSocket1.cpuBusrtTimeD.left,dataSocket1.cpuBusrtTimeD.right,dataSocket1.seed);
         break;
      }

      case 4:
      {
         dCpuBurstTime=new Distribution(Distribution::normal,dataSocket1.cpuBusrtTimeD.left,dataSocket1.cpuBusrtTimeD.right,dataSocket1.seed);
         break;
      }
   }



   p.generateTimes(dArrTime,dDurationTime);

   switch(dataSocket1.algorithm)
   {
      case Simulator::ST_FCFS:
      {
         FCFS ff(p.getBaseProcess(), dataSocket1.n,t);
         ff.simulate(dCpuBurstTime, dBlockingTime,sS);
         break;
      }

      case Simulator::ST_SJF:
      {
         SJF sf(p.getBaseProcess(),dataSocket1.n,t);
         sf.simulate(dCpuBurstTime, dBlockingTime,sS);
         break;
      }

      case Simulator::ST_PSJF:
      {
         PSJF pf(p.getBaseProcess(),dataSocket1.n,t);
         pf.simulate(dCpuBurstTime,dBlockingTime,sS);
         break;
      }

      case Simulator::ST_RR:
      {
         RR rf(p.getBaseProcess(),dataSocket1.n,dataSocket1.quantum,t);
         rf.simulate(dCpuBurstTime,dBlockingTime,sS);
         break;
      }


   }
   delete dArrTime;
   delete dDurationTime;
   delete dCpuBurstTime;
   delete dBlockingTime;
   close(t);

   std::cout<<"Fin thread "<<t<<std::endl;

   return NULL;
}

Simulator::Simulator()
{

}


void Simulator::simulate(int _s)
{

   nombreLocal.sin_family = AF_INET;//dominio de direcciones
   nombreLocal.sin_port = htons(_s);//host to network , invertir el orden del flujo de datos
   nombreLocal.sin_addr.s_addr = INADDR_ANY;//de quien voy a fe

   //Construir un socket
   //dominio //tipodeSock
   if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
   {
      perror("abriendo socket");//resuelve errores de sistema
      return;
   }

   //bincular la direccion de mi puerto con el socket
   if (bind(s, (struct sockaddr *)&nombreLocal,  sizeof(nombreLocal)) < 0)
   {
      perror("haciendo el bind");
      return;
   }
   //prepara la cola
   if (listen(s, 5 ) < 0 )
   {
      perror("en el listen");
      return;
   }

   pthread_t sThread;
   __ss=s;

   do{


      tamNombreRemoto = sizeof(struct sockaddr_in);
      //atiende un cliente por un nuevo socket
      if ( ( t = accept(s, &nombreRemoto, (socklen_t *)&tamNombreRemoto)) < 0)
      {
         perror("en el accept");
         printf(" t = %d \n", t );
         return;

      }


      if( pthread_create( &sThread, NULL ,  connection_handler , (void*) &t) < 0)
      {
         perror("could not create thread");
         return;
      }


   } while ( 1 );

}


Simulator::~Simulator(){

   if(s>=0)
      close(s);
}
