/**
  * @file waintwindow.h
  * @brief Declaracion de la clase PaintWindow.
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */
#ifndef PAINTWINDOW_H
#define PAINTWINDOW_H

#include <QMainWindow>
#include <eventData.h>
#include <mylabel.h>
#include <QGraphicsItem>
#include <QMovie>
#include <QPainter>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QGraphicsAnchor>
#include <processpropertiesdialog.h>
#include <uiprocess.h>
#include <QSignalMapper>
#include <queuedialog.h>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <DataSocket1.h>
#include <QString>
namespace Ui {
class PaintWindow;
}
/**
  * @class PaintWindow
  * Clase que gestiona la ventana de la simulacion
  * Hereda de QMainWindow
  */
class PaintWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor
     * @param parent puntero al padre (QWidget)
     * @param n nombre del algoritmo
     * @param ds puntero a la configuracion inicial de la simulacion
     */
    PaintWindow(QWidget *parent,QString n ,DataSocket1 * ds);
    /**
     * @brief Destructor
     */
    ~PaintWindow();

    /**
     * @brief Configurar posicion de las etiquetas a pintar
     */
    void setPos();

    /**
     * @brief Metodo para realizar la animacion de aparecer y desvanecer
     * @param label etiqueta que aparece y desaparece
     * @param val valor final del efecto
     */
    void plusHide(MyLabel * label,int val);

    /**
     * @brief Metodo para realizar la animacion de rotar de los engranajes
     * @param label etiqueta del engranaje
     * @param angle angulo de giro.
     */
    void rotate(MyLabel *label, int angle);

    /**
     * @brief Metodo para pintar la etiqueta
     * @param label etiqueta a pintar
     * @param path ruta de la imagen de la etiqueta
     * @param x valor de la coordenada x
     * @param y valor de la coordenada y
     * @param w valor del ancho de la imagen
     * @param h valor del alto de la imagen
     * @param text texto para el dialogo
     */
    void paintLabel(QLabel * label , QString path,int x,int y,int w,int h,QString text);

    /**
     * @brief Metodo para procesar el evento que llega
     * @param eData Evento nuevo
     */
    void setEvent(EventData eData);

    /**
     * @brief Metodo para inicializar la ventana
     */
    void settings();

    /**
     * @brief Metodo para insertar un proceso y actualizar la cola de procesos
     * @param qDialogQ Cola en donde se insertara el proceso
     * @param process Puntero al proceso a insertar
     * @param label Puntero a vector de etiquetas que representan la cola graficamente
     */
    void updateQueue(QueueDialog * qDialogQ,UiProcess **process,MyLabel **label);

    /**
     * @brief Metodo para la animacion de finalizacion
     */
    void setFinished();

    QString iconName;/**< nombre del la imagen del algoritmo usado*/

