/**
  * @file threadsocket.cpp
  * @brief Definicion de los metodos de la clase ThreadSocket
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */
#include "threadsocket.h"
#include <iostream>
#include <graphswindow.h>

#include <unistd.h>


ThreadSocket::ThreadSocket(QObject* parent,QLabel * l,PaintWindow* pw, QHBoxLayout *hl,DataSocket1 *ds, GraphsWindow *gw,QString n):
QThread(parent)
{
    this->label = l;
    this->paintWindow = pw;
    this->graphsWindow=gw;
    this->layout=hl;
    this->dataSocket=ds;
    this->iconName=n;

    this->fs=0;
    this->socketId=0;

    if(pw!=NULL){
    connect(paintWindow, SIGNAL(closed()),this, SLOT(closedWindow()));
    connect(paintWindow, SIGNAL(nextEventSignal()),this, SLOT(nextEvent()));
    }

}

ThreadSocket::~ThreadSocket(){
}

void ThreadSocket::setConnected(bool c){
    this->connected=c;
}


int ThreadSocket::setConnection(char *ip,int port){

    struct sockaddr_in nombre;
    struct hostent* hostServidor;

    connected=false;

    if ((socketId = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("abriendo socket");
        return 1;
    }

if ((hostServidor=gethostbyname(ip))==NULL){
        //if ((hostServidor=gethostbyname("127.0.0.1"))==NULL){
        perror("conectando al servidor");
        return 1;
    }

    bzero(&(nombre),sizeof(struct sockaddr));
    nombre.sin_family = AF_INET;
    nombre.sin_port = htons(port);
    nombre.sin_addr = *((struct in_addr *)hostServidor->h_addr);

    if (::connect(socketId, (struct sockaddr*)&nombre, sizeof(struct sockaddr)) < 0) {
        perror("en el conect");
        return 1;
    }
    connected=true;
    return 0;

}

void ThreadSocket::closedWindow(){

    if (connected)
        finishConnection(-1);

}

void ThreadSocket::abort(){

    connected=false;
    eDataSend.event=(-1);
    write(socketId,(char*)(&eDataSend), sizeof(struct EventData));
    ::close(socketId);
    if(fs==3){
        paintWindow->close();
        fs=0;
    }

}


void ThreadSocket::startSimulation(){

    connected=true;
    eDataSend.event=0;
    fs=3;
    write(socketId,(char*)(dataSocket), sizeof(struct DataSocket1));
    paintWindow->settings();

}

void ThreadSocket::nextEvent(){

    if(connected){
         read(socketId,(char*)(&eDataRecive), sizeof(struct EventData));
        if(eDataRecive.event==6){

            paintWindow->setFinished();
            finishConnection(1);
        }

        else{
            paintWindow->setEvent(eDataRecive);
            write(socketId,(char*)(&eDataSend), sizeof(struct EventData));
        }
    }
}

void ThreadSocket::finishConnection(int value){

    fs=value;
    eDataSend.event=value;
    write(socketId,(char*)(&eDataSend), sizeof(struct EventData));
    emit finishedConnection();
    ::close(socketId);
    connected=false;
}

void ThreadSocket::getGrahpsData(){

    std::ofstream filew;
    std::ofstream fileu;
    std::ofstream filet;

    QString nfilew =iconName+"WaitingTime"+".log";
    QString nfileu =iconName+"UsedTime"+".log";
    QString nfilet =iconName+"TurnAroundTime"+".log";
    FinalSocket fs;
    bool find=false;
    double min;
    UiProcess *p;

    filew.open(nfilew.toStdString().c_str());
    fileu.open(nfileu.toStdString().c_str());
    filet.open(nfilet.toStdString().c_str());
    connected=true;
    eDataSend.event=0;
    write(socketId,(char*)(dataSocket), sizeof(struct DataSocket1));

    while(connected){

         read(socketId,(char*)(&eDataRecive), sizeof(struct EventData));
        if(eDataRecive.event==6){
        write(socketId,(char*)(&eDataSend), sizeof(struct EventData));
        read(socketId,(char*)(&fs), sizeof(struct FinalSocket));
        break;
        }

        else{
            if(eDataRecive.event==2){
                if(!find){
                    min=eDataRecive.time;
                    find=true;
                }
                filew<<eDataRecive.pid<<" "<<eDataRecive.time<<" "<<eDataRecive.waitingTime<<"\n";
                fileu<<eDataRecive.pid<<" "<<eDataRecive.time<<" "<<eDataRecive.usedTime/eDataRecive.nT<<"\n";
                filet<<eDataRecive.pid<<" "<<eDataRecive.time<<" "<<eDataRecive.time-eDataRecive.arrTime<<"\n";
                p=new UiProcess(0);
                p->seteData(eDataRecive);
                graphsWindow->queue->insertProcess(p);
        }
            if(write(socketId,(char*)(&eDataSend), sizeof(struct EventData))<0)
                break;
        }
    }

    if(connected){

        filew.close();
        fileu.close();
        filet.close();

        graphsWindow->gPw.setParams(graphsWindow->iconName+"WaitingTime",fs.maxWaitingTime,fs.minWaitingTime,fs.averageWaitingTime,\
                       fs.sDWaitingTime);
        graphsWindow->gPu.setParams(graphsWindow->iconName+"UsedTime",fs.maxUsedTime,fs.minUsedTime,fs.averageUsedTime,\
                        fs.sDUsedTime);
        graphsWindow->gPt.setParams(graphsWindow->iconName+"TurnAroundTime",fs.maxTurnAround,fs.minTurnAround,fs.turnAround,\
                        fs.sDTurnAround);
QString aux(iconName.toStdString().substr(0,3).c_str());
        graphsWindow->generalP.setParams(fs.simulationTime,fs.throughPut,fs.inCPU,fs.inIO,fs.cpuUtil,fs.IOAvgTime,\
                                         fs.averageUsedTime,dataSocket->n+1,min,graphsWindow->iconName,aux);
        finishConnection(0);
    }
}

void ThreadSocket::run(){

    getGrahpsData();
}
