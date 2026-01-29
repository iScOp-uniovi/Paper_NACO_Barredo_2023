#ifndef _OPMUTACION_H
#define _OPMUTACION_H

#include "tools/random.h"
#include "chromosome/cromosoma.h"
#include "poblacion.h"
#include "operador.h"

using namespace std;

/******************************************************************/
/*                                                                */
/*        especificacion de la clase opMutacion<PobT,CroT>        */
/*                                                                */
/******************************************************************/

template <class PobT, class CroT>
class opMutacion:public operador<PobT> {
 public:
  // Constructor
  opMutacion(const double & prMut = 0.0);
  /* Necesita: una probabilidad de mutacion
  */

  virtual ~opMutacion(){};
  // Operaciones
  void mutaIndividuos(PobT & pob);
  /* Necesita: una poblacion
     Modifica: muta cada uno de sus individuos de acuerdo
     con la probabilidad de mutacion
  */
  virtual void aplica(PobT & pob);
  /* Necesita: una poblacion
     Modifica: muta la poblacion
  */
 
 protected:
  // Generador de numeros aleatorios
  genRandom & r;

  // Probabilidad de mutacion
  double pm;
  
  virtual void mutaIndividuo(CroT & cr) = 0;  
  /* Necesita: un cromosoma
     Modifica: el cromosoma es mutado
  */
};


/******************************************************************/
/*                                                                */
/*          implementacion de la clase opMutacion<PobT,CroT>      */
/*                                                                */
/******************************************************************/

template <class PobT, class CroT>
opMutacion<PobT,CroT>::opMutacion(const double & prMut)
  :r(*genRandomSingleton::getInstance()), pm(prMut)
{}


template <class PobT, class CroT>
void opMutacion<PobT,CroT>::mutaIndividuos(PobT & pob)
{
  for(unsigned int ind=0; ind<pob.totalIndividuos(); ++ind)
    if(r.frandom() <= pm){
      pob[ind].invalida(); // Invalidar el cromosoma, ya que sera modificado
      mutaIndividuo(pob[ind]);
    }
}


template <class PobT, class CroT>
void opMutacion<PobT,CroT>::aplica(PobT & pob)
{
  mutaIndividuos(pob);
}

#endif
