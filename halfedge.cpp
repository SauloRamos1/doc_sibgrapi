#include "halfedge.h"



bool HalfEdgeGraph::almostEqual(float a, float b)
{
    //return fabs(a - b) <= FLT_EPSILON;
    return fabs(a - b) <= 3;
}



void HalfEdgeGraph::criaestruturadehalfedges(QVector<QVector<float>> listadecurvas)
{

///https://cs.stackexchange.com/questions/2450/how-do-i-construct-a-doubly-connected-edge-list-given-a-set-of-line-segments/2516#2516
    ///1. For each endpoint, create a vertex.
    ///
    ///
    // ---------------------- Cria Lista de Vértices-----------------------------
    for (int i = 0; i < listadecurvas.size(); i++){
        Vertex *vertex1 = new Vertex;
        Vertex *vertex2 = new Vertex;

        vertex1->x = listadecurvas[i][0];
        vertex1->y = listadecurvas[i][1];

        vertex2->x = listadecurvas[i][6];
        vertex2->y = listadecurvas[i][7];

        listadevertex.push_back(vertex1);
        listadevertex.push_back(vertex2);
    }

    // ---------------------- Limpa itens duplicados da Lista de Vértices-----------------------------
    cout << "# de vertices: " << listadevertex.size() << endl;

    int qtdeitensduplicados;

    for (int j = 0; j < listadevertex.size(); j++){

        for (int k = j+1; k < listadevertex.size(); k++){

            if (almostEqual(listadevertex[j]->x,listadevertex[k]->x) && (almostEqual(listadevertex[j]->y, listadevertex[k]->y))){
                qtdeitensduplicados+=1;
                //qDebug () << listadevertex[j]->x << "  " << listadevertex[k]->x << j  <<" "<< k;
                listadevertex.remove(k);
                k--;

            } else {


            }
        }
    }

    cout << "# de vertices apos limpeza: " << listadevertex.size() << endl;

    // ---------------------- Limpa itens duplicados da Lista de Vértices-----------------------------
    ///2. For each input segment, create two half-edges, and assign their tail vertices and twins.
    ///
    //-----------------------Cria Half-edges para as curvas----------------------------------

    for (int i = 0; i < listadecurvas.size(); i++){

        HalfEdge *he0 = new HalfEdge;
        HalfEdge *he1 = new HalfEdge;

        he0->next = nullptr;
        he0->prev = nullptr;

        he1->next = nullptr;
        he1->prev = nullptr;

        he0->twin = he1;
        he1->twin = he0;

        he0->p0.setX(listadecurvas[i][0]);
        he0->p0.setY(listadecurvas[i][1]);
        he0->p1.setX(listadecurvas[i][2]);
        he0->p1.setY(listadecurvas[i][3]);
        he0->p2.setX(listadecurvas[i][4]);
        he0->p2.setY(listadecurvas[i][5]);
        he0->p3.setX(listadecurvas[i][6]);
        he0->p3.setY(listadecurvas[i][7]);

        he1->p0.setX(listadecurvas[i][6]);
        he1->p0.setY(listadecurvas[i][7]);
        he1->p1.setX(listadecurvas[i][4]);
        he1->p1.setY(listadecurvas[i][5]);
        he1->p2.setX(listadecurvas[i][2]);
        he1->p2.setY(listadecurvas[i][3]);
        he1->p3.setX(listadecurvas[i][0]);
        he1->p3.setY(listadecurvas[i][1]);

        Vertex *vertex1 = new Vertex;
        Vertex *vertex2 = new Vertex;

        vertex1->x = listadecurvas[i][0];
        vertex1->y = listadecurvas[i][1];

        vertex2->x = listadecurvas[i][6];
        vertex2->y = listadecurvas[i][7];

        he0->tail = vertex1;
        he1->tail = vertex2;



        halfedgeslist.push_back(he0);
        halfedgeslist.push_back(he1);

    }

    //-----------------------Cria Half-edges para as curvas----------------------------------


    ///3. For each endpoint, sort the half-edges whose tail vertex is that endpoint in clockwise order.

    vector<HalfEdge *> clockwisehalfedgeslist; //Lista de half-edges whose tail vertex is that endpoint in clockwise order.


    int tjunctions = 0;

    int linhassugestivas = 0;

    for (int i=0; i < listadevertex.size(); i++){

        for (int j=0; j < halfedgeslist.size(); j++){
            if (almostEqual(listadevertex[i]->x,halfedgeslist[j]->tail->x) && (almostEqual(listadevertex[i]->y, halfedgeslist[j]->tail->y))){
                clockwisehalfedgeslist.push_back(halfedgeslist[j]);
            }
        }
        // Uma half-edge começa naquele vértice

        // É ponto da linha sugestiva!!

        if (clockwisehalfedgeslist.size() == 1){
            // clockwisehalfedgeslist[0]->prev =clockwisehalfedgeslist[0];
            //  clockwisehalfedgeslist[0]->twin->next = clockwisehalfedgeslist[0]->twin;

            clockwisehalfedgeslist[0]->prev =clockwisehalfedgeslist[0]->twin;
            clockwisehalfedgeslist[0]->twin->next = clockwisehalfedgeslist[0];
            linhassugestivas +=1;

        }

        // Duas half-edges começam naquele vértice
        if (clockwisehalfedgeslist.size() == 2) {

            clockwisehalfedgeslist[0]->twin->next = clockwisehalfedgeslist[1];
            clockwisehalfedgeslist[1]->twin->next = clockwisehalfedgeslist[0];

            clockwisehalfedgeslist[0]->prev = clockwisehalfedgeslist[1]->twin;
            clockwisehalfedgeslist[1]->prev = clockwisehalfedgeslist[0]->twin;



        }

        // Três half-edges começam naquele vértice

        if (clockwisehalfedgeslist.size() == 3) {

            tjunctions+=1;

            QVector <float> desordenado;
            QVector <float> ordenado;

            float he1atan = atan2 (clockwisehalfedgeslist[0]->twin->tail->y - clockwisehalfedgeslist[0]->tail->y,clockwisehalfedgeslist[0]->twin->tail->x - clockwisehalfedgeslist[0]->tail->x);
            float he2atan = atan2 (clockwisehalfedgeslist[1]->twin->tail->y - clockwisehalfedgeslist[1]->tail->y,clockwisehalfedgeslist[1]->twin->tail->x - clockwisehalfedgeslist[1]->tail->x);
            float he3atan = atan2 (clockwisehalfedgeslist[2]->twin->tail->y - clockwisehalfedgeslist[2]->tail->y,clockwisehalfedgeslist[2]->twin->tail->x - clockwisehalfedgeslist[2]->tail->x);

            desordenado.push_back(he1atan);
            desordenado.push_back(he2atan);
            desordenado.push_back(he3atan);

            ordenado = desordenado;

            qSort(ordenado);

            // qDebug () << ordenado;
            // qDebug () << desordenado;
            // qDebug () << "--";

            ///4. For every pair of half-edges e1, e2 in clockwise order, assign e1->twin->next = e2 and e2->prev = e1->twin.
            ///
            ///

            int e1 = desordenado.indexOf(ordenado[0]);
            int e2 = desordenado.indexOf(ordenado[1]);

            clockwisehalfedgeslist[e1]->twin->next = clockwisehalfedgeslist[e2];
            clockwisehalfedgeslist[e2]->prev = clockwisehalfedgeslist[e1]->twin;

            e1 = desordenado.indexOf(ordenado[1]);
            e2 = desordenado.indexOf(ordenado[2]);

            clockwisehalfedgeslist[e1]->twin->next = clockwisehalfedgeslist[e2];
            clockwisehalfedgeslist[e2]->prev = clockwisehalfedgeslist[e1]->twin;

            e1 = desordenado.indexOf(ordenado[2]);
            e2 = desordenado.indexOf(ordenado[0]);

            clockwisehalfedgeslist[e1]->twin->next = clockwisehalfedgeslist[e2];
            clockwisehalfedgeslist[e2]->prev = clockwisehalfedgeslist[e1]->twin;


            //qDebug () << clockwisehalfedgeslist[0]->tail->x << ", " <<  clockwisehalfedgeslist[0]->tail->y << "-->" <<clockwisehalfedgeslist[0]->twin->tail->x << ", " <<  clockwisehalfedgeslist[0]->twin->tail->y << " Angulo:" << he1atan;
            //qDebug () << clockwisehalfedgeslist[1]->tail->x << ", " <<  clockwisehalfedgeslist[1]->tail->y << "-->" <<clockwisehalfedgeslist[1]->twin->tail->x << ", " <<  clockwisehalfedgeslist[1]->twin->tail->y << " Angulo:" << he2atan;
            //qDebug () << clockwisehalfedgeslist[2]->tail->x << ", " <<  clockwisehalfedgeslist[2]->tail->y << "-->" <<clockwisehalfedgeslist[2]->twin->tail->x << ", " <<  clockwisehalfedgeslist[2]->twin->tail->y << " Angulo:" << he3atan;

        }

        if (clockwisehalfedgeslist.size() == 4) {
            qDebug () << "Erro, T-junction com 4 linhas" ;

            qDebug () << clockwisehalfedgeslist[0]->p0;
        }

        clockwisehalfedgeslist.clear();

    }


    qDebug () << "# de Half-Edges " << halfedgeslist.size();
    qDebug () << "# de T-junctions: " << tjunctions;

    qDebug () << "# de Linhas Sugestivas: " << linhassugestivas;

    ///Pick one of the half-edges and assign it as the representative for the endpoint.
    ///


    int halfedgesconectadas =0;
    for (int i=0; i < halfedgeslist.size(); i++){

        if (halfedgeslist[i]->next == nullptr || halfedgeslist[i]->prev == nullptr){
            qDebug () << "Nao tem prev ou next";
            qDebug () << halfedgeslist[i]->tail->x <<"," <<halfedgeslist[i]->tail->y;

        } else {
            halfedgesconectadas +=1;
        }

    }


    qDebug () << "# de Half-Edges Conectadas:" << halfedgesconectadas;



    qDebug () << " ---------ESTRUTURA DE HALF-EDGES CRIADA--------"    ;


}
//--------------- Separa em ciclos ------------

/// Agora cria uma lista com as half-edges que representam um ciclo
///
///
///

QVector<HalfEdge*> HalfEdgeGraph::separaciclos(){
    while (halfedgeslist.size() != 0){

        HalfEdge* begin = halfedgeslist[halfedgeslist.size()-1];
        HalfEdge* half = begin;



        listadeciclos.push_back(begin);


        do
        {

            half->numerodociclo = listadeciclos.size();

            //qDebug () << half->numerodociclo;

            halfedgeslist.erase(find(halfedgeslist.begin(), halfedgeslist.end(), half));

            half = half->next;

        }
        while(half != begin);
    }

    qDebug () << "# de ciclos: " << listadeciclos.size();
    return listadeciclos;

}
