#include "opMutSimple2.h"

/******************************************************************/
/*                                                                */
/*          implementacion de la clase opMutSimple2               */
/*                                                                */
/******************************************************************/

opMutSimple2::opMutSimple2(const double & prMut)
  :opMutacion <poblacion <crPermuta>, crPermuta>(prMut)
{}


void opMutSimple2::mutaIndividuo(crPermuta & cr)
{
  cr.intercambiaGenes(r.rnd(0, cr.numGenes()-1), r.rnd(0, cr.numGenes()-1));
}
