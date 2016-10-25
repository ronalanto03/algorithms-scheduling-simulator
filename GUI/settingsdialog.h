/**
  * @file settingsdialog.h
  * @brief Declaracion de la clase SettingsDialog.
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */
#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H
#include <DataSocket1.h>
#include <QMessageBox>
#include <QDialog>

namespace Ui {
class SettingsDialog;
}

/**
  * @class SettingsDialog
  * Clase que gestiona el dialogo de las configuaraciones de la simulacion
  * Hereda de QDialog
  */
class SettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor
     * @param parent puntero al padre (QWidget)
     * @param ds puntero a la estructura de configuracion inicial
     */
    explicit SettingsDialog(QWidget *parent = 0,DataSocket1 * ds=0);

    /**
     * @brief Destructor
     */
    ~SettingsDialog();

    /**
     * @brief Verifica si los datos introducidos son correctos
     * @return 0:Error en los datos 1:sin errores
     */
    int check();

    DataSocket1 *ds;/**< Estructura que guarda los parametros de la configuracion inicial*/

    
private:
    Ui::SettingsDialog *ui;/**< Ui generada por Qt*/

private slots:

    /**
     * @brief Guarda los valores en la estructura de configuracion inicial
     * @return 0:Error en los datos 1:sin errores
     */
    int save();

    /**
     * @brief Carga los valores en la estructura de configuracion inicial
     */
    void load();

    /**
     * @brief Mantiene el algoritmo asignado
     */
    void stayAlgorithm();

    /**
     * @brief Habilita el valor del extremo derecho de la configuracion del tiempo de llegada
     */
    void enableArrTimeSb();

    /**
     * @brief Habilita el valor del extremo derecho de la configuracion del tiempo de duracion
     */
    void enableDurTimeSB();

    /**
     * @brief Habilita el valor del extremo derecho de la configuracion del tiempo de bloqueo
     */
    void enableBlockTimeSb();

    /**
     * @brief Habilita el valor del extremo derecho de la configuracion del tiempo de rafaga
     */
    void enableBurstTimeSB();

};

#endif // SETTINGSDIALOG_H
