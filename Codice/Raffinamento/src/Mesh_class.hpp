#ifndef __MESH_H
#define __MESH_H
#include "OggettiGeometrici_class.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <fstream>
#include <iomanip>

namespace ProjectLibrary
{
    class Mesh
    {
        private:
            static vector<Punto> Punti; //vettore dei punti
            static vector<Lato> Lati; //vettore dei lati
            static vector<Triangolo> Triangoli; //vettore dei triangoli
            static list<idTriangoloArea> TriangoliOrdinati; //lista di struct che tiene conto dell'ordinamento per area dei triangoli

        public:

            Mesh(){}

            ///metodo per raffinare
            bool Raffina(const int& theta); //funzione che inizia il raffinamento prendendo in imput il numero di triangoli da raffinare

            ///metodo per importare Dati
            bool Importa();

            ///metodo per Stampare Dati
            bool Stampa();

            ///metodo per testare la mesh
            bool TestMesh();

            ///metodi per leggere le static
            static vector<Punto> getPunti() {return Punti;}
            static vector<Lato> getLati() {return Lati;}
            static vector<Triangolo> getTriangoli() {return Triangoli;}
            static list<idTriangoloArea> getTriangoliOrdinati() {return TriangoliOrdinati;}

            ///metodi amici di Mesh
            //metodo di Lato amico di Mesh
            friend double Lato::calcolaLunghezza(); //deve accedere al vector di punti
            friend array<double,2> Lato::CalcolaPuntoMedio(); //deve accedere al vector di punti

            ///metodi di Triangolo amici di Mesh
            friend double Triangolo::calcolaAreaSegno(); //deve accedere al vector di punti
            friend int Triangolo::getLatoLungo(); //deve accedere al vector di lati
            friend int Triangolo::getVerticeOpposto(const int& idLato); //deve accedere al vector di punti e lati
            friend void Triangolo::SpegniTriangolo(const int& idLatoCorrente); //deve accedere al vector di  lati

        class GestioneDati
        {
            public:
                GestioneDati(){}

                bool ImportPunti();
                bool ImportLati();
                bool ImportTriangoli();

                bool StampaPunti();
                bool StampaLati();
                bool StampaTriangoli();
        };

        class GestioneAlgoritmo
        {
            private:
                int puntoSospeso = -1;
                int triangoloFittizio = -1;
                int latoNuovoTF = -1;

                int triangoloBase = -1, triangoloBase2 = -1;
                int latoLungoTB = -1, latoLungoTB2 = -1;
                int latoFiglio1TB = -1, latoFiglio1TB2 = -1;
                int latoFiglio2TB = -1, latoFiglio2TB2 = -1;
                int puntoMedioTB = -1, puntoMedioTB2 = -1;
                int latoNuovoTB = -1, latoNuovoTB2 = -1;
                int puntoOppostoTB = -1, puntoOppostoTB2 = -1;

            public:
                int CreaPunto(const array<double,2>& coordinate);
                int CreaLato(const array<int,2>& idPunti);
                int CreaTriangolo(const array<int,3>& idPunti, const array<int,3>& idLati);

                array<int,2> Crea2Lati(const int& idPunto, const int& idLatoVecchio);
                array<int,2> Crea2Triangoli(const int& idPuntoNuovo, const int& idLatoVecchio, const array<int,3>& idLati, const int& idTriangoloVecchio);

                int individuaTriangoloAdiacente(const int& idTriangolo,const int& idLato);
                void AssegnaAdiacenza(const int& idTriangoloNuovo,const int& idTriangoloVecchio = -1);

                bool Raffina1Triangolo(const int& idTriangolo);
                void InserisciTriangolo(const idTriangoloArea &T);
        };
    };
}
#endif // __MESH_H
