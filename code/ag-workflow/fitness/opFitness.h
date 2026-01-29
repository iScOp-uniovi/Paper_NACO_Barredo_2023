#ifndef _OPFITNESS_H
#define _OPFITNESS_H

#include <string>
#include "chromosome/cromosoma.h"
#include "poblacion.h"
#include "operador.h"

using namespace std;

/******************************************************************/
/*                                                                */
/*          especificacion de la clase opFitness                  */
/*                                                                */
/******************************************************************/

template <class CroT, class ProT>
class opFitness:public operador<poblacion<CroT> > {
 public:
  // Constructor
  opFitness(const ProT & prob);
  /* Necesita: un problema a resolver
   */

  // Destructor
  virtual ~opFitness(){};

  // Observadores
  unsigned int totalEvaluados() const;
  /* Produce: el total de individuos evaluados con el operador de fitness
  */

  // Operaciones
  virtual void evaluaPoblacion(poblacion<CroT> & pob);
  /* <?> en caso de paralelismo en la evaluacion, esta seria la
         funcion a redefinir
  */
  /* Necesita: una poblacion a evaluar
     Modifica: el numero de individuos evaluados y define el valor
     del fitness de cada cromosoma (no calculado aun)
  */
  virtual void aplica(poblacion<CroT> & pob);
  /* Necesita: una poblacion
     Modifica: evalua la poblacion
  */
  
protected:
  // Problema a resolver
  const ProT & p; 

  // Numero de cromosomas evaluados
  unsigned int numEvaluados; 

  virtual void evaluaCromosoma(CroT & cr)=0;
  /* Necesita: un individuo (cromosoma)
     Modifica: calcula y actualiza el fitness del individuo
  */
};


/******************************************************************/
/*                                                                */
/*          implementacion de la clase opFitness                  */
/*                                                                */
/******************************************************************/

template <class CroT, class ProT>
opFitness<CroT,ProT>::opFitness(const ProT & prob)
  : p(prob), numEvaluados(0)
{}


template <class CroT, class ProT>
unsigned int opFitness<CroT,ProT>::totalEvaluados() const
{
  return numEvaluados;
}


template <class CroT, class ProT>
void opFitness<CroT,ProT>::aplica(poblacion<CroT> & pob)
{
  evaluaPoblacion(pob);
}

template <class CroT, class ProT>
void opFitness<CroT,ProT>::evaluaPoblacion(poblacion<CroT> & pob)
{
	pob.actualizaMejor(0);
	pob.actualizaPeor(0);
	for(unsigned int ind=0; ind<pob.totalIndividuos();++ind)       {
		//  cout << ind << endl;
		if(!pob[ind].evaluado()){
			evaluaCromosoma(pob[ind]);
			if(pob[ind] < pob[pob.mejorIndividuo()])
				pob.actualizaMejor(ind);
			if(pob[pob.peorIndividuo()] < pob[ind])
				pob.actualizaPeor(ind);
			++numEvaluados;
		}
	}
}


#endif
