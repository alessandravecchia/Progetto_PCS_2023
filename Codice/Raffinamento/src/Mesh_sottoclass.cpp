#include "Mesh_class.hpp"

namespace ProjectLibrary
{

///definizione METODI DI GESTIONE DATI********************************************************************

bool Mesh::GestioneDati::ImportPunti()
{
    GestioneAlgoritmo G;
    ifstream file;
    file.open("./MeshInput/Cell0Ds.csv");

    if(file.fail())
      return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
      listLines.push_back(line);
    file.close();

    listLines.pop_front();

    int numPunti = listLines.size();

    if (numPunti == 0)
    {
      cerr << "Non ci sono Punti" << endl;
      return false;
    }

    for (const string& line : listLines) //riempio il vector dei punti
    {
      istringstream converter(line);
      int id;
      int marker;
      array<double,2> coordinate;
      converter >> id >> marker >> coordinate[0] >> coordinate[1];
      G.CreaPunto(coordinate);
    }
    return true;
}

bool Mesh::GestioneDati::ImportLati()
{
    GestioneAlgoritmo G;
    ifstream file;
    file.open("./MeshInput/Cell1Ds.csv");

    if(file.fail())
      return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
      listLines.push_back(line);

    file.close();

    listLines.pop_front(); //elimino la prima riga

    int numLati = listLines.size();
    if (numLati == 0) //controllo che nella lista ci siano lati
    {
      cerr << "Non ci sono Lati" << endl;
      return false;
    }

    for (const string& line : listLines) //riempio il vector dei lati
    {
      istringstream converter(line);
      int id;
      int marker;
      array<int,2> idPuntiLato;
      converter >> id >> marker >> idPuntiLato[0] >> idPuntiLato[1];
      G.CreaLato(idPuntiLato);
    }

    return true;
}

bool Mesh::GestioneDati::ImportTriangoli()
{
    GestioneAlgoritmo G;
    ifstream file;
    file.open("./MeshInput/Cell2Ds.csv");

    if(file.fail())
      return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
      listLines.push_back(line);

    file.close();

    listLines.pop_front();

    int numTriangoli = listLines.size();

    if (numTriangoli == 0)
    {
      cerr << "Non ci sono Triangoli" << endl;
      return false;
    }

    for (const string& line : listLines) //riempio il vector dei triangoli
    {
      istringstream converter(line);
      int id;
      array<int,3> idPuntiTriangolo;
      array<int,3> idLatiTriangolo;
      converter >>  id  >> idPuntiTriangolo[0] >> idPuntiTriangolo[1]>> idPuntiTriangolo[2] >> idLatiTriangolo[0]>> idLatiTriangolo[1] >> idLatiTriangolo[2];
      G.CreaTriangolo(idPuntiTriangolo, idLatiTriangolo);
      G.AssegnaAdiacenza(Triangoli.size() - 1); //assegna ad ogni lato del triangolo l'id del triangolo
    }

    return true;
}

bool Mesh::GestioneDati::StampaPunti()
{
    ofstream file;
    file.open("./MeshOutput/Cell0Ds.csv");

    if(file.fail())
      return false;

    file << "Id "<< "Marker " << "X "<< "Y " << endl;

    for(unsigned int i = 0; i < Punti.size(); i++)
        file << i << " "  << 0 << " " << scientific << Punti[i].coordinate[0] << " "
             << scientific << Punti[i].coordinate[1]<<endl;

    file.close();
    return true;
}

bool Mesh::GestioneDati::StampaLati()
{
    ofstream file;
    file.open("./MeshOutput/Cell1Ds.csv");

    if(file.fail())
      return false;

    file << "Id "<< "Marker "<<"Origin "<<"End"<< endl;

    for(unsigned int i = 0; i < Lati.size(); i++)
    {
        if(Lati[i].stato == true)
         file << i << " " << 0 << " " << Lati[i].idPuntiLato[0] << " " << Lati[i].idPuntiLato[1]<<endl;
    }

    file.close();
    return true;
}

bool Mesh::GestioneDati::StampaTriangoli()
{
    ofstream file;
    file.open("./MeshOutput/Cell2Ds.csv");

    if(file.fail())
      return false;

    file << "Id "<<"Vertices "<<"Edges"<< endl;

    for(unsigned int i = 0; i < Triangoli.size(); i++)
    {
        if(Triangoli[i].stato == true)
        {
        file << i << " ";
        file << Triangoli[i].idPuntiTriangolo[0] << " " << Triangoli[i].idPuntiTriangolo[1] << " " << Triangoli[i].idPuntiTriangolo[2] << " ";
        file << Triangoli[i].idLatiTriangolo[0] << " " << Triangoli[i].idLatiTriangolo[1] << " " << Triangoli[i].idLatiTriangolo[2] << endl;
        }
    }

    file.close();
    return true;
}

///definizione METODI DI GESTIONE ALGORITMO********************************************************************

int Mesh::GestioneAlgoritmo::CreaPunto(const array<double, 2>& coordinate)
{
    Punti.push_back(Punto(coordinate)); //aggiungo al vector un oggetto Punto
    int id = Punti.size() - 1;
    return id;
}

int Mesh::GestioneAlgoritmo::CreaLato(const array<int,2>& idPunti)
{
    Lato L1 = Lato(idPunti);
    Lati.push_back(L1); //aggiungo al vector un oggetto Lato
    int id = Lati.size() - 1;
    return id;
}

int Mesh::GestioneAlgoritmo::CreaTriangolo(const array<int,3>& idPunti, const array<int,3>& idLati)
{
    GestioneAlgoritmo G;
    Triangolo T =  Triangolo(idPunti, idLati);
    Triangoli.push_back(T); //aggiungo al vector un oggetto Triangolo
    int id = Triangoli.size() - 1;

    ///crea la struct associata al triangolo e la inserisce nella giusta posizione
    idTriangoloArea T1 = idTriangoloArea(id, T.area);
    G.InserisciTriangolo(T1);
    return id;
}

array<int,2> Mesh::GestioneAlgoritmo::Crea2Lati(const int& idPunto, const int& idLatoVecchio)
{
    //quando memorizzi gli id dei punti metti in seconda posizione quello nuovo
    array<int,2> PuntiOldL = Lati[idLatoVecchio].idPuntiLato;
    array<int,2> PuntiNewL1 = {PuntiOldL[0], idPunto};
    array<int,2> PuntiNewL2 = {PuntiOldL[1], idPunto};
    int idNewL1 = CreaLato(PuntiNewL1);
    int idNewL2 = CreaLato(PuntiNewL2);
    array<int,2> idLatiNew = {idNewL1, idNewL2};
    return idLatiNew;
}

array<int,2> Mesh::GestioneAlgoritmo::Crea2Triangoli(const int& idPuntoNuovo,const int& idLatoVecchio, const array<int,3>& idLati, const int& idTriangoloVecchio)
{   
   ///assegnazione vertici
   //quando memorizzi gli id dei lati metti nelle prime due posizioni i triangoli figli e nell'ultima id lato nuovo
   int idPuntoOpposto = Triangoli[idTriangoloVecchio].getVerticeOpposto(idLatoVecchio);   
   array<int,3> idPuntiNewT1 = {(Lati[idLati[0]].idPuntiLato)[0],idPuntoNuovo,idPuntoOpposto}; //assegno a idPunti del primo triangolo da creare gli id dei punti del lato nuovo
   array<int,3> idPuntiNewT2 = {(Lati[idLati[1]].idPuntiLato)[0],idPuntoNuovo,idPuntoOpposto}; //(Lati[idLati[0]].idPuntiLato)[0] è zero fisso perchè nel crea2Lati metto al secondo posto il punto nuovo

   ///creo un array di lati candidati a essere i latocorretto1 e latocorretto2
   array<int,3> idLatiCandidatiNewT = Triangoli[idTriangoloVecchio].idLatiTriangolo; //lati candidati a essere usati per i triangoli nuovi dei lati del triangolo vecchio
   for(int i=0; i<3;i++)
    if(idLatiCandidatiNewT[i] == idLatoVecchio) {idLatiCandidatiNewT[i] = -1;} //metto a -1 l'id del triangolo vecchio lasciando solo gli id dei lati effettivamente candidati

   ///trova lato corretto1
   int latoCorretto1 = -1;
   for(int i = 0; i < 3; i++)
   {
    if(idLatiCandidatiNewT[i] != -1)
    {
      array<int,2> idPuntidiLatoCandidato = Lati[idLatiCandidatiNewT[i]].idPuntiLato; //prendo i punti del primo lato candidato

      //controllo che i punti del lato candidato selezionato siano uguali ai punti che
      if ((idPuntidiLatoCandidato[0] == idPuntiNewT1[0] && idPuntidiLatoCandidato[1] == idPuntoOpposto)||
          (idPuntidiLatoCandidato[1] == idPuntiNewT1[0] && idPuntidiLatoCandidato[0] == idPuntoOpposto))
      {
        latoCorretto1 = idLatiCandidatiNewT[i];
        idLatiCandidatiNewT[i] = -1;
      }
    }
   }

   ///trova lato corretto2
   int latoCorretto2 = -1;
   for(int i=0; i<3;i++)
   {
    if(idLatiCandidatiNewT[i] != -1)
    {
        latoCorretto2 = idLatiCandidatiNewT[i];
        idLatiCandidatiNewT[i] = -1;
    }
   }

   array<int,3> idLatiNewT1 = {idLati[0],latoCorretto1,idLati[2]};
   array<int,3> idLatiNewT2 = {idLati[1],latoCorretto2,idLati[2]};

   int idNewT1 = CreaTriangolo(idPuntiNewT1,idLatiNewT1);
   int idNewT2 = CreaTriangolo(idPuntiNewT2,idLatiNewT2);
   array<int,2> idTriangoliNew = {idNewT1, idNewT2};
   AssegnaAdiacenza(idNewT1,idTriangoloVecchio);
   AssegnaAdiacenza(idNewT2,idTriangoloVecchio);

   return idTriangoliNew;
}

void Mesh::GestioneAlgoritmo::AssegnaAdiacenza(const int& idTriangoloNuovo, const int& idTriangoloVecchio)
{
    array<int, 3> TLati = Triangoli[idTriangoloNuovo].idLatiTriangolo;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (Lati[TLati[i]].triangoliAdiacenti[j] == idTriangoloVecchio || Lati[TLati[i]].triangoliAdiacenti[j] == -1)
            {
                Lati[TLati[i]].riempiTriangoliAdiacenti(idTriangoloNuovo, j);
                break;
            }
        }
    }

    return;
}


