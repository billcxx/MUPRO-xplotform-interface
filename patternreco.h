#ifndef PATTERNRECO_H
#define PATTERNRECO_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <array>
#include <view.h>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <batch.h>

namespace Ui {
class patternReco;
}

class patternReco : public QDialog
{
    Q_OBJECT

public:
    explicit patternReco(QWidget *parent = 0);
    ~patternReco();

private slots:
    void on_loadImage_clicked();

    void on_colorPicker_PB_released();

    void on_addPhase_PB_released();

    void on_deletePhase_PB_released();

    void on_tolerance_slider_valueChanged(int position);

    void on_tolerance_LE_editingFinished();

    void colorImage(int r, int g, int b, int tolerance,int label);

    double colorWithinRange(int R,int G, int B, int r, int g, int b, int tolerance);

    void colorByTemp(int position);

    void colorByTable(int index,bool considerTemp);

    std::array<double,3> convertRGBToLab(int intR,int intG,int intB);

    void on_refersh_PB_released();

    void on_exportInfo_PB_released();

    void on_loadInfo_PB_released();

    void on_exportData_PB_released();

    void on_scalarVectorSwitch_Combo_currentIndexChanged(int index);

    void on_phaseNumber_LE_editingFinished();

    void clearProcessedImage();

    void colorTableRow(int row);

    void on_vectorValue_LE_textChanged(const QString &arg1);

    QImage* makePeriodic(QImage *input);

    void loadImage(QString load);

    void updateColorByDistance();

private:
    Ui::patternReco *ui;
    View *originalView= new View("Original view");
    View *processedView= new View("Processed view");
    QGraphicsPixmapItem *processedPixmap,*originalPixmap;
    QGraphicsScene *originalScene,*processedScene;
    QVector<QRgb> colorTable;
    int **domainRGB,**indexMap;
    double ***colorDistance;
    double outDomain[27][3];
    double M[3][3];
    double white[3];
    double epsilon=0.008856,kappa=903.3;
};

#endif // PATTERNRECO_H
