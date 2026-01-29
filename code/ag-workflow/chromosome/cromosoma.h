#ifndef _CROMOSOMA_H
#define _CROMOSOMA_H

#define INVALIDO FitT()

#ifdef __GNUG__
#pragma interface
#endif

#include "fitness/heft_service.h"
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

/******************************************************************/
/*                                                                */
/*          especificacion de la clase cromosoma<GenT,FitT>       */
/*                                                                */
/******************************************************************/

struct Schedule{
  int task_id {0};
  double ast {0.0};
  double eft {0.0};
  int host_id {0};
};

bool operator<(const Schedule& schedule1, const Schedule& schedule2) ;

template <class GenT, class FitT = double>
class cromosoma {
 public:
  // Constructores
  cromosoma(const unsigned int& nGens = 0, const FitT& f = INVALIDO,
            const bool& evaluado = false,
      const vector<Schedule>& solution = vector<Schedule>());
  cromosoma(const cromosoma<GenT, FitT>& c);

  // Destructor.
  virtual ~cromosoma(){};

  // Sobrecarga operadores
  virtual bool operator<(const cromosoma<GenT, FitT>& c) const;
  /* Produce: cierto si el fitness es menor que el de c
     Error: si el individuo no fue evaluado
  */
  bool operator==(const cromosoma<GenT, FitT>& c) const;
  /* Produce: cierto si dos cromosomas son iguales
   */
  cromosoma<GenT, FitT>& operator=(const cromosoma<GenT, FitT>& c);
  /* Produce: una copia del cromosoma c
   */
  GenT& operator[](const unsigned int& indice);
  const GenT& operator[](const unsigned int& indice) const;
  /* Produce: una referencia al gen indexado
   */

  // Observadores
  unsigned int numGenes() const;
  /* Produce: el numero de genes
   */
  virtual void fenotipo(ostream& out) const;
  /* Necesita: un stream de salida
     Produce:  vuelca el fenotipo por la salida
  */
  virtual void genotipo(ostream& out) const;
  /* Necesita: un stream de salida
     Produce:  vuelca el genotipo por la salida
  */
  FitT fitness() const;
  /* Produce: el valor del fitness
     Error:    si el individuo no fue evaluado
  */
  bool evaluado() const;
  /* Produce: un booleano indicando si el cromosoma ya fue evaluado
   */
  bool solucion() const;
  /* Produce: un booleano indicando si es solucucion o no
   */

  vector<Schedule> getSchedule() const;


  // Modificadores
  void fijaNumGenes(const unsigned int& nGens);
  /* Necesita: el nuevo numero de genes del cromosoma
     Modifica: el numero de genes del cromosoma
     Error:    si el numero es negativo
  */
  void intercambiaGenes(const unsigned int& pos1, const unsigned int& pos2);
  /* Necesita: la posicion de dos genes a intercambiar
     Modifica: intercambia el valor de los dos genes en el cromosoma
     Error:    si alguna posicion esta fuera de rango
  */
  void fijaFitness(const FitT& v);
  /* Necesita: el valor del fitness
     Modifica: el valor actual del fitness y condicion de evaluado
  */
  void invalida();
  /* Modifica: pone a falso el flag de solucion y evaluado, y fija su
     fitness a -1 (como valor no valido)
  */
  void fijaSolucion(const bool& v);
  /* Necesita: un booleano indicando si es solucion
     Modifica: si el individuo es o no solucion
  */

  void setSchedule(const vector<Schedule>& aSchedule);
  vector<GenT>& getGenes();
  /* Produce: una referencia a los genes
   */



 protected:
  // Numero total de genes
  unsigned int totGens;

  // Genotipo
  vector<GenT> genes;

  // Valor del fitness
  FitT fit;

  // Cierto si el fitness es valido
  bool fitEvaluado;

  // Cierto si el individuo codifica una solucion
  bool esSol;

  vector<Schedule> schedule;



};

template <class GenT, class FitT>
ostream& operator<<(ostream& salida, const cromosoma<GenT, FitT>& cr);
template <class GenT, class FitT>
istream& operator>>(istream& entrada, cromosoma<GenT, FitT>& cr);

/******************************************************************/
/*                                                                */
/*          implementacion de la clase cromosoma<GenT,FitT>       */
/*                                                                */
/******************************************************************/

template <class GenT, class FitT>
cromosoma<GenT, FitT>::cromosoma(const unsigned int& nGens, const FitT& f,
                                 const bool& evaluado,
                                 const vector<Schedule>& solution)
    : totGens(nGens),
      genes(nGens),
      fit(f),
      fitEvaluado(evaluado),
      esSol(false),
schedule(solution){}

