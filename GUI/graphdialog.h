#ifndef GRAPHDIALOG_H
#define GRAPHDIALOG_H

#include <QDialog>
#include <multSimData.h>
#include <string>
using namespace std;
namespace Ui {
class GraphDialog;
}

class GraphDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GraphDialog(QWidget *parent = 0);
    ~GraphDialog();
    void plot(MutlSimData *msd,bool *enabled,QString name, int index, int np);

    /**
     * @brief Ejecuta los comandos de gnuPlot
     */
    void gnuplot(QString *file,string name, int cant, bool *enabled, double a, int np);


private:
    Ui::GraphDialog *ui;

    double amplitude[4];
    int *waitingClass[4];
    int *usedClass[4];
    int *turnaroundClass[4];
    QString imagePath;

public slots:

    /**
     * @brief Muestra el dialogo de guardar
     */
    void saveAs();
};

#endif // GRAPHDIALOG_H
