#ifndef _OPSELECCION_H
#define _OPSELECCION_H

#include <vector>
#include "chromosome/cromosoma.h"
#include "poblacion.h"
#include "escalado.h"
#include "operador.h"

using namespace std;

// Prototipo de poblacion (por referencias cruzadas)
template <class CroT>class poblacion;

/******************************************************************/
/*                                                                */
/*           especifiacion de la clase opSeleccion<CroT,FitT>     */
/*                                                                */
/******************************************************************/

template <class CroT, class FitT = double>
class opSeleccion: public operador<poblacion<CroT> >{
  public:
  // Constructor
  opSeleccion(escalado<CroT,FitT> & esc);
  /* Necesita: un operador de escalado
   */
  
  //Destructor
  virtual ~opSeleccion(){};
  
  // Operaciones
  virtual void seleccionaIndividuos(poblacion<CroT> & pob) = 0;
  /* Necesita: una poblacion
     Modifica: modifica la poblacion de acuerdo con un criterio de seleccion
  */
  virtual void aplica(poblacion<CroT> & pob) = 0;
  /* Necesita: una poblacion
     Modifica: modifica la poblacion 
  */
  virtual void aplica2(poblacion<CroT> & pob);
  /* Necesita: una poblacion
     Modifica: modifica la poblacion por segunda vez (si es conveniente)
  */
  
protected:
  // Operador de escalado
  escalado<CroT,FitT> & opEsc;
};


/******************************************************************/
/*                                                                */
/*        implementacion de la clase opSeleccion<CroT,FitT>       */
/*                                                                */
/******************************************************************/

template <class CroT, class FitT>
opSeleccion<CroT, FitT>::opSeleccion(escalado<CroT,FitT> & esc)
  : opEsc(esc)
{}


template <class CroT, class FitT>
void opSeleccion<CroT, FitT>::aplica2(poblacion<CroT> & pob)
{}

#endif
