#ifndef _OPGENESIS_H
#define _OPGENESIS_H

#define _strdup strdup

#include <fstream>
#include <string.h>
#include "poblacion.h"
#include "chromosome/cromosoma.h"
#include "operador.h"
#include "tools/excepcion.h"

using namespace std;

/******************************************************************/
/*                                                                */
/*     especificacion de la clase opGenesis<PobT,ProT,CroT>       */
/*                                                                */
/******************************************************************/

template <class PobT, class ProT, class CroT>
class opGenesis:public operador<PobT> {
 public:
  // Constructor
  opGenesis(const ProT & prob, char*  nombre = 0);
  /* Necesita: un problema a resolver y el nombre de un archivo
     conteniendo una poblacion inicial
  */

  // Destructor
  virtual ~opGenesis();

  // Operaciones
  void iniciaPoblacion(PobT & pob);
  /* Necesita: una poblacion de individuos nulos
     Modifica: la poblacion creando los individuos, primero 
     con los individuos del archivo (si existe), y a continuacion
     con individuos generados por esta clase para el problema
  */
  virtual void aplica(PobT & pob);
  /* Necesita: una poblacion
     Modifica: inicia la poblacion
  */
  
 protected:
  // Problema a resolver
  const ProT & pr;
  
  // Nombre del archivo con la poblacion inicial
  char* nfich;
  
  virtual void generaIndividuo(CroT & cr) = 0;
  /* Necesita: un cromosoma en blanco
     Modifica: el cromosoma conteniendo una posible solucion al problema
  */
};


/******************************************************************/
/*                                                                */
/*      implementacion de la clase opGenesis<PobT,ProT,CroT>      */
/*                                                                */
/******************************************************************/

template <class PobT, class ProT, class CroT>
opGenesis<PobT, ProT, CroT>::opGenesis(const ProT & prob, char* nombre)
    :pr(prob), nfich(nombre?_strdup(nombre):nombre)
{}


template <class PobT, class ProT, class CroT>
opGenesis<PobT, ProT, CroT>::~opGenesis()
{
  delete nfich;
}


template <class PobT, class ProT, class CroT>
void opGenesis<PobT, ProT, CroT>::iniciaPoblacion(PobT & pob)
{
  unsigned int  ind(0);
  // Si hay archivo de poblacion inicial, comenzamos por ellos
  if (nfich){
    ifstream f(nfich);
    if(!f.good())
      throw(fichExc("void opGenesis<PobT, ProT, CroT>::iniciaPoblacion(PobT & pob)", nfich));

    char aux[500];    
    unsigned int nInd;
   
    // Comentario inicial
    f.getline(aux,500,'\n');

    // Numero de individuos a leer
    f >> nInd;   
    nInd = min(nInd, pob.totalIndividuos());

    // Leer los individuos
    while(ind < nInd){
      f >> pob[ind];
      pob[ind++].invalida();
    }
     
    f.close();
  }
  // Gnerar resto de individuos (o su totalidad sino no habia pobini)
  while (ind < pob.totalIndividuos())
    generaIndividuo(pob[ind++]); 
}


template <class PobT, class ProT, class CroT>
void opGenesis<PobT, ProT, CroT>::aplica(PobT & pob)
{
  iniciaPoblacion(pob);
}

#endif
