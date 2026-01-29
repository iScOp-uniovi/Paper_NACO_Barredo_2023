#ifndef _OPMUTSIMPLE1_H
#define _OPMUTSIMPLE1_H

#include "chromosome/crPermuta.h"
#include "opMutacion.h"

using namespace std;

/******************************************************************/
/*                                                                */
/*          especificacion de la clase opMutSimple1               */
/*                                                                */
/******************************************************************/

class opMutSimple1: public opMutacion <poblacion <crPermuta>, crPermuta>{
 public:
  // Constructor
  opMutSimple1(const double & prMut = 0.0);

 private:
  // Operacion
  void mutaIndividuo(crPermuta & cr);
};

#endif