int Mesh::GestioneAlgoritmo::individuaTriangoloAdiacente(const int &idTriangolo, const int &idLato)
{

    int idTriangoloAdiacente = -1;

    if(Lati[idLato].triangoliAdiacenti[1] != -1)
    {
        if(((Lati[idLato].triangoliAdiacenti)[0] != idTriangolo && Lati[idLato].triangoliAdiacenti[0] != -1) && Triangoli[idTriangolo].stato == true)
        {
          idTriangoloAdiacente = (Lati[idLato].triangoliAdiacenti)[0];
        }
        else if(((Lati[idLato].triangoliAdiacenti)[1] != idTriangolo && Lati[idLato].triangoliAdiacenti[0] != -1) && Triangoli[idTriangolo].stato == true)
        {
           idTriangoloAdiacente = (Lati[idLato].triangoliAdiacenti)[1];
        }
        else
        {
           cerr<<"Triangolo adiacente non trovato"<<endl;
        }
    }

    return idTriangoloAdiacente;

}

bool Mesh::GestioneAlgoritmo::Raffina1Triangolo(const int &idTriangolo)
{
    array<int,2> idNuovitriangoli;
    triangoloBase = idTriangolo;
    latoLungoTB = Triangoli[triangoloBase].getLatoLungo();

    array<double,2> coord = Lati[latoLungoTB].CalcolaPuntoMedio();
    puntoMedioTB = CreaPunto(coord);

    puntoOppostoTB = Triangoli[triangoloBase].getVerticeOpposto(latoLungoTB);
    array<int,2> PuntiPerLatoNuovo = {puntoMedioTB, puntoOppostoTB};
    latoNuovoTB = CreaLato(PuntiPerLatoNuovo);

    array<int,2> idNuoviLati = Crea2Lati(puntoMedioTB, latoLungoTB);
    latoFiglio1TB = idNuoviLati[0];
    latoFiglio2TB = idNuoviLati[1];
    array<int,3> LatiCreazioneTriangoli = {latoFiglio1TB, latoFiglio2TB, latoNuovoTB};
    idNuovitriangoli = Crea2Triangoli(puntoMedioTB, latoLungoTB, LatiCreazioneTriangoli, triangoloBase);

    bool continueLoop = true;
    while(continueLoop)
    {
        if(puntoSospeso != -1)
        {
            array<int,2> PuntiPerLatoNuovo = {puntoMedioTB2, puntoSospeso};
            latoNuovoTF = CreaLato(PuntiPerLatoNuovo); //qua lato nuovo fittizio

            array<int,3> LatiCreazioneTriangoli = {latoFiglio1TB, latoFiglio2TB, latoNuovoTF};
            idNuovitriangoli = Crea2Triangoli(puntoMedioTB, latoLungoTB, LatiCreazioneTriangoli, triangoloFittizio);

            Triangoli[triangoloFittizio].SpegniTriangolo(triangoloFittizio);

            Triangoli[triangoloBase].SpegniTriangolo(triangoloBase);
            triangoloBase = triangoloBase2;
            triangoloBase2 = -1;

            Lati[latoLungoTB].SpegniLato();
            latoLungoTB = latoLungoTB2;
            latoLungoTB2 = -1;

            latoFiglio1TB = latoFiglio1TB2;
            latoFiglio2TB = latoFiglio2TB2;

            latoFiglio1TB2 = -1;
            latoFiglio2TB2 = -1;

            puntoMedioTB = puntoMedioTB2;
            puntoMedioTB2 = -1;

            puntoSospeso = -1;
        }

        ///ricerca del triangolo adiacente
        if(Lati[latoLungoTB].triangoliAdiacenti[1] != -1)
        {
           int triangoloAdiacente = individuaTriangoloAdiacente(triangoloBase, latoLungoTB);
           if(Triangoli[triangoloAdiacente].stato == true)
           {
               triangoloBase2 = triangoloAdiacente;

           }else{

              cerr << "TriangoloAdiacente non trovato " << "triangolo da cui e partita la ricerca " << triangoloBase << " lato da cui e partita la ricerca " << latoLungoTB << endl;
              return false;
           }


        }else{

            Triangoli[triangoloBase].SpegniTriangolo(triangoloBase);
            Lati[latoLungoTB].SpegniLato();
            return true;
        }

        latoLungoTB2 = Triangoli[triangoloBase2].getLatoLungo();

        if (latoLungoTB == latoLungoTB2)
        {
           puntoOppostoTB2 = Triangoli[triangoloBase2].getVerticeOpposto(latoLungoTB);
           array<int,2> PuntiPerLatoNuovo = {puntoMedioTB, puntoOppostoTB2};
           latoNuovoTB2 = CreaLato(PuntiPerLatoNuovo);


           array<int,3> LatiCreazioneTriangoli = {latoFiglio1TB, latoFiglio2TB, latoNuovoTB2};
           idNuovitriangoli = Crea2Triangoli(puntoMedioTB, latoLungoTB, LatiCreazioneTriangoli, triangoloBase2);

           Triangoli[triangoloBase].SpegniTriangolo(triangoloBase);
           Lati[latoLungoTB].SpegniLato();
           Triangoli[triangoloBase2].SpegniTriangolo(triangoloBase2);
           return true;

        }else{

            puntoSospeso = puntoMedioTB;
            array<double,2> coord = Lati[latoLungoTB2].CalcolaPuntoMedio();
            puntoMedioTB2 = CreaPunto(coord);

            puntoOppostoTB2 = Triangoli[triangoloBase2].getVerticeOpposto(latoLungoTB2);
            array<int,2> PuntiPerLatoNuovo = {puntoMedioTB2, puntoOppostoTB2};
            latoNuovoTB2 = CreaLato(PuntiPerLatoNuovo);

            array<int,2> idNuoviLati =   Crea2Lati(puntoMedioTB2, latoLungoTB2);
            latoFiglio1TB2 = idNuoviLati[0];
            latoFiglio2TB2 = idNuoviLati[1];

            array<int,3> LatiCreazioneTriangolo = {latoFiglio1TB2, latoFiglio2TB2, latoNuovoTB2};
            idNuovitriangoli = Crea2Triangoli(puntoMedioTB2, latoLungoTB2, LatiCreazioneTriangolo, triangoloBase2);


            ///seleziona e salva triangolo fittizio
            for(int i=0;i<2;i++)
            {
              for(int j=0;j<3;j++)
              {                  
                  if((Triangoli[idNuovitriangoli[i]].idLatiTriangolo)[j] == latoLungoTB)
                    triangoloFittizio = idNuovitriangoli[i];
              }
            }
        }
    }

    return false;
}

