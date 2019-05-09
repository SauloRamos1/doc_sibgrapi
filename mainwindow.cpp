#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "halfedge.h"

#include<stdlib.h>

#include <stdio.h>
#include <string.h>
#include <float.h>
#include <fstream>

#include <QCoreApplication>
#include <QVector>
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <algorithm>
#include <float.h>
#include <QDebug>
#include <QPoint>

#define NANOSVG_IMPLEMENTATION
#include "nanosvg.h"
#define NANOSVGRAST_IMPLEMENTATION
#include "nanosvgrast.h"

#include <QMessageBox>
#include <QPolygon>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    path = "C:/Users/srdcp/Dropbox/ProjetoDoutorado/ProjetoDoutorado/Apps/doc_v3";

    files = path.entryList(QStringList() << "*.svg" << "*.SVG",QDir::Files);


    ui->listWidget->addItems(files);


    contoursamplingvalue = ui->contoursampling->value();
    gridsamplingvalue = ui->gridsampling->value();

    ui->contoursamplingvalue->setText(QString ("%1").arg(contoursamplingvalue));
    ui->gridsamplingvalue->setText(QString ("%1").arg(gridsamplingvalue));

    // Ajuste Border Cycles
    lshapesvalue = ui->slider_lshapes->value();
    ui->label_lshapes->setText(QString ("%1").arg(1/lshapesvalue));

    // Ajuste Membros Simétricos
    lsym = ui->slider_lsym->value();
    ui->label_lsym->setText(QString ("%1").arg(1/lsym));

    ldepthsym = ui->slider_ldepthsym->value();
    ui->label_ldepthsym->setText(QString ("%1").arg(1/ldepthsym));

    // Ajuste Island
    lisland = ui->slider_lisland->value();
    ui->label_lisland->setText(QString ("%1").arg(1/lisland));

    ldepthisland = ui->slider_ldepthisland->value();
    ui->label_ldepthisland->setText(QString ("%1").arg(1/ldepthisland));

    // Ajuste Adjacent

    ladj = ui->slider_ladj->value();
    ui->label_ladj->setText(QString ("%1").arg(1/ladj));

    adjnewcontour = ui->slider_adjnewcontour->value();
    ui->label_adjnewcontour->setText(QString ("%1").arg(adjnewcontour));

    ldepthadj = ui->slider_ldepthadj->value();
    ui->label_ldepthadj->setText(QString ("%1").arg(1/ldepthadj));



}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e){

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);

    if (imagemcarregada == true){

        pintaciclos(&painter);

        //   gerarbf(&painter);
    }


}


float MainWindow::getPathArea(QPainterPath p, float step)
{
    QPointF a,b;
    float len;
    float area=0;
    for(len=0; len<p.length(); len+=step)
    {
        a=p.pointAtPercent(p.percentAtLength(len));
        b=p.pointAtPercent(p.percentAtLength(len+step>p.length()?p.length():len+step));
        area+=(b.x() - a.x())*(a.y()+b.y());
    }
    return area/float(2);
}


bool MainWindow::almostEqual(float a, float b)
{
    //return fabs(a - b) <= FLT_EPSILON;
    return fabs(a - b) <= 3;
    //return fabs(a - b) <= 3;
}

// Marca os ciclos com inteiros -
void MainWindow::defineciclo(HalfEdge* half){
    HalfEdge* begin = half;

    //    if (half->cycle != 0){
    //        return;
    //    }

    int ciclo = half->cycle;
    do {
        half->cycle = ciclo;

        half = half->next;
    } while (half != begin);

}

QPolygonF MainWindow::criapoligono(HalfEdge *half){

    HalfEdge* begin = half;

    QPolygon poligonodociclo;

    do {
        QPoint ponto (half->p0.x(),half->p0.y());
        if (!poligonodociclo.containsPoint(ponto,Qt::WindingFill)){
            poligonodociclo << QPoint (half->p0.x(),half->p0.y());
        }

        half = half->next;
    } while (half != begin);

    return poligonodociclo;

}


void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    qDebug () <<files ;

    fileName.clear();

    fileName = path.absoluteFilePath(fileName);
    fileName.append("/") ;
    fileName.append(files.at(currentRow));

    fileSvg.clear();
    fileSvg = files.at(currentRow);
    qDebug () << fileName;

}

void MainWindow::on_pushButton_released()
{


    //    QString fileName;
    //    QByteArray fileFormat = "svg";

    //    fileName = QFileDialog :: getOpenFileName (this ,"Open File",QDir::homePath(), QString("\%1 Files (*.\%2)").arg(QString (fileFormat.toUpper())).arg(QString(fileFormat)));
    //    //fileName = "/home/saulo/Dropbox/Saulo/ProjetoDoutorado/Apps/gato.svg";
    const char *file = fileName.toStdString().c_str();

    if (!fileName.isEmpty()){
        imagemcarregada = true;
    }

    // Load

    NSVGimage* image;

    //image = nsvgParseFromFile("gato.svg", "px", 96);

    image = nsvgParseFromFile(file, "px", 96);

    ncurvas = 0;
    //QTime t;
    //t.start();

    for (NSVGshape *shape = image->shapes; shape != NULL; shape = shape->next) {
        for (NSVGpath *path = shape->paths; path != NULL; path = path->next) {
            for (int i = 0; i < path->npts-1; i += 3) {
                float* p = &path->pts[i*2];


                QVector<float> curva(8);
                curva[0] = (float)p[0] ;
                curva[1] = (float)p[1] ;
                curva[2] = (float)p[2] ;
                curva[3] = (float)p[3] ;
                curva[4] = (float)p[4] ;
                curva[5] = (float)p[5] ;
                curva[6] = (float)p[6] ;
                curva[7] = (float)p[7] ;

                if (!((curva[0] == curva [6]) && (curva[1] == curva[7]) && curva[2] == curva [4])){
                    listadecurvas.push_back(curva);
                    //qDebug () << curva;

                    ncurvas += 1;
                }

            }
        }
    }

    HalfEdgeGraph g;

    g.criaestruturadehalfedges(listadecurvas);

    listadeciclos = g.separaciclos();
    imagemcarregada = true;

    classificaciclos();

    this->update();

}

QPainterPath MainWindow::criapath (HalfEdge* half){
    HalfEdge* begin = half;

    QPainterPath totalPath;

    do
    {
        QPainterPath myPath;

        myPath.moveTo(half->p0.x(),half->p0.y());
        myPath.cubicTo(half->p1.x(),half->p1.y(),half->p2.x(),half->p2.y(),half->p3.x(),half->p3.y());

        totalPath.addPath(myPath);

        half = half->next;

    } while(half != begin);

    return totalPath;

}

void MainWindow::pintaciclos(QPainter *painter){


    for (int i = 0; i <listadeciclos.size(); i++){

        //        \definecolor{outer}{RGB}{251,154,153}
        //        \definecolor{border}{RGB}{55,126,184}
        //        \definecolor{island}{RGB}{77,175,74}
        //        \definecolor{adjacent}{RGB}{152,78,163}
        //        \definecolor{feature}{RGB}{255,127,0}
        //        \definecolor{others}{RGB}{228,26,28}

        //Pinta Outer
        //        if (listadeciclos[i]->cycle == 1){
        //            QPainterPath  totalPath = criapath (listadeciclos[i]);
        //            painter->setPen(QPen(QColor(251,154,153,99), 7, Qt::SolidLine));
        //            painter->drawPath(totalPath);
        //        }
        //Pinta Border

        if (listadeciclos[i]->cycle == 2){
            QPainterPath  totalPath = criapath (listadeciclos[i]);
            painter->setPen(QPen(QColor(55,126,184), 3, Qt::DashDotLine));
            painter->drawPath(totalPath);
        }

        //Pinta Island

        if (listadeciclos[i]->cycle == 3){
            QPainterPath  totalPath = criapath (listadeciclos[i]);
            painter->setPen(QPen(QColor(77,175,74), 3, Qt::DashDotLine));
            painter->drawPath(totalPath);
        }

        //Pinta Adjacents

        if (listadeciclos[i]->cycle == 4){
            QPainterPath  totalPath = criapath (listadeciclos[i]);
            painter->setPen(QPen(QColor(152,78,163), 3, Qt::DashDotLine));
            painter->drawPath(totalPath);
        }

        //Pinta Features

        if (listadeciclos[i]->cycle == 5){
            QPainterPath  totalPath = criapath (listadeciclos[i]);
            painter->setPen(QPen(QColor(255,127,0), 3, Qt::DashDotLine));
            painter->drawPath(totalPath);
        }

        //Pinta Others

        //        if (listadeciclos[i]->cycle == 6){
        //            QPainterPath  totalPath = criapath (listadeciclos[i]);
        //            painter->setPen(QPen(QColor(228,26,28), 2, Qt::DashDotLine));
        //            painter->drawPath(totalPath);
        //        }

        //Pinta Simétricos
        if (listadeciclos[i]->cycle == 7){
            QPainterPath  totalPath = criapath (listadeciclos[i]);
            painter->setPen(QPen(QColor(255,0,0), 3, Qt::DashDotLine));
            painter->drawPath(totalPath);
        }

        //Pinta Simétricos em Background
        if (listadeciclos[i]->cycle == 8){
            QPainterPath  totalPath = criapath (listadeciclos[i]);
            painter->setPen(QPen(QColor(0,0,255), 3, Qt::DashDotLine));
            painter->drawPath(totalPath);
        }

    }

    gerarbf(painter);
}

