/**
  * @file datawindow.cpp
  * @brief Definicion de los metodos de la clase DataWindow.
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */

#include "datawindow.h"
#include "ui_datawindow.h"
#include <graphdialog.h>

DataWindow::DataWindow(QWidget *parent, DataSocket1 *ds) :
    QMainWindow(parent),
    ui(new Ui::DataWindow)
{
    ui->setupUi(this);

    this->dataSocket=ds;

    names[0]="FirstComeFirstServe";
    names[1]="ShortestJobFirst";
    names[2]="Pre.ShortesrJobFirst";
    names[3]="RoundRobin";


    counter=0;
        connect(ui->pButtonGraph, SIGNAL(released()),this, SLOT(plot()));

}

DataWindow::~DataWindow()
{
    delete ui;
}


void DataWindow::setData(){

    int j=0;
    QStandardItemModel *model1 = new QStandardItemModel(4, 9, this);

    model1->setHorizontalHeaderItem(0, new QStandardItem(QString("Algorithm")));
    model1->setHorizontalHeaderItem(1, new QStandardItem(QString("Time")));
    model1->setHorizontalHeaderItem(2, new QStandardItem(QString("Processes")));
    model1->setHorizontalHeaderItem(3, new QStandardItem(QString("CPU \n Utilization")));
    model1->setHorizontalHeaderItem(4, new QStandardItem(QString("Throughput")));
    model1->setHorizontalHeaderItem(5, new QStandardItem(QString("Average\nUsed Time")));
    model1->setHorizontalHeaderItem(6, new QStandardItem(QString("Averag\nBlocked Time")));
    model1->setHorizontalHeaderItem(7, new QStandardItem(QString("Entries\nCPU")));
    model1->setHorizontalHeaderItem(8, new QStandardItem(QString("Entries\nI/O")));


    QStandardItemModel *model2 = new QStandardItemModel(4, 9, this);

    model2->setHorizontalHeaderItem(0, new QStandardItem(QString("Algorithm")));
    model2->setHorizontalHeaderItem(1, new QStandardItem(QString("Average\nTurnaround")));
    model2->setHorizontalHeaderItem(2, new QStandardItem(QString("Minimum\nTurnaround")));
    model2->setHorizontalHeaderItem(3, new QStandardItem(QString("Maximum\nTurnaround")));
    model2->setHorizontalHeaderItem(4, new QStandardItem(QString("SD\nTurnaround")));
    model2->setHorizontalHeaderItem(5, new QStandardItem(QString("Average\nWaiting")));
    model2->setHorizontalHeaderItem(6, new QStandardItem(QString("Minimum\nWaiting")));
    model2->setHorizontalHeaderItem(7, new QStandardItem(QString("Maximum\nWaiting")));
    model2->setHorizontalHeaderItem(8, new QStandardItem(QString("SD\nWaiting")));


    for(int i =0;i<4;i++){
        if(enabled[i]){
            model1->setItem(j, 0, new QStandardItem(names[i]));
            model1->setItem(j, 1, new QStandardItem(QString::number(generalp[i].time)));
            model1->setItem(j, 2, new QStandardItem(QString::number(generalp[i].nPro-1)));
            model1->setItem(j, 3, new QStandardItem(QString::number(generalp[i].cpuu)));
            model1->setItem(j, 4, new QStandardItem(QString::number(generalp[i].throughput)));
            model1->setItem(j, 5, new QStandardItem(QString::number(generalp[i].usAvgtime)));
            model1->setItem(j, 6, new QStandardItem(QString::number(generalp[i].ioAvgtime)));
            model1->setItem(j, 7, new QStandardItem(QString::number(generalp[i].cpuIn)));
            model1->setItem(j, 8, new QStandardItem(QString::number(generalp[i].ioIn)));


            model2->setItem(j, 0, new QStandardItem(names[i]));
            model2->setItem(j, 1, new QStandardItem(QString::number(graphpt[i].avg)));
            model2->setItem(j, 2, new QStandardItem(QString::number(graphpt[i].min)));
            model2->setItem(j, 3, new QStandardItem(QString::number(graphpt[i].max)));
            model2->setItem(j, 4, new QStandardItem(QString::number(graphpt[i].des)));
            model2->setItem(j, 5, new QStandardItem(QString::number(graphpw[i].avg)));
            model2->setItem(j, 6, new QStandardItem(QString::number(graphpw[i].min)));
            model2->setItem(j, 7, new QStandardItem(QString::number(graphpw[i].max)));
            model2->setItem(j, 8, new QStandardItem(QString::number(graphpw[i].des)));
            j++;
        }
    }

    QHeaderView *header = new QHeaderView(Qt::Horizontal,this);

    //    header->setResizeMode(QHeaderView::Stretch);
    header->setSectionResizeMode(QHeaderView::Stretch);

    ui->qtableA->setHorizontalHeader(header);
    for(int i = 0;i<9;i++)
        ui->qtableA->setColumnWidth(i,86.7);


     QFont fnt;
     fnt.setPointSize(10);
     fnt.setFamily("Arial");
    header->setFont(fnt);

    QHeaderView *header2 = new QHeaderView(Qt::Horizontal,this);
//    header2->setResizeMode(QHeaderView::Stretch);
    header2->setSectionResizeMode(QHeaderView::Stretch);
    ui->qtableB->setHorizontalHeader(header2);
    for(int i = 0;i<9;i++)
        ui->qtableB->setColumnWidth(i,86.7);

    fnt.setPointSize(10);
    header2->setFont(fnt);


    ui->qtableA->setModel(model1);
    ui->qtableB->setModel(model2);
    ui->qtableA->verticalHeader()->setVisible(false);
    ui->qtableB->verticalHeader()->setVisible(false);
    ui->qtableA->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->qtableB->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->qtableA->resizeColumnsToContents();
    ui->qtableB->resizeColumnsToContents();

}

void DataWindow::closeEvent(QCloseEvent *event) {
    emit closed();
    close();
}


void DataWindow::plot(){

    GraphDialog dialog;
    dialog.plot(msd,enabled,ui->cboxGraph->currentText(),ui->cboxGraph->currentIndex(),dataSocket->n);
    dialog.exec();

}
