/**
  * @file datawindow.h
  * @brief Declaracion de la clase DataWindow.
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */

#ifndef DATAWINDOW_H
#define DATAWINDOW_H

#include <QMainWindow>
#include<DataSocket1.h>
#include<eventData.h>
#include<QStandardItemModel>
#include<uiprocess.h>
#include <multSimData.h>

namespace Ui {
class DataWindow;
}

/**
  * class GraphsWindow
  * Clase que gestiona la ventana para mostrar datos de la simulacion vs
  */
class DataWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    DataWindow(QWidget *parent,DataSocket1 *ds);
    ~DataWindow();
    DataSocket1 *dataSocket;
    GeneralParams generalp[4];
    GraphParams graphpw[4];
    GraphParams graphpt[4];
    GraphParams graphpu[4];


    QString names[4];
    bool enabled[4];

    MutlSimData msd[4];

    int counter;
    int num;

    void setData();

    /**
     * @brief Redefinicion del Metodo QWidget::closeEvent(QCloseEvent *event)
     * @param event Puntero al evento generado
     */
    void closeEvent(QCloseEvent *event);
    
private:
    Ui::DataWindow *ui;



signals:

    /**
     * @brief Se;al emitida cuando se cierra la ventana
     */
    void closed();
public slots:

    /**
     * @brief lanza a graphDialog con la grafica seleccionada
     */
    void plot();

};

#endif // DATAWINDOW_H
