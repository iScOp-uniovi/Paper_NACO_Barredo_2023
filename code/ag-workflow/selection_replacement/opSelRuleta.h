#ifndef _OPSELRULETA_H
#define _OPSELRULETA_H

#include <iostream>
#include <math.h>
#include "tools/random.h"
#include "opSeleccion.h"

using namespace std;
                        
/******************************************************************/
/*                                                                */
/*        especificacion de la clase opSelRuleta<CroT>            */
/*                                                                */
/******************************************************************/

template <class CroT,class FitT>
class opSelRuleta: public opSeleccion<CroT>{
 public:
  // Constructor
  opSelRuleta(genRandom & genRnd, escalado<CroT> & esc, const unsigned int & nind = 0);
  /* Necesita: un generador de numeros aleatorios, un operador de escalado  y el tamanio
     de la poblacion
  */

  // Operaciones
  virtual void seleccionaIndividuos(poblacion<CroT> & pob);
  /* Necesita: una poblacion
     Modifica: crea una seleccion interna de individuos por el
     metodo de la ruleta
  */
  virtual void aplica(poblacion<CroT> & pob);
  /* Necesita: una poblacion
     Modifica: crea una seleccion interna de individuos por el
     metodo de la ruleta
  */

 protected:
  // Generador de numeros aleatorios
  genRandom & r;

 private:
  // Vector de fitness acumulado
  vector<FitT> ac_fit;
  // Poblacion auxiliar
  poblacion<CroT> pobAux;
  
  void normalizaFitness(const poblacion<CroT> & pob);
  /* Necesita: una poblacion
     Modifica: el vector interno de fitness acumulado de la poblacion
  */
};


/******************************************************************/
/*                                                                */
/*          implementacion de la clase opSelRuleta<CroT>          */
/*                                                                */
/******************************************************************/

template <class CroT, class FitT>
opSelRuleta<CroT,FitT>::opSelRuleta(genRandom & genRnd, escalado<CroT> & esc, const unsigned int & nind)
  : opSeleccion<CroT>(esc),r(genRnd), ac_fit(nind), pobAux(nind)
{}


template <class CroT, class FitT>
void opSelRuleta<CroT,FitT>::seleccionaIndividuos(poblacion<CroT> & pob)
{
  double aleat;
  unsigned int pos;
  FitT limSup;
  unsigned int nind(pob.totalIndividuos());

  normalizaFitness(pob); // Calcular los valores de ac_fit
  //que se van a utilizar para seleccionar los individuos.

  // Seleccionar una poblacion entera de individuos
  for(unsigned int ind=0; ind<nind; ++ind){
    pos    = 0;
    limSup = ac_fit[pos];
    aleat  = r.frandom();

    // Buscar el indice de aleat en ac_fit
    while ((aleat > limSup) && (pos < nind-1))
      limSup = ac_fit[++pos];


    // Los individuos seleccionados se almacenan en pobAux
    pobAux[ind] = pob[pos];
  }
  // Recuperar la poblacion
  pob = pobAux;
}


template <class CroT, class FitT>
void opSelRuleta<CroT,FitT>::aplica(poblacion<CroT> & pob)
{
  seleccionaIndividuos(pob);
}


template <class CroT, class FitT>
void opSelRuleta<CroT,FitT>::normalizaFitness(const poblacion<CroT> & pob)
{
  unsigned int nind(pob.totalIndividuos());
  opEsc.actualiza(pob);
  double valor_escalado(opEsc.valorActual());

  // Calcular la suma de fitness
  ac_fit[0] = pob[0].fitness()-valor_escalado;
  for (unsigned int ind=1; ind<nind; ++ind)
    ac_fit[ind] = ac_fit[ind-1] + pob[ind].fitness()-valor_escalado;

  // Normalizar entre 0..1(ac_fit[nind-1]==0 si todos los individuos son iguales)
  for (unsigned int ind=0; ind<nind && ac_fit[nind-1]!=0; ++ind)
    ac_fit[ind] /= ac_fit[nind-1];
}

#endif

