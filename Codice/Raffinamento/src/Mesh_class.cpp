#include "Mesh_class.hpp"
#include <algorithm>

namespace ProjectLibrary
{

///Definizione parte statica di Mesh*********************

vector<Punto> Mesh::Punti;
vector<Lato> Mesh::Lati;
vector<Triangolo> Mesh::Triangoli;
list<idTriangoloArea> Mesh::TriangoliOrdinati;

///definizione METODI DI MESH********************************************************************

bool Mesh::Importa(){

    GestioneDati G;

    if(!G.ImportPunti()){

        cerr << "errore lettura file punti" << endl;
        return false;
    }
    if(!G.ImportLati()){

        cerr << "errore lettura file lati" << endl;
        return false;
    }
    if(!G.ImportTriangoli()){

        cerr << "errore lettura file triangoli" << endl;
        return false;
    }

    if(!TestMesh()){

        cerr << "Mesh Sbagliata in ingresso" << endl;
        return false;
    }

    return true;
}

bool Mesh::Stampa()
{
    GestioneDati G;

    if(!TestMesh()){

        cerr << "Mesh Sbagliata in uscita" << endl;
        return false;
    }

    if(!G.StampaPunti()){

        cerr << "errore scrittura file punti" << endl;
        return false;
    }
    if(!G.StampaLati()){

        cerr << "errore scrittura file lati" << endl;
        return false;
    }
    if(!G.StampaTriangoli()){

        cerr << "errore scrittura file triangoli" << endl;
        return false;
    }

    return true;
}

bool Mesh::TestMesh()
{
 for(unsigned int i = 0; i < Triangoli.size(); i++)
  {
      if(Triangoli[i].area == 0)//tolleranza
      {
        cerr << "c: " << i << "Area nulla" << endl;
        return false;
      }
 }
      return true;
}

/*bool Mesh::Raffina(const int& theta)
{
    GestioneAlgoritmo G;
    int idTriangolo = -1;

    for(int e = 0; e < theta; e++)
    {
        for (const auto& T : TriangoliOrdinati)
        {
            if(Triangoli[T.id].stato == true)
            {              
              idTriangolo = T.id;
              break;
            }
        }
        G.Raffina1Triangolo(idTriangolo);
     }

     return true;
}*/

///versione di raffina che elimina i triangoli selezionati
bool Mesh::Raffina(const int& theta)
{
    GestioneAlgoritmo G;
    int idTriangolo = -1;

    for(int e = 0; e < theta; e++)
    {

        for(auto it = TriangoliOrdinati.begin(); it != TriangoliOrdinati.end(); ++it){

            if(Triangoli[it->id].stato == true)
            {
              idTriangolo = it->id;
              TriangoliOrdinati.erase(it);
              break;
            }
        }
        G.Raffina1Triangolo(idTriangolo);
     }

//    cout << "Ntriangoli " << Triangoli.size() << endl;

     return true;
}

///versione di raffina che elimina i triangoli selezionati e usa il sort
/*bool Mesh::Raffina(const int& theta)
{
    GestioneAlgoritmo G;
    int idTriangolo = -1;

    for(int e = 0; e < theta; e++)
    {

        for(auto it = TriangoliOrdinati.begin(); it != TriangoliOrdinati.end(); ++it){

            TriangoliOrdinati.sort();
            if(Triangoli[it->id].stato == true)
            {
              idTriangolo = it->id;
              TriangoliOrdinati.erase(it);
              break;
            }
        }
        G.Raffina1Triangolo(idTriangolo);
     }

    //cout << "Ntriangoli " << Triangoli.size() << endl;

     return true;
}*/
}
