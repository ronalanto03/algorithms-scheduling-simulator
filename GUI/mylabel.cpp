/**
  * @file mylabel.cpp
  * @brief Definicion de los metodos de la clase MyLabel.
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */
#include "mylabel.h"

MyLabel::MyLabel( QWidget * parent)
    : QLabel(parent)
{

}


void MyLabel::mousePressEvent ( QMouseEvent * event )
{
    if(event->button() == Qt::MoveAction)
        emit dragMoveAction();

    if(event->button() == Qt::LeftButton)
        emit leftButtonAction();

}

