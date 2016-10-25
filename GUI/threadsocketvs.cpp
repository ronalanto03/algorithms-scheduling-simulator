/**
  * @file threadsocketvs.cpp
  * @brief Definicion de los metodos de la clase ThreadSocketVs
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */

#include "threadsocketvs.h"

#include <unistd.h>

ThreadSocketVs::ThreadSocketVs(QObject *parent,DataWindow *dw):
    QThread(parent)
{
    this->dataWindow=dw;

    for(int i=0;i<4;i++){
        gw[i] = NULL;
        threads[i]=NULL;
    }

    connect(dataWindow, SIGNAL(closed()),this, SLOT(closedWindow()));
}

int ThreadSocketVs::setConnection(int port){

    struct sockaddr_in nombre;
    struct hostent* hostServidor;

    connected=false;

    if ((socketId = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("abriendo socket");
        return 1;
    }

    if ((hostServidor=gethostbyname("10.11.44.118"))==NULL){
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

void ThreadSocketVs::abort(){


    for(int i=0;i<4;i++){
        if(dataWindow->enabled[i]){
            threads[i]->abort();
        }
     }
    eDataSend.event=(-1);
    ::close(socketId);
    terminate();
}

void ThreadSocketVs::finishConnection(int value){

    fs=value;
    eDataSend.event=value;
    write(socketId,(char*)(&eDataSend), sizeof(struct EventData));
    emit finishedConnection();
    ::close(socketId);
    connected=false;
}


void ThreadSocketVs::closedWindow(){

    if (connected)
        finishConnection(-1);

}

void ThreadSocketVs::run(){

startSimulation();

}

void ThreadSocketVs::startSimulation(){

    fs=1;
    DataSocket1 dataSocket(0);
    dataSocket.n=3;
    int j=0;
    int k;
    dataSocket.algorithm=4+dataWindow->num;
    write(socketId,(char*)(&dataSocket), sizeof(struct DataSocket1));

    for(int i=0;i<4;i++){
        if(dataWindow->enabled[i]){

            if(threads[i]!=NULL){
                delete threads[i];
                threads[i]=NULL;

            }

            threads[i]=new ThreadSocket(NULL,NULL,NULL,NULL,NULL,gw[i],"vs/"+dataWindow->names[i]);
            threads[i]->dataSocket=dataWindow->dataSocket;
            threads[i]->dataSocket->algorithm=i+1;
            threads[i]->setConnection("",31059);
            threads[i]->run();
            msleep(100);
        }
    }

    for(int i=0;i<4;i++){
        if(dataWindow->enabled[i]){

            read(socketId,(char*)&dataWindow->msd[i], sizeof(struct MutlSimData));

            std::cout<<dataWindow->msd[i].turnAroundTimeAmplitude<<"\n";
            std::cout<<dataWindow->msd[i].usedTimeAmplitude<<"\n";
            std::cout<<dataWindow->msd[i].waitingTimeAmplitude<<"\n";
            std::cout<<"SOCKET "<<socketId<<"\n";
            k=44433;
            write(socketId,(char*)&k, sizeof(int));

            dataWindow->graphpw[i].setParams(gw[i]->gPw);
            dataWindow->graphpu[i].setParams(gw[i]->gPu);
            dataWindow->graphpt[i].setParams(gw[i]->gPt);
            dataWindow->generalp[i].setParams(gw[i]->generalP);
        }
    }
        finishConnection(0);

}
