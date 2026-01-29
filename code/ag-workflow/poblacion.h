#ifndef _POBLACION_H
#define _POBLACION_H

#include "chromosome/cromosoma.h"

using namespace std;

/******************************************************************/
/*                                                                */
/*          especificacion de la clase poblacion<CroT>            */
/*                                                                */
/******************************************************************/

template <class CroT>
class poblacion {
 public:
  // Constructores
  poblacion(const unsigned int & nind = 0, const unsigned int & ngenes = 0);
  poblacion(const poblacion & pob);

  // Destructor
  ~poblacion(){};

  // Sobrecarga de operadores
  CroT & operator [](const unsigned int & indice);
  /* Necesita: el indice de un individuo
     Produce:  el individuo que ocupa esa posicion en la poblacion
     Error:    si el indice esta fuera de rango
  */
  const CroT & operator [](const unsigned int & indice) const;
  /* Necesita: el indice de un individuo
     Produce:  el individuo que ocupa esa posicion en la poblacion
     Error:    si el indice esta fuera de rango
  */
  poblacion<CroT> & operator =(const poblacion<CroT> & pob);
  /* Necesita: una poblacion
     Produce:  una copia de la poblacion dada
  */

  // Observadores
  unsigned int totalIndividuos() const;
  /* Produce: el tamano de la poblacion
   */
  unsigned int mejorIndividuo() const;
  /* Produce: el indice del mejor individuo
     Error  : si es desconocido (numInd)
  */
  unsigned int peorIndividuo() const;
  /* Produce: el indice del mejor individuo
     Error  : si es desconocido (numInd)
  */
  
  // Modificadores
  void fijaTamPoblacion(const unsigned int & nind);
  /* Necesita: el nuevo tamano de la poblacion
     Modifica: el tamano de la poblacion
  */
  void actualizaMejor(const unsigned int & indice);
  /* Necesita: el indice de un individuo ya evaluado
     Modifica: actualiza el indice del mejor individuo
     Error   : si el indice esta fuera de rango
  */
  void actualizaPeor(const unsigned int & indice);
  /* Necesita: el indice de un individuo ya evaluado
     Modifica: actualiza el indice del peor individuo 
     Error   : si el indice esta fuera de rango
  */

 protected:
  // Numero de individuos de la poblacion
  unsigned int numInd;
  
  // Individuos de la poblacion
  vector<CroT> ind;
  
  // Indice del mejor individuo
  unsigned int indMejor; 
  
  // Indice del peor individuo
  unsigned int indPeor;
};

template<class CroT>
istream & operator >>(istream & entrada, poblacion<CroT> & pob);

template<class CroT>
ostream & operator <<(ostream & salida, const poblacion<CroT> & pob);


/******************************************************************/
/*                                                                */
/*          implementacion de la clase poblacion<CroT>            */
/*                                                                */
/******************************************************************/

template<class CroT>
poblacion<CroT>::poblacion(const unsigned int & nind, const unsigned int & ngenes)
  :numInd(nind), ind(nind), indMejor(0), indPeor(0)
{
  for(unsigned int x=0; x<numInd; ++x)
    ind[x].fijaNumGenes(ngenes);
}


template<class CroT>
poblacion<CroT>::poblacion(const poblacion & pob)
  : numInd(pob.numInd), ind(pob.ind), indMejor(pob.indMejor), indPeor(pob.indPeor)
{}


template<class CroT>
CroT & poblacion<CroT>::operator [](const unsigned int & indice) 
{
  CroT & individuo = ind[indice];
  
  return individuo;
}


template<class CroT>
const CroT & poblacion<CroT>::operator [](const unsigned int & indice) const
{
  const CroT & individuo = ind[indice];

  return individuo;
}


template <class CroT>
poblacion<CroT> & poblacion<CroT>::operator =(const poblacion<CroT> & pob)
{  
  numInd   = pob.numInd;
  ind      = pob.ind;  
  indMejor = pob.indMejor;  
  indPeor  = pob.indPeor;  

  return *this;
}


template<class CroT>
unsigned int poblacion<CroT>::totalIndividuos() const
{
  return numInd;
}


template<class CroT>
unsigned int poblacion<CroT>::mejorIndividuo() const
{
  return indMejor;
}


template<class CroT>
unsigned int poblacion<CroT>::peorIndividuo() const
{
  return indPeor;
}


template<class CroT>
void  poblacion<CroT>::fijaTamPoblacion(const unsigned int & nind)
{
  numInd = nind;
}


template<class CroT>
void  poblacion<CroT>::actualizaMejor(const unsigned int & indice)
{
  indMejor = indice;
}


template<class CroT>
void  poblacion<CroT>::actualizaPeor(const unsigned int & indice)
{
  indPeor = indice;
}


template<class CroT>
istream & operator >>(istream & entrada, poblacion<CroT> & pob)
{
  for(int x=0; x<pob.totalIndividuos(); ++x)
    entrada >> pob[x];
  
  return entrada;
}


template<class CroT>
ostream & operator <<(ostream & salida, const poblacion<CroT> & pob)
{
  for(unsigned int x=0; x<pob.totalIndividuos(); ++x)
    salida << pob[x] << endl;

  return salida;
}

#endif

