/**
  * @file settingsdialog.cpp
  * @brief Definicion de los metodos de la clase SettingsDialog
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */
#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <iostream>

SettingsDialog::SettingsDialog(QWidget *parent, DataSocket1 * ds ) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)

{
    ui->setupUi(this);

    this->ds=ds;

    QDialog::connect(ui->cBoxAlgorithm,SIGNAL(currentIndexChanged(int)),this,SLOT(stayAlgorithm()));

    QDialog::connect(ui->cBoxArrTime,SIGNAL(currentIndexChanged(QString)),this,SLOT(enableArrTimeSb()));
    QDialog::connect(ui->cBoxDuration,SIGNAL(currentIndexChanged(QString)),this,SLOT(enableDurTimeSB()));
    QDialog::connect(ui->cBoxBlockTime,SIGNAL(currentIndexChanged(QString)),this,SLOT(enableBlockTimeSb()));
    QDialog::connect(ui->cBoxBurstTime,SIGNAL(currentIndexChanged(QString)),this,SLOT(enableBurstTimeSB()));
    QDialog::connect(ui->pButtonCancel,SIGNAL(released()),this,SLOT(close()));
    QDialog::connect(ui->pButtonSave,SIGNAL(released()),this,SLOT(save()));


    load();

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::enableArrTimeSb(){
    if(ui->cBoxArrTime->currentIndex()==0 || ui->cBoxArrTime->currentIndex()==2 )
        ui->sBoxArrTimeR->setEnabled(false);
    else
        ui->sBoxArrTimeR->setEnabled(true);
}
void SettingsDialog::enableDurTimeSB(){
    if(ui->cBoxDuration->currentIndex()==2 || ui->cBoxDuration->currentIndex()==0 )
        ui->sBoxDurTimeR->setEnabled(false);
    else
        ui->sBoxDurTimeR->setEnabled(true);
}
void SettingsDialog::enableBlockTimeSb(){
    if(ui->cBoxBlockTime->currentIndex()==0 || ui->cBoxBlockTime->currentIndex()==2 )
        ui->sBoxBlockTimeR->setEnabled(false);
    else
               ui->sBoxBlockTimeR->setEnabled(true);
}
void SettingsDialog::enableBurstTimeSB(){
    if(ui->cBoxBurstTime->currentIndex()==0 || ui->cBoxBurstTime->currentIndex()==2 )
        ui->sBoxBurstTimeR->setEnabled(false);
    else
        ui->sBoxBurstTimeR->setEnabled(true);
}

int SettingsDialog::save(){

    if(!check())
        return 0;

    ds->n=ui->sBoxNum->value();
    ds->quantum =ui->sBoxQuantum->value();

    ds->arrTimeD.t=ui->cBoxArrTime->currentIndex()+1;
    ds->arrTimeD.left=ui->sBoxArrTimeL->value();
    ds->arrTimeD.right=ui->sBoxArrTimeR->value();

    ds->durationTimeD.t=ui->cBoxDuration->currentIndex()+1;
    ds->durationTimeD.left=ui->sBoxDurTimeL->value();
    ds->durationTimeD.right=ui->sBoxDurTimeR->value();

    ds->blockingTimeD.t=ui->cBoxBlockTime->currentIndex()+1;
    ds->blockingTimeD.left=ui->sBoxBlockTimeL->value();
    ds->blockingTimeD.right=ui->sBoxBlockTimeR->value();

    ds->cpuBusrtTimeD.t=ui->cBoxBurstTime->currentIndex()+1;
    ds->cpuBusrtTimeD.left=ui->sBoxBurstTimeL->value();
    ds->cpuBusrtTimeD.right=ui->sBoxBurstTimeR->value();

    ds->seed=ui->sBoxSeed->value();

    close();

}

void SettingsDialog::load(){
    /*1:FCFS.2:SJF.3:PSJF.4:RR*/
    ui->cBoxAlgorithm->setCurrentIndex(ds->algorithm-1);

    if(ds->algorithm==4){
        ui->sBoxQuantum->setEnabled(true);
        ui->labelQuantum->setEnabled(true);
    }

    ui->sBoxNum->setValue(ds->n);
    ui->sBoxQuantum->setValue(ds->quantum);

    ui->cBoxArrTime->setCurrentIndex(ds->arrTimeD.t-1);
    ui->sBoxArrTimeL->setValue(ds->arrTimeD.left);
    ui->sBoxArrTimeR->setValue(ds->arrTimeD.right);

    ui->cBoxDuration->setCurrentIndex(ds->durationTimeD.t-1);
    ui->sBoxDurTimeL->setValue(ds->durationTimeD.left);
    ui->sBoxDurTimeR->setValue(ds->durationTimeD.right);

    ui->cBoxBlockTime->setCurrentIndex(ds->blockingTimeD.t-1);
    ui->sBoxBlockTimeL->setValue(ds->blockingTimeD.left);
    ui->sBoxBlockTimeR->setValue(ds->blockingTimeD.right);

    ui->cBoxBurstTime->setCurrentIndex(ds->cpuBusrtTimeD.t-1);
    ui->sBoxBurstTimeL->setValue(ds->cpuBusrtTimeD.left);
    ui->sBoxBurstTimeR->setValue(ds->cpuBusrtTimeD.right);

    ui->sBoxSeed->setValue(ds->seed);
}

void  SettingsDialog::stayAlgorithm(){
    ui->cBoxAlgorithm->setCurrentIndex(ds->algorithm-1);
}

int SettingsDialog::check(){

    QMessageBox msgBox;
    QString str;
    if((ui->cBoxArrTime->currentIndex()==1 || ui->cBoxArrTime->currentIndex()==3 )&& ui->sBoxArrTimeL->value()>ui->sBoxArrTimeR->value()){
        str="Invalid values for arrival time parameters";
    }
    else if((ui->cBoxDuration->currentIndex()==1 || ui->cBoxDuration->currentIndex()==3) && ui->sBoxDurTimeL->value()>ui->sBoxDurTimeR->value()){
        str="Invalid values for duration time parameters";
    }
    else if((ui->cBoxBlockTime->currentIndex()==1 || ui->cBoxBlockTime->currentIndex()==3)&& ui->sBoxBlockTimeL->value()>ui->sBoxBlockTimeR->value()){
        str="Invalid values for blocking time parameters";
    }
    else if((ui->cBoxBurstTime->currentIndex()==1||ui->cBoxBurstTime->currentIndex()==3) && ui->sBoxBurstTimeL->value()>ui->sBoxBurstTimeR->value()){
        str="Invalid values for cpu burst time parameters";
    }
    else
        str="";

    if(!str.isEmpty()){
     msgBox.setText("Error");
     msgBox.setInformativeText(str);
     msgBox.setMinimumWidth(300);
     msgBox.setStandardButtons(QMessageBox::Close);
     msgBox.exec();
     return 0;
    }
    else
        return 1;

}
