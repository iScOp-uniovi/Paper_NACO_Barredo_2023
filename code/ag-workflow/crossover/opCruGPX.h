#ifndef _OPCRUGPX_H
#define _OPCRUGPX_H


#include "chromosome/crPermuta.h"
#include "opCruce.h"
#include "problem/problema.h"

using namespace std;

/******************************************************************/
/*                                                                */
/*          especificacion de la clase opCruGPX                   */
/*                                                                */
/******************************************************************/

class opCruGPX : public opCruce <poblacion <crPermuta>, crPermuta>{
 public:
  // Constructor
  opCruGPX(const problema& _pr, const double & prCru = 0.0);
  
 private:
  // el problema
  const problema &pr;

  // Operacion
  virtual void cruzaParIndividuos(crPermuta & cr1, crPermuta & cr2);
  /* Necesita: dos cromosomas
     Modifica: el cromosoma cr1 con el resultado del cruce
  */
};

#endif
