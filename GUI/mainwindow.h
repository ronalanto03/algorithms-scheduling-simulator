/**
  * @file mainwindow.h
  * @brief Declaracion de la clase MainWindow.
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QProgressBar>
#include <QMainWindow>
#include <settingsdialog.h>
#include <graphswindow.h>
#include <datawindow.h>
#include <paintwindow.h>
#include <iostream>
#include <string>
#include <QString>
#include <QFileDialog>
#include<threadsocket.h>
#include<threadsocketvs.h>
#include <QSignalMapper>
#include <QMovie>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <aboutdialog.h>

namespace Ui {
class MainWindow;
}
/**
  * @class MainWindow
  * Clase que gestiona la ventana principal
  * Hereda de QMainWindow
  */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor por defecto
     */
    explicit MainWindow(char *ip,int port=31059);
    /**
     * @brief Destructor
     */
    ~MainWindow();

private:



    Ui::MainWindow *ui;/**< Ui generada por Qt creator*/

    int port;/**< puerto para la coneccion por sockets*/
    char * ip;

    ThreadSocket *tsRR;/**< Puntero del hilo de conexion para el algortmo Round Robin*/

    ThreadSocket *tsFCFS;/**< Puntero del hilo de conexion para el algortmo First Come First Serve */

    ThreadSocket *tsSJF;/**< Puntero del hilo de conexion para el algortmo Shortest Job First*/

    ThreadSocket *tsPSJF;/**< Puntero del hilo de conexion para el algortmo de Reloj*/

    ThreadSocketVs *tsvs;/**< Puntero del hilo de conexion auxiliar para vs*/

    DataWindow *dwvs;/**< Puntero para la ventana de simulacion del algoritmo Round Robin*/

    PaintWindow *pwRR;/**< Puntero para la ventana de simulacion del algoritmo Round Robin*/

    PaintWindow *pwFCFS;/**< Puntero para la ventana de simulacion del algoritmo First Come First Serve*/

    PaintWindow *pwSJF;/**< Puntero para la ventana de simulacion del algoritmo Shortest Job First*/

    PaintWindow *pwPSJF;/**< Puntero para la ventana de simulacion del algoritmo Pre Shortest Job First.*/

    GraphsWindow * gwRR;/**< Puntero para la ventana de graficas del algoritmo Round Robin*/

    GraphsWindow * gwFCFS;/**< Puntero para la ventana de graficas del algoritmo First Come First Serve*/

    GraphsWindow * gwSJF;/**< Puntero para la ventana de graficas del algoritmo Shortest Job First*/

    GraphsWindow * gwPSJF;/**< Puntero para la ventana de graficas del algoritmo Pre.Shortest Job First*/

    GraphsWindow * gw[4];/**< Puntero para la ventana de graficas */


    DataSocket1* simulationSettings[5];/**< parametros de las simulaciones*/


    QSignalMapper * SMrunTrheads;/**< Mapeo de se;ales para los hilos*/

    QSignalMapper * SMcancelSimulation,* SMcancelSimulation2;/**< Mapeo de se;ales para cancelar la simulacion*/

    QSignalMapper * SMenableOptions;/**< Mapeo de se;ales para gestionar las opciones de simulacion*/

    QSignalMapper * SMSimulationType;/**< Mapeo de se;ales para gestionar el tipo de simulacion*/

public slots:

    /**
     * @brief Corre el hilo de ejecucion para la comunicacion por socket modo self
     * @param thread puntero al hilo del algoritmo selecionado
       @return 1 si hay error al conectar 0 si se conecto correctamente
     */
    int runThreadSocketSelf(QObject* obj);

    /**
     * @brief Corre el hilo de ejecucion para la comunicacion por socket modo vs
       @return 1 si hay error al conectar 0 si se conecto correctamente
     */
    int runThreadSocketVs();

    /**
     * @brief Muestra el dialogo de configuracion de la simulacion
     * @param alg indicador del algoritmo
     * @return 1 si hay error al conectar 0 si se conecto correctamente
     */
    void showSettings(int alg);

    /**
     * @brief Cancela la simulacion modo self
     * @param obj puntero al hilo del algoritmo selecionado
     */
    void cancelSimulation(QObject * obj);

    /**
     * @brief Cancela la simulacion modo vs
     */
    void cancelSimulationVs();

    /**
     * @brief habilita los botones modo self
     * @param obj puntero al layout del algoritmo selecionado
     */
    void enableOptions(QObject * obj);
    /**
     * @brief Muestra las imagenes auxiliares modo self
     * @param obj puntero al hilo del algoritmo selecionado
     */
    void setIcons(QObject *obj);

    /**
     * @brief selecciona todos los algoritmos
     */
    void selectAll();

    /**
     * @brief Muestra las imagenes auxiliares modo vs
     */
    void setIconsVs();

    /**
     * @brief muestra menu about
     */
    void about();


};

#endif // MAINWINDOW_H
