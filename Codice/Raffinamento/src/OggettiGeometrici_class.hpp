#ifndef __OGGETTI_GEOMETRICI_H
#define __OGGETTI_GEOMETRICI_H

#include <array>
#include <cmath>

using namespace std;

namespace ProjectLibrary
{

class Tolleranze
{
    public:
    static double geometricTol;
    static double geometricTol_Squared;
    static double max_tolerance(const double& x, const double& y) {return x > y ? x : y;}
};

class Punto
{
   public:
      array<double,2> coordinate;

      //Costruttori
      Punto(){}
      Punto(const array<double,2>& coordinate);

};

class Lato
{
   public:
      bool stato = true; //indica se il lato è attivo o meno
      array<int,2> idPuntiLato; //id dei punti che compongono il lato
      double lunghezza = 0;
      array<int,2> triangoliAdiacenti = {-1, -1}; //vettore che contiene gli id dei triangoli che hanno questo lato

      //Costruttori
      Lato(){}
      Lato(const array<int,2>& idPuntiLato);

      //metodo per calcolare la lunghezza
      double calcolaLunghezza(); //calcola la lunghezza va inizializzato nella classe mesh come metodo amico
      array<double,2> CalcolaPuntoMedio(); //Restituisce le coordinate del punto medio del lato

      //metodo che inserisce l'idTriangolo in TriangoliAdiacenti alla posizione specificata
      void riempiTriangoliAdiacenti(const int& idTriangolo, const int& posizione) { triangoliAdiacenti[posizione] = idTriangolo; return; }

      //metodo che spegne il Lato
      void SpegniLato() {triangoliAdiacenti = {-1, -1}; stato=false; return;}

      //metodi per confronto lati per lunghezza
      bool operator>=(const Lato& L1) const {
          return lunghezza > L1.lunghezza + Tolleranze::geometricTol * max(lunghezza, L1.lunghezza);
      }

};

class Triangolo
{
   public:
      bool stato = true; //indica se il triangolo è attivo o meno
      array<int,3> idPuntiTriangolo; //id dei punti che compongono il triangolo
      array<int,3> idLatiTriangolo; //id dei lati che compongono il triangolo
      double area = 0;

      //Costruttori
      Triangolo(){}
      Triangolo(const array<int,3>& idPuntiTriangolo,const array<int,3>& idLatiTriangolo);

      double calcolaAreaSegno(); //calcola l'area con segno.
      void ordinaVertici(); //ordina i vertici in senso antiorario e salva in area l'area in modulo.

      int getLatoLungo();
      int getVerticeOpposto(const int &idLato);

      //metodo che spegne il Triangolo
      void SpegniTriangolo(const int& idTriangoloCorrente);
};

struct idTriangoloArea
{
      int id;
      double area;
      idTriangoloArea(const int& id, const double& area);

      ///metodi per confronto struc triangoli per area
      bool operator>(const idTriangoloArea& T1) const {
          return area > T1.area + Tolleranze::geometricTol_Squared * max(area, T1.area);
      }

      bool operator<(const idTriangoloArea& T1) const {
          return area < T1.area - Tolleranze::geometricTol_Squared * max(area, T1.area);
      }

      bool operator==(const idTriangoloArea& T1) const {
          return !(area < T1.area) && !(area > T1.area);
      }

};

}
#endif // __OGGETTI_GEOMETRICI_H


