#ifndef _OPFITORDEN_H
#define _OPFITO_H

#include "chromosome/crPermuta.h"
#include "opFitness.h"
#include "problem/proPermuta.h"
#include "problem/problema.h"
#include "tools/unit_parser.h"
#include <iterator>
#include <limits.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/******************************************************************/
/*                                                                */
/*          especificacion de la clase opFitOrden                 */
/*                                                                */
/******************************************************************/

class opFitOrden : public opFitness<crPermuta, problema> {
 private:
  heftmatic::UnitParser unitParser;
  heftmatic::HeftService heftService_;

 public:
  // Constructor
  opFitOrden(const problema& prob);
  /* Necesita: el problema a resolver
   */

  // Operaciones

  void evaluaCromosoma(crPermuta& cr);
  /* Necesita: un cromosoma
     Modifica: planifica el cromosoma, calcula su makespan y evalua si es
     solucion al problema
  */
};

#endif
