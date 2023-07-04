#ifndef __TEST_MESH_H
#define __TEST_MESH_H

#include <gtest/gtest.h>
#include "OggettiGeometrici_class.hpp"
#include "Mesh_class.hpp"

using namespace testing;
using namespace std;
using namespace ProjectLibrary;

Mesh M;
Mesh::GestioneAlgoritmo H;

TEST(TestGestioneAlgoritmo, InserisciTriangolo)
{
    // Crea oggetti Triangolo da inserire
    idTriangoloArea T1(1, 5.0);
    idTriangoloArea T2(2, 2.5);
    idTriangoloArea T3(3, 7.2);

    // Inserisci i triangoli nell'ordine inverso
    H.InserisciTriangolo(T3);
    H.InserisciTriangolo(T2);
    H.InserisciTriangolo(T1);

    // Verifica che i triangoli siano ordinati correttamente
    std::ostringstream oss;
    for (const auto& triangolo : M.getTriangoliOrdinati())
            oss << triangolo.id << " ";


    std::string risultatoCorretto = "3 1 2 ";
    ASSERT_EQ(oss.str(), risultatoCorretto);
}

TEST(TestGestioneAlgoritmo, individuaTriangoloAdiacente)
{
    // Crea quattro oggetti Punto
    array<double, 2> coordinate1 = {0.0, 1.0};
    array<double, 2> coordinate2 = {0.0, 12.0};
    array<double, 2> coordinate3 = {3.0, 1.0};
    array<double, 2> coordinate4 = {-10.0, 1.0};
    int idPunto1 = H.CreaPunto(coordinate1);
    int idPunto2 = H.CreaPunto(coordinate2);
    int idPunto3 = H.CreaPunto(coordinate3);
    int idPunto4 = H.CreaPunto(coordinate4);

    // Crea cinque oggetti Lato
    array<int, 2> idPuntiLato1 = {idPunto1, idPunto2};
    int idLato1 = H.CreaLato(idPuntiLato1);
    array<int, 2> idPuntiLato2 = {idPunto2, idPunto3};
    int idLato2 = H.CreaLato(idPuntiLato2);
    array<int, 2> idPuntiLato3 = {idPunto3, idPunto1};
    int idLato3 = H.CreaLato(idPuntiLato3);
    array<int, 2> idPuntiLato4 = {idPunto1, idPunto4};
    int idLato4 = H.CreaLato(idPuntiLato4);
    array<int, 2> idPuntiLato5 = {idPunto4, idPunto2};
    int idLato5 = H.CreaLato(idPuntiLato5);

    // Crea due triangoli con lati in comune
    array<int, 3> idPuntiTriangolo1 = {idPunto1, idPunto2, idPunto3};
    array<int, 3> idLatiTriangolo1 = {idLato1, idLato2, idLato3};
    int idTriangolo1 = H.CreaTriangolo(idPuntiTriangolo1, idLatiTriangolo1);
    H.AssegnaAdiacenza(idTriangolo1);
    array<int, 3> idPuntiTriangolo2 = {idPunto1, idPunto4, idPunto2};
    array<int, 3> idLatiTriangolo2 = {idLato1, idLato4, idLato5};
    int idTriangolo2 = H.CreaTriangolo(idPuntiTriangolo2, idLatiTriangolo2);
    H.AssegnaAdiacenza(idTriangolo2);

    // Verifica che i triangoli abbiano l'adiacenza corretta
    ASSERT_EQ(H.individuaTriangoloAdiacente(idTriangolo1,idLato1), idTriangolo2);
}

#endif // __TEST_MESH_H
