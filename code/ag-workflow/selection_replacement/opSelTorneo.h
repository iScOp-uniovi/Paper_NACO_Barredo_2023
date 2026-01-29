#ifndef _OPSELTORNEO_H
#define _OPSELTORNEO_H

#include <iostream>
#include <math.h>
#include <set>
#include <iterator>
#include "tools/random.h"
#include "opSeleccion.h"

using namespace std;

/******************************************************************/
/*                                                                */
/*          especificacion de la clase opSelTorneo<CroT,FitT>          */
/*                                                                */
/******************************************************************/

template <class CroT, class FitT>
class opSelTorneo: public opSeleccion<CroT,FitT>{
 public:
  // Constructor
  opSelTorneo(escalado<CroT,FitT> & esc, const unsigned int & nind = 0, const unsigned int & nsel = 2);
  /* Necesita: un operador de escalado, el tamano
     de la poblacion y el numero de cromosomas entre los que se debe realizar la seleccion
  */

  virtual ~opSelTorneo() { }

  // Operaciones
  virtual void seleccionaIndividuos(poblacion<CroT> & pob);
  /* Necesita: una poblacion
     Modifica: baraja aleatoriamente la poblacion
  */
  virtual void aplica(poblacion<CroT> & pob);
  /* Necesita: una poblacion
     Modifica: crea una seleccion interna de individuos por el
     metodo del torneo en su primer paso
  */
  virtual void aplica2(poblacion<CroT> & pob);
  /* Necesita: una poblacion
     Modifica: crea una seleccion interna de individuos por el
     metodo del torneo en su segundo paso
  */

 protected:
  // Generador de numeros aleatorios
  genRandom & r;

  virtual void aceptacion(poblacion<CroT> & pob);
  /* Necesita: una poblacion
     Modifica: conserva los mejores individuos de entre cada grupo de padres e hijos
     y actualiza el mejor individuo de la poblacion(el peor no es necesario)
  */

 private:
  // Copia de la seleccion
  poblacion<CroT> pobAux;

  // Tama�o del grupo en el que seleccionar
  unsigned int nSel;
};


/******************************************************************/
/*                                                                */
/*          implementacion de la clase opSelTorneo<CroT,FitT>          */
/*                                                                */
/******************************************************************/

template <class CroT, class FitT>
opSelTorneo<CroT,FitT>::opSelTorneo(escalado<CroT,FitT> & esc,
			       const unsigned int & nind, const unsigned int & nsel)
  : opSeleccion<CroT,FitT>(esc), r(*genRandomSingleton::getInstance()), pobAux(nind) , nSel(nsel)
{}


template <class CroT, class FitT>
void opSelTorneo<CroT,FitT>::seleccionaIndividuos(poblacion<CroT> & pob)
{
  unsigned int nind = pob.totalIndividuos();

  // Seleccionar una poblacion entera de individuos
  for(unsigned int ind = 0; ind < nind; ++ind)
    swap(pob[ind], pob[r.rnd(0, nind-1)]);

  // Almacenar la poblacion una vez barajada
  pobAux = pob;
}


template <class CroT, class FitT>
void opSelTorneo<CroT,FitT>::aceptacion(poblacion<CroT> & pob)
{
  set<CroT> individuos;
  typename set<CroT>::iterator itr;
  CroT mejorIndividuo;
  unsigned int indiceMejor = (unsigned int)0;

  for(unsigned int pos1=0, pos2; pos1<pob.totalIndividuos(); pos1+=nSel){
    // Delimitar el rango del grupo de individuos
    (pos1 + nSel > pob.totalIndividuos()) ? pos2 = pob.totalIndividuos()-1
      : pos2 = pos1 + nSel -1;
    // Ordenar los individuos del grupo eliminando repetidos
    for(unsigned int ind=pos1; ind<pos2+1; ++ind){
      individuos.insert(pobAux[ind]);
      individuos.insert(pob[ind]);
    }
    itr = individuos.begin(); // Mejor individuo del grupo

    // Si es el mejor individuo de la poblacion
    if((!mejorIndividuo.evaluado())||(*itr < mejorIndividuo)){
      mejorIndividuo = *itr;
      indiceMejor    = pos1;
    }

    for(unsigned int ind=pos1; ind<pos2+1; ++ind, ++itr){
      // Si faltan cromosomas reescribir la secuencia
      if(itr == individuos.end())
	itr = individuos.begin();

      // Actualizar la poblacion
      pob[ind] = *itr;
    }
    individuos.clear();
  }
  pob.actualizaMejor(indiceMejor);
}


template <class CroT, class FitT>
void opSelTorneo<CroT,FitT>::aplica(poblacion<CroT> & pob)
{
  seleccionaIndividuos(pob);
}


template <class CroT, class FitT>
void opSelTorneo<CroT,FitT>::aplica2(poblacion<CroT> & pob)
{
  aceptacion(pob);
}
 
#endif

