/**
  * @file processpropertiesdialog.h
  * @brief Declaracion de la clase ProcessPropertiesDialog.
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */
#ifndef PROCESSPROPERTIESDIALOG_H
#define PROCESSPROPERTIESDIALOG_H
#include<uiprocess.h>
#include <QDialog>

namespace Ui {
class processPropertiesDialog;
}

/**
  * @class ProcessPropertiesDialog
  * Clase que gestiona el dialogo con las propiedades del proceso
  * Hereda de QDialog
  */
class ProcessPropertiesDialog : public QDialog
{
    Q_OBJECT
    
public:

    /**
     * @brief Constructor
     * @param parent puntero al padre (QWidget)
     * @param p Proceso a mostrar en el dialogo
     */
    ProcessPropertiesDialog(QWidget *parent,UiProcess *p);
    /**
     * @brief Destructor
     */
    ~ProcessPropertiesDialog();


private:

    Ui::processPropertiesDialog *ui;/**< Ui generada por QtCreator */
};

#endif // PROCESSPROPERTIESDIALOG_H
