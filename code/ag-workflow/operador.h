#ifndef _OPERADOR_H
#define _OPERADOR_H

/******************************************************************/
/*                                                                */
/*          especificacion de la clase operador<PobT>             */ 
/*                                                                */
/******************************************************************/

template<class PobT>
class operador{
 public:
  // Operaciones
  virtual void aplica(PobT & pob) = 0;
  /* Necesita: una poblacion
     Modifica: la poblacion de acuerdo al tipo de operador aplicado
  */
  virtual ~operador(){}
};

#endif
