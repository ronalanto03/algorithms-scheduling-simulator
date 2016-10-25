/**
  * @file queuedialog.cpp
  * @brief Definicion de los metodos de la clase QueueDialog
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */
#include "queuedialog.h"
#include "ui_queuedialog.h"
#include "iostream"
#include <QStandardItemModel>
#include <QString>
#include <fstream>
#include <QFileDialog>
QueueDialog::QueueDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueueDialog)
{
    ui->setupUi(this);
    connect(ui->pButtonSave, SIGNAL(released()),this, SLOT(saveAs()));
    updateData();
}

QueueDialog::~QueueDialog()
{
    delete ui;
}
void QueueDialog::insertProcess(UiProcess *p){
    queue.enqueue(p);
}

void QueueDialog::updateBlockedTime(double time){

    UiProcess *p;
    for(int i = 0; i<queue.length();i++){
        p=queue.value(i);
        p->setBlockingTime(p->getBlockingTime()-time);
    }

}

void QueueDialog::updateWaitingTime(double time){

    UiProcess *p;
    for(int i = 0; i<queue.length();i++){
        p=queue.value(i);
        p->setWaitingTime(p->getWaitingTime()+time);
    }

}

int QueueDialog::insertProcessPriority(UiProcess *p,int pri){
    UiProcess *pe;
    if(!queue.isEmpty()){

        for(int i = 0; i<queue.size();i++){
            pe=queue.value(i);

            if(pri==0 && p->getBlockingTime()<pe->getBlockingTime()){
            queue.insert(i,p);
            return 0;
            }

            if(pri==1 && p->getCpuBurstTime()<pe->getCpuBurstTime()){
                queue.insert(i,p);
                return 0;
            }
        }

    }
    queue.enqueue(p);
    return 0;

}
UiProcess * QueueDialog::removeProcess(){

    UiProcess *p = queue.dequeue();

    return p;
}
bool QueueDialog::isEmpty(){

    return (queue.isEmpty());
}

void QueueDialog::updateData(){
    UiProcess *p;



    QStandardItemModel *model = new QStandardItemModel(0, 13, this);

    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Nro.")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("PId")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("ArrivalTime")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("CPUBurstTime")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("RemainingTime")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("BlockedTime")));
    model->setHorizontalHeaderItem(6, new QStandardItem(QString("WaitingTime")));
    model->setHorizontalHeaderItem(7, new QStandardItem(QString("UsedTime")));
    model->setHorizontalHeaderItem(8, new QStandardItem(QString("DurationTime")));
    model->setHorizontalHeaderItem(9, new QStandardItem(QString("EndingTime")));
    model->setHorizontalHeaderItem(10, new QStandardItem(QString("Cpu Entries")));
    model->setHorizontalHeaderItem(11, new QStandardItem(QString("I/O Entries")));
    model->setHorizontalHeaderItem(12, new QStandardItem(QString("Total Blocking Time")));

    QHeaderView *header = new QHeaderView(Qt::Horizontal,this);
    ui->processTable->resizeColumnsToContents();

     ui->processTable->setHorizontalHeader(header);
     QFont fnt;
     fnt.setPointSize(8);
     fnt.setFamily("Arial");
    header->setFont(fnt);

    for(int i = 0; i<queue.size();i++){
        p=queue.value(i);
        model->setItem(i, 0, new QStandardItem(QString::number(i)));
        model->setItem(i, 1, new QStandardItem(QString::number(p->getPid())));
        model->setItem(i, 2, new QStandardItem(QString::number(p->getArrTime())));
        model->setItem(i, 3, new QStandardItem(QString::number(p->getCpuBurstTime())));
        model->setItem(i, 4, new QStandardItem(QString::number(p->getRemainingTime())));
        model->setItem(i, 5, new QStandardItem(QString::number(p->getBlockingTime())));
        model->setItem(i, 6, new QStandardItem(QString::number(p->getWaitingTime())));
        model->setItem(i, 7, new QStandardItem(QString::number(p->getUsedTime())));
        model->setItem(i, 8, new QStandardItem(QString::number(p->getDurationTime())));
        if(p->getEndingTime()!=0)
        model->setItem(i, 9, new QStandardItem(QString::number(p->getEndingTime())));

        model->setItem(i, 10, new QStandardItem(QString::number(p->getnT())));
        model->setItem(i, 11, new QStandardItem(QString::number(p->getnB())));
        model->setItem(i, 12, new QStandardItem(QString::number(p->getallBlockingTime())));

    }

    ui->processTable->setModel(model);
    ui->processTable->verticalHeader()->setVisible(false);
    ui->processTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void QueueDialog::cleanQueue(){

    while(!queue.isEmpty()){
        delete queue.dequeue();
    }
}

void QueueDialog::setPathColor(QString c){
    pathColor=c;
}

QString QueueDialog::getPathColor(){
    return pathColor;
}


void QueueDialog::saveAs(){
    std::ofstream file;
    UiProcess *p;
    QString name("queue.txt");
    file.open(name.toStdString().c_str());

    file<<"Nro\t"<<"PID\t"<<"ArrivalTime\t"<<"CpuBurstTime\t"<<"BlockingTime\t"\
        <<"WaitingTime\t"<<"UsedTime\t"<<"DurationTime\t"<<"EndingTime\t"<<"CPUEntries\t"\
       <<"I/OEntires\t"<<"AllBlockingTime\n";

    for(int i = 0; i<queue.size();i++){
        p=queue.value(i);
        file<<i<<"\t";
        file<<p->getPid()<<"\t";
        file<<p->getArrTime()<<"\t";
        file<<p->getCpuBurstTime()<<"\t";
        file<<p->getRemainingTime()<<"\t";
        file<<p->getBlockingTime()<<"\t";
        file<<p->getWaitingTime()<<"\t";
        file<<p->getUsedTime()<<"\t";
        file<<p->getDurationTime()<<"\t";
        file<<p->getEndingTime()<<"\t";
        file<<p->getnT()<<"\t";
        file<<p->getnB()<<"\t";
        file<<p->getallBlockingTime()<<"\n";

    }

    file.close();

    QString path="cp ";

    path+=name;
    path+="\ ";

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(name),
               tr("Text Files (*.txt)"));
               if (!fileName.isEmpty()) {
                   path+=fileName;
                    system(path.toStdString().c_str());
                   }
               }
