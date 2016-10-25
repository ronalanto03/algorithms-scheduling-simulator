/**
  * @file uiprocess.h
  * @brief Declaracion de la clase UiProcess.
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */
#ifndef UIPROCESS_H
#define UIPROCESS_H
#include <QObject>
#include <QString>
#include <eventData.h>

/**
  * @class UiProcess
  * Clase para almacenar un proceso en la GUI
  * Herede de QObject
  */

class UiProcess: public QObject{

    Q_OBJECT
public:

		// Constructors/Destructors

		/**
		 * Empty Constructor
		 */
    UiProcess (QObject*p ):QObject(p){

            pid=-1;
            arrTime=0;
            durationTime=0;
            cpuBurstTime=0;
            remainingTime=0;
            blockingTime=0;
            waitingTime=0;
            usedTime=0;
            endingTime=0;

        }

		/**
		 * Empty Destructor
		 */
        ~UiProcess ( ){


        }


private:


        int quantum;/**< quantum para el RR*/

        int event;/**< tipo de evento */

        int pid;/**<  Id del proceso */

        double arrTime;/**<  Tiempo de llegada del proceso */

        double durationTime;/**< Tiempo de duracion total del proceso */

        double cpuBurstTime;/**< Tiempo de rafaga */

        double remainingTime;/**< Tiempo que le falta al proceso para terminar su ejecucion */

        double blockingTime;/**< Tiempo de bloqueo del proceso */

        double waitingTime;/**< Tiempo de espera del proceso. */

        double usedTime;/**< Tiempo de Uso del proceso */

        double endingTime;/**<  Tiempo de finalizacion del proceso. */

        int nT;/**< Numero de veces que el proceso asociado al evento se ha montado en cpu*/

        int nB;/**< Numero de veces que el proceso asociado al evento ha bajado a bloqueado*/

        double allBlockingTime;/**< Total de tiempo de blockeo de un proceso */

public:

		/**
         * @brief Asigna el pid
         * @param new_var nuevo valor de pid
		 */
		void setPid ( int new_var )		 {
						pid = new_var;
		}


		/**
         * @brief Obtiene el pid
         * @return pid del proceso
		 */
		int getPid ( )		 {
				return pid;
		}

		/**
         * @brief Asigna el tiempo de llegada
         * @param new_var nuevo valor de arrTime
		 */
		void setArrTime ( double new_var )		 {
						arrTime = new_var;
		}

		/**
         * @brief Obtiene el tiempo de llegada
         * @return tiempo de llegada del proceso
		 */
		double getArrTime ( )		 {
				return arrTime;
		}

		/**
         * @brief Asigna el tiempo de duracion
         * @param new_var nuevo valor de durationTime
		 */
		void setDurationTime ( double new_var )		 {
						durationTime = new_var;
		}

		/**
         * @brief Obtiene el tiempo de duracion
         * @return tiempo de duracion del proceso
		 */
		double getDurationTime ( )		 {
                return durationTime;
		}

        /**
         * @brief asigna el tiempo de rafaga del cpu
         * @param new_var nuevo valor para cpuBurstTime
         */
        void setCpuBurstTime ( double new_var )		 {
                        cpuBurstTime = new_var;
        }

        /**
         * @brief Obtiene el tiempo de rafaga del cpu
         * @return tiempo de rafaga del cpu
         */
        double getCpuBurstTime ( )		 {
                return cpuBurstTime;
        }

        /**
         * @brief Asigna el valor del tiempo restante
         * @param new_var nuevo valor para remainingTime
         */
        void setRemainingTime ( double new_var )		 {
                        remainingTime = new_var;
        }

        /**
         * @brief Obtiene el valor del tiempo restante
         * @return tiempo restante
         */
        double getRemainingTime ( )		 {
                return remainingTime;
        }

        /**
         * @brief Asigna el tiempo de bloqueo del proceso
         * @param new_var nuevo valor para blockingTime
         */
        void setBlockingTime ( double new_var )		 {
                        blockingTime = new_var;
        }

        /**
         * @brief Obtiene el valor de blockingTime
         * @return tiempo de bloqueo
         */
        double getBlockingTime ( )		 {
                return blockingTime;
        }

        /**
         * @brief Asigna el tiempo de espera
         * @param new_var nuevo valor para waitingTime
         */
        void setWaitingTime ( double new_var )		 {
                        waitingTime = new_var;
        }

        /**
         * @brief Obtiene el valor del tiempo de espera
         * @return tiempo de espera
         */
        double getWaitingTime ( )		 {
                return waitingTime;
        }

        /**
         * @brief Asigna el tiempo de uso
         * @param new_var nuevo valor para usedTime
         */
        void setUsedTime ( double new_var )		 {
                        usedTime = new_var;
        }
        /**
         * @brief Obtiene el valor del tiempo de uso
         * @return tiempo de uso
         */
        double getUsedTime ( )		 {
                return usedTime;
        }