void MainWindow::classificaciclos(){

    QVector <int> areas ;

    int menorarea = 0;
    QVector <HalfEdge*> others;
    HalfEdge* outercycle;

    for (int i = 0; i < listadeciclos.size(); i++){

        HalfEdge* begin = listadeciclos[i];
        HalfEdge* half = begin;

        QPainterPath totalPath;

        do
        {
            QPainterPath myPath;

            myPath.moveTo(half->p0.x(),half->p0.y());
            myPath.cubicTo(half->p1.x(),half->p1.y(),half->p2.x(),half->p2.y(),half->p3.x(),half->p3.y());

            totalPath.addPath(myPath);

            half = half->next;

        } while(half != begin);

        int area = getPathArea(totalPath, 10);


        if (area >=0){
            //            int r = rand() % 255;
            //            int g = rand() % 255;
            //            int b = rand() % 255;
            //            painter->setPen(QPen(QColor(r,g,b), 5, Qt::DashDotDotLine));
            //            painter->drawPath(totalPath);
        } else {
            others.push_back(listadeciclos[i]);
            if (area < menorarea){
                menorarea = area;
                outercycle = listadeciclos[i];
                //others.removeLast();
            }

        }

        areas.push_back(area);
    }

    //Remove Outer da lista de Others

    int apagaindex = others.indexOf(outercycle);

    others.removeAt(apagaindex);

    // ---------------

    /// 0 - Não Classificado - OK
    /// 1 - Outer Cycle - oK
    /// 2 - Border - oK
    /// 3 - Island - oK
    /// 4 - Adjacent Border Cycle
    /// 5 - Adjacent Feature Cycle
    /// 6 - Others
    ///
    /// Após identificar simetria
    ///
    /// 7 - Membro Simétrico
    /// 8 - Background do membro simétrico

    //  ----  Classifica OuterCycle ----

    outercycle->cycle = 1;

    defineciclo(outercycle);

    //   ----  Classifica Others e Island ----

    for (int i=0 ; i < others.size(); i++){
        others[i]->cycle = 6;
        defineciclo(others[i]);

        //Todo ciclo inverso ao other é island
        others[i]->twin->cycle = 3;
        defineciclo(others[i]->twin);
    }

    //  ------ Identifica Border

    HalfEdge* begin = outercycle;
    HalfEdge* half = begin;


    do {
        half->twin->cycle = 2;

        defineciclo(half->twin);

        half = half->next;
    } while (half != begin);

    // ------ Classifica Restante como Adjacent para depois separar em adjacent ou feature

    for (int i = 0; i <listadeciclos.size(); i++){

        if (almostEqual(areas[i], 0)){ // É adjacent ou border
            listadeciclos[i]->cycle = 4;
            defineciclo(listadeciclos[i]);
        }
    }

    QVector <HalfEdge*> adjacenteslist;

    QVector <QVector <HalfEdge*>> adjacentesefeatureslist;

    for (int i = 0; i <listadeciclos.size(); i++){

        if (listadeciclos[i]->cycle == 4){
            adjacenteslist.push_back(listadeciclos[i]);
        }
    }

    if (adjacenteslist.size() > 1){
        for (int i = 0; i < adjacenteslist.size(); i++){
            for (int j = 0; j < adjacenteslist.size(); j++){

                // - - - - - -Se uma adjacente estiver dentro da outra - - - - -
                if (i != j){


                    QPolygonF poligono1 = criapoligono(adjacenteslist[i]);
                    QPolygonF poligono2 = criapoligono(adjacenteslist[j]);

                    if (poligono1.boundingRect().contains(poligono2.boundingRect())){
                        adjacenteslist[i]->cycle = 4;
                        defineciclo(adjacenteslist[i]);
                        adjacenteslist[j]->cycle = 5;
                        defineciclo(adjacenteslist[j]);
                    } else if  (poligono2.boundingRect().contains(poligono1.boundingRect())){
                        adjacenteslist[j]->cycle = 4;
                        defineciclo(adjacenteslist[j]);
                        adjacenteslist[i]->cycle = 5;
                        defineciclo(adjacenteslist[i]);
                    }

                    //                    if (poligono1.contains(poligono2.at(0))){
                    //                        //Adjacent é 1, Feature é 2
                    //                        qDebug () <<" a ";


                    //                    } else if (poligono2.contains(poligono1.at(0))){
                    //                        //Adjacent é 2, Feature é 1
                    //                        qDebug () <<" a ";

                    //                    }



                }



            }
        }
    }






    //----------Identifica PICOS-----------

    //painter->setPen(QPen(QColor(50, 50, 50), 4, Qt::SolidLine));

    QVector <HalfEdge*> linhassugestivas;



    for (int i = 0; i < listadeciclos.size(); i++){

        if (listadeciclos[i]->cycle == 2){

            HalfEdge* begin = listadeciclos[i];
            HalfEdge* half = begin;

            do
            {

                if (half->next == half->twin){
                    //painter->drawEllipse(half->p3,5,5);
                    linhassugestivas.push_back(half);
                }

                half = half->next;

            } while(half != begin);
        }


    }

    float distancia1 = 0; //Soma das distancias pela primeira aresta
    float distancia2 = 0; //Soma das distancias pela segunda aresta

    if (linhassugestivas.size() > 2){
        linhassugestivas.push_back(linhassugestivas.at(0));
    }

    //    for (int i = 0;  i < linhassugestivas.size()-1; i = i +2){
    //        painter->setPen(QPen(QColor(50, 50, 50), 1, Qt::SolidLine));
    //        painter->drawLine(linhassugestivas[i]->p3,linhassugestivas[i+1]->p3);

    //    }

    if (linhassugestivas.size() == 2){

        // Testa se a ordem das linhassugestivas está certa...
        // Caso o ciclo tenha começado no meio das linhas
        // Soma a quantidade de halfedges que passa para chegar no outro ponto

        qDebug () << "Tamanho 2";
        HalfEdge* begin = linhassugestivas[0];
        HalfEdge* half = begin;

        do
        {
            distancia1 +=1;
            half = half->next;

        } while(half != linhassugestivas[1]);

        begin = linhassugestivas[1];
        half = begin;

        do
        {
            distancia2 +=1;
            half = half->next;

        } while(half != linhassugestivas[0]);

        if (distancia2 < distancia1){ //Inverte as Halfs pq o ciclo começou no meio das 2
            HalfEdge* aux;
            aux = linhassugestivas[1];
            linhassugestivas[1] = linhassugestivas [0];
            linhassugestivas[0] = aux;
        }
    }


    distancia1 = 0; //Soma das distancias pela primeira aresta
    distancia2 = 0; //Soma das distancias pela segunda aresta

    if (linhassugestivas.size() > 2){
        // ---- Testa primeiros pares
        for (int i = 0;  i < linhassugestivas.size()-1; i = i +2){

            distancia1 += QLineF( linhassugestivas[i]->p3, linhassugestivas[i+1]->p3).length();
        }
        for (int i = 1;  i < linhassugestivas.size()-1; i = i +2){

            distancia2 += QLineF( linhassugestivas[i]->p3, linhassugestivas[i+1]->p3).length();

        }

        //    qDebug () << "Distancia 1:" << distancia1;
        //    qDebug () << "Distancia 2:" << distancia2;

        // --- A distancia menor, tem os pares corretos

        if (distancia1 < distancia2){
            linhassugestivas.removeAt(linhassugestivas.size()-1);
        } else {
            linhassugestivas.removeAt(0);
        }

    }

    //    for (int i = 0;  i < linhassugestivas.size()-1; i = i +2){
    //        painter->setPen(QPen(QColor(255, 0, 0), 1, Qt::SolidLine));
    //        painter->drawLine(linhassugestivas[i]->p3,linhassugestivas[i+1]->p3);

    //    }

    qDebug () << "# de Linhas Sugestivas" << linhassugestivas.size();

    for (int i = 0;  i < linhassugestivas.size()-1; i = i +2){

        //painter->setPen(QPen(QColor(50, 50, 50), 5, Qt::SolidLine));
        //painter->drawLine(linhassugestivas[i]->p3,linhassugestivas[i+1]->p3);

        HalfEdge *he0 = new HalfEdge;
        HalfEdge *he1 = new HalfEdge;

        he0->twin = he1;
        he1->twin = he0;

        he0->p3 = linhassugestivas[i]->p3;
        he0->p2 = linhassugestivas[i]->p3 + (linhassugestivas[i]->p3 - linhassugestivas[i]->p2);

        he0->p1 =  linhassugestivas[i+1]->p3 + (linhassugestivas[i+1]->p3 - linhassugestivas[i+1]->p2);
        he0->p0 = linhassugestivas[i+1]->p3;

        //painter->setPen(QPen(QColor(50, 50, 50), 4, Qt::SolidLine));

        QPainterPath myPath;

        myPath.moveTo(he0->p0.x(),he0->p0.y());
        myPath.cubicTo(he0->p1.x(),he0->p1.y(),he0->p2.x(),he0->p2.y(),he0->p3.x(),he0->p3.y());

        //painter->drawPath(myPath);

        // Agora tem que desenhar a linha do corpo abaixo e fechar o ciclo das half-edges

        // O ponto em vermelho é o primeiro

        //painter->setPen(QPen(QColor(255, 0, 0), 5, Qt::SolidLine));
        //painter->drawEllipse (linhassugestivas[i]->p3,3,3);

        //painter->setPen(QPen(QColor(50, 50, 50), 4, Qt::SolidLine));

        //=== Aqui preciso encontrar a Half-Edge que faz um T pra desligar o ciclo do membro simétrico
        // Partindo das linhas sugestivas (picos) encontrar a próxima Half-Edge que a twin não faz parte do ciclo

        //painter->setPen(QPen(QColor(0, 0, 255), 10, Qt::SolidLine));
        HalfEdge* begin = linhassugestivas[i];
        HalfEdge* half = begin;


        HalfEdge* cheganot1 ; //Half-edge que chega no T-junction

        while(half->numerodociclo == half->twin->numerodociclo)
        {

            half = half->prev;

        }

        cheganot1 = half;


        QPainterPath linha1;

        linha1.moveTo(half->p0.x(),half->p0.y());
        linha1.cubicTo(half->p1.x(),half->p1.y(),half->p2.x(),half->p2.y(),half->p3.x(),half->p3.y());

        //painter->drawPath(linha1);

        begin = linhassugestivas[i+1];
        half = begin;


        HalfEdge* saidot2 ; //Half-edge que sai do T-junction

        while(half->numerodociclo == half->twin->numerodociclo)
        {

            half = half->next;

        }

        saidot2 = half;


        QPainterPath linha2;

        linha2.moveTo(half->p0.x(),half->p0.y());
        linha2.cubicTo(half->p1.x(),half->p1.y(),half->p2.x(),half->p2.y(),half->p3.x(),half->p3.y());

        //painter->drawPath(linha2);

        //painter->setPen(QPen(QColor(0, 255, 0), 4, Qt::DotLine));


        // ---------------- Desenha a linha que fecha o corpo abaixo do membro simétrico ----------------
        HalfEdge *he3 = new HalfEdge;
        //HalfEdge *he4 = new HalfEdge;

        // he3->twin = he4;
        // he4->twin = he3;

        he3->p0 = cheganot1->p3;
        he3->p1 = cheganot1->p3 + (cheganot1->p3 - cheganot1->p2);

        he3->p2 =  saidot2->p0 + (saidot2->p0 - saidot2->p1);
        he3->p3 = saidot2->p0;

        QPainterPath linhadocorpo;

        linhadocorpo.moveTo(he3->p0.x(),he3->p0.y());
        linhadocorpo.cubicTo(he3->p1.x(),he3->p1.y(),he3->p2.x(),he3->p2.y(),he3->p3.x(),he3->p3.y());

        //painter->drawPath(linhadocorpo);
        // ---------------- ------------------------------ ----------------

        //------------------Fecha os ciclos --- Membro simétrico e corpo abaixo -----------

        // Membro Simétrico
        // he0 -- interno, antihorário
        // he1 -- externo, horário

        //Corpo abaixo do membro simétrico
        // he3 -- Interno, Border cycle
        // he4 --Externo, Outer cycle

        // Linhas:
        // linhassugestivas[i] e linhassugestivas[i+1]  -- Primeira e segunda linha
        // cheganot / saidot -- linha que chega no membro e linha que sai no membro  (Ambos no T)

        //Fecha o ciclo das half-edges internas do membro simétrico

        he0->next = linhassugestivas[i]->twin;
        linhassugestivas[i]->twin->prev = he0;

        he0->prev = linhassugestivas[i+1];
        linhassugestivas[i+1]->next = he0; // ESTÁ AQUI O PROBLEMA

        ///ACHO QUE POR CAUSA DO REPAINT / UPDATE SEI Lá
        /// Talvez terminando os ciclos,  volte ao normal
        /// IR até o fim de fechar os ciclos e rodar.. Aí os ciclos estarão certos.

        // Só da pra garantir o he0.

        //        he1->prev = linhassugestivas[i];
        //        linhassugestivas[i]->next = he1;
        //        he1->next = linhassugestivas[i+1]->twin;
        //        linhassugestivas[i+1]->twin->prev = he1;

        // Liga he3 e he4

        // Está faltando pular o ciclo interno (border)

        //Desliga o membro do corpo

        // Só da pra garantir o he3

        //        cheganot1->twin->prev->next = cheganot1->next;
        //        cheganot1->next->prev = cheganot1->twin->prev;

        //        saidot2->prev->next = saidot2->twin->next;
        //        saidot2->twin->next->prev = saidot2->prev;

        //-------

        cheganot1->next = he3;
        he3->prev = cheganot1;
        he3->next = saidot2;
        saidot2->prev = he3;

        // Só da pra garantir o he3

        //        he4->next = cheganot1->twin;
        //        cheganot1->twin->prev = he4;
        //        he4->prev = saidot2->twin;
        //        saidot2->twin->next = he4;


        // 7 - Membro simétrico


        //        QVector <HalfEdge* > backuplistadeciclos = listadeciclos;

        //        listadeciclos.clear();

        //        for (int j = 0; j < backuplistadeciclos.size() ; j++){
        //            if (backuplistadeciclos[j]->cycle != 2){
        //                listadeciclos.push_back(backuplistadeciclos[j]);
        //            }
        //        }

        //Limpa lista de ciclos pra adicionar o novo ciclo

        for (int j = 0; j < listadeciclos.size() ; j++){

            HalfEdge* begin = listadeciclos[j];
            HalfEdge* half = begin;

            do
            {

                if (half == he0->next || half == he3->next){


                    listadeciclos.removeAt(j);
                    j--;
                    break;


                }

                half = half->next;

            } while(half != begin);



        }


        he0->cycle = 7; // 7 - Membro simétrico

        defineciclo(he0);


        he3->cycle = 2; // Border

        defineciclo(he3);

        //he4->cycle = 1; // Outer


        listadeciclos.push_back(he0);
        //        listadeciclos.push_back(he1);

        listadeciclos.push_back(he3);
        //        listadeciclos.push_back(he4);



    }

    // -------------------------------------------------------------------------------------------------------
    /// -- Agora elimina os border cycles correspondentes aos membros simétricos
    ///
    ///
    ///
    ///
    ///


    for (int i = 0; i < listadeciclos.size(); i++){
        float distanciaentremembros = INT_MAX;
        int ciclodobackground;
        if (listadeciclos[i]->cycle == 7){
            QPolygonF poligonodomembrosimetrico = criapoligono(listadeciclos[i]);
            QRectF rectdomembro = poligonodomembrosimetrico.boundingRect();

            //QPointF centro = rectdomembro.center();
            // qDebug () << centro;


            for (int j = 0; j < listadeciclos.size(); j++){
                if (j != i && listadeciclos[j]->cycle == 2){
                    QPolygonF poligonodoborder = criapoligono(listadeciclos[j]);
                    QRectF rectdoborder = poligonodoborder.boundingRect();

                    //QPointF centrodoborder = rectdoborder.center();
                    //qDebug () << centrodoborder;

                    float  novadistancia = 0;

                    novadistancia += QLineF (rectdomembro.bottomLeft(),rectdoborder.bottomLeft()).length();
                    novadistancia += QLineF (rectdomembro.bottomRight(),rectdoborder.bottomRight()).length();
                    novadistancia += QLineF (rectdomembro.topLeft(),rectdoborder.topLeft()).length();
                    novadistancia += QLineF (rectdomembro.topRight(),rectdoborder.topRight()).length();

                    if (novadistancia < distanciaentremembros){
                        distanciaentremembros = novadistancia;
                        ciclodobackground = j; //Salva index do possível ciclo em background
                    }
                }

            }

            listadeciclos[ciclodobackground]->cycle = 8;
            defineciclo(listadeciclos[ciclodobackground]);
            //            listadeciclos.removeAt(ciclodobackground);
            //            i--;

        }

    }

}


