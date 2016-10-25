/**
  * @file graphswindow.cpp
  * @brief Definicion de los metodos de la clase GraphsWindow.
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */
#include "graphswindow.h"
#include "ui_graphswindow.h"

GraphsWindow::GraphsWindow(QWidget * parent, QString iconName):
    QMainWindow(parent),
    ui(new Ui::GraphsWindow)
{
    ui->setupUi(this);

    ui->labelImage->setStyleSheet("border: 8px solid grey;");
    queue = new QueueDialog(this);

    this->iconName=iconName;

    QMainWindow::connect(ui->cBoxAlgorithm, SIGNAL(currentIndexChanged(int)),this, SLOT(changedImage()));
    QMainWindow::connect(ui->cBoxAxis, SIGNAL(currentIndexChanged(int)),this, SLOT(changedImage()));
    QMainWindow::connect(ui->pButtonSave, SIGNAL(released()),this, SLOT(saveAs()));
    QMainWindow::connect(ui->pButtonClose, SIGNAL(released()),this, SLOT(close()));

    QMainWindow::connect(ui->pButtonPt, SIGNAL(released()),queue, SLOT(show()));


}

void GraphsWindow::changeImage(int type, int axis){

    string name=generalP.path.toStdString();
    stringstream sce;
    sce<<std::fixed;



    if(type==0){
        name+=gPw.data.toStdString();
        sce<<"Max. Time :"<<gPw.max;
        ui->labelMax->setText(QString(sce.str().c_str()));
        sce.str("");
        sce<<"Min. Time :"<<gPw.min;
        ui->labelMin->setText(QString(sce.str().c_str()));
        sce.str("");
        sce<<"Avg. Time :"<<gPw.avg;
        ui->labelAvg->setText(QString(sce.str().c_str()));
        sce.str("");
        sce<<"Avg. Time :"<<gPw.des;
        ui->labelSD->setText(QString(sce.str().c_str()));

    }
    else if(type==1){
        name+=gPu.data.toStdString();
        sce<<"Max. Time :"<<gPu.max;
        ui->labelMax->setText(QString(sce.str().c_str()));
        sce.str("");
        sce<<"Min. Time :"<<gPu.min;
        ui->labelMin->setText(QString(sce.str().c_str()));
        sce.str("");
        sce<<"Avg. Time :"<<gPu.avg;
        ui->labelAvg->setText(QString(sce.str().c_str()));
        sce.str("");
        sce<<"S.D. Time :"<<gPu.des;
        ui->labelSD->setText(QString(sce.str().c_str()));

    }

    else{
        name+=gPt.data.toStdString();
        sce<<"Max. Time :"<<gPt.max;
        ui->labelMax->setText(QString(sce.str().c_str()));
        sce.str("");
        sce<<"Min. Time :"<<gPt.min;
        ui->labelMin->setText(QString(sce.str().c_str()));
        sce.str("");
        sce<<"Avg. Time :"<<gPt.avg;
        ui->labelAvg->setText(QString(sce.str().c_str()));
        sce.str("");
        sce<<"S.D. Time :"<<gPt.des;
        ui->labelSD->setText(QString(sce.str().c_str()));

    }



    if(axis==0)
        name+="_p";

    else
        name+="_t";

    name+=".png";
    QPixmap p(name.c_str());

    ui->labelTitle->setText((generalP.algname.toStdString()+" "+ui->cBoxAlgorithm->currentText().toStdString()).c_str());
    ui->labelImage->setScaledContents(true);
    ui->labelImage->setPixmap(p);
}

GraphsWindow::~GraphsWindow()
{
    string name;
    name="self/";
    name+=gPw.data.toStdString();
    name+=".png";
    remove(name.c_str());
    name="self/";
    name+=gPu.data.toStdString();
    name+=".png";
    remove(name.c_str());
    name="self/";
    name+=gPt.data.toStdString();
    name+=".png";
    remove(name.c_str());
    delete ui;
}


