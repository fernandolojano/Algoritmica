/*ES:   Asignatura: Algoritmica
        Trabajo: Practica 3 - Greedy
        Descripcion: TSP con método de Cercanía */ 

// LIBRERIAS
//      Entrada/Salida
#include <iostream>
//      Vectores
#include <vector>
//      Abrir archivos
#include <fstream>
//      Procesado de Cadenas
#include <string>
#include <sstream>
//      Hacer operaciones matematicas
#include <cmath>
//      Obtener el MAX_FLT
#include <cfloat>
#include <climits>

using namespace std;

// FUNCIONES
//      Funcion auxiliar para calcular distancia euclidea entre dos puntos.
int calcularDistancia(float x2, float x1, float y2, float y1)
{
    return (int)(round ( sqrt( pow(x2 - x1, 2) + pow(y2 - y1, 2) ) ) );
}

//      Funcion TSP Greedy por Cercania
void tspCercania(float **matrizIN, float **&matrizOUT, int dim)
{
    int nodoIni, nodoFin, nodoVec, caminoMin = 0, distActual, distanciaMin;

    nodoIni = 0;
    nodoFin = nodoIni;

    matrizOUT[0][0] = matrizIN[nodoIni][0];
    matrizOUT[0][1] = matrizIN[nodoIni][1];
    matrizOUT[0][2] = matrizIN[nodoIni][2];

    matrizIN[nodoIni][0] = -1;

    for (int i = 0; i < dim-1; i++)
    {  
        distanciaMin = INT_MAX;
        for (int j = 0; j < dim; j++)
        {
            if(matrizIN[j][0] >= 0)
            {
                distActual = calcularDistancia(matrizIN[j][1], matrizIN[nodoIni][1], matrizIN[j][2], matrizIN[nodoIni][2]);

                if (distActual <= distanciaMin)
                {
                    distanciaMin = distActual;
                    nodoVec = j;
                }
            }

        }

        caminoMin += distanciaMin;
        
        matrizOUT[i+1][0] = matrizIN[nodoVec][0];
        matrizOUT[i+1][1] = matrizIN[nodoVec][1];
        matrizOUT[i+1][2] = matrizIN[nodoVec][2];

        matrizIN[nodoVec][0] = -1;
        nodoIni = nodoVec;
    }
        matrizOUT[dim][0] = matrizOUT[0][0];
        matrizOUT[dim][1] = matrizOUT[0][1];
        matrizOUT[dim][2] = matrizOUT[0][2];

        caminoMin += calcularDistancia(matrizIN[nodoFin][1], matrizIN[nodoIni][1], matrizIN[nodoFin][2], matrizIN[nodoIni][2]);

        cout <<"CAMINO: "<< caminoMin << endl
             <<"INICIO_CAMINO_CERCANIA"<< endl;

        for (int i = 0; i < dim+1; i++)
        {
            cout <<matrizOUT[i][0]<<"\t" <<matrizOUT[i][1]<<"\t"<<matrizOUT[i][2]<<endl;
        }
}

//      Funcion Main
int main(int argc, char * argv[])
{

    if (argc != 2)
    {
      cerr << "Formato: ./" << argv[0] << " <rutaArchivo.tsp>" << endl;
      return -1;
    }

    float **matriz,**matrizOUT;
    int dim;
    string linea = "";
    istringstream aux2;
    ifstream archivo (argv[1]);

    if (archivo.is_open())
    {
        int aux;
        while (linea.compare("NODE_COORD_SECTION") != 0)
        {
            getline(archivo,linea);
            aux = linea.find("DIMENSION");
            if(aux != -1)
            {
                aux = linea.find(":");
                aux2.str(linea.substr(aux+1,-1));
                aux2 >> dim;
            }
        }

        matriz = new float*[dim];
        matrizOUT = new float*[dim+1];

        float a,b,c;

        for(int i=0; i<dim; i++)
        {
            archivo >> a >> b >> c;
            matriz[i] = new float[3];
            matriz[i][0] = a;
            matriz[i][1] = b;
            matriz[i][2] = c;

            matrizOUT[i] = new float[3];
            matrizOUT[i][0] = 0;
            matrizOUT[i][1] = 0;
            matrizOUT[i][2] = 0;
            
        }
        matrizOUT[dim] = new float[3];
        archivo.close();
    }

    else cout << "No se puede abrir el archivo."; 


  /*    for(int i=0; i<dim; i++)
        {
            cout << matriz[i][0] << " "<<matriz[i][1]<<" "<<matriz[i][2]<<endl;
        }
*/

   tspCercania(matriz,matrizOUT,dim);

// Eliminar la matriz.
 for (int i = 0; i < dim; i++)
 {
    delete [] matriz[i];
    delete [] matrizOUT[i];
 }

  delete [] matriz;
  delete [] matrizOUT;

  return 0;
}