#ifndef __TEST_OGGETTI_GEOMETRICI_G
#define __TEST_OGGETTI_GEOMETRICI_G

#include <gtest/gtest.h>
#include "Mesh_class.hpp"
#include "OggettiGeometrici_class.hpp"

using namespace testing;
using namespace std;
using namespace ProjectLibrary;

Mesh::GestioneAlgoritmo G;

TEST(TestLato, TestCalcolaLungGezza)
{

    // Crea due oggetti Punto
    array<double,2> coordinate1 = {0.0, 0.0};
    array<double,2> coordinate2 = {3.0, 4.0};
    int P1 = G.CreaPunto(coordinate1);
    int P2 = G.CreaPunto(coordinate2);

    // Crea un oggetto Lato
    array<int,2> idPuntiLato = {P1, P2};
    int L1 = G.CreaLato(idPuntiLato);

    // Calcola la lungGezza del lato
    double lunghezza = Mesh::getLati()[L1].calcolaLunghezza();

    // Verifica se la lungGezza calcolata è corretta (nell'esempio dovrebbe essere 5.0)
    ASSERT_DOUBLE_EQ(lunghezza, 5.0);
}

TEST(TestLato, CalcolaPuntoMedio)
{

    // Crea due oggetti Punto
    array<double,2> coordinate1 = {0.0, 0.0};
    array<double,2> coordinate2 = {4.0, 8.0};
    int P1 = G.CreaPunto(coordinate1);
    int P2 = G.CreaPunto(coordinate2);

    // Crea un oggetto Lato
    array<int,2> idPuntiLato = {P1, P2};
    int L1 = G.CreaLato(idPuntiLato);

    // Calcola il punto medio del lato
    array<double, 2> puntoMedio = Mesh::getLati()[L1].CalcolaPuntoMedio();

    // Verifica se il punto medio calcolato è corretto (nell'esempio dovrebbe essere {2.0, 4.0})
    ASSERT_DOUBLE_EQ(puntoMedio[0], 2.0);
    ASSERT_DOUBLE_EQ(puntoMedio[1], 4.0);
}

TEST(TestTriangolo, calcolaAreaSegno)
{

    // Crea tre oggetti Punto
    array<double,2> coordinate1 = {0.0, 0.0};
    array<double,2> coordinate2 = {0.0, 5.0};
    array<double,2> coordinate3 = {3.0, 0.0};
    int P1 = G.CreaPunto(coordinate1);
    int P2 = G.CreaPunto(coordinate2);
    int P3 = G.CreaPunto(coordinate3);

    // Crea tre oggetto Lato
    array<int,2> idPuntiLato1 = {P1, P2};
    int L1 = G.CreaLato(idPuntiLato1);
    array<int,2> idPuntiLato2 = {P2, P3};
    int L2 = G.CreaLato(idPuntiLato2);
    array<int,2> idPuntiLato3 = {P3, P1};
    int L3 = G.CreaLato(idPuntiLato3);

    // Crea un oggetto Triangolo
    array<int,3> PuntiTriangolo = {P1, P2, P3};
    array<int,3> LatiTriangolo = {L1, L2, L3};
    int T1 = G.CreaTriangolo(PuntiTriangolo, LatiTriangolo);

    // Calcola il punto medio del lato
    double areaSegno = Mesh::getTriangoli()[T1].calcolaAreaSegno();

    ASSERT_DOUBLE_EQ(areaSegno, 7.5);

}

TEST(TestTriangolo, getLatoLungo)
{

    // Crea tre oggetti Punto
    array<double,2> coordinate1 = {0.0, 0.0};
    array<double,2> coordinate2 = {0.0, 10.0};
    array<double,2> coordinate3 = {3.0, 0.0};
    int P1 = G.CreaPunto(coordinate1);
    int P2 = G.CreaPunto(coordinate2);
    int P3 = G.CreaPunto(coordinate3);

    // Crea tre oggetto Lato
    array<int,2> idPuntiLato1 = {P1, P2};
    int L1 = G.CreaLato(idPuntiLato1);
    array<int,2> idPuntiLato2 = {P2, P3};
    int L2 = G.CreaLato(idPuntiLato2);
    array<int,2> idPuntiLato3 = {P3, P1};
    int L3 = G.CreaLato(idPuntiLato3);

    // Crea un oggetto Triangolo
    array<int,3> PuntiTriangolo = {P1, P2, P3};
    array<int,3> LatiTriangolo = {L1, L2, L3};
    int T1 = G.CreaTriangolo(PuntiTriangolo, LatiTriangolo);

    // Restituisce il lato lungo del triangolo
    int idLatoLungo = Mesh::getTriangoli()[T1].getLatoLungo();

    ASSERT_EQ(idLatoLungo, L2);
}

TEST(TestTriangolo, getVerticeOpposto)
{

    // Crea tre oggetti Punto
    array<double,2> coordinate1 = {0.0, 0.0};
    array<double,2> coordinate2 = {0.0, 10.0};
    array<double,2> coordinate3 = {3.0, 0.0};
    int P1 = G.CreaPunto(coordinate1);
    int P2 = G.CreaPunto(coordinate2);
    int P3 = G.CreaPunto(coordinate3);

    // Crea tre oggetto Lato
    array<int,2> idPuntiLato1 = {P1, P2};
    int L1 = G.CreaLato(idPuntiLato1);
    array<int,2> idPuntiLato2 = {P2, P3};
    int L2 = G.CreaLato(idPuntiLato2);
    array<int,2> idPuntiLato3 = {P3, P1};
    int L3 = G.CreaLato(idPuntiLato3);

    // Crea un oggetto Triangolo
    array<int,3> PuntiTriangolo = {P1, P2, P3};
    array<int,3> LatiTriangolo = {L1, L2, L3};
    int T1 = G.CreaTriangolo(PuntiTriangolo, LatiTriangolo);

    // Restituisce il vertice opposto al lato fissato
    int idVerticeOpposto = Mesh::getTriangoli()[T1].getVerticeOpposto(L3);

    ASSERT_EQ(idVerticeOpposto, P2);
}

#endif // __TEST_OGGETTI_GEOMETRICI_G
