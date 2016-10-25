/**
  * @file graphswindow.h
  * @brief Declaracion de la clase GraphsWindow.
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */

#ifndef GRAPHSWINDOW_H
#define GRAPHSWINDOW_H

#include <QMainWindow>
#include <uiprocess.h>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <queuedialog.h>
#define NUM_COMMANDS 11
using namespace std;
namespace Ui {
class GraphsWindow;
}
/**
  * class GraphsWindow
  * Clase que gestiona la ventana para mostrar las graficas de la simulacion
  */

class GraphsWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    GraphsWindow(QWidget *parent,QString iconName);
    ~GraphsWindow();

    GraphParams gPw;/**< Parametros para graficar tiempo de espera*/

    GraphParams gPu;/**< Parametros para graficar tiempo de uso*/

    GraphParams gPt;/**< Parametros para graficar tiempo de turnAround */

    GeneralParams generalP;/**< Parametros generales de la simulacion */

    QueueDialog *queue;/**< Cola para mostrar procesos finalizados*/

    QString iconName;/**< Nombre del algoritmo usado*/


    /**
     * @brief LLama a los metodos de graficar
     */
    void plot();
    /**
     * @brief Guarda los valores comunes entre tipos de grafica
     */
    void setLabels();

private:
    Ui::GraphsWindow *ui;/**< Ui generada por Qt creator*/

    /**
     * @brief Configura los parametros de las graficas
     * @param gp parametros de configuracion
     */
    void grahpsSettings(GraphParams gp);
    /**
     * @brief Ejecuta los comandos de gnuPlot
     * @param file nombre del archivo con los datos a graficar
     * @param name nombre de la grafica
     * @param path ruta de la imagen
     * @param smx valor maximo del eje x
     * @param smy valor maximo del eje y
     * @param sav valor promedio
     * @param sboxX valor de grosor de linea
     * @param sxl nombre del eje x
     * @param pos columna a graficar en el eje x
     * @param min Minimo valor a graficar
     */
    void gnuplot(string file,string name,string path,string smx,string smy,\
                 string sav,string sboxW ,string sxl,string pos,string min);

    /**
     * @brief Ejecuta los comandos de gnuPlot
     * @param type tipo de grafica
     * @param axis parametro del eje x
     */
    void changeImage(int type, int axis);


private slots:
    /**
     * @brief Cambia la imagen de la grafica
     */
    void changedImage();

    /**
     * @brief Muestra el dialogo de guardar
     */
    void saveAs();
};

#endif // GRAPHSWINDOW_H
