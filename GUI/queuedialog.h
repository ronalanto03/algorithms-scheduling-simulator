/**
  * @file queuedialog.h
  * @brief Declaracion de la clase QueueDialog.
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */
#ifndef QUEUEDIALOG_H
#define QUEUEDIALOG_H

#include <QDialog>
#include <QQueue>
#include <uiprocess.h>
namespace Ui {
class QueueDialog;
}

/**
  * @class QueueDialog
  * Clase que gestiona el dialogo con los procesos en las colas
  * Hereda de QDialog
  */
class QueueDialog : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor
     * @param parent puntero al padre (QWidget)
     */
    explicit QueueDialog(QWidget *parent = 0);

    /**
     * @brief Destructor
     */
    ~QueueDialog();

    /**
     * @brief Inserta un proceso a la cola
     * @param p Puntero al proceso a insertar
     */
    void insertProcess(UiProcess *p);

    /**
     * @brief Inserta con prioridad un proceso a la cola
     * @param p Puntero al proceso a insertar
     * @param pri Prioridad del proceso
     */
    int insertProcessPriority(UiProcess *p,int pri);

    /**
     * @brief Elimina el proceso en la punta a la cola
     * @return Puntero al proceso eliminado
     */
    UiProcess * removeProcess();

    /**
     * @brief Elimina el proceso en la punta a la cola
     * @return 1:vacia 0:almenos un elemento en la cola
     */
    bool isEmpty();

    /**
     * @brief Actualiza los valores de la cola para mostrar el dialogo
     */
    void updateData();

    /**
     * @brief Limpia la cola
     */
    void cleanQueue();

    /**
     * @brief Asigna la ruta de la imagen con el color respectivo
     * @param c ruta de la imagen
     */
    void setPathColor(QString c);

    /**
     * @brief Actualiza los valores del tiempo de bloqueo de los procesos
     * @param time diferencia de tiempo entre el anterior y el actual
     */
    void updateBlockedTime(double time);

    /**
     * @brief Actualiza los valores del tiempo de espera de los procesos
     * @param time diferencia de tiempo entre el anterior y el actual
     */
    void updateWaitingTime(double time);

    /**
     * @brief devuelve la ruta de la imagen de la cola
     * @return Cadena con la ruta
     */
    QString getPathColor();


    QQueue<UiProcess *> queue;/**< Cola de procesos*/

private:

    Ui::QueueDialog *ui;/**< Ui generada por Qt*/
    QString pathColor;/**< Color de la cola*/

private slots:

    /**
     * @brief Muestra el dialogo para guardar los valores de la cola
     */
    void saveAs();


};

#endif // QUEUEDIALOG_H