///inserimento insertion sort
/*void Mesh::GestioneAlgoritmo::InserisciTriangolo(const idTriangoloArea &T)
{
    auto it = TriangoliOrdinati.begin();
        while (it != TriangoliOrdinati.end() && *it > T)
            ++it;

        TriangoliOrdinati.insert(it, T);
    return;
}*/

///inserimento binary insertion sort
/*void Mesh::GestioneAlgoritmo::InserisciTriangolo(const idTriangoloArea &T)
{
    auto inizio = TriangoliOrdinati.begin();
        auto fine = TriangoliOrdinati.end();

        while (inizio != fine)
        {
            auto dist = distance(inizio, fine);
            auto half = next(inizio, dist / 2);

            if (T < *half)
            {
                inizio = next(half);

            }
            else if (*half < T)
            {
                fine = half;
            }
            else if (*half == T)
            {
                TriangoliOrdinati.insert(half, T);
                return;
            }
        }

        TriangoliOrdinati.insert(inizio, T);
        return;
}*/

///inserimento spezzo a metà e vado lineare dal centro alle estremità
/*void Mesh::GestioneAlgoritmo::InserisciTriangolo(const idTriangoloArea &T)
{
    auto inizio = TriangoliOrdinati.begin();
    auto fine = TriangoliOrdinati.end();
    auto dist = distance(inizio, fine);
    auto half = next(inizio, dist / 2);
    if(T < *half){

    auto it = TriangoliOrdinati.begin();
        while (it != TriangoliOrdinati.end() && *it > T)
            ++it;

        TriangoliOrdinati.insert(it, T);
        return;

    }else if(T > *half){

        auto it = TriangoliOrdinati.end();
            while (it != TriangoliOrdinati.begin() && *it < T)
                --it;

            TriangoliOrdinati.insert(next(it), T);
            return;
    }else if(T == *half){
        TriangoliOrdinati.insert(half, T);
        return;
    }

    return;
}*/

