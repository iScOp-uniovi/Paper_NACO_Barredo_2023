#ifndef _ESCMATTFELD_H
#define _ESCMATTFELD_H

#include "escalado.h"

using namespace std;

/******************************************************************/
/*                                                                */
/*          especificacion de la clase escMattfeld                */
/*                                                                */
/******************************************************************/

template <class CroT, class FitT>
class escMattfeld: public escalado<CroT,FitT> {
 public:
  escMattfeld(const FitT & escIni = FitT());
  virtual void actualiza(const poblacion<CroT> & pob);
};


/******************************************************************/
/*                                                                */
/*          implementacion de la clase escMattfeld                */
/*                                                                */
/******************************************************************/

template <class CroT, class FitT>
escMattfeld<CroT,FitT>::escMattfeld(const FitT & escIni)
  :escalado<CroT,FitT>(escIni)
{}

template <class CroT, class FitT>
void escMattfeld<CroT,FitT>::actualiza(const poblacion<CroT> & pob)
{
  this->esc = pob[pob.peorIndividuo()].fitness();
}

#endif
