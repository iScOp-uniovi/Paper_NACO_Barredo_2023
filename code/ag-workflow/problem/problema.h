#ifndef _PROBLEMA_H
#define _PROBLEMA_H

#include <string>
#include <iostream>

using namespace std;

/******************************************************************/
/*                                                                */
/*          especificacion de la clase problema                   */
/*                                                                */
/******************************************************************/

class problema{
 public:
  // Constructor
  problema(const char* nombre);

  // Destructor
  virtual ~problema();

  // Observadores
  const char*  nombreProblema() const;
  /* Produce: El nombre del problema resuelto
   */
  virtual int getSol() const = 0;
  /* Produce: La mejor solucion conocida del problema
   */
 protected:
  // Nombre del fichero del problema
  char* nfich;
};

ostream & operator <<(ostream & salida, const problema & pro);

istream & operator >>(istream & entrada, const problema & pro);

#endif 
