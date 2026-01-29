#ifndef _RANDOM_H
#define _RANDOM_H

#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
//#include "excepcion.h"

using namespace std;

/******************************************************************/
/*                                                                */
/*          especificacion de la clase random                     */
/*                                                                */
/******************************************************************/

//using namespace std;

enum tipoSemilla {fija, aleatoria};

enum tipoGenerador {sistema, secuencia}; 


class genRandom{
 public:
  genRandom(const tipoSemilla & tipo = aleatoria, const tipoGenerador & tipoG = secuencia);
  int rnd(int low, int high);

  double frandom();

 protected:
  int TipoRandom; // 0: C++, 1: Algoritmo
  tipoSemilla tSemilla; // tipo de semilla para generador de numeros aleatorios
  tipoGenerador tGenerador; // tipo de generador de numeros aleatorios
  double oldrand[55];
  int jrand; // Indice en vector.

  void own_randomize(double randomseed);
  void advance_random();
  void warmup_random(double random_seed);
};

class genRandomSingleton{
private:
	static genRandom* gr;
	static tipoSemilla tipo;
	static tipoGenerador tipoG;
	genRandomSingleton(){}
public:
	static genRandom* getInstance(){
		if(gr == NULL)
			gr = new genRandom(tipo,tipoG);
		return gr;
	}
	static void init(const tipoSemilla & _tipo, const tipoGenerador & _tipoG){
		if(gr != NULL)
			throw runtime_error("genRandomSingleton::init() una vez creada la instancia");
		// configuramos
		genRandomSingleton::tipo = _tipo;
		genRandomSingleton::tipoG = _tipoG;
		genRandomSingleton::getInstance();
	}

};



#endif
