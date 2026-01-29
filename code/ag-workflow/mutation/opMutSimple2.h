#ifndef _OPMUTSIMPLE2_H
#define _OPMUTSIMPLE2_H

#include "chromosome/crPermuta.h"
#include "opMutacion.h"

using namespace std;


/******************************************************************/
/*                                                                */
/*          especificacion de la clase opMutSimple2              */
/*                                                                */
/******************************************************************/

class opMutSimple2: public opMutacion <poblacion <crPermuta>, crPermuta>{
 public:
  // constructor
  opMutSimple2(const double & prMut = 0.0);

 private:
  // operaciones
  void mutaIndividuo(crPermuta & cr);
};


#endif