private:

    int posMat[18][2];/**< Posiciones para las animaciones*/

    int anglePR1;/**< Angulo de giro para el engranaje 1*/

    int anglePR2;/**< Angulo de giro para el engranaje 2*/

    int pos;/**< posicion de inicio de la animacion de mover proceso*/

    int posStop;/**< posicion final de la animacion de mover proceso*/

    Ui::PaintWindow *ui;/**< Ui generada por Qt*/

    QTimer * timer;/**< temporizador usado para rotar los engranajes */

    QTimer * timerP;/**< temporizador usado para las animaciones de mover procesos */

    QTimer * timerFr;/**< temporizador usado para la corrida libre */

    MyLabel *labelRQ[7];/**< Vector de etiquetas para pintar la cola de listo */

    MyLabel *labelBQ[7];/**< Vector de etiquetas para pintar la cola de bloqueado */

    UiProcess *processRQ[4];/**< Vector de procesos en los extremos de la cola de listo  */

    UiProcess *processBQ[4];/**< Vector de procesos en los extremos de la cola de bloqueado  */

    MyLabel *labelG1,*labelG2;/**< Etiquetas para pintar los engranajes*/

    MyLabel *labelPRP1;/**< Etiquetas para pintar el proceso en ejecucion*/

    MyLabel *labelPlusRQ,*labelPlusBQ,*labelPlusPR,*labelPlus,*labelBef,*labelPlusF;/**< Etiquetas para pintar los simbolos de adicion*/

    MyLabel *labelBox,*labelInput,*labelInput2,*labelOutput,*labelOutput2,*labelFQ;/**< Etiquetas para pintar los simbolos de entrada y salida*/

    MyLabel *labelAlgorithmIcon;/**< Etiqueta para pintar el tipo de algoritmo usado*/

    MyLabel *labelClock;/**< Etiquta para pintar el reloj*/

    MyLabel *labelPrAnimation[3];/**< Etiquetas para pintar la animacion de movimiento del proceso*/

    MyLabel *labelFinished;/**< Etiqueta para pintar la animacion final*/

    UiProcess *processPRP1;/**< Proceso en ejecucion*/

    QueueDialog * qDialogRQ,*qDialogBQ,*qDialogFQ; /**< Dialogos para las colas de listo bloqueado y finalizado*/

    DataSocket1 * simulationSettings;/**< Configuracion inicial de la simulacion*/

    /**
     * @brief Dibujar proceso ejecutandose en el procesador
     * @param p proceso a mostrar en el procesador
     * @param c tipo de proceso 1:real , 0:nulo
     */
    void putGraphicPr(UiProcess *p,int c);

    /**
     * @brief Actualiza las colas graficas de procesos para insersion
     * @param qDialogQ Puntero a la cola a actualizar
     * @param process Puntero el vector de procesos que simula la cola grafica
     * @param label Puntero a el vector de etiquetas que simula la cola grafica
     * @param p Puntero al proceso a insertar
     * @param type Tipo de cola 0:listo 1:bloqueado
     */
    void pushGraphicQueue(QueueDialog * qDialogQ,UiProcess **process,MyLabel **label ,UiProcess * p,int type);

    /**
     * @brief Actualiza las colas graficas de procesos para eliminacion
     * @param qDialogQ Puntero a la cola a actualizar
     * @param process Puntero el vector de procesos que simula la cola grafica
     * @param label Puntero a el vector de etiquetas que simula la cola grafica
     */
    UiProcess * popGraphicQueue(QueueDialog * qDialogQ,UiProcess **process,MyLabel** label);

    /**
     * @brief Actualiza el dialogo de las etiquetas
     * @param label Puntero a la etiqueta a modificar su dialogo informacion
     * @param p Puntero el proceso que contiene la informacion
     */
    void setLabelToolTip(MyLabel * label,UiProcess * p);

    /**
     * @brief Configura el tipo de distribucion y sus parametros
     * @param dd Structura con los valores de la distribucion
     * @return Cadena con la configuracion de la distribucion
     */
    QString selectDist(DistributionData dd);

    /**
     * @brief Redefinicion del Metodo QWidget::closeEvent(QCloseEvent *event)
     * @param event Puntero al evento generado
     */
    void closeEvent(QCloseEvent *event);

private slots:

    /**
     * @brief Metodo que habilita la corrida libre
     */
    void startFreeRun();

    /**
     * @brief Metodo que detiene la corrida libre
     */
    void stopFreeRun();

    /**
     * @brief Metodo para configurar y ejecutar los parametros de rotacion de los engranajes
     */
    void rotateAnimation();

    /**
     * @brief Metodo para emitir la se;al para pedir un proximo evento
     */
    void nextEventSlot();

    /**
     * @brief Metodo para generar animacion de movimiento de procesos
     */
    void processAnimation();

    /**
     * @brief Metodo para mostrar el dialogo con las propiedades de un proceso
     * @param obj Puntero al proceso a mostrar
     */
    void processProperties(QObject *obj);

    /**
     * @brief Metodo para mostrar el dialogo con los procesos en la cola de listo
     */
    void showRQueueDialog();

    /**
     * @brief Metodo para mostrar el dialogo con los procesos en la cola de bloqueado
     */
    void showBQueueDialog();

    /**
     * @brief Metodo para mostrar el dialogo con los procesos en la cola de finalizado
     */
    void showFQueueDialog();

signals:

    /**
     * @brief Se;al emitida cuando se cierra la ventana
     */
    void closed();

    /**
     * @brief Se;al emitida para solicitar un nuevo evento
     */
    void nextEventSignal();

};

#endif // PAINTWINDOW_H

