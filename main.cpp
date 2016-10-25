/**
  * @file main.cpp
  * @brief programa principal
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */

/*Para Correr ejecutar el servidor con ./simulator port y el ./SimProRC ip port
  */
#include <QApplication>
#include "mainwindow.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sstream>
#include <unistd.h> //To call close(int)
#include <simulator.h>

using namespace std;



void *startServer(void *);

int main(int argc, char *argv[]){

    int port;
//    system("rm -r sf");
//    system("rm -r vs");
//    system("mkdir sf");
//    system("mkdir vs");

    port =31010;

    pthread_t serverThread;
    QApplication a(argc, argv);

    pthread_create(&serverThread, NULL, startServer, NULL);

    MainWindow w("localhost",31010);
    /*aqui va la deqclaracion del hilo y su invocacion*/


    w.show();
    a.exec();
    return 0;


}

void* startServer(void* p)
{
   Simulator sim;
   sim.simulate(31010);
   return NULL;
}
