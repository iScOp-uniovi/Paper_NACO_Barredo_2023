#ifndef _OPGENPERMUTA_H
#define _OPGENPERMUTA_H

#include "tools/random.h"
#include "opGenesis.h"
#include "chromosome/crPermuta.h"
#include "problem/proPermuta.h"

using namespace std;

template <class PobT, class ProT, class CroT>
class opGenesis;

/******************************************************************/
/*                                                                */
/*          especificacion de la clase opGenPermuta               */
/*                                                                */
/******************************************************************/

class OpGenPermuta: public opGenesis<poblacion<crPermuta>, proPermuta, crPermuta>{
 public:
  // Constructor
  OpGenPermuta(const proPermuta & prob,  char*  nombre = 0);

  // Operacion
  void generaIndividuo(crPermuta & cr);
  
 private:
  // Generador de numeros aleatorios
  genRandom & r;
};


#endif
