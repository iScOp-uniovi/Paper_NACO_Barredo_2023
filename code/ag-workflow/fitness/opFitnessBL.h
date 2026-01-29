//---------------------------------------------------------------------------

#ifndef opFitnessBLH
#define opFitnessBLH
//---------------------------------------------------------------------------
#include "opFitness.h"

template <class CroT, class ProT>
class opFitnessBL: public opFitness<CroT, ProT>{
 public:
  // Constructor
  opFitnessBL(const ProT & prob);
  /* Necesita: un problema a resolver
   */

  static unsigned int getVecinosEvaluados()
  { return vecinosEvaluados;}
  static unsigned int getVecinosNFEvaluados()
  { return vecinosNoFactibles;}
  protected:
  static unsigned int vecinosEvaluados;
  static unsigned int vecinosNoFactibles;
};


template <class CroT, class ProT>
opFitnessBL<CroT,ProT>::opFitnessBL(const ProT & prob):opFitness<CroT,ProT>(prob)
{
}

template <class CroT, class ProT>
unsigned int opFitnessBL<CroT,ProT>::vecinosEvaluados = 0;

template <class CroT, class ProT>
unsigned int opFitnessBL<CroT,ProT>::vecinosNoFactibles = 0;
#endif
