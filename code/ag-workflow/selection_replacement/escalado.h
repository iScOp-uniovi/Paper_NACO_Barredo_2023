#ifndef _ESCALADO_H
#define _ESCALADO_H



#include "poblacion.h"

using namespace std;

// Prototipo de poblacion (por referencias cruzadas)
template <class CroT>
class poblacion;

template <class CroT, class FitT>
class escalado {
 public:
  // Constructor
  escalado(const FitT & escIni = FitT());

  // Observadores
  const FitT  valorActual() const;
  /* Produce: el valor de escalado
     Error  : si el valor es VINVALIDO
  */

  // Operaciones
  virtual void actualiza(const poblacion<CroT> & pob) = 0;

 protected:
  FitT esc;
};


template <class CroT, class FitT>
escalado<CroT,FitT>::escalado(const FitT & escIni)
  :esc(escIni)
{}


template <class CroT, class FitT>
const FitT  escalado<CroT,FitT>::valorActual() const
{
  return esc;
}

#endif
