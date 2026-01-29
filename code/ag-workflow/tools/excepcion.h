#ifndef _EXCEPCION_H
#define _EXCEPCION_H

#include <string.h>

class excepcion{
 public:
  // Constructor
  excepcion(const string & funcion)
    :metodo("En " + funcion)
    {}
    
  // Operacion
  const string donde() const{return metodo;}
  
 private:
  const string metodo;
};
  
/* Trata el fallo en la apertura de un fichero
 */
class fichExc: public excepcion{
 public:
  // Constructor
  fichExc(const string & funcion, const string & archivo)
    :excepcion(funcion), archivo("Imposible abrir " + archivo)
    {}

  // Operacion
  const string que() const{return archivo;}

 private:
  const string archivo;
};

/* Trata un parametro invalido
 */
class valExc: public excepcion{
 public:
  // Constructor
  valExc(const string & funcion, const string & parametro)
    :excepcion(funcion), param("Valor invalido de " + parametro)
    {}

  // Operacion
  const string que() const{return param;}

 private:
  const string param;
};

/* Trata la validez del fichero con el problema
 */
class probExc: public excepcion{
 public:
  probExc(const string & funcion, const string & problema)
    :excepcion(funcion), error("Fallo en el fichero del problema" + problema)
    {}
  
  const string que() const{return error;}
  
 private:
  const string error;
};

#endif
