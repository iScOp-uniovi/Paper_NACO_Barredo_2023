#include "opMutSimple1.h"

/******************************************************************/
/*                                                                */
/*          implementacion de la clase opMutSimple1               */
/*                                                                */
/******************************************************************/

opMutSimple1::opMutSimple1(const double & prMut)
  :opMutacion <poblacion <crPermuta>, crPermuta>(prMut)
{}


void opMutSimple1::mutaIndividuo(crPermuta & cr)
{
  unsigned int pos = r.rnd(0, cr.numGenes()-1);
  pos == (cr.numGenes()-1) ? cr.intercambiaGenes(pos, 0) 
    : cr.intercambiaGenes(pos, pos+1);
}
