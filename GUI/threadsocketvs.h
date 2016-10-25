/**
  * @file threadsocketVs.h
  * @brief Declaracion de la clase ThreadSocketVs
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */
#ifndef THREADSOCKETVS_H
#define THREADSOCKETVS_H

#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <QThread>
#include <datawindow.h>
#include <DataSocket1.h>
#include <eventData.h>
#include <threadsocket.h>
#include <paintwindow.h>
/**
  * @class ThreadSocketVs
  * Clase que gestiona la comunicacion por sockets modo vs
  * Hereda de QThread
  */
class ThreadSocketVs : public QThread
{
    Q_OBJECT
public:
    ThreadSocketVs(QObject *parent,DataWindow* dw);

    int fs; /**< Guarda el estado de finalizado*/

    int socketId;/**< Guarda el id del socket*/

    ThreadSocket *threads[4];

    DataWindow *dataWindow;/**< Puntero a la ventana de graficos*/

    bool connected;/**< Guarda el estado de conectado*/

    GraphsWindow *gw[4]/**< Guarda parametros de la simulacion*/;

    PaintWindow *pw[4]/**< Guarda parametros de la simulacion*/;

    EventData eDataSend;/**< Estuctura con la informacion a enviar*/

    EventData eDataRecive;/**< Estuctura con la informacion a recibir*/



    void run();


    /**
     * @brief Crea la coneccion con el socket
     * @param port id del puerto a conectarse
     * @return 0:sin errores 1:error(es) en la coneccion
     */
    int setConnection(int port);

    /**
     * @brief Empieza la transferencia de datos
     */
    void startSimulation();

    /**
     * @brief aborta la simulacion
     */
    void abort();

    
signals:

    /**
      * @brief Se;al emitida cuando finaliza la coneccion
      */
    void finishedConnection();
    
public slots:

    /**
      * @brief Cierra el socket si la ventana de simulacion se cierra
      */
    void closedWindow();


private:

    /**
      * @brief Obtiene los valores para generar las graficas
      */
    void getGrahpsData();

    /**
      * @brief Finaliza la coneccion con el socket
      * @param value tipo de finalizacion
      */
    void finishConnection(int value);
    
};

#endif // THREADSOCKETVS_H