/// 0 - Não Classificado
/// 1 - Outer Cycle
/// 2 - Border
/// 3 - Island
/// 4 - Adjacent Border Cycle
/// 5 - Adjacent Feature Cycle
/// 6 - Others
///
/// Após identificar simetria
///
/// 7 - Membro Simétrico
/// 8 - Background do membro simétrico

/// USAMOS SOMENTE
/// 2 - Border
/// 3 - Island
/// 4 - Adjacent Border Cycle
/// 5 - Adjacent Feature Cycle
/// 7 - Membro Simétrico
///
///
void MainWindow::gerarbf(QPainter *painter){

    //        \definecolor{outer}{RGB}{251,154,153}
    //        \definecolor{border}{RGB}{55,126,184}
    //        \definecolor{island}{RGB}{77,175,74}
    //        \definecolor{adjacent}{RGB}{152,78,163}
    //        \definecolor{feature}{RGB}{255,127,0}
    //        \definecolor{others}{RGB}{228,26,28}

    for (int i = 0 ; i < listadeciclos.size() ; i++){

        switch (listadeciclos[i]->cycle) {

        case 2:
            painter->setPen(QPen(QColor(55,126,184), 3, Qt::SolidLine));
            break;
        case 3:
            painter->setPen(QPen(QColor(77,175,74), 3, Qt::SolidLine));
            break;
        case 4:
            painter->setPen(QPen(QColor(152,78,163), 3, Qt::SolidLine));
            break;
        case 5:
            painter->setPen(QPen(QColor(255,127,0), 3, Qt::SolidLine));
            break;
        case 7:
            painter->setPen(QPen(QColor(255,0,0), 3, Qt::SolidLine));
            break;

        }

        std::vector<QVector3D>knownPoints;
        std::vector<QVector3D>knownNormals;

        std::vector<QVector3D>totalPoints;
        std::vector<QVector3D>totalNormals;


        // Amostra Pontos e Normais no contorno do Border Cycle;
        if (listadeciclos[i]->cycle == 2){
            QPainterPath border;

            border = criapath(listadeciclos[i]) ;
            for (float var = border.length(); var > 0 ; var = var - contoursamplingvalue){

                float percent = var / border.length();

                QLineF angleline;
                /* Set the origin: */
                angleline.setP1(border.pointAtPercent(percent));
                QVector3D ponto;

                ponto.setX(border.pointAtPercent(percent).x());
                ponto.setY(border.pointAtPercent(percent).y());
                ponto.setZ(0);
                knownPoints.push_back(ponto);

                /* Set the angle and length: */
                angleline.setAngle(border.angleAtPercent(percent)-90);
                angleline.setLength(1);
                QVector3D vetornormal(0,0,0);

                vetornormal.setX(angleline.x2()-angleline.x1());
                vetornormal.setY(angleline.y2()-angleline.y1());

                knownNormals.push_back(vetornormal);

                painter->drawLine(ponto.x(), ponto.y(),ponto.x() + vetornormal.x()*5,ponto.y() + vetornormal.y()*5);

            }

            std::string outFile = "rbf";
            outFile.append("_");
            outFile.append(fileSvg.toStdString());
            //Remover o .svg do nome
            outFile.pop_back();
            outFile.pop_back();
            outFile.pop_back();
            outFile.pop_back();
            //std::string s = ;
            outFile.append("_ID");
            outFile.append(std::to_string(listadeciclos[i]->cycle));
            outFile.append("_Ciclo");
            outFile.append(std::to_string(i));
            outFile.append(".data");

            QFont font = painter->font() ;
            font.setPointSize ( 18 );
            //font.setWeight(QFont::DemiBold);
            painter->setFont(font);

            QString s = QString::number(i);

            QRectF boundingbox = border.boundingRect();

            qDebug ()<< "Bounding box size: " <<  boundingbox.size() << " - Ciclo:" << i;

            painter->drawText(boundingbox, Qt::BottomRightCorner, s);

            ///pode ser via seletor de arquivo.
            ///Preencha os vetores com os pontos do desenho e as normais conhecidas
            ///precisamos pontos 3D; preencha o z com 0
            ///
            ///
            ///

            //////////PREENCHER OS VETORES KNOWNPOINTS & KNOWNNORMALS

            //EXPORTA DADOS RBF

            QPolygonF poligonodabezier;

            for(QVector3D pi:knownPoints){
                totalPoints.push_back(pi);
                poligonodabezier << QPoint (pi.x(),pi.y());
            }

            for(QVector3D ui:knownNormals){
                ui.normalize();
                totalNormals.push_back(ui);
            }

            float xmin = boundingbox.left();
            float xmax = boundingbox.right();
            float ymin = boundingbox.top();
            float ymax = boundingbox.bottom();

            cout <<  outFile << endl;
            // qDebug () << xmax-xmin;
            // qDebug () << ymax-ymin;

            painter->drawRect(boundingbox);


            //float spacing = (xmax - xmin) /10;  //5.0;///Espacamento do grid
            float spacing = gridsamplingvalue;
            int r,g,b;
            // qDebug ()<< "Spacing" << spacing;
            for(float x = xmin; x < xmax; x = x + spacing)
            {
                for(float y = ymin; y < ymax; y = y + spacing)
                {
                    QPointF ponto (x,y);

                    if (poligonodabezier.containsPoint(ponto,Qt::WindingFill)){

                        ///para cada ponto do grid... que esteja dentro do contorno
                        QVector3D p(x,y,0);
                        //calcula o peso
                        float weight = 0;
                        for(QVector3D pi:knownPoints)
                        {
                            weight += 1.0/((p-pi).lengthSquared());///acho que isso retorna a norma ao 2

                            ///PROBLEMA
                            /// Talvez tenha que trazer os pontos para 0~1
                        }

                        ///calcula a normal
                        QVector3D n(0,0,0);
                        for(int i = 0; i <knownNormals.size(); i++)
                        {
                            QVector3D pi = knownPoints.at(i);
                            QVector3D ui = knownNormals.at(i);
                            n += (ui / (p-pi).lengthSquared());///acho que isso retorna a norma ao 2
                        }

                        n = n / weight;

                        n.setZ(sqrt(1 - n.x()*n.x() - n.y()*n.y()));

                        if  (n.z() < .5){

                            r = (abs(n.x()) + 1)/2*255;
                            g = (abs(n.y()) + 1)/2*255;
                            b = (n.z() + 1)/2*255;

                            //painter->setPen(QPen(QColor(r,g,b), 5, Qt::SolidLine));
                            //painter->drawLine(ponto.x(), ponto.y(), ponto.x(), ponto.y());

                            //painter->setPen(QPen(QColor(50,50,50), 3, Qt::SolidLine));

                            //painter->setPen(QPen(QColor(51, 153, 255), 4, Qt::SolidLine));
                            //painter->drawLine(ponto.x(), ponto.y(), ponto.x(), ponto.y());
                            //painter->drawPoint(ponto.x(),ponto.y());
                            painter->drawRoundRect(ponto.x(),ponto.y(),2,2);
                            // painter->drawEllipse(ponto.x(),ponto.y(),1,1);

                            ///Tem que dar uma altura para esses pontos, eu tô chutando o z da normal, mas nao sei se serve.
                            //p.setZ(n.z());

                            ///calculou para um ponto no grid a norma dele. agora coloca no vetor final.
                            //p.setZ(1);

                            p.setZ(n.z()*(boundingbox.width()/lshapesvalue));
                            totalPoints.push_back(p);
                            totalNormals.push_back(n);
                            //qDebug () << p;
                            //qDebug () << "Z+ .. " << "Ponto: " <<p << "Normal: "<< n;
                            p.setZ(n.z()*(-boundingbox.width()/lshapesvalue));
                            totalPoints.push_back(p);
                            //qDebug () << p;
                            n.setZ(n.z()*-1);
                            //n = n*-1;
                            totalNormals.push_back(n);

                            //qDebug () << "Z- .. " << "Ponto: " <<p << "Normal: "<< n;
                        }
                    }


                }

            }

            ///agora abre um arquivo pra salvar estes dados para serem entrada do RBF. Esse é o formato que eu uso
            std::ofstream fOut;
            fOut.open(outFile.c_str());
            fOut << "3" <<std::endl;
            fOut << knownPoints.size() <<std::endl;
            for(QVector3D p:knownPoints)
            {
                fOut << p.x() <<" " << p.y()<< " " << p.z()<< std::endl;
            }

            fOut << totalNormals.size() << std::endl;

            for(int i = 0; i < totalNormals.size(); i++)
            {

                QVector3D p = totalPoints.at(i);
                QVector3D n = totalNormals.at(i);

                fOut << n.x() <<" " << n.y()<< " " << n.z()<< std::endl;
                fOut << p.x() <<" " << p.y()<< " " << p.z()<< std::endl;
            }
            fOut << "0" << std::endl;
            fOut.close();

        }

        if (listadeciclos[i]->cycle == 3){ // Se for Island (3)

            for (int j = 0 ; j < listadeciclos.size() ; j++){

                if (listadeciclos[j]->cycle == 2){


                    QPainterPath border = criapath(listadeciclos[j]) ;
                    QPainterPath island = criapath(listadeciclos[i]) ;

                    QPolygonF poligonodocorpo = criapoligono(listadeciclos[j]);
                    QPolygonF poligonodomembro = criapoligono(listadeciclos[i]);

                    QPointF pontodomembro(listadeciclos[i]->p0);

                    if (poligonodocorpo.containsPoint(poligonodomembro.boundingRect().center(),Qt::WindingFill)){
                        //if (border.boundingRect().contains(island.boundingRect())){

                        qDebug () << i << "COM " << j;

                        //Poligono do Corpo abaixo do membro sugestivo

                        std::vector<QVector3D>PointsdoCorpo;
                        std::vector<QVector3D>NormalsdoCorpo;

                        for (float var = border.length(); var > 0 ; var = var - contoursamplingvalue) {

                            float percent = var / border.length();
                            poligonodocorpo << QPointF (border.pointAtPercent(percent).x(),border.pointAtPercent(percent).y());

                            QLineF angleline;
                            /* Set the origin: */
                            angleline.setP1(island.pointAtPercent(percent));
                            QVector3D ponto;

                            ponto.setX(island.pointAtPercent(percent).x());
                            ponto.setY(island.pointAtPercent(percent).y());
                            ponto.setZ(0);
                            PointsdoCorpo.push_back(ponto);

                            /* Set the angle and length: */
                            angleline.setAngle(island.angleAtPercent(percent)-90);
                            angleline.setLength(1);
                            QVector3D vetornormal(0,0,0);

                            vetornormal.setX(angleline.x2()-angleline.x1());
                            vetornormal.setY(angleline.y2()-angleline.y1());

                            NormalsdoCorpo.push_back(vetornormal);
                        }


                        //Poligono do Membro acima do Corpo

                        poligonodomembro.clear();
                        for (float var = island.length(); var > 0 ; var = var - contoursamplingvalue) {
                            float percent = var / island.length();

                            poligonodomembro << QPointF (island.pointAtPercent(percent).x(),island.pointAtPercent(percent).y());

                            QLineF angleline;
                            /* Set the origin: */
                            angleline.setP1(island.pointAtPercent(percent));
                            QVector3D ponto;

                            ponto.setX(island.pointAtPercent(percent).x());
                            ponto.setY(island.pointAtPercent(percent).y());
                            ponto.setZ(0);
                            knownPoints.push_back(ponto);

                            /* Set the angle and length: */
                            angleline.setAngle(island.angleAtPercent(percent)-90);
                            angleline.setLength(1);
                            QVector3D vetornormal(0,0,0);

                            vetornormal.setX(angleline.x2()-angleline.x1());
                            vetornormal.setY(angleline.y2()-angleline.y1());

                            knownNormals.push_back(vetornormal);

                            painter->drawLine(ponto.x(), ponto.y(),ponto.x() + vetornormal.x()*5,ponto.y() + vetornormal.y()*5);
                        }


                        QFont font = painter->font() ;
                        font.setPointSize ( 18 );
                        //font.setWeight(QFont::DemiBold);
                        painter->setFont(font);

                        QString s = QString::number(i);

                        QRectF boundingbox = island.boundingRect();

                        qDebug ()<< "Bounding box size: " <<  boundingbox.size() << " - Ciclo:" << i;

                        painter->drawText(boundingbox, Qt::BottomRightCorner, s);

                        ///pode ser via seletor de arquivo.
                        ///Preencha os vetores com os pontos do desenho e as normais conhecidas
                        ///precisamos pontos 3D; preencha o z com 0
                        ///
                        ///
                        ///

                        //////////PREENCHER OS VETORES KNOWNPOINTS & KNOWNNORMALS

                        //EXPORTA DADOS RBF

                        float xmin = boundingbox.left();
                        float xmax = boundingbox.right();
                        float ymin = boundingbox.top();
                        float ymax = boundingbox.bottom();

                        // NOVO IGUAL AO ARTIGO E QUALI
                        // Hz = Hb - Hl
                        float hz;  // Altura do membro simétrico em relação ao corpo
                        float hb; // Altura do ponto da normal mais alta no corpo
                        float hl;  // Altura do ponto da normal mais alta no membro simétrico

                        painter->drawRect(boundingbox);

                        QVector3D pontomaisalto(0,0,0);
                        QVector3D normaldopontomaisalto (0,0,0);

                        //float spacing = (xmax - xmin) /10;  //5.0;///Espacamento do grid


                        // qDebug ()<< "Spacing" << spacing;
                        for(QVector3D pi:knownPoints){
                            totalPoints.push_back(pi);

                        }

                        for(QVector3D ui:knownNormals){
                            ui.normalize();
                            totalNormals.push_back(ui);
                        }

                        /// Neste caso o grid sampling tem que ficar dentro dos corpos.. para corpos muito pequenos um valor padrão não funciona; por ex: 20
                        /// Tem que ser ajustado pro corpo


                        float spacing = boundingbox.width()/gridsamplingvalue;



                        ///Calcula Normais
                        for(float x = xmin; x < xmax; x = x + spacing){

                            for(float y = ymin; y < ymax; y = y + spacing){

                                QPointF ponto (x,y);

                                //                                painter->setPen(QPen(QColor(255,0,0), 1, Qt::SolidLine));
                                //                                painter->drawLine(ponto.x(), ponto.y(), ponto.x(), ponto.y());

                                if (poligonodomembro.containsPoint(ponto,Qt::WindingFill)){


                                    ///para cada ponto do grid... que esteja dentro do contorno
                                    QVector3D p(x,y,0);
                                    //calcula o peso
                                    float weight = 0;
                                    for(QVector3D pi:knownPoints)
                                    {
                                        weight += 1.0/((p-pi).lengthSquared());///acho que isso retorna a norma ao 2

                                        ///PROBLEMA
                                        /// Talvez tenha que trazer os pontos para 0~1
                                    }

                                    ///calcula a normal
                                    QVector3D n(0,0,0);
                                    for(int k = 0; k <knownNormals.size(); k++)
                                    {
                                        QVector3D pi = knownPoints.at(k);
                                        QVector3D ui = knownNormals.at(k);
                                        n += (ui / (p-pi).lengthSquared());///acho que isso retorna a norma ao 2
                                    }

                                    n = n / weight;

                                    n.setZ(sqrt(1 - n.x()*n.x() - n.y()*n.y()));

                                    if  (n.z() < 0.5){

                                        int r = (abs(n.x()) + 1)/2*255;
                                        int g = (abs(n.y()) + 1)/2*255;
                                        int b = (n.z() + 1)/2*255;

                                        painter->setPen(QPen(QColor(r,g,b), 1, Qt::SolidLine));
                                        painter->drawLine(ponto.x(), ponto.y(), ponto.x(), ponto.y());

                                        ///Tem que dar uma altura para esses pontos, eu tô chutando o z da normal, mas nao sei se serve.
                                        //p.setZ(n.z());

                                        ///calculou para um ponto no grid a norma dele. agora coloca no vetor final.
                                        //p.setZ(1);

                                        p.setZ(n.z()*(boundingbox.width()/lisland));
                                        totalPoints.push_back(p);
                                        totalNormals.push_back(n);
                                        p.setZ(n.z()*(-boundingbox.width()/lisland));
                                        totalPoints.push_back(p);
                                        n.setZ(n.z()*-1);
                                        totalNormals.push_back(n);
                                    }

                                    if (n.z() > normaldopontomaisalto.z()){
                                        normaldopontomaisalto.setZ(n.z());
                                        pontomaisalto.setX(p.x());
                                        pontomaisalto.setY(p.y());
                                        hl = normaldopontomaisalto.z()*(island.boundingRect().width()/lshapesvalue);
                                    }
                                }
                            }
                        }

                        // Calcula a altura do corpo a partir da normal mais alta do membro simétrico

                        //calcula o peso
                        float weight = 0;
                        for(QVector3D pi:PointsdoCorpo)
                        {
                            weight += 1.0/((pontomaisalto-pi).lengthSquared());///acho que isso retorna a norma ao 2

                            ///PROBLEMA
                            /// Talvez tenha que trazer os pontos para 0~1
                        }

                        ///calcula a normal
                        QVector3D n(0,0,0);
                        for(int k = 0; k <NormalsdoCorpo.size(); k++)
                        {
                            QVector3D pi = PointsdoCorpo.at(k);
                            QVector3D ui = NormalsdoCorpo.at(k);
                            n += (ui / (pontomaisalto-pi).lengthSquared());///acho que isso retorna a norma ao 2
                        }

                        n = n / weight;

                        n.setZ(sqrt(1 - n.x()*n.x() - n.y()*n.y()));

                        float alturadomembro = n.z()*(border.boundingRect().width()/ldepthisland);
                        hb = n.z() * (border.boundingRect().width()/ldepthisland);

                        // Calculo profundidade segundo o artigo e quali
                        hz = hb-hl;
                        qDebug () << "Altura do membro: "  << alturadomembro;
                        //alturadomembro = hz;

                        qDebug () << "Hz: " << hz;


                        //painter->setPen(QPen(Qt::black, 7, Qt::SolidLine));
                        painter->drawEllipse(pontomaisalto.x(), pontomaisalto.y(),20,20);
                        qDebug () << pontomaisalto;



                        //std::string outFile = "rbf.data";

                        std::string outFile = "rbf";
                        outFile.append("_");
                        outFile.append(fileSvg.toStdString());
                        //Remover o .svg do nome
                        outFile.pop_back();
                        outFile.pop_back();
                        outFile.pop_back();
                        outFile.pop_back();
                        //std::string s = ;
                        outFile.append("_ID");
                        outFile.append(std::to_string(listadeciclos[i]->cycle));
                        outFile.append("_Ciclo");
                        outFile.append(std::to_string(i));
                        outFile.append("_1");
                        outFile.append(".data");

                        ///agora abre um arquivo pra salvar estes dados para serem entrada do RBF. Esse é o formato que eu uso
                        std::ofstream fOut1;
                        fOut1.open(outFile.c_str());
                        fOut1 << "3" <<std::endl;
                        fOut1 << knownPoints.size() <<std::endl;
                        for(QVector3D p:knownPoints)
                        {
                            fOut1 << p.x() <<" " << p.y()<< " " << p.z()+alturadomembro << std::endl;
                        }

                        fOut1 << totalNormals.size() << std::endl;

                        for(int k = 0; k < totalNormals.size(); k++)
                        {

                            QVector3D p = totalPoints.at(k);
                            QVector3D n = totalNormals.at(k);

                            fOut1 << n.x() <<" " << n.y()<< " " << n.z()<< std::endl;
                            fOut1 << p.x() <<" " << p.y()<< " " << p.z()+alturadomembro<< std::endl;
                        }
                        fOut1 << "0" << std::endl;
                        fOut1.close();

                        outFile = "rbf";
                        outFile.append("_");
                        outFile.append(fileSvg.toStdString());
                        //Remover o .svg do nome
                        outFile.pop_back();
                        outFile.pop_back();
                        outFile.pop_back();
                        outFile.pop_back();
                        //std::string s = ;
                        outFile.append("_ID");
                        outFile.append(std::to_string(listadeciclos[i]->cycle));
                        outFile.append("_Ciclo");
                        outFile.append(std::to_string(i));
                        outFile.append("_2");
                        outFile.append(".data");

                        ///agora abre um arquivo pra salvar estes dados para serem entrada do RBF. Esse é o formato que eu uso
                        std::ofstream fOut;
                        fOut.open(outFile.c_str());
                        fOut << "3" <<std::endl;
                        fOut << knownPoints.size() <<std::endl;
                        for(QVector3D p:knownPoints)
                        {
                            fOut << p.x() <<" " << p.y()<< " " << p.z()-alturadomembro << std::endl;
                        }

                        fOut << totalNormals.size() << std::endl;

                        for(int k = 0; k < totalNormals.size(); k++)
                        {

                            QVector3D p = totalPoints.at(k);
                            QVector3D n = totalNormals.at(k);

                            fOut << n.x() <<" " << n.y()<< " " << n.z()<< std::endl;
                            fOut << p.x() <<" " << p.y()<< " " << p.z()-alturadomembro<< std::endl;
                        }
                        fOut << "0" << std::endl;
                        fOut.close();



                    }
                }
            }


        }

        if (listadeciclos[i]->cycle == 7){ // Se for um membro simétrico (7)

            for (int j = 0 ; j < listadeciclos.size() ; j++){

                if (listadeciclos[j]->cycle == 2){

                    QPainterPath simetrico = criapath(listadeciclos[i]) ;

                    QPainterPath border = criapath(listadeciclos[j]) ;

                    QPointF pontodomembro(listadeciclos[i]->p0);


                    if (border.intersects(simetrico)){

                        qDebug () << i << "COM " << j;

                        //Poligono do Corpo abaixo do membro sugestivo
                        QPolygon poligonodocorpo;
                        QPolygon poligonodomembro;

                        std::vector<QVector3D>PointsdoCorpo;
                        std::vector<QVector3D>NormalsdoCorpo;


                        for (float var = border.length(); var > 0 ; var = var - contoursamplingvalue) {

                            float percent = var / border.length();
                            poligonodocorpo << QPoint (border.pointAtPercent(percent).x(),border.pointAtPercent(percent).y());

                            QLineF angleline;
                            /* Set the origin: */
                            angleline.setP1(simetrico.pointAtPercent(percent));
                            QVector3D ponto;

                            ponto.setX(simetrico.pointAtPercent(percent).x());
                            ponto.setY(simetrico.pointAtPercent(percent).y());
                            ponto.setZ(0);
                            PointsdoCorpo.push_back(ponto);

                            /* Set the angle and length: */
                            angleline.setAngle(simetrico.angleAtPercent(percent)-90);
                            angleline.setLength(1);
                            QVector3D vetornormal(0,0,0);

                            vetornormal.setX(angleline.x2()-angleline.x1());
                            vetornormal.setY(angleline.y2()-angleline.y1());

                            NormalsdoCorpo.push_back(vetornormal);
                        }


                        //Poligono do Membro acima do Corpo

                        for (float var = simetrico.length(); var > 0 ; var = var - contoursamplingvalue) {
                            float percent = var / simetrico.length();
                            poligonodomembro << QPoint (simetrico.pointAtPercent(percent).x(),simetrico.pointAtPercent(percent).y());

                            QLineF angleline;
                            /* Set the origin: */
                            angleline.setP1(simetrico.pointAtPercent(percent));
                            QVector3D ponto;

                            ponto.setX(simetrico.pointAtPercent(percent).x());
                            ponto.setY(simetrico.pointAtPercent(percent).y());
                            ponto.setZ(0);
                            knownPoints.push_back(ponto);

                            /* Set the angle and length: */
                            angleline.setAngle(simetrico.angleAtPercent(percent)-90);
                            angleline.setLength(1);
                            QVector3D vetornormal(0,0,0);

                            vetornormal.setX(angleline.x2()-angleline.x1());
                            vetornormal.setY(angleline.y2()-angleline.y1());

                            knownNormals.push_back(vetornormal);

                            painter->drawLine(ponto.x(), ponto.y(),ponto.x() + vetornormal.x()*1,ponto.y() + vetornormal.y()*1);
                        }


                        QFont font = painter->font() ;
                        font.setPointSize ( 18 );
                        //font.setWeight(QFont::DemiBold);
                        painter->setFont(font);

                        QString s = QString::number(i);

                        QRectF boundingbox = simetrico.boundingRect();

                        qDebug ()<< "Bounding box size: " <<  boundingbox.size() << " - Ciclo:" << i;

                        painter->drawText(boundingbox, Qt::BottomRightCorner, s);

                        ///pode ser via seletor de arquivo.
                        ///Preencha os vetores com os pontos do desenho e as normais conhecidas
                        ///precisamos pontos 3D; preencha o z com 0
                        ///
                        ///
                        ///

                        //////////PREENCHER OS VETORES KNOWNPOINTS & KNOWNNORMALS

                        //EXPORTA DADOS RBF

                        float xmin = boundingbox.left();
                        float xmax = boundingbox.right();
                        float ymin = boundingbox.top();
                        float ymax = boundingbox.bottom();

                        // NOVO IGUAL AO ARTIGO E QUALI
                        // Hz = Hb - Hl
                        float hz;  // Altura do membro simétrico em relação ao corpo
                        float hb; // Altura do ponto da normal mais alta no corpo
                        float hl;  // Altura do ponto da normal mais alta no membro simétrico

                        painter->drawRect(boundingbox);

                        QVector3D pontomaisalto(0,0,0);
                        QVector3D normaldopontomaisalto (0,0,0);



                        //float spacing = (xmax - xmin) /10;  //5.0;///Espacamento do grid
                        /// Neste caso o grid sampling tem que ficar dentro dos corpos.. para corpos muito pequenos um valor padrão não funciona; por ex: 20
                        /// Tem que ser ajustado pro corpo


                        float spacing = boundingbox.width()/gridsamplingvalue;
                        int r,g,b;
                        // qDebug ()<< "Spacing" << spacing;
                        for(QVector3D pi:knownPoints){
                            totalPoints.push_back(pi);

                        }

                        for(QVector3D ui:knownNormals){
                            ui.normalize();
                            totalNormals.push_back(ui);
                        }

                        ///Calcula Normais
                        for(float x = xmin; x < xmax; x = x + spacing)
                        {
                            for(float y = ymin; y < ymax; y = y + spacing)
                            {
                                QPoint ponto (x,y);

                                if (poligonodomembro.containsPoint(ponto,Qt::WindingFill)){

                                    ///para cada ponto do grid... que esteja dentro do contorno
                                    QVector3D p(x,y,0);
                                    //calcula o peso
                                    float weight = 0;
                                    for(QVector3D pi:knownPoints)
                                    {
                                        weight += 1.0/((p-pi).lengthSquared());///acho que isso retorna a norma ao 2

                                        ///PROBLEMA
                                        /// Talvez tenha que trazer os pontos para 0~1
                                    }

                                    ///calcula a normal
                                    QVector3D n(0,0,0);
                                    for(int k = 0; k <knownNormals.size(); k++)
                                    {
                                        QVector3D pi = knownPoints.at(k);
                                        QVector3D ui = knownNormals.at(k);
                                        n += (ui / (p-pi).lengthSquared());///acho que isso retorna a norma ao 2
                                    }

                                    n = n / weight;

                                    n.setZ(sqrt(1 - n.x()*n.x() - n.y()*n.y()));

                                    if  (n.z() < .5){

                                        r = (abs(n.x()) + 1)/2*255;
                                        g = (abs(n.y()) + 1)/2*255;
                                        b = (n.z() + 1)/2*255;

                                        //painter->setPen(QPen(QColor(r,g,b), 1, Qt::SolidLine));
                                        painter->drawLine(ponto.x(), ponto.y(), ponto.x(), ponto.y());

                                        ///Tem que dar uma altura para esses pontos, eu tô chutando o z da normal, mas nao sei se serve.
                                        //p.setZ(n.z());

                                        ///calculou para um ponto no grid a norma dele. agora coloca no vetor final.
                                        //p.setZ(1);

                                        p.setZ(n.z()*(boundingbox.width()/lsym));
                                        totalPoints.push_back(p);
                                        totalNormals.push_back(n);
                                        p.setZ(n.z()*(-boundingbox.width()/lsym));
                                        totalPoints.push_back(p);
                                        n.setZ(n.z()*-1);
                                        totalNormals.push_back(n);
                                    }

                                    if (poligonodocorpo.containsPoint(ponto, Qt::WindingFill) && n.z() > normaldopontomaisalto.z()){
                                        normaldopontomaisalto = n;
                                        pontomaisalto.setX(ponto.x());
                                        pontomaisalto.setY(ponto.y());
                                        hl = normaldopontomaisalto.z()*(poligonodomembro.boundingRect().width()/ldepthsym);
                                    }
                                }
                            }
                        }

                        // Calcula a altura do corpo a partir da normal mais alta do membro simétrico

                        //calcula o peso
                        float weight = 0;
                        for(QVector3D pi:PointsdoCorpo)
                        {
                            weight += 1.0/((pontomaisalto-pi).lengthSquared());///acho que isso retorna a norma ao 2

                            ///PROBLEMA
                            /// Talvez tenha que trazer os pontos para 0~1
                        }

                        ///calcula a normal
                        QVector3D n(0,0,0);
                        for(int k = 0; k <NormalsdoCorpo.size(); k++)
                        {
                            QVector3D pi = PointsdoCorpo.at(k);
                            QVector3D ui = NormalsdoCorpo.at(k);
                            n += (ui / (pontomaisalto-pi).lengthSquared());///acho que isso retorna a norma ao 2
                        }

                        n = n / weight;

                        n.setZ(sqrt(1 - n.x()*n.x() - n.y()*n.y()));

                        float alturadomembro = n.z()*(poligonodocorpo.boundingRect().width()/ldepthsym);
                        hb = n.z() * (poligonodocorpo.boundingRect().width()/ldepthsym);

                        // Calculo profundidade segundo o artigo e quali
                        hz = hb-hl;
                        qDebug () << "Altura do membro: "  << alturadomembro;
                        //  alturadomembro = hz;

                        qDebug () << "Hz: " << hz;


                        //painter->setPen(QPen(Qt::black, 7, Qt::SolidLine));
                        painter->drawEllipse(pontomaisalto.x(), pontomaisalto.y(),20,20);
                        qDebug () << pontomaisalto;



                        //std::string outFile = "rbf.data";

                        std::string outFile = "rbf";
                        outFile.append("_");
                        outFile.append(fileSvg.toStdString());
                        //Remover o .svg do nome
                        outFile.pop_back();
                        outFile.pop_back();
                        outFile.pop_back();
                        outFile.pop_back();
                        //std::string s = ;
                        outFile.append("_ID");
                        outFile.append(std::to_string(listadeciclos[i]->cycle));
                        outFile.append("_Ciclo");
                        outFile.append(std::to_string(i));
                        outFile.append("_1");
                        outFile.append(".data");

                        ///agora abre um arquivo pra salvar estes dados para serem entrada do RBF. Esse é o formato que eu uso
                        std::ofstream fOut1;
                        fOut1.open(outFile.c_str());
                        fOut1 << "3" <<std::endl;
                        fOut1 << knownPoints.size() <<std::endl;
                        for(QVector3D p:knownPoints)
                        {
                            fOut1 << p.x() <<" " << p.y()<< " " << p.z()+alturadomembro << std::endl;
                        }

                        fOut1 << totalNormals.size() << std::endl;

                        for(int k = 0; k < totalNormals.size(); k++)
                        {

                            QVector3D p = totalPoints.at(k);
                            QVector3D n = totalNormals.at(k);

                            fOut1 << n.x() <<" " << n.y()<< " " << n.z()<< std::endl;
                            fOut1 << p.x() <<" " << p.y()<< " " << p.z()+alturadomembro<< std::endl;
                        }
                        fOut1 << "0" << std::endl;
                        fOut1.close();

                        outFile = "rbf";
                        outFile.append("_");
                        outFile.append(fileSvg.toStdString());
                        //Remover o .svg do nome
                        outFile.pop_back();
                        outFile.pop_back();
                        outFile.pop_back();
                        outFile.pop_back();
                        //std::string s = ;
                        outFile.append("_ID");
                        outFile.append(std::to_string(listadeciclos[i]->cycle));
                        outFile.append("_Ciclo");
                        outFile.append(std::to_string(i));
                        outFile.append("_2");
                        outFile.append(".data");

                        ///agora abre um arquivo pra salvar estes dados para serem entrada do RBF. Esse é o formato que eu uso
                        std::ofstream fOut;
                        fOut.open(outFile.c_str());
                        fOut << "3" <<std::endl;
                        fOut << knownPoints.size() <<std::endl;
                        for(QVector3D p:knownPoints)
                        {
                            fOut << p.x() <<" " << p.y()<< " " << p.z()-alturadomembro << std::endl;
                        }

                        fOut << totalNormals.size() << std::endl;

                        for(int k = 0; k < totalNormals.size(); k++)
                        {

                            QVector3D p = totalPoints.at(k);
                            QVector3D n = totalNormals.at(k);

                            fOut << n.x() <<" " << n.y()<< " " << n.z()<< std::endl;
                            fOut << p.x() <<" " << p.y()<< " " << p.z()-alturadomembro<< std::endl;
                        }
                        fOut << "0" << std::endl;
                        fOut.close();



                    }
                }

            }
        }

        if (listadeciclos[i]->cycle == 4){ // Se for um Adjacent
            bool temfeature = false;
            for (int j = 0; j< listadeciclos.size() ; j++){ //Pesquisa se tem um feature

                if (listadeciclos[j]->cycle == 5){//Verifica se tem Feature correspondente à esta adjacente

                    QPolygonF poligono1 = criapoligono(listadeciclos[i]);
                    QPolygonF poligono2 = criapoligono(listadeciclos[j]);

                    if (poligono1.boundingRect().contains(poligono2.boundingRect())){

                        temfeature = true;

                        // Cria um Path a partir do ciclo
                        // Deve-se quebrar o ciclo nas extremidades

                        // Encontra duas extremidades
                        HalfEdge* half1 = listadeciclos[i];

                        while (half1->next != half1->twin){

                            half1 = half1->next;
                        }

                        painter->drawEllipse(half1->p3,2,2);

                        HalfEdge* half2 = half1->next;

                        while (half2->next != half2->twin){

                            half2 = half2->next;
                        }

                        painter->drawEllipse(half2->p3,2,2);

                        QPainterPath contorno1;

                        HalfEdge* begin = half2->next;
                        HalfEdge* half = begin;

                        do {
                            contorno1.moveTo(half->p0.x(),half->p0.y());
                            contorno1.cubicTo(half->p1.x(),half->p1.y(),half->p2.x(),half->p2.y(),half->p3.x(),half->p3.y());

                            half = half->next;
                        } while (half != half1->next);


                        /// --- pEga area pra saber orientação das Half-edges e consequentemente das normais


                        float areacontorno1 = getPathArea(contorno1, 10);
                        qDebug () << "Area do contorno 1:" << areacontorno1;

                        float angulopranormal;
                        if (areacontorno1 < 0){
                            angulopranormal = 90;
                        } else {
                            angulopranormal = -90;
                        }


                        QPolygonF poligonodabezier;

                        for (float var = contorno1.length(); var >0; var = var - contoursamplingvalue){


                            float percent = var / contorno1.length();
                            qDebug() << percent;

                            QLineF angleline;
                            /* Set the origin: */
                            angleline.setP1(contorno1.pointAtPercent(percent));
                            QVector3D ponto;

                            ponto.setX(contorno1.pointAtPercent(percent).x());
                            ponto.setY(contorno1.pointAtPercent(percent).y());

                            poligonodabezier << QPointF (ponto.x(),ponto.y());

                            knownPoints.push_back(ponto);

                            /* Set the angle and length: */
                            angleline.setAngle(contorno1.angleAtPercent(percent)+angulopranormal);
                            angleline.setLength(1);
                            QVector3D vetornormal(0,0,0);

                            vetornormal.setX(angleline.x2()-angleline.x1());
                            vetornormal.setY(angleline.y2()-angleline.y1());

                            knownNormals.push_back(vetornormal);

                            painter->drawPath(contorno1);
                            painter->drawLine(ponto.x(), ponto.y(),ponto.x() + vetornormal.x()*5,ponto.y() + vetornormal.y()*5);



                        }

                        //Calcula normais do contorno acima

                        std::vector<QVector3D>knownPoints2;
                        std::vector<QVector3D>knownNormals2;


                        float alturacontornointerno = 0;

                        HalfEdge* half3 = listadeciclos[j];

                        while (half3->next != half3->twin){

                            half3 = half3->next;
                        }

                        painter->drawEllipse(half3->p3,2,2);

                        HalfEdge* half4 = half3->next;

                        while (half4->next != half4->twin){

                            half4 = half4->next;
                        }

                        painter->drawEllipse(half2->p3,2,2);

                        QPainterPath contorno2;

                        begin = half4->next;
                        half = begin;

                        do {
                            contorno2.moveTo(half->p0.x(),half->p0.y());
                            contorno2.cubicTo(half->p1.x(),half->p1.y(),half->p2.x(),half->p2.y(),half->p3.x(),half->p3.y());

                            half = half->next;
                        } while (half != half3->next);

                        QPolygonF poligonointerno;

                        float areacontorno2 = getPathArea(contorno2, 10);

                        qDebug () << "Area do contorno 2:" << areacontorno2;


                        if (areacontorno2 < 0){
                            angulopranormal = 90;
                        } else {
                            angulopranormal = -90;
                        }


                        for (float var = contorno2.length(); var >0; var = var - contoursamplingvalue){

                            float percent = var / contorno2.length();

                            QVector3D p(0,0,0);
                            p.setX(contorno2.pointAtPercent(percent).x());
                            p.setY(contorno2.pointAtPercent(percent).y());
                            //calcula o peso
                            float weight = 0;
                            for(QVector3D pi:knownPoints)
                            {
                                weight += 1.0/((p-pi).lengthSquared());
                            }
                            QVector3D n(0,0,0);
                            for(int i = 0; i <knownNormals.size(); i++)
                            {
                                QVector3D pi = knownPoints.at(i);
                                QVector3D ui = knownNormals.at(i);
                                n += (ui / (p-pi).lengthSquared());
                            }
                            n = n / weight;
                            n.setZ(sqrt(1 - n.x()*n.x() - n.y()*n.y()));

                            QRectF boundingbox0 = contorno1.boundingRect();
                            QRectF boundingbox1 = contorno2.boundingRect();

                            p.setZ(n.z()*(boundingbox0.width()/ladj));

                            poligonointerno << QPoint (p.x(),p.y());

                            //Seta em Z altura em relação ao corpo abaixo

                            QLineF angleline;
                            // Set the origin:
                            angleline.setP1(contorno2.pointAtPercent(percent));

                            // Set the angle and length:
                            angleline.setAngle(contorno2.angleAtPercent(percent)+angulopranormal);
                            angleline.setLength(1);
                            QVector3D vetornormal(0,0,0);

                            vetornormal.setX(angleline.x2()-angleline.x1());
                            vetornormal.setY(angleline.y2()-angleline.y1());
                            vetornormal.setZ(n.z());


                            knownPoints2.push_back(p);
                            knownNormals2.push_back(vetornormal);

                            p.setZ(p.z()*-1);
                            knownPoints2.push_back(p);
                            vetornormal.setZ(n.z()*-1);
                            knownNormals2.push_back(vetornormal);

                            p.setZ(p.z()*-1);
                            alturacontornointerno += p.z();

                            int r = 0;
                            int g = 0;
                            int b = p.z()*15;


                            // painter->setPen(QPen(QColor(50,50,50), 2, Qt::SolidLine));
                            painter->setPen(QPen(QColor(255,127,0), 3, Qt::DashDotLine));

                            // painter->drawPath(contorno2);

                            painter->drawLine(p.x(), p.y(),p.x() + vetornormal.x()*5,p.y() + vetornormal.y()*5);
                        }

                        //------------------------------------------------------

                        // Define altura do contorno interno pela média da soma da altura dos pontos no contorno interno

                        alturacontornointerno = alturacontornointerno / knownPoints2.size();

                        // Define normais da nova linha que fecha o membro adjacente

                        /// CRIA A LINHA QUE FECHA O MEMBRO ADJACENTE
                        ///
                        /// areacontorno1 < 0; significa que ciclo é horário
                        /// areacontorno1 > 0; significa que ciclo é antihorario
                        ///



                        HalfEdge *he0 = new HalfEdge;
                        HalfEdge *he1 = new HalfEdge;

                        he0->twin = he1;
                        he1->twin = he0;

                        he0->p3 = half1->p3;
                        he0->p2 = half1->p3 + (half1->p3 - half1->p2);

                        he0->p1 =  half2->p3 + (half2->p3 - half2->p2);
                        he0->p0 =  half2->p3;

                        //painter->setPen(QPen(QColor(50, 50, 50), 4, Qt::SolidLine));

                        QPainterPath linhaquefechaadjacente;

                        if (areacontorno1 < 0){
                            angulopranormal = 90;

                            linhaquefechaadjacente.moveTo(he0->p3.x(),he0->p3.y());
                            linhaquefechaadjacente.cubicTo(he0->p2.x(),he0->p2.y(),he0->p1.x(),he0->p1.y(),he0->p0.x(),he0->p0.y());

                        } else {
                            angulopranormal = -90;

                            linhaquefechaadjacente.moveTo(he0->p0.x(),he0->p0.y());
                            linhaquefechaadjacente.cubicTo(he0->p1.x(),he0->p1.y(),he0->p2.x(),he0->p2.y(),he0->p3.x(),he0->p3.y());
                        }

                        painter->setPen(QPen(QColor(50, 50, 50), 4, Qt::DashLine));
                        painter->drawPath(linhaquefechaadjacente);

                        for (float var = linhaquefechaadjacente.length(); var >0; var = var - contoursamplingvalue){

                            //                             painter->drawPath(linhaquefechaadjacente);
                            float percent = var / linhaquefechaadjacente.length();


                            QVector3D p(0,0,0);
                            p.setX(linhaquefechaadjacente.pointAtPercent(percent).x());
                            p.setY(linhaquefechaadjacente.pointAtPercent(percent).y());
                            p.setZ(alturacontornointerno*-adjnewcontour); //Define altura da nova linha que fecha o membro adjacente
                            // p.setZ(0);

                            QLineF angleline;
                            // Set the origin:
                            angleline.setP1(linhaquefechaadjacente.pointAtPercent(percent));

                            // Set the angle and length:
                            angleline.setAngle(linhaquefechaadjacente.angleAtPercent(percent)+angulopranormal);
                            angleline.setLength(1);
                            QVector3D vetornormal(0,0,0);

                            vetornormal.setX(angleline.x2()-angleline.x1());
                            vetornormal.setY(angleline.y2()-angleline.y1());
                            //vetornormal.setZ(n.z());

                            painter->drawLine(p.x(), p.y(),p.x() + vetornormal.x()*5,p.y() + vetornormal.y()*5);


                            knownPoints.push_back(p);
                            knownNormals.push_back(vetornormal);
                        }
                        for(QVector3D pi:knownPoints){
                            totalPoints.push_back(pi);
                        }

                        for(QVector3D ui:knownNormals){
                            ui.normalize();
                            totalNormals.push_back(ui);
                        }

                        QRectF boundingbox1 = contorno2.boundingRect();

                        float xmin = boundingbox1.left();
                        float xmax = boundingbox1.right();
                        float ymin = boundingbox1.top();
                        float ymax = boundingbox1.bottom();

                        float spacing = gridsamplingvalue;
                        int r,g,b;

                        for(float x = xmin; x < xmax; x = x + spacing)
                        {
                            for(float y = ymin; y < ymax; y = y + spacing)
                            {

                                QPointF ponto (x,y);


                                if (poligonointerno.containsPoint(ponto,Qt::WindingFill)){
                                    // if (poligonodabezier.containsPoint(ponto,Qt::WindingFill)){
                                    ///para cada ponto do grid... que esteja dentro do contorno
                                    QVector3D p(x,y,alturacontornointerno);
                                    //calcula o peso
                                    float weight = 0;
                                    for(QVector3D pi:knownPoints)
                                    {
                                        weight += 1.0/((p-pi).lengthSquared());///acho que isso retorna a norma ao 2

                                        ///PROBLEMA
                                        /// Talvez tenha que trazer os pontos para 0~1
                                    }

                                    ///calcula a normal
                                    QVector3D n(0,0,0);
                                    for(int i = 0; i <knownNormals.size(); i++)
                                    {
                                        QVector3D pi = knownPoints.at(i);
                                        QVector3D ui = knownNormals.at(i);
                                        n += (ui / (p-pi).lengthSquared());///acho que isso retorna a norma ao 2
                                    }

                                    n = n / weight;

                                    n.setZ(sqrt(1 - n.x()*n.x() - n.y()*n.y()));

                                    qDebug () << n;

                                    p.setZ(alturacontornointerno);
                                    //n.setZ(n.z()*(boundingbox0.width()/10));

                                    qDebug () << p;

                                    if  (n.z() < 1){

                                        r = (abs(n.x()) + 1)/2*255;
                                        g = (abs(n.y()) + 1)/2*255;
                                        b = (n.z() + 1)/2*255;

                                        painter->setPen(QPen(QColor(r,g,b), 1, Qt::SolidLine));
                                        painter->drawLine(p.x(), p.y(), p.x(), p.y());

                                        totalPoints.push_back(p);
                                        p.setZ(p.z()*-1);
                                        totalPoints.push_back(p);


                                        //n.setZ(n.z()*alturacontornointerno);
                                        //n.setZ(n.z()+alturacontornointerno);

                                        totalNormals.push_back(n);
                                        n.setZ(n.z()*-1);
                                        totalNormals.push_back(n);

                                    }
                                }
                            }
                        }

                        /// PRECISA ENCONTRAR EM QUAL BORDER QUE ESTÁ Para calcular altura
                        ///
                        ///
                        for (int k = 0; k < listadeciclos.size() ; k++){
                            QPolygonF poligonodocorpo = criapoligono(listadeciclos[k]);

                            if (poligonodocorpo.containsPoint(poligonodabezier.boundingRect().center(),Qt::WindingFill)){

                                QPainterPath border = criapath(listadeciclos[k]);

                                std::vector<QVector3D>PointsdoCorpo;
                                std::vector<QVector3D>NormalsdoCorpo;


                                for (float var = border.length(); var > 0 ; var = var - contoursamplingvalue) {

                                    float percent = var / border.length();
                                    poligonodocorpo << QPoint (border.pointAtPercent(percent).x(),border.pointAtPercent(percent).y());

                                    QLineF angleline;
                                    /* Set the origin: */
                                    angleline.setP1(border.pointAtPercent(percent));
                                    QVector3D ponto;

                                    ponto.setX(border.pointAtPercent(percent).x());
                                    ponto.setY(border.pointAtPercent(percent).y());
                                    ponto.setZ(0);
                                    PointsdoCorpo.push_back(ponto);

                                    /* Set the angle and length: */
                                    angleline.setAngle(border.angleAtPercent(percent)-90);
                                    angleline.setLength(1);
                                    QVector3D vetornormal(0,0,0);

                                    vetornormal.setX(angleline.x2()-angleline.x1());
                                    vetornormal.setY(angleline.y2()-angleline.y1());

                                    NormalsdoCorpo.push_back(vetornormal);
                                }


                                QVector3D pontopracalcularaltura (0,0,0);
                                pontopracalcularaltura.setX(linhaquefechaadjacente.pointAtPercent(0.5).x());
                                pontopracalcularaltura.setY(linhaquefechaadjacente.pointAtPercent(0.5).y());
                                float weight = 0;
                                for(QVector3D pi:PointsdoCorpo)
                                {
                                    weight += 1.0/((pontopracalcularaltura-pi).lengthSquared());///acho que isso retorna a norma ao 2

                                    ///PROBLEMA
                                    /// Talvez tenha que trazer os pontos para 0~1
                                }

                                ///calcula a normal
                                QVector3D n(0,0,0);
                                for(int l = 0; l <NormalsdoCorpo.size(); l++)
                                {
                                    QVector3D pi = PointsdoCorpo.at(l);
                                    QVector3D ui = NormalsdoCorpo.at(l);
                                    n += (ui / (pontopracalcularaltura-pi).lengthSquared());///acho que isso retorna a norma ao 2
                                }

                                n = n / weight;

                                n.setZ(sqrt(1 - n.x()*n.x() - n.y()*n.y()));

                                float alturadomembro = n.z()*(poligonodocorpo.boundingRect().width()/lshapesvalue);
                                alturadomembro += alturacontornointerno*ldepthadj;
                                /// MUDAR A LINHA ACIMA - Não dá pra estimar


                                std::string outFile = "rbf";
                                outFile.append("_");
                                outFile.append(fileSvg.toStdString());
                                //Remover o .svg do nome
                                outFile.pop_back();
                                outFile.pop_back();
                                outFile.pop_back();
                                outFile.pop_back();
                                //std::string s = ;
                                outFile.append("_ID");
                                outFile.append(std::to_string(listadeciclos[i]->cycle));
                                outFile.append("_Ciclo");
                                outFile.append(std::to_string(i));
                                outFile.append("_1");
                                outFile.append(".data");

                                ///agora abre um arquivo pra salvar estes dados para serem entrada do RBF. Esse é o formato que eu uso
                                std::ofstream fOut1;
                                fOut1.open(outFile.c_str());
                                fOut1 << "3" <<std::endl;
                                fOut1 << knownPoints.size() <<std::endl;
                                for(QVector3D p:knownPoints)
                                {
                                    fOut1 << p.x() <<" " << p.y()<< " " << p.z()+alturadomembro<< std::endl;
                                }

                                fOut1 << totalNormals.size() << std::endl;

                                for(int l = 0; l < totalNormals.size(); l++)
                                {

                                    QVector3D p = totalPoints.at(l);
                                    QVector3D n = totalNormals.at(l);

                                    fOut1 << n.x() <<" " << n.y()<< " " << n.z()<< std::endl;
                                    fOut1 << p.x() <<" " << p.y()<< " " << p.z()+alturadomembro<< std::endl;
                                }
                                fOut1 << "0" << std::endl;
                                fOut1.close();


                                outFile = "rbf";
                                outFile.append("_");
                                outFile.append(fileSvg.toStdString());
                                //Remover o .svg do nome
                                outFile.pop_back();
                                outFile.pop_back();
                                outFile.pop_back();
                                outFile.pop_back();
                                //std::string s = ;
                                outFile.append("_ID");
                                outFile.append(std::to_string(listadeciclos[i]->cycle));
                                outFile.append("_Ciclo");
                                outFile.append(std::to_string(i));
                                outFile.append("_2");
                                outFile.append(".data");

                                ///agora abre um arquivo pra salvar estes dados para serem entrada do RBF. Esse é o formato que eu uso
                                std::ofstream fOut;
                                fOut.open(outFile.c_str());
                                fOut << "3" <<std::endl;
                                fOut << knownPoints.size() <<std::endl;
                                for(QVector3D p:knownPoints)
                                {
                                    //if (almostEqual(p.z(),alturacontornointerno*-5)){ // Significa que é a linha que fecha, que deve estar invertida
                                    if (almostEqual(p.z(),alturacontornointerno*-adjnewcontour)){ // Significa que é a linha que fecha, que deve estar invertida
                                        fOut << p.x() <<" " << p.y()<< " " << (p.z()*-1)-alturadomembro << std::endl;

                                    } else {
                                        fOut << p.x() <<" " << p.y()<< " " << p.z()-alturadomembro << std::endl;
                                    }

                                }

                                fOut << totalNormals.size() << std::endl;

                                for(int k = 0; k < totalNormals.size(); k++)
                                {

                                    QVector3D p = totalPoints.at(k);
                                    QVector3D n = totalNormals.at(k);

                                    fOut << n.x() <<" " << n.y()<< " " << n.z()<< std::endl;
                                    //if (almostEqual(p.z(),alturacontornointerno*-5)){ // Significa que é a linha que fecha, que deve estar invertida
                                    if (almostEqual(p.z(),alturacontornointerno*-adjnewcontour)){ // Significa que é a linha que fecha, que deve estar invertida
                                        fOut << p.x() <<" " << p.y()<< " " << (p.z()*-1)-alturadomembro << std::endl;

                                    } else {
                                        fOut << p.x() <<" " << p.y()<< " " << p.z()-alturadomembro << std::endl;
                                    }
                                }
                                fOut << "0" << std::endl;
                                fOut.close();

                            }

                        }




                    }



                }
            }

            if (!temfeature){ // Se a adjacent border não possuir feature -- igual braco do coelho


                HalfEdge* half1 = listadeciclos[i];

                while (half1->next != half1->twin){

                    half1 = half1->next;
                }

                painter->drawEllipse(half1->p3,4,4);

                HalfEdge* half2 = half1->next;

                while (half2->next != half2->twin){

                    half2 = half2->next;
                }

                painter->drawEllipse(half2->p3,4,4);

                QPainterPath contorno1;

                HalfEdge* begin = half2->next;
                HalfEdge* half = begin;

                do {
                    contorno1.moveTo(half->p0.x(),half->p0.y());
                    contorno1.cubicTo(half->p1.x(),half->p1.y(),half->p2.x(),half->p2.y(),half->p3.x(),half->p3.y());

                    half = half->next;
                } while (half != half1->next);

                /// --- pEga area pra saber orientação das Half-edges e consequentemente das normais

                float areacontorno1 = getPathArea(contorno1, 10);
                qDebug () << "Area do contorno 1:" << areacontorno1;

                float angulopranormal;
                if (areacontorno1 < 0){
                    angulopranormal = 90;
                } else {
                    angulopranormal = -90;
                }


                QPolygonF poligonodabezier;

                for (float var = contorno1.length(); var >0; var = var - contoursamplingvalue){


                    float percent = var / contorno1.length();
                    qDebug() << percent;

                    QLineF angleline;
                    /* Set the origin: */
                    angleline.setP1(contorno1.pointAtPercent(percent));
                    QVector3D ponto;

                    ponto.setX(contorno1.pointAtPercent(percent).x());
                    ponto.setY(contorno1.pointAtPercent(percent).y());

                    poligonodabezier << QPointF (ponto.x(),ponto.y());

                    knownPoints.push_back(ponto);

                    /* Set the angle and length: */
                    angleline.setAngle(contorno1.angleAtPercent(percent)+angulopranormal);
                    angleline.setLength(1);
                    QVector3D vetornormal(0,0,0);

                    vetornormal.setX(angleline.x2()-angleline.x1());
                    vetornormal.setY(angleline.y2()-angleline.y1());

                    knownNormals.push_back(vetornormal);

                    int r = 0;
                    int g = 0;
                    int b = ponto.z()*10;

                    painter->drawPath(contorno1);
                    painter->drawLine(ponto.x(), ponto.y(),ponto.x() + vetornormal.x()*10,ponto.y() + vetornormal.y()*10);

                }


                // Realiza a ligação entre as extremidades abertas da Adjacent Cycle

                /// CRIA A LINHA QUE FECHA O MEMBRO ADJACENTE
                ///
                /// areacontorno1 < 0; significa que ciclo é horário
                /// areacontorno1 > 0; significa que ciclo é antihorario
                ///



                HalfEdge *he0 = new HalfEdge;
                HalfEdge *he1 = new HalfEdge;

                he0->twin = he1;
                he1->twin = he0;

                he0->p3 = half1->p3;
                he0->p2 = half1->p3 + (half1->p3 - half1->p2);

                he0->p1 =  half2->p3 + (half2->p3 - half2->p2);
                he0->p0 =  half2->p3;

                //painter->setPen(QPen(QColor(50, 50, 50), 4, Qt::SolidLine));

                QPainterPath linhaquefechaadjacente;

                if (areacontorno1 < 0){
                    angulopranormal = 90;

                    linhaquefechaadjacente.moveTo(he0->p3.x(),he0->p3.y());
                    linhaquefechaadjacente.cubicTo(he0->p2.x(),he0->p2.y(),he0->p1.x(),he0->p1.y(),he0->p0.x(),he0->p0.y());

                } else {
                    angulopranormal = -90;

                    linhaquefechaadjacente.moveTo(he0->p0.x(),he0->p0.y());
                    linhaquefechaadjacente.cubicTo(he0->p1.x(),he0->p1.y(),he0->p2.x(),he0->p2.y(),he0->p3.x(),he0->p3.y());
                }

                painter->drawPath(linhaquefechaadjacente);





                for (float var = linhaquefechaadjacente.length(); var >0; var = var - contoursamplingvalue){

                    painter->drawPath(linhaquefechaadjacente);
                    float percent = var / linhaquefechaadjacente.length();


                    QVector3D p(0,0, -poligonodabezier.boundingRect().width()/adjnewcontour);
                    p.setX(linhaquefechaadjacente.pointAtPercent(percent).x());
                    p.setY(linhaquefechaadjacente.pointAtPercent(percent).y());
                    // p.setZ(alturacontornointerno*-5);

                    QLineF angleline;
                    // Set the origin:
                    angleline.setP1(linhaquefechaadjacente.pointAtPercent(percent));

                    // Set the angle and length:
                    angleline.setAngle(linhaquefechaadjacente.angleAtPercent(percent)+angulopranormal);
                    angleline.setLength(1);
                    QVector3D vetornormal(0,0,0);

                    vetornormal.setX(angleline.x2()-angleline.x1());
                    vetornormal.setY(angleline.y2()-angleline.y1());
                    vetornormal.setZ(0);

                    painter->drawLine(p.x(), p.y(),p.x() + vetornormal.x()*10,p.y() + vetornormal.y()*10);


                    knownPoints.push_back(p);
                    knownNormals.push_back(vetornormal);
                }


                /// PRECISA ENCONTRAR EM QUAL BORDER QUE ESTÁ Para calcular altura
                ///
                ///
                ///
                float alturadomembro;

                for (int k = 0; k < listadeciclos.size() ; k++){

                    QPolygonF poligonodocorpo = criapoligono(listadeciclos[k]);

                    QPolygonF poligonodabezier = criapoligono(listadeciclos[i]);

                    QPainterPath border = criapath(listadeciclos[k]);



                    if (poligonodocorpo.containsPoint(poligonodabezier.boundingRect().center(),Qt::WindingFill)){


                        std::vector<QVector3D>PointsdoCorpo;
                        std::vector<QVector3D>NormalsdoCorpo;


                        for (float var = border.length(); var > 0 ; var = var - contoursamplingvalue) {

                            float percent = var / border.length();
                            poligonodocorpo << QPoint (border.pointAtPercent(percent).x(),border.pointAtPercent(percent).y());

                            QLineF angleline;
                            /* Set the origin: */
                            angleline.setP1(border.pointAtPercent(percent));
                            QVector3D ponto;

                            ponto.setX(border.pointAtPercent(percent).x());
                            ponto.setY(border.pointAtPercent(percent).y());
                            ponto.setZ(0);
                            PointsdoCorpo.push_back(ponto);

                            /* Set the angle and length: */
                            angleline.setAngle(border.angleAtPercent(percent)-90);
                            angleline.setLength(1);
                            QVector3D vetornormal(0,0,0);

                            vetornormal.setX(angleline.x2()-angleline.x1());
                            vetornormal.setY(angleline.y2()-angleline.y1());

                            NormalsdoCorpo.push_back(vetornormal);
                        }


                        QVector3D pontopracalcularaltura (0,0,0);
                        pontopracalcularaltura.setX(linhaquefechaadjacente.pointAtPercent(0.5).x());
                        pontopracalcularaltura.setY(linhaquefechaadjacente.pointAtPercent(0.5).y());
                        float weight = 0;
                        for(QVector3D pi:PointsdoCorpo)
                        {
                            weight += 1.0/((pontopracalcularaltura-pi).lengthSquared());///acho que isso retorna a norma ao 2

                            ///PROBLEMA
                            /// Talvez tenha que trazer os pontos para 0~1
                        }

                        ///calcula a normal
                        QVector3D n(0,0,0);
                        for(int l = 0; l <NormalsdoCorpo.size(); l++)
                        {
                            QVector3D pi = PointsdoCorpo.at(l);
                            QVector3D ui = NormalsdoCorpo.at(l);
                            n += (ui / (pontopracalcularaltura-pi).lengthSquared());///acho que isso retorna a norma ao 2
                        }

                        n = n / weight;

                        n.setZ(sqrt(1 - n.x()*n.x() - n.y()*n.y()));

                        alturadomembro = 0 ;

                        alturadomembro = n.z()*(poligonodocorpo.boundingRect().width()/ldepthadj);
                        alturadomembro += adjnewcontour;
                        //alturadomembro = alturadomembro*ldepthadj;

                        //alturadomembro = n.z()*(border.boundingRect().width()/ladj);
                        //alturadomembro = alturadomembro*10;
                        qDebug () << "----------";
                        qDebug () << alturadomembro;
                        qDebug () << "----------";


                    }
                }

                for(QVector3D pi:knownPoints){
                    totalPoints.push_back(pi);
                }

                for(QVector3D ui:knownNormals){
                    ui.normalize();
                    totalNormals.push_back(ui);
                }

                QRectF boundingbox1 = contorno1.boundingRect();

                float xmin = boundingbox1.left();
                float xmax = boundingbox1.right();
                float ymin = boundingbox1.top();
                float ymax = boundingbox1.bottom();

                float spacing = gridsamplingvalue;
                int r,g,b;

                for(float x = xmin; x < xmax; x = x + spacing)
                {
                    for(float y = ymin; y < ymax; y = y + spacing)
                    {

                        QPointF ponto (x,y);

                        //if (poligonointerno.containsPoint(ponto,Qt::WindingFill)){
                        if (poligonodabezier.containsPoint(ponto,Qt::WindingFill)){
                            ///para cada ponto do grid... que esteja dentro do contorno
                            QVector3D p(x,y,0);
                            //calcula o peso
                            float weight = 0;
                            for(QVector3D pi:knownPoints)
                            {
                                weight += 1.0/((p-pi).lengthSquared());///acho que isso retorna a norma ao 2

                                ///PROBLEMA
                                /// Talvez tenha que trazer os pontos para 0~1
                            }

                            ///calcula a normal
                            QVector3D n(0,0,0);
                            for(int i = 0; i <knownNormals.size(); i++)
                            {
                                QVector3D pi = knownPoints.at(i);
                                QVector3D ui = knownNormals.at(i);
                                n += (ui / (p-pi).lengthSquared());///acho que isso retorna a norma ao 2
                            }

                            n = n / weight;

                            n.setZ(sqrt(1 - n.x()*n.x() - n.y()*n.y()));


                            p.setZ(n.z()*(boundingbox1.width()/ladj));


                            if  (n.z() < 0.5){

                                r = (abs(n.x()) + 1)/2*255;
                                g = (abs(n.y()) + 1)/2*255;
                                b = (n.z() + 1)/2*255;

                                painter->setPen(QPen(QColor(r,g,b), 1, Qt::SolidLine));
                                painter->drawLine(p.x(), p.y(), p.x(), p.y());

                                totalPoints.push_back(p);
                                p.setZ(p.z()*-1);
                                totalPoints.push_back(p);

                                totalNormals.push_back(n);
                                n.setZ(n.z()*-1);
                                totalNormals.push_back(n);
                            }
                        }
                    }
                }


                std::string outFile = "rbf";
                outFile.append("_");
                outFile.append(fileSvg.toStdString());
                //Remover o .svg do nome
                outFile.pop_back();
                outFile.pop_back();
                outFile.pop_back();
                outFile.pop_back();
                //std::string s = ;
                outFile.append("_ID");
                outFile.append(std::to_string(listadeciclos[i]->cycle));
                outFile.append("_Ciclo");
                outFile.append(std::to_string(i));
                outFile.append("_1");
                outFile.append(".data");

                ///agora abre um arquivo pra salvar estes dados para serem entrada do RBF. Esse é o formato que eu uso
                std::ofstream fOut1;
                fOut1.open(outFile.c_str());
                fOut1 << "3" <<std::endl;
                fOut1 << knownPoints.size() <<std::endl;
                for(QVector3D p:knownPoints)
                {
                    fOut1 << p.x() <<" " << p.y()<< " " << p.z()+alturadomembro<< std::endl;
                }

                fOut1 << totalNormals.size() << std::endl;

                for(int l = 0; l < totalNormals.size(); l++)
                {

                    QVector3D p = totalPoints.at(l);
                    QVector3D n = totalNormals.at(l);

                    fOut1 << n.x() <<" " << n.y()<< " " << n.z()<< std::endl;
                    fOut1 << p.x() <<" " << p.y()<< " " << p.z()+alturadomembro<< std::endl;
                }
                fOut1 << "0" << std::endl;
                fOut1.close();


                outFile = "rbf";
                outFile.append("_");
                outFile.append(fileSvg.toStdString());
                //Remover o .svg do nome
                outFile.pop_back();
                outFile.pop_back();
                outFile.pop_back();
                outFile.pop_back();
                //std::string s = ;
                outFile.append("_ID");
                outFile.append(std::to_string(listadeciclos[i]->cycle));
                outFile.append("_Ciclo");
                outFile.append(std::to_string(i));
                outFile.append("_2");
                outFile.append(".data");

                ///agora abre um arquivo pra salvar estes dados para serem entrada do RBF. Esse é o formato que eu uso
                std::ofstream fOut;
                fOut.open(outFile.c_str());
                fOut << "3" <<std::endl;
                fOut << knownPoints.size() <<std::endl;
                for(QVector3D p:knownPoints)
                {
                    if (almostEqual(p.z(),-poligonodabezier.boundingRect().width()/adjnewcontour)){ // Significa que é a linha que fecha, que deve estar invertida
                        fOut << p.x() <<" " << p.y()<< " " << (p.z()*-1)-alturadomembro << std::endl;

                    } else {
                        fOut << p.x() <<" " << p.y()<< " " << p.z()-alturadomembro << std::endl;
                    }

                }

                fOut << totalNormals.size() << std::endl;

                for(int k = 0; k < totalNormals.size(); k++)
                {

                    QVector3D p = totalPoints.at(k);
                    QVector3D n = totalNormals.at(k);

                    fOut << n.x() <<" " << n.y()<< " " << n.z()<< std::endl;
                    if (almostEqual(p.z(),-poligonodabezier.boundingRect().width()/adjnewcontour)){ // Significa que é a linha que fecha, que deve estar invertida
                        fOut << p.x() <<" " << p.y()<< " " << (p.z()*-1)-alturadomembro << std::endl;

                    } else {
                        fOut << p.x() <<" " << p.y()<< " " << p.z()-alturadomembro << std::endl;
                    }
                }
                fOut << "0" << std::endl;
                fOut.close();

            }

        }




    }
}





