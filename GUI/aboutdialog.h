/**
  * @file aboutdialog.h
  * @brief Declaracion de la clase AboutDialog.
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */
#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui {
class AboutDialog;
}
/**
  * @class AboutDialog
  * Clase que gestiona el dialogo de contacto
  * Hereda de QDialog
  */

class AboutDialog : public QDialog
{
    Q_OBJECT
    
public:
    /**
      * @brief Constructor
      */
    explicit AboutDialog(QWidget *parent = 0);


    /**
      * @brief Destructor
      */
    ~AboutDialog();
    
private:
    Ui::AboutDialog *ui;/**< Ui generada por QtCreator*/
};

#endif // ABOUTDIALOG_H
