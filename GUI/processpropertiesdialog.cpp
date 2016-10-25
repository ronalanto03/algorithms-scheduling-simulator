/**
  * @file processpropertiesdialog.cpp
  * @brief Definicion de los metodos de la clase ProcessPropertiesDialog.
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */
#include "processpropertiesdialog.h"
#include "ui_processpropertiesdialog.h"
#include <iostream>
ProcessPropertiesDialog::ProcessPropertiesDialog(QWidget *parent,UiProcess * p):
    QDialog(parent),
    ui(new Ui::processPropertiesDialog)
{

    ui->setupUi(this);

    ui->lEditPId->setReadOnly(true);
    ui->lEditArrTime->setReadOnly(true);
    ui->lEditBurstTime->setReadOnly(true);
    ui->lEditBlockedTime->setReadOnly(true);
    ui->lEditDuration->setReadOnly(true);
    ui->lEditRemainingTime->setReadOnly(true);
    ui->lEditUsedTime->setReadOnly(true);
    ui->lEditWaitTime->setReadOnly(true);
    ui->lEditnB->setReadOnly(true);
    ui->lEditNt->setReadOnly(true);


    ui->lEditPId->setText(QString::number(p->getPid()));
    ui->lEditBlockedTime->setText(QString::number(p->getBlockingTime()));
    ui->lEditBurstTime->setText(QString::number(p->getCpuBurstTime()));
    ui->lEditDuration->setText(QString::number(p->getDurationTime()));
    ui->lEditArrTime->setText(QString::number(p->getArrTime()));
    ui->lEditRemainingTime->setText(QString::number(p->getRemainingTime()));
    ui->lEditUsedTime->setText(QString::number(p->getUsedTime()));
    ui->lEditWaitTime->setText(QString::number(p->getWaitingTime()));
    ui->lEditnB->setText(QString::number(p->getnB()));
    ui->lEditNt->setText(QString::number(p->getnT()));
    ui->lEditallbt->setText(QString::number(p->getallBlockingTime()));

}

ProcessPropertiesDialog::~ProcessPropertiesDialog()
{
    delete ui;
}