void GraphsWindow::grahpsSettings(GraphParams gp){

    string file =generalP.path.toStdString()+gp.data.toStdString()+".log";
    string namet =generalP.path.toStdString()+ gp.data.toStdString()+"_t";
    string namep =generalP.path.toStdString()+ gp.data.toStdString()+"_p";
        float boxW=0;
        float mxp,mxt,my;



        boxW=(gp.max*10)/(gp.max*gp.max);
        mxp=generalP.nPro*1.10;
        mxt=generalP.time*1.10;
        my=gp.max*1.20;

        stringstream smxp,smxt,smy,sav,sboxW,sxlp,sxlt,post,posp,sminp,smint;
        smxp << mxp;
        smy << my;
        sav << gp.avg;
        sboxW<<boxW;
        sxlp<<"PID";
        posp<<"1";
        sminp<<"-1";
        gnuplot(file,gp.data.toStdString(),namep,smxp.str(),smy.str(),sav.str(),sboxW.str(),sxlp.str(),posp.str(),sminp.str());
        smxt<<mxt;
        sxlt<<"time";
        post<<"2";
        smint<<(generalP.min*0.9);

        gnuplot(file,gp.data.toStdString(),namet,smxt.str(),smy.str(),sav.str(),sboxW.str(),sxlt.str(),post.str(),smint.str());


}

void GraphsWindow::plot(){

    string name;
    name=gPw.data.toStdString();
    name.erase(name.length()-11,11);
    setLabels();
    grahpsSettings(gPu);
    grahpsSettings(gPw);
    grahpsSettings(gPt);

    name+=" ";
    changeImage(0,0);
    ui->cBoxAlgorithm->setCurrentIndex(0);
    queue->updateData();

}

void GraphsWindow::saveAs(){

    QString name;
    QString path="cp ";

    if(ui->cBoxAlgorithm->currentIndex()==0)
        name=gPw.data+".png";
    if(ui->cBoxAlgorithm->currentIndex()==1)
        name=gPu.data+".png";
    else
        name=gPt.data+".png";

    path+=name;
    path+="\ ";

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(name),
               tr("Text Files (*.png)"));
               if (!fileName.isEmpty()) {
                   path+=fileName;
                    system(path.toStdString().c_str());
                   }
               }

void GraphsWindow::setLabels(){
    stringstream sce;
    sce<<std::fixed;

    ui->labelCpuEntries->setText("CPU Entries: "+QString::number((generalP.cpuIn)));
    ui->labelCpuUt->setText("CPU Utilization: "+QString::number((generalP.cpuu)));
    ui->labelIOEntries->setText("I/O Entries: "+QString::number((generalP.ioIn)));

    sce<<"I/O Avg. Time: "<<generalP.ioAvgtime;
    ui->labelIOavgTime->setText(sce.str().c_str());

    ui->labelThrogh->setText("throughput: "+QString::number((generalP.throughput)));
    sce.str("");
    sce<<"Simulation Time: "<<generalP.time;
    ui->labelSimTime->setText(sce.str().c_str());

}


void GraphsWindow::gnuplot(string file,string name,string path,string smx,string smy,\
                                  string sav,string sboxW ,string sxl,string pos,string min){

    string commandsForGnuplot[NUM_COMMANDS] =\
    {"set title \""+name+"\"",\
     "set terminal png ",\
     "set xr ["+min+":"+smx+"]",\
     "set xlabel \""+sxl+"\"",\
     "set ylabel \""+name+"\"",\
     "set yr [0:"+smy+"]",\
     "set output \""+path+".png\"",\
     "set style fill solid 0.8 border -1",\
     "set boxwidth "+sboxW+" absolute",\
     "set arrow from "+min+","+sav+" to "+smx+","+sav+" nohead lt -1 lw 1.2 lc rgb \"red\" ",\
     "plot '"+file+"' using "+pos+":3:0 w impulses lc rgb \"blue\" title '"+name+"'"};


    ofstream plot;
    string pa;

    pa=generalP.path.toStdString()+name+".plt";
    plot.open(pa.c_str());
    int i;
      for (i=0; i < NUM_COMMANDS; i++)
          plot<<commandsForGnuplot[i].c_str()<<"\n";

      plot.close();
      string po="gnuplot "+pa;
      system(po.c_str());

      //remove(pa.c_str());
      //remove(file.c_str());

}

void GraphsWindow::changedImage(){

    changeImage(ui->cBoxAlgorithm->currentIndex(),ui->cBoxAxis->currentIndex());

}
