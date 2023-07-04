#include "OggettiGeometrici_class.hpp"
#include "Mesh_class.hpp"
#include <limits>
namespace ProjectLibrary
{
///definizione TOLLERANZE*********************************************************************

double Tolleranze::geometricTol = 0;
double Tolleranze::geometricTol_Squared = Tolleranze::max_tolerance(Tolleranze::geometricTol * Tolleranze::geometricTol,
                                                          numeric_limits<double>::epsilon());

///definizione COSTRUTTORI********************************************************************

Punto::Punto(const array<double, 2>& coordinate) :
             coordinate(coordinate) {}

Lato::Lato(const array<int,2>& idPuntiLato) :
           idPuntiLato(idPuntiLato)
           {lunghezza = calcolaLunghezza();}

Triangolo::Triangolo(const array<int, 3>& idPuntiTriangolo,
                     const array<int, 3>& idLatiTriangolo) :
                     idPuntiTriangolo(idPuntiTriangolo),
                     idLatiTriangolo(idLatiTriangolo)
                     {ordinaVertici();}

idTriangoloArea::idTriangoloArea(const int& id,
                                 const double& area) :
                                 id(id),
                                 area(area)
                                 {}



///METODI PUNTO***********************************************************************

///METODI LATO***********************************************************************

double Lato::calcolaLunghezza()
{
    double x1 = Mesh::Punti[idPuntiLato[0]].coordinate[0];
    double y1 = Mesh::Punti[idPuntiLato[0]].coordinate[1];
    double x2 = Mesh::Punti[idPuntiLato[1]].coordinate[0];
    double y2 = Mesh::Punti[idPuntiLato[1]].coordinate[1];
    lunghezza = sqrt(x1*x1 + x2*x2 + y1*y1 + y2*y2 - 2*(x1*x2 + y1*y2)); //calcola la lunghezza del lato
    return lunghezza;
}

array<double,2> Lato::CalcolaPuntoMedio()
{
    array<double,2> coordinatePM;
    array<double,2> coordinateP1 = Mesh::Punti[idPuntiLato[0]].coordinate;
    array<double,2> coordinateP2 = Mesh::Punti[idPuntiLato[1]].coordinate;
    coordinatePM[0] = (coordinateP1[0] + coordinateP2[0]) * 0.5;
    coordinatePM[1] = (coordinateP1[1] + coordinateP2[1]) * 0.5;
  return coordinatePM;
}

///METODI TRIANGOLO***********************************************************************

double Triangolo::calcolaAreaSegno()
{
    double x1 = Mesh::Punti[idPuntiTriangolo[0]].coordinate[0];
    double y1 = Mesh::Punti[idPuntiTriangolo[0]].coordinate[1];
    double x2 = Mesh::Punti[idPuntiTriangolo[1]].coordinate[0];
    double y2 = Mesh::Punti[idPuntiTriangolo[1]].coordinate[1];
    double x3 = Mesh::Punti[idPuntiTriangolo[2]].coordinate[0];
    double y3 = Mesh::Punti[idPuntiTriangolo[2]].coordinate[1];
    area = 0.5 * (x1*y2 + x2*y3 + x3*y1 - (x1*y3 + x2*y1 + x3*y2));

  return area;
}

int Triangolo::getLatoLungo()
{
    int idLatoLungo = 0;
    Lato L1 = Mesh::Lati[idLatiTriangolo[0]]; //mi fornisce l'oggetto lato che ha come id il primo elemento del array di lati del trangolo
    Lato L2 = Mesh::Lati[idLatiTriangolo[1]];
    Lato L3 = Mesh::Lati[idLatiTriangolo[2]];

    if(L1 >= L2 && L1 >= L3)
       idLatoLungo = idLatiTriangolo[0];
    if(L2 >= L1 && L2 >= L3)
       idLatoLungo = idLatiTriangolo[1];
    if(L3 >= L2 && L3 >= L1)
      idLatoLungo = idLatiTriangolo[2];
    return idLatoLungo;
}

void Triangolo::ordinaVertici()
{
    if(calcolaAreaSegno() <= 0)
    {
        swap(idPuntiTriangolo[1], idPuntiTriangolo[2]); //scambio l'ordine di due vertici
        calcolaAreaSegno(); //così in area verrà memorizzata l'area positiva
    }
    return;
}

int Triangolo::getVerticeOpposto(const int& idLato)
{
    int idVerticeOpposto = 0;
    array<int,2> idOriginEnd = Mesh::Lati[idLato].idPuntiLato; //prendo gli id dei punti che costituiscono il lato
    int idOrigin = idOriginEnd[0]; //prendo l'origine del lato
    int idEnd = idOriginEnd[1]; //prendo la fine del lato
    if(idPuntiTriangolo[0] != idOrigin && idPuntiTriangolo[0] != idEnd){
       idVerticeOpposto = idPuntiTriangolo[0];
    }else if(idPuntiTriangolo[1] != idOrigin && idPuntiTriangolo[1] != idEnd){
       idVerticeOpposto = idPuntiTriangolo[1];
    }else if(idPuntiTriangolo[2] != idOrigin && idPuntiTriangolo[2] != idEnd){
       idVerticeOpposto = idPuntiTriangolo[2];
    }
    return idVerticeOpposto;

}

void Triangolo::SpegniTriangolo(const int& idTriangoloCorrente)
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 2; j++)
        {
           if(Mesh::Lati[idLatiTriangolo[i]].triangoliAdiacenti[j] == idTriangoloCorrente)
               Mesh::Lati[idLatiTriangolo[i]].riempiTriangoliAdiacenti(-1,j);
        }
    }
    stato = false;
    return;
}

}