template <class GenT, class FitT>
cromosoma<GenT, FitT>::cromosoma(const cromosoma<GenT, FitT>& c)
    : totGens(c.totGens),
      genes(c.genes),
      fit(c.fit),
      fitEvaluado(c.fitEvaluado),
      esSol(c.esSol),
      schedule(c.schedule) {}

template <class GenT, class FitT>
bool cromosoma<GenT, FitT>::operator<(const cromosoma<GenT, FitT>& c) const {
  if (!c.evaluado() || !evaluado())
    throw runtime_error("cromosoma<>::operator<(): cromosoma no evaluado");
  // Un individuo es mejor que otro si tiene menor fitness o si el otro no esta
  // evaluado
  return (fitness() < c.fitness());
}

template <class GenT, class FitT>
bool cromosoma<GenT, FitT>::operator==(const cromosoma<GenT, FitT>& c) const {
  // Comparar primero fitness
  if (!evaluado() || !c.evaluado() || (fitness() == c.fitness()) ||
      (getSchedule() == c.getSchedule()))
    // Comparar gen a gen
    return genes == c.genes;

  return false;
}

template <class GenT, class FitT>
cromosoma<GenT, FitT>& cromosoma<GenT, FitT>::operator=(
    const cromosoma<GenT, FitT>& c) {
  fit = c.fit;
  fitEvaluado = c.fitEvaluado;
  totGens = c.totGens;
  genes = c.genes;
  esSol = c.esSol;
  schedule = c.schedule;

  return *this;
}

template <class GenT, class FitT>
GenT& cromosoma<GenT, FitT>::operator[](const unsigned int& indice) {
  return genes[indice];
}

template <class GenT, class FitT>
const GenT& cromosoma<GenT, FitT>::operator[](
    const unsigned int& indice) const {
  return genes[indice];
}

template <class GenT, class FitT>
unsigned int cromosoma<GenT, FitT>::numGenes() const {
  return totGens;
}

template <class GenT, class FitT>
void cromosoma<GenT, FitT>::fenotipo(ostream& out) const {
  genotipo(out);
}

template <class GenT, class FitT>
void cromosoma<GenT, FitT>::genotipo(ostream& out) const {
  out << *this;
}

template <class GenT, class FitT>
FitT cromosoma<GenT, FitT>::fitness() const {
  return fit;
}

template <class GenT, class FitT>
bool cromosoma<GenT, FitT>::evaluado() const {
  return fitEvaluado;
}

template <class GenT, class FitT>
bool cromosoma<GenT, FitT>::solucion() const {
  return esSol;
}

template <class GenT, class FitT>
vector<Schedule> cromosoma<GenT, FitT>::getSchedule() const {
  return schedule;
}

template <class GenT, class FitT>
vector<GenT>& cromosoma<GenT, FitT>::getGenes() {
  return genes;
}

template <class GenT, class FitT>
void cromosoma<GenT, FitT>::fijaNumGenes(const unsigned int& nGens) {
  totGens = nGens;
  genes.resize(totGens);
}

template <class GenT, class FitT>
void cromosoma<GenT, FitT>::intercambiaGenes(const unsigned int& pos1,
                                             const unsigned int& pos2) {
  swap(genes[pos1], genes[pos2]);
}

template <class GenT, class FitT>
void cromosoma<GenT, FitT>::fijaFitness(const FitT& v) {
  fit = v;
  fitEvaluado = true;
}

template <class GenT, class FitT>
void cromosoma<GenT, FitT>::invalida() {
  esSol = false;
  fitEvaluado = false;
  fit = INVALIDO;
  schedule =  vector<Schedule>();
}

template <class GenT, class FitT>
void cromosoma<GenT, FitT>::fijaSolucion(const bool& v) {
  esSol = v;
}

template <class GenT, class FitT>
void cromosoma<GenT, FitT>::setSchedule(
    const vector<Schedule>& aSchedule) {
  schedule = aSchedule;
}

template <class GenT, class FitT>
ostream& operator<<(ostream& salida, const cromosoma<GenT, FitT>& cr) {
  salida << "[ ";
  for (unsigned int gen = 0; gen < cr.numGenes(); ++gen) {
    salida << cr[gen];
    if (gen + 1 < cr.numGenes()) salida << ' ';
  }
  salida << " ]";
  if (cr.evaluado()) salida << " " << cr.fitness();
  return salida;
}

template <class GenT, class FitT>
istream& operator>>(istream& entrada, cromosoma<GenT, FitT>& cr) {
  for (unsigned int gen = 0; gen < cr.numGenes(); ++gen) entrada >> cr[gen];

  return (entrada);
}

#endif
