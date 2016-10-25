/**
  * @file threadsocket.h
  * @brief Declaracion de la clase ThreadSocket
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */
#ifndef THREADSOCKET_H
#define THREADSOCKET_H
#include <QThread>
#include <stdio.h>
#include <QString>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <QLabel>
#include <QPixmap>
#include <paintwindow.h>
#include <eventData.h>
#include <DataSocket1.h>
#include <QHBoxLayout>
#include <fstream>
#include <graphswindow.h>
/**
  * @class ThreadSocket
  * Clase que gestiona la comunicacion por sockets
  * Hereda de QThread
  */
class ThreadSocket:public QThread{

    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent puntero al padre (QWidget)
     * @param l puntero a la etiqueta de imagen de informacion
     * @param pw puntero a la ventana de simulacion
     * @param hl puntero al layout del algoritmo
     * @param ds puntero a la estructura de configuracion inicial
     * @param gw puntero a la ventana de graficos
     */
    ThreadSocket(QObject *parent,QLabel *l,PaintWindow* pw,QHBoxLayout *hl,DataSocket1 *ds,GraphsWindow * gw,QString n);

    /**
     * @brief Destructor
     */
    ~ThreadSocket();

    /**
     * @brief Empieza la transferencia de datos
     */
    void startSimulation();

    /**
     * @brief Redefinicion del metodo QThread::run()
     */
    void run();

    /**
     * @brief Asigna un valor a la variable connected
     * @param c nuevo valor de connected
     */
    void setConnected(bool c);


    QLabel * label;/**< Etiqueta para pintar la imagen de informacion*/

    QHBoxLayout *layout; /**< Puntero al layout del algoritmo*/

    PaintWindow * paintWindow;/**< Puntero a la ventana de simulacion*/

    GraphsWindow * graphsWindow;/**< Puntero a la ventana de graficos*/

    bool connected;/**< Guarda el estado de conectado*/

    int fs; /**< Guarda el estado de finalizado*/

    int socketId;/**< Guarda el id del socket*/

    DataSocket1 *dataSocket;/**< Puntero a la estructura de configuracion inicial*/

    EventData eDataSend;/**< Estuctura con la informacion a enviar*/

    EventData eDataRecive;/**< Estuctura con la informacion a recibir*/

    QString iconName;/**< Nombre del algoritmo*/

    /**
     * @brief Crea la coneccion con el socket
     * @param port id del puerto a conectarse
     * @return 0:sin errores 1:error(es) en la coneccion
     */
    int setConnection(char *ip, int port);

    /**
     * @brief aborta la simulacion
     */
    void abort();
private:
    friend class MainWindow;

    /**
      * @brief Obtiene los valores para generar las graficas
      */
    void getGrahpsData();

    /**
      * @brief Finaliza la coneccion con el socket
      * @param value tipo de finalizacion
      */
    void finishConnection(int value);

private slots:

    /**
      * @brief Cierra el socket si la ventana de simulacion se cierra
      */
    void closedWindow();

    /**
      * @brief Recibe un nuevo evento para simular
      */
    void nextEvent();

signals:

    /**
      * @brief Se;al emitida cuando finaliza la coneccion
      */
    void finishedConnection();

};

#endif // THREADSOCKET_H