///// - -------- INTERFACE --------



void MainWindow::on_slider_lshapes_sliderMoved(int position)
{
    lshapesvalue = ui->slider_lshapes->value();
    ui->label_lshapes->setText(QString ("%1").arg(1/lshapesvalue));
    //update();
}

void MainWindow::on_slider_lsym_sliderMoved(int position)
{
    lsym = ui->slider_lsym->value();
    ui->label_lsym->setText(QString ("%1").arg(1/lsym));
}

void MainWindow::on_slider_ldepthsym_sliderMoved(int position)
{
    ldepthsym = ui->slider_ldepthsym->value();
    ui->label_ldepthsym->setText(QString ("%1").arg(1/ldepthsym));
}

void MainWindow::on_slider_lisland_sliderMoved(int position)
{
    lisland = ui->slider_lisland->value();
    ui->label_lisland->setText(QString ("%1").arg(1/lisland));
}

void MainWindow::on_slider_ldepthisland_sliderMoved(int position)
{
    ldepthisland = ui->slider_ldepthisland->value();
    ui->label_ldepthisland->setText(QString ("%1").arg(1/ldepthisland));
}


void MainWindow::on_slider_adjnewcontour_sliderMoved(int position)
{
    adjnewcontour = ui->slider_adjnewcontour->value();
    ui->label_adjnewcontour->setText(QString ("%1").arg(adjnewcontour));
}

void MainWindow::on_slider_ldepthadj_sliderMoved(int position)
{
    ldepthadj = ui->slider_ldepthadj->value();
    ui->label_ldepthadj->setText(QString ("%1").arg(1/ldepthadj));
}

void MainWindow::on_slider_ladj_sliderMoved(int position)
{
    ladj = ui->slider_ladj->value();
    ui->label_ladj->setText(QString ("%1").arg(1/ladj));
}

void MainWindow::on_contoursampling_sliderMoved(int position)
{
    contoursamplingvalue = ui->contoursampling->value();
    ui->contoursamplingvalue->setText(QString ("%1").arg(contoursamplingvalue));
    update();

}

void MainWindow::on_gridsampling_sliderMoved(int position)
{

    gridsamplingvalue = ui->gridsampling->value();
    ui->gridsamplingvalue->setText(QString ("%1").arg(gridsamplingvalue));
    update();

}



