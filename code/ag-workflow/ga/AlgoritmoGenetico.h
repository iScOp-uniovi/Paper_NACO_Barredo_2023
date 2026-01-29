/*
 * AlgoritmoGenetico.h
 *
 *  Created on: 03/03/2012
 *      Author: puente
 */

#ifndef ALGORITMOGENETICO_H_
#define ALGORITMOGENETICO_H_

#include <iostream>

class AlgoritmoGenetico{
public:
	virtual void tabla(std::ostream &out) const = 0;
	/*
	 * Necesita: un flujo de salida
	 * Modifica: vuelca la configuración del algoritmo en el flujo
	 */
	virtual ~AlgoritmoGenetico(){ }
};


#endif /* ALGORITMOGENETICO_H_ */
