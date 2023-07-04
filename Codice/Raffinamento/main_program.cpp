#include "Mesh_class.hpp"
#include "OggettiGeometrici_class.hpp"
#include <chrono>

using namespace ProjectLibrary;

int main()
{
  /// Tolleranza (SELEZIONABILE DALL'UTENTE)
  Tolleranze::geometricTol = 1.0e-12;

  /// Numero di triangoli da cui far partire il raffinamento (SELEZIONABILE DALL'UTENTE)
  int nRaffina = 1000;

  auto start = chrono::high_resolution_clock::now();
  Mesh M;

  if(!M.Importa())
  {
      cerr<<"Import non riuscito " << endl;
  }
  else
  {
      cout <<"Import riuscito "<<endl;
  }

  if(!M.Raffina(nRaffina))
  {
      cerr<<"Raffinamento non riuscito "<<endl;
  }
  else
  {
      cout<<"Raffinamento riuscito "<<endl;
  }

  if(!M.Stampa())
  {
      cerr<<"Stampa non riuscita " <<endl;
  }
  else
  {
      cout<<"Stampa riuscita"<<endl;
  }

  auto end = chrono::high_resolution_clock::now();

  chrono::duration<double, milli > duration = end - start;
  double executionTime = duration.count();

  /// Stampa il tempo di esecuzione
  cout <<"nTriangoliSelezionati: " << nRaffina << "; Tempo di esecuzione: " << executionTime << " millisecondi." << endl;

  return 0;
}

