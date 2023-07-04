# Progetto_PCS_2023
Utilizzo del programma di raffinamento
Per utilizzare il programma `e necessario creare 2 cartelle nella cartella di debug: una cartella ”MeshInput” e una cartella ”MeshOutput”.
Nella cartella ”MeshInput” `e necessaria la presenza di 3 file:
• Il file Cell0Ds.csv che faccia riferimento alle informazioni sui punti.
• Il file Cell1Ds.csv che faccia riferimento alle informazioni sui lati.
• Il file Cell2Ds.csv che faccia riferimento alle informazioni sui triangoli.
Questi file devono seguire la seguente struttura:
• Cell0Ds.csv
Id Marker X Y
Dove Id e Marker sono due numeri interi, X ed Y numeri reali.
• Cell1s.csv
Id Marker Origin End
In questo file si hanno 4 numeri interi su ogni riga, in particolare Origin ed End fanno riferimento agli Id dei punti del file Cell0Ds.csv
• Cell2s.csv
Id Vertices Edges
In questo file si hanno 7 numeri interi su ogni riga, in particolare Vertices ed Edges fanno riferimento agli Id dei punti e dei lati dei file Cell0Ds.csv e Cell1Ds.csv
⋆ In caso di assenza della cartella di input verr`a visualizzato l’errore: ”Errore di lettura del file dei punti” e ”Import non riuscito”
⋆ In caso di assenza della cartella di output verr`a visualizzato l’errore: ”Errore di scrittura del file dei punti” e ”Stampa non riuscita”.
In presenza di un corretto input `e possibile utilizzare il programma settando dal main una tolleranza per valutare quanto precisa debba essere la compara- zione di lati ed aree e un valore intero ”nTriangoli” per decidere quanto raffinata debba essere la raffinazione.
A programma eseguito correttamente verranno creati 3 file .csv nella cartella ”MeshOutput” con la stessa struttura di quelli in input che faranno riferimento alla mesh raffinata col metodo di bisezione dei triangoli.