///inserimento spezzo a metà e vado lineare dalle estremità al centro
/*void Mesh::GestioneAlgoritmo::InserisciTriangolo(const idTriangoloArea &T)
{
    auto inizio = TriangoliOrdinati.begin();
    auto fine = TriangoliOrdinati.end();
    auto dist = distance(inizio, fine);
    auto half = next(inizio, dist / 2);
    if(T < *half){

    auto it = TriangoliOrdinati.end();
        while (it != half && *it < T)
            --it;

        TriangoliOrdinati.insert(next(it), T);
        return;

    }else if(T > *half){

        auto it = TriangoliOrdinati.begin();
            while (it != half && *it > T)
                ++it;

            TriangoliOrdinati.insert(it, T);
            return;
    }else if(T == *half){
        TriangoliOrdinati.insert(half, T);
        return;
    }

    return;
}*/

/// Reverse Insertion sort
void Mesh::GestioneAlgoritmo::InserisciTriangolo(const idTriangoloArea &T)
{
    auto it = TriangoliOrdinati.end();
        while (it != TriangoliOrdinati.begin() && *it < T)
            --it;

        TriangoliOrdinati.insert(next(it), T);
    return;
}

/// Inserimento per usare il sort standard
/*void Mesh::GestioneAlgoritmo::InserisciTriangolo(const idTriangoloArea &T)
{
    TriangoliOrdinati.push_back(T);
    return;
}*/


}


