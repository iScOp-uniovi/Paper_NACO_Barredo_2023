#define _strdup strdup

#include "problema.h"
#include <string.h>

/******************************************************************/
/*                                                                */
/*          implementacion de la clase problema                   */
/*                                                                */
/******************************************************************/

problema::problema(const char* nombre) 
  :nfich(_strdup(nombre))
{}


problema::~problema()
{
  if(nfich)
    delete [] nfich;
}


const char*  problema::nombreProblema() const
{
  return nfich;
}


ostream & operator <<(ostream & salida, const problema & pro)
{
  salida << "Problema: " << pro.nombreProblema() << endl;

  return salida;
}


istream & operator >>(istream & entrada, const problema & pro)
{
  return entrada;
}
