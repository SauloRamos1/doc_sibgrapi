#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QPainter>

#include <QFileDialog>

#include <QList>
#include <QVector>
#include <QDebug>

#include <QListWidget>

#include <halfedge.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *e);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QDir path;
    QStringList files;
    QString fileName;

    QString fileSvg;

    float contoursamplingvalue;
    float gridsamplingvalue;

    float lshapesvalue; // float lambdashapesvalue;

    // Não vai mais existir ---  lambdadepthpartsvalue;

    // Ajuste Membros Simétricos
    float lsym;  // Largura dos Membros Simétricos
    float ldepthsym; // Profundidade dos Membros Simétricos

    // Ajuste Island
    float lisland; // Largura dos Island
    float ldepthisland; //Profundidade dos Island

    // Ajuste Adjacent
    float ladj; // Largura para adjacents sem features
    float adjnewcontour; //Constante que multiplica altura das normais do feature para saber onde colocar nova linha do adjacent
    float ldepthadj; // Profundidade dos Adjacent


    bool imagemcarregada = false;
    int ncurvas = 0;



    QVector<QVector<float>> listadecurvas;
    QVector<HalfEdge*> listadeciclos;


    void classificaciclos();

    void pintaciclos(QPainter *painter);

    float getPathArea(QPainterPath p, float step);

    bool almostEqual(float a, float b);

    void defineciclo(HalfEdge* half);

    QPainterPath criapath (HalfEdge* half);

    QPolygonF criapoligono (HalfEdge* half);

    void gerarbf(QPainter *painter);

private:
    Ui::MainWindow *ui;

public slots:

private slots:
    void on_pushButton_released();

    void on_listWidget_currentRowChanged(int currentRow);

    void on_contoursampling_sliderMoved(int position);
    void on_gridsampling_sliderMoved(int position);

    void on_slider_lshapes_sliderMoved(int position);
    void on_slider_lsym_sliderMoved(int position);
    void on_slider_ldepthsym_sliderMoved(int position);
    void on_slider_lisland_sliderMoved(int position);
    void on_slider_ldepthisland_sliderMoved(int position);
    void on_slider_adjnewcontour_sliderMoved(int position);
    void on_slider_ldepthadj_sliderMoved(int position);
    void on_slider_ladj_sliderMoved(int position);
};

#endif // MAINWINDOW_H