        /**
         * @brief Obtiene el valor del tiempo de finalizacion
         * @return tiempo de finalizacion
         */
        double getEndingTime ( )		 {
                return endingTime;
        }

        /**
         * @brief Asigna el tiempo de finalizacion
         * @param new_var nuevo valor para endingTime
         */
        void setEndingTime ( double new_var )		 {
                        endingTime = new_var;
        }

        /**
         * @brief Asigna el valor del numero de entradas al cpu
         * @param new_var nuevo valor para nT
         */
        void setnT ( double new_var )		 {
                        nT = new_var;
        }

        /**
         * @brief Obtiene el valor del numero de entradas al cpu
         * @return numero de entradas al cpu
         */
        int getnT ( )		 {
                return nT;
        }

        /**
         * @brief Asigna el valor de entradas a bloqueo
         * @param new_var nuevo valor para nB
         */
        void setnB ( double new_var )		 {
                        nB = new_var;
        }

        /**
         * @brief Obtiene el valor del numero de entradas a bloqueo
         * @return numero de entradas a bloqueo
         */
        int getnB ( )		 {
                return nB;
        }

        /**
         * @brief Asigna el valor del tiempo total de bloqueo
         * @param new_var nuevo valor para allBlockingTime
         */
        void setallBlockingTime ( double new_var )		 {
                        allBlockingTime = new_var;
        }

        /**
         * @brief Obtiene el valor del tiempo total de bloqueo
         * @return total de tiempo de bloqueo
         */
        double getallBlockingTime ( )		 {
                return allBlockingTime;
        }

        /**
         * @brief Asigna los valores de un evento al proceso
         * @param new_var evento
         */
        void seteData(EventData eD){

            event=eD.event;
            pid=eD.pid;
            endingTime=eD.time;
            arrTime=eD.arrTime;
            durationTime=eD.durationTime;
            remainingTime=eD.remainingTime;
            waitingTime=eD.waitingTime;
            cpuBurstTime=eD.cpuBurstTime;
            blockingTime=eD.blockingTime;
            quantum=eD.quantum;
            usedTime=eD.usedTime;
            nT=eD.nT;
            nB=eD.nB;
            allBlockingTime=eD.allBlockingTime;
        }

        /**
         * @brief Asigna los valores de un proceso al proceso
         * @param new_var puntero al proceso
         */
        void setProcess(UiProcess* eD){

            event=eD->event;
            pid=eD->pid;
            endingTime=eD->endingTime;
            arrTime=eD->arrTime;
            durationTime=eD->durationTime;
            remainingTime=eD->remainingTime;
            waitingTime=eD->waitingTime;
            cpuBurstTime=eD->cpuBurstTime;
            blockingTime=eD->blockingTime;
            quantum=eD->quantum;
            usedTime=eD->usedTime;
            nT=eD->nT;
            nB=eD->nB;
            allBlockingTime=eD->allBlockingTime;
        }
        /**
         * @brief Asigna los valores por defecto del proceso
         */
        void setDefault(){

            event=-2;
            pid=-1;
            endingTime=0;
            arrTime=0;
            durationTime=0;
            remainingTime=0;
            waitingTime=0;
            cpuBurstTime=0;
            blockingTime=0;
            quantum=0;
            usedTime=0;
            nT=0;
            nB=0;
            allBlockingTime=0;
        }

};


struct GraphParams{

    GraphParams(){
        data="";
        max=0;
        min=0;
        avg=0;
        des=0;


    }

    void setParams(QString d,double mx,double mn,double av,double ds){
        data=d;
        max=mx;
        min=mn;
        avg=av;
        des=ds;
    }

    void setParams(GraphParams g){
        data=g.data;
        max=g.max;
        min=g.min;
        avg=g.avg;
        des=g.des;

    }

    QString data;
    double max;
    double min;
    double avg;
    double des;

};

struct GeneralParams{

    GeneralParams(){

        time=0;
        throughput=0;
        cpuIn=0;
        ioIn=0;
        cpuu=0;
        ioAvgtime==0;
        nPro=0;
        algname="";
        path="";

    }

    void setParams(double t,double th,double ci,double ii,double cu,double ioa,double usa,double np,double m, QString n,QString ph){

        time=t;
        throughput=th;
        cpuIn=ci;
        ioIn=ii;
        cpuu=cu;
        ioAvgtime=ioa;
        usAvgtime=usa;
        nPro=np;
        min =m;
        algname=n;
        path=ph;

    }

    void setParams(GeneralParams g){
        time=g.time;
        throughput=g.throughput;
        cpuIn=g.cpuIn;
        ioIn=g.ioIn;
        cpuu=g.cpuu;
        ioAvgtime=g.ioAvgtime;
        usAvgtime=g.usAvgtime;
        nPro=g.nPro;
        min =g.min;
        algname=g.algname;
        path=g.path;

    }

    double time;
    double throughput;
    double cpuIn;
    double ioIn;
    double cpuu;
    double ioAvgtime;
    double usAvgtime;
    double nPro;
    double min;
    QString algname;
    QString path;

    };



#endif // UiProcess_H
