#ifndef _OPMUTALEATORIO_H
#define _OPMUTALEATORIO_H

#include "chromosome/crPermuta.h"
#include "opMutacion.h"
#include "problem/problema.h"

using namespace std;


/******************************************************************/
/*                                                                */
/*          especificacion de la clase opMutAleatorio   */
/*                                                                */
/******************************************************************/

class opMutAleatorio: public opMutacion <poblacion <crPermuta>, crPermuta>{
 public:
  // Constructor

  opMutAleatorio(const problema& _pr,const double & prMut = 0.0 );

  ~opMutAleatorio(){}

 private:
  // Operacion
  void mutaIndividuo(crPermuta & cr);
  // el problema
  const problema &pr;
};

#endif
