#ifndef _ESCCTE_H
#define _ESCCTE_H

#include "escalado.h"

using namespace std;

/******************************************************************/
/*                                                                */
/*          especificacion de la clase escCte                     */
/*                                                                */
/******************************************************************/

template <class CroT, class FitT>
class escCte: public escalado<CroT,FitT> {
 public:
  escCte(const FitT & escIni = FitT());
  virtual void actualiza(const poblacion<CroT> & pob){};
};


/******************************************************************/
/*                                                                */
/*          implementacion de la clase escCte                     */
/*                                                                */
/******************************************************************/

template <class CroT, class FitT>
escCte<CroT,FitT>::escCte(const FitT & escIni)
  :escalado<CroT,FitT>(escIni)
{}

#endif
