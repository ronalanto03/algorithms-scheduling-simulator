/**
  * @file mylabel.h
  * @brief Declaracion de la clase MyLabel.
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */
#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QMouseEvent>

/**
  * @class MyLabel
  * Clase para gestionar las imagenes
  * Hereda de Qlabel
  */
class MyLabel : public QLabel
{
    Q_OBJECT
public:

    /**
     * @brief Constructor por defecto
     */
    explicit MyLabel(QWidget *parent=0);

    /**
     * @brief Redefinicion del metodo que gestiona los click del raton
     * @param event Puntero al evento del raton
     */
    void mousePressEvent ( QMouseEvent * event );


    virtual ~MyLabel(){}

Q_SIGNALS:

    /**
     * @brief Se;al emitida por que el puntero esta sobre el label
     */
    void dragMoveAction();
    /**
     * @brief se;al emitida por que el puntero dio click sobre el label
     */
    void leftButtonAction();
    

    
};

#endif // MYLABEL_H
