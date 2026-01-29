#ifndef _CRPERMUTA_H
#define _CRPERMUTA_H

#include "tools/random.h"
#include "cromosoma.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// tipo de gen de nuestro problema: par<ID_task,ID_VM>
typedef pair<int,int> TGen;

// tipo de fitness de nuestro problema
typedef double TFit;

// nuestros cromosomas
typedef cromosoma<TGen,TFit> crPermuta;


// TFit: operadores necesarios para el tipo gen
namespace std{
template<class T1, class T2>
ostream & operator<<(ostream &out, const std::pair<T1,T2> & g) {
	out << " " << g.first << " " << g.second << " ";
	return out;
}

template<class T1, class T2>
istream & operator>>(istream & in, std::pair<T1,T2> & g) {
	in >> g.first >> g.second;
	return in;
}

// solo necesario por como esta implementado cruce GPX (utiliza como clave TGen, luego necesitamos operator<())
template<class T>
bool operator<(const pair<T,T> & g1, const pair<T,T> & g2){
	if(g1.first < g2.first)
		return true;
	if((g1.first == g2.first) && (g1.second < g2.second))
		return true;
	return false;
}
};


#endif
