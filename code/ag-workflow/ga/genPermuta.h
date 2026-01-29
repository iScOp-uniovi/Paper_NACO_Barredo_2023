#ifndef _GENPERMUTA_H
#define _GENPERMUTA_H

/******************************************************************/
/*                                                                */
/*          especificacion de la clase genPermuta                 */
/*                                                                */
/******************************************************************/

#include "poblacion.h"
#include "chromosome/crPermuta.h"
#include "selection_replacement/escCte.h"
#include "selection_replacement/escMattfeld.h"
//#include "opSelRuleta.h"
#include "selection_replacement/opSelTorneo.h"
#include "crossover/opCruGPX.h"
#include "mutation/opMutSimple1.h"
#include "mutation/opMutSimple2.h"
#include "mutation/opMutAleatorio.h"
#include "tools/excepcion.h"
#include "problem/problema.h"
#include "fitness/opFitness.h"
#include "ga/AlgoritmoGenetico.h"
#include <csignal>

using namespace std;

class genPermuta: public AlgoritmoGenetico{
 public:
  // Constructor
  genPermuta();

  // Destructor
  ~genPermuta();
  /* Modifica: elimina los objetos creado dinamicamente
   */

  // Modificadores
  opSeleccion<crPermuta,TFit> & fijaSeleccion();
  /* Modifica: genera el operador de seleccion
   */
  opCruce<poblacion<crPermuta>,crPermuta> & fijaCruce(problema & prob);
  /* Modifica: genera el operador de cruce
   */
  opMutacion<poblacion<crPermuta>,crPermuta> & fijaMutacion(problema & prob);
  /* Modifca: genera el operador de mutacion
   */
  opFitness<crPermuta,problema>  & fijaFitness(const problema & elProblema);
  /* Modifica: genera un operador de fitness
   */

  // Operaciones
  void ejecuta(const char* fich);
  /* Necesita: el nombre de un experimento
     Modifica: ejecuta el experimento contenido en fich
  */
  void tabla(ostream &out)const;
  /* Necesita: un stream de salida
     Modifica: vuelca en el stream su informacion en formato CSV
  */

 private:
  // Fichero del experimento
  const char* fExp;

  // Parametros del experimento:

  // Nombre del fichero del problema
  char* fichProb;
  // Nombre del fichero de infraestructura de hosts
  char* fichHosts;
  // Probabilidad de cruce
  double probCruce;
  // Probabilidad de mutacion
  double probMut;
  // Tama�o de la poblacion
  unsigned int tamPob;
  // Numero de generaciones
  unsigned int numGen;
  // Numero de pruebas
  unsigned int numPruebas;
  // Tipo de seleccion
  unsigned int tipoSeleccion;
  // Tipo de cruce
  unsigned int tipoCruce;
  // Tipo de mutacion
  unsigned int tipoMutacion;
  // Numero de individuos a cruzar(GYT)
  unsigned int nCruce;
  // Tipo de fitness
  unsigned int tipoFitness;
  // Funcion objetivo del fitness directo
  unsigned int objetivo;
  // Tipo de semilla
  unsigned int tipoSemilla; // 1: generaci�n de sem. aleat., 0: siempre la misma
  // Tipo de escalado
  unsigned int tipoEscalado;
  // Valor de escalado
  TFit valorEscalado;
  // Fichero de poblacion inicial
  char* fichPobIni;
  // Fichero de salida
  char* fichSal;
  // Comentario del problema
  char* coment;

  // Operadores
  escalado<crPermuta,TFit>* esc;
  opSeleccion<crPermuta,TFit>* sel;
  opCruce<poblacion<crPermuta>,crPermuta>* cru;
  opMutacion<poblacion<crPermuta>,crPermuta>* mut;
  opFitness<crPermuta, problema>* fit;

  // Operaciones
  void cargaParametros();
  void filtraComentario(ifstream & f,bool formal = true);
  void borraOperadores();
  // Busqueda Local
  unsigned int perctBL; // porcentaje de individuos a aplicar la BL (si el fitness la usa)
  unsigned int niterBL; // % de iteraciones entre aplicaciones consecutivas de la BL (si el fitness la usa)

  // traza
  unsigned int iter; // iteracion/generacion actual

  // restricciones de tiempo
  double maxSecs;
};

#endif
