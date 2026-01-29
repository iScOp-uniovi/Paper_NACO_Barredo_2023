#ifndef _OPCRUCE_H
#define _OPCRUCE_H

#include "tools/random.h"
#include "chromosome/cromosoma.h"
#include "poblacion.h"
#include "operador.h"

using namespace std;

/******************************************************************/
/*                                                                */
/*          especificacion de la clase opCruce<PobT,CroT>         */
/*                                                                */
/******************************************************************/

template <class PobT, class CroT>
class opCruce: public operador<PobT> {
 public:
  // Constructor
  opCruce(const double & prCru = 0.0);
  /* Necesita: la probabilidad de cruce a aplicar
  */
  
  // Destructor
  virtual ~opCruce(){};
  
  // Observadores
  unsigned int totalEvaluados() const;
  /* Produce: el numero de individuos evaluados con el operador de cruce
   */
  
  // Operaciones
  virtual void cruzaIndividuos(PobT & pob);
  /* Necesita: una poblacion (una vez seleccionados sus individuos)
     Modifica: cruza los individuos de acuerdo con la probabilidad 
     de cruce, tomando para ello pares adyacentes: 
     pob[0] y pob[1], pob[2] y pob[3]...
  */
  virtual void aplica(PobT & pob);
  /* Necesita: una poblacion
     Modifica: cruza los individuos de acuerdo con la probabilidad 
     de cruce
  */
  
 protected:
  // Generador de numeros aleatorios
  genRandom & r;
  
  // Probabilidad de cruce
  double pc;
  
  // Numero de cromosomas evaluados (necesario para el cruce GYT)
  unsigned int numEvaluados; 
  
  virtual void cruzaParIndividuos(CroT & cr1, CroT & cr2) = 0;  
  /* Necesita: dos cromosomas
     Modifica: el cromosoma cr1 con el resultado del cruce
  */
};

/******************************************************************/
/*                                                                */
/*          implementacion de la clase opCruce                    */
/*                                                                */
/******************************************************************/

template <class PobT, class CroT>
opCruce<PobT,CroT>::opCruce(const double & prCru)
  :r(*genRandomSingleton::getInstance()), pc(prCru), numEvaluados(0)
{}


template <class PobT, class CroT>
unsigned int opCruce<PobT, CroT>::totalEvaluados() const
{
  return numEvaluados;
}


template <class PobT, class CroT>
void opCruce<PobT,CroT>::cruzaIndividuos(PobT & pob)
{
  CroT aux; 
  
  for(unsigned int ind=0; ind+1<pob.totalIndividuos(); ind+=2)
    if(r.frandom() <= pc){
      //aux = pob[ind]; OJO, no se copia aqui, se hace una vez invalidado
      pob[ind].invalida(); // Invalidar los cromosomas, ya que seran modificados
      aux = pob[ind];
      pob[ind+1].invalida();
      cruzaParIndividuos(pob[ind], pob[ind+1]);
      cruzaParIndividuos(pob[ind+1], aux);
    }
}


template <class PobT, class CroT>
void opCruce<PobT,CroT>::aplica(PobT & pob)
{
  cruzaIndividuos(pob);
}

#endif



