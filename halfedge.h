#ifndef HALFEDGE_H
#define HALFEDGE_H


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

using namespace std;

// ----------------- Structs --------------------
struct HalfEdge;

struct Vertex{

    float x;
    float y;
    HalfEdge* half;     //Representative Half-edge of this EndPoint

    /* rep->tail == this */
};

struct Face {
    struct HalfEdge *half;  //Representative Half-edge of this Face

    /* rep->left == this */
};

struct HalfEdge {

    struct HalfEdge *prev;             /* prev->next == this */
    struct HalfEdge *next;             /* next->prev == this */
    struct HalfEdge *twin;             /* twin->twin == this */
    struct Vertex *tail;                    /* twin->next->tail == tail &&
                                                             prev->twin->tail == tail */
    struct Face *left;                        /* prev->left == left && next->left == left */

    QPointF p0;
    QPointF p1;
    QPointF p2;
    QPointF p3;

    int cycle = 0;

    int numerodociclo;

};


// ----------------- Structs --------------------


class HalfEdgeGraph
{
public:

    // ----------------- Variables --------------------

    vector<vector<float> >listadebezier;
    QVector<Vertex*> listadevertex;

    vector<HalfEdge*> halfedgeslist;
    QVector<QVector<float>> listadecurvas;

    QVector <HalfEdge*> listadeciclos;

    QString fileName;



    // ----------------- Variables --------------------
    // ----------------- Methods --------------------

public:

    bool almostEqual(float a, float b);

    void criaestruturadehalfedges(QVector<QVector<float>> listadecurvas);

    QVector<HalfEdge*> separaciclos();

};

#endif // HALFEDGE_H
