#ifndef _TRAZA_H
#define _TRAZA_H

#include "crono.h"
#include "crossover/opCruce.h"
#include "fitness/opFitnessBL.h"
#include "ga/AlgoritmoGenetico.h"
#include "poblacion.h"
#include "problem/proPermuta.h"
#include <climits>
#include <ctime>
#include <fstream>
#include <time.h>
#include <vector>
#include <iomanip>

using namespace std;

/******************************************************************/
/*                                                                */
/*          especificacion de la clase traza                      */
/*                                                                */
/******************************************************************/

// class AlgoritmoGenetico;  // forward

template <class FitT, class PobT, class CroT, class ProT>
class traza {
 public:
  // Constructor
  traza(const unsigned int& npru = 0, const unsigned int& ngen = 0);

  // Operaciones
  void iniciaPrueba(const unsigned int& np);
  /* Necesita: el numero de prueba actual
     Modifica: el tiempo de inicio de la prueba actual
  */
  void actualizaPrueba(const unsigned int& np, const unsigned int& gen,
                       const poblacion<CroT>& pob);
  /* Necesita: el numero de prueba y generacion actuales y una poblacion
     Modifica: el mejor individuo y la media de la poblacion
  */
  void finPrueba(const unsigned int& np, const poblacion<CroT>& pob,
                 const opFitness<CroT, ProT>& ft,
                 const opCruce<PobT, CroT>& cr);
  /* Necesita: el numero de prueba actual, una poblacion y operadores de fitness
     y cruce Modifica: la duracion de la prueba actual, la mejor solucion, el
     numero de soluciones encontradas y el numero de individuos evaluados
  */
  void finaliza(const problema& pr, const poblacion<CroT>& pob,
                const char* nfich, const AlgoritmoGenetico& ag);
  /* Necesita: un problema, la poblacion, el nombre de un fichero para almacenar
     los resultados y el genetico (por su configuracion) Modifica: los ficheros
     de resultados, nfich
   */

 protected:
  // Numero de pruebas
  unsigned int nP;
  // Numero de generaciones
  unsigned int nG;
  // Mejor fitness de todas las pruebas
  FitT mejorSolucion;
  // Mejor fitness por generacion y prueba
  vector<vector<FitT> > mejorFitness;
  // Media de la poblacion poblacion por generacion y prueba
  vector<vector<FitT> > mediaFitness;
  // Tiempo por prueba
  vector<clock_t> tiempoPrueba;
  // Mejor individuo por prueba
  vector<CroT> mejorSol;
  // Numero de soluciones encontradas por prueba
  vector<unsigned int> numSols;
  // Numero de individuos evaluados por prueba
  vector<unsigned int> totalEvaluados;
  // Numero de vecinos evaluados por prueba
  vector<unsigned int> totalVecinos;
  // Numero de vecinos generados no factibles por prueba
  vector<unsigned int> totalNFVecinos;

  // ultima generacion supervisada por prueba (por si el AG no ejecuta todas las
  // generaciones)
  vector<unsigned int> ultGen;

 private:
  void muestraPrueba(unsigned int& p, ostream& out);
  /* Necesita: el numero de prueba y un stream de salida
     Modifica: el fichero de resultados
  */
  void escribirTablaFitness(ostream& out) const;
  /* Necesita: un stream de salida
     Modifica: el fichero de resultados, "media.txt" y "max.txt"
  */
  void escribirTablaFitnessMejor(ostream& out) const;
  void escribirTablaFitnessMedia(ostream& out) const;
};

/******************************************************************/
/*                                                                */
/*          implementacion de la clase traza                      */
/*                                                                */
/******************************************************************/

template <class FitT, class PobT, class CroT, class ProT>
traza<FitT, PobT, CroT, ProT>::traza(const unsigned int& npru,
                                     const unsigned int& ngen)
    : nP(npru),
      nG(ngen),
      mejorSolucion(FitT()),
      mejorFitness(npru, vector<FitT>(ngen)),
      mediaFitness(npru, vector<FitT>(ngen)),
      tiempoPrueba(npru),
      mejorSol(npru + 1),
      numSols(npru + 1, 0),
      totalEvaluados(npru + 1, 0),
      totalVecinos(npru + 1, 0),
      totalNFVecinos(npru + 1, 0) {
  ultGen.resize(npru);
}

template <class FitT, class PobT, class CroT, class ProT>
void traza<FitT, PobT, CroT, ProT>::iniciaPrueba(const unsigned int& np) {
  // Tiempo inicial
  tiempoPrueba[np] = clock();
}

template <class FitT, class PobT, class CroT, class ProT>
void traza<FitT, PobT, CroT, ProT>::actualizaPrueba(
    const unsigned int& np, const unsigned int& gen,
    const poblacion<CroT>& pob) {
  // actualizamos la ultima generacion supervisada (por si acaba el AG antes de
  // tiempo)
  ultGen[np] = gen;

  // Acumulador para el fitness medio de la generacion actual
  // (si el fitness es multiobjetivo habria que replantear el calculo promedio)
  FitT acu = FitT();

  // Mejor individuo
  mejorFitness[np][gen] = pob[pob.mejorIndividuo()].fitness();

  // Media de la poblacion
  for (unsigned int ind = 0; ind < pob.totalIndividuos(); ++ind)
    acu = acu + pob[ind].fitness();
  acu = acu / pob.totalIndividuos();
  mediaFitness[np][gen] = acu;

  /*
  FitT acu2 = FitT();
  for(unsigned int ind=0; ind<pob.totalIndividuos(); ++ind)
    acu2 = acu2 + pob[ind].getF1();
  acu2 = acu2 / pob.totalIndividuos();
  mediaF1[np][gen] = acu2;

  acu2 = 0;
  for(unsigned int ind=0; ind<pob.totalIndividuos(); ++ind)
    acu2 = acu2 + pob[ind].getF2();
  acu2 = acu2 / pob.totalIndividuos();
  mediaF2[np][gen] = acu2;

  acu2 = 0;
  for(unsigned int ind=0; ind<pob.totalIndividuos(); ++ind)
    acu2 = acu2 + pob[ind].getF3();
  acu2 = acu2 / pob.totalIndividuos();
  mediaF3[np][gen] = acu2;

  double acu2d = 0;
  for(unsigned int ind=0; ind<pob.totalIndividuos(); ++ind)
    acu2d = acu2d + pob[ind].getF4();
  acu2d = acu2d / pob.totalIndividuos();
  mediaF4[np][gen] = acu2d;

  acu2d = 0;
  for(unsigned int ind=0; ind<pob.totalIndividuos(); ++ind)
    acu2d = acu2d + pob[ind].getF5();
  acu2d = acu2d / pob.totalIndividuos();
  mediaF5[np][gen] = acu2d;

  acu2d = 0;
  for(unsigned int ind=0; ind<pob.totalIndividuos(); ++ind)
    acu2d = acu2d + pob[ind].getF6();
  acu2d = acu2d / pob.totalIndividuos();
  mediaF6[np][gen] = acu2d;

  acu2d = 0;
  for(unsigned int ind=0; ind<pob.totalIndividuos(); ++ind)
    acu2d = acu2d + pob[ind].getF7();
  acu2d = acu2d / pob.totalIndividuos();
  mediaF7[np][gen] = acu2d;

  // Media de la poblacion
  double acu3 = 0.0;
  for(unsigned int ind=0; ind<pob.totalIndividuos(); ++ind)
    acu3 = acu3 + pob[ind].fitness().criterio1();
  acu3 = acu3 / pob.totalIndividuos();
  mediaC1[np][gen] = acu3;
  */
}

template <class FitT, class PobT, class CroT, class ProT>
void traza<FitT, PobT, CroT, ProT>::finPrueba(const unsigned int& np,
                                              const poblacion<CroT>& pob,
                                              const opFitness<CroT, ProT>& ft,
                                              const opCruce<PobT, CroT>& cr) {
  // Tiempo total
  tiempoPrueba[np] = clock() - tiempoPrueba[np];

  // Mejor solucion
  mejorSol[np] = pob[pob.mejorIndividuo()];
  if (mejorSolucion == FitT())
    mejorSolucion = mejorSol[np].fitness();
  else
    mejorSolucion = min(mejorSolucion, mejorSol[np].fitness());

  // Soluciones encontradas
  for (unsigned int ind = 0; ind < pob.totalIndividuos(); ++ind)
    if (pob[ind].solucion()) {
      ++numSols[np];
      ++numSols[nP];
    }

  // Individuos evaluados
  totalEvaluados[nP] += totalEvaluados[np] =
      ft.totalEvaluados() + cr.totalEvaluados() - totalEvaluados[nP];

  // si el operador de fitness lleva busqueda local se muestran los vecinos
  // generados
  const opFitnessBL<CroT, ProT>* opFBL =
      dynamic_cast<const opFitnessBL<CroT, ProT>*>(&ft);
  if (opFBL) {
    totalVecinos[nP] += totalVecinos[np] =
        opFBL->getVecinosEvaluados() - totalVecinos[nP];
    totalNFVecinos[nP] += totalNFVecinos[np] =
        opFBL->getVecinosNFEvaluados() - totalNFVecinos[nP];
  }
}

template <class FitT, class PobT, class CroT, class ProT>
void traza<FitT, PobT, CroT, ProT>::finaliza(const problema& pr,
                                             const poblacion<CroT>& pob,
                                             const char* nfich,
                                             const AlgoritmoGenetico& a) {
  fstream f;
  f.open(nfich, ios::out);

  if (!f.good())
    throw(fichExc("void traza<FitT,PobT,CroT,ProT>::finaliza(...)", nfich));

  f << "//Fichero de resultados de la ejecucion del problema: "
    << pr.nombreProblema();
  time_t t = time(0);
  char s[80];
  // windows:  f << " Fecha: " << ctime_s(s,79,& t) << endl;
  f << " Fecha: " << ctime(&t) << endl;  // linux
  // Tamano del problema y solucion conocida al problema
  f << pob[0].numGenes() << "  " << pr.getSol() << endl;

  // Mostrar solucion de cada prueba
  for (unsigned int p = 0; p < nP; ++p) muestraPrueba(p, f);

  // Muestra fitness
  escribirTablaFitness(f);

  // Datos del experimento
  f << "Duracion del experimento, mejor solucion, numero de individuos "
       "evaluados y numero de soluciones"
    << endl;
  f << (double)clock() / (double)CLOCKS_PER_SEC << "  " << mejorSolucion << "  "
    << totalEvaluados[nP] << "  " << numSols[nP] << endl;

  f.close();

  // Si el fichero de salida no es "resultados.txt" volcar una copia al mismo
  if (strcmp(nfich, "resultados.txt")) {
    ofstream f2("resultados.txt");
    f.open(nfich, ios::in);
    if (!f.good())
      throw(fichExc("void traza<FitT,PobT,CroT,ProT>::finaliza(...)", nfich));
    if (!f2.good())
      throw(fichExc("void traza<FitT,PobT,CroT,ProT>::finaliza(...)",
                    "resultados.txt"));
    char c;
    while (f.get(c)) f2.put(c);
    f.close();
    f2.close();
  }
  // resumen en tabla.txt
  ofstream ftabla("tabla.txt", ios_base::out);
  // resultados
  double acum = 0;
  double best = INT_MAX;
  double worst = 0;
  for (unsigned int prueba = 0; prueba < nP; ++prueba) {
    acum = acum + mejorFitness[prueba][ultGen[prueba]];
    if (mejorFitness[prueba][ultGen[prueba]] < best)
      best = mejorFitness[prueba][ultGen[prueba]];
    if (mejorFitness[prueba][ultGen[prueba]] > worst)
      worst = mejorFitness[prueba][ultGen[prueba]];
  }

  ftabla << pr.nombreProblema() << ":" << best << ":"
         << double(acum) / double(nP) << ":" << worst << ":";
  ftabla << totalEvaluados[nP] << ":" << totalVecinos[nP] << ":"
         << totalNFVecinos[nP] << ":";
  double acu = 0;
  for (unsigned int x = 0; x < nP; x++) acu += ultGen[x] + 1;
  ftabla << "Gen(" << acu / nP << "):";

  ftabla << "T(" << crono::getTime() << "):";

  a.tabla(ftabla);

  ftabla.close();

  // permutaciones en soluciones.txt
  ofstream fsols("soluciones.txt", ios_base::out);

  // Get the problem
  const auto& pro_pr = dynamic_cast<const proPermuta&>(pr);
  const auto& task_ids = pro_pr.getTaskIds();
  const auto& host_ids = pro_pr.getHostsIds();
  const auto& hosts_json = pro_pr.getHostsJson();

  // Create the json template with the hostsJson already defined
  // Crete a json for scheduling
  nlohmann::json schedule_json;
  // Create hostsJson field
  schedule_json["machines"] = nlohmann::json::array();
  for (const auto& host : hosts_json) {
    nlohmann::json item_json = nlohmann::json::object();
    item_json["name"] = host.second.name;
    item_json["cores"] = std::to_string(host.second.cores);
    item_json["cpu_speed"] = host.second.flops;
    item_json["disk_speed"] = host.second.disk_speed;
    item_json["network_speed"] = host.second.network_speed;
    schedule_json["machines"].push_back(item_json);
  }

  for (unsigned int prueba = 0; prueba < nP; ++prueba) {
    mejorSol[prueba].genotipo(fsols);

    fsols << endl;
    // Set the schedule filed to empty each time
    schedule_json["schedule"] = nlohmann::json::array();
    for (unsigned int i = 0; i < mejorSol[prueba].numGenes(); ++i) {
      // write each gen
      nlohmann::json item_json = nlohmann::json::object();
      item_json["task_id"] = task_ids[mejorSol[prueba][i].first];
      item_json["host"] = host_ids[mejorSol[prueba][i].second];
      schedule_json["schedule"].push_back(item_json);
    }
    std::ostringstream json_file;
    json_file << "schedule-" << prueba << ".json";
    std::ofstream ofs(json_file.str());
    ofs << std::setw(4) << schedule_json << std::endl;
    ofs.close();

    // Write the schedule of the selected task
//    nlohmann::json result_json = nlohmann::json::array();
//    for (auto& item : mejorSol[prueba].getSchedule()) {
//      nlohmann::json item_json = nlohmann::json::object();
//      item_json["name"] = item.second.task_name;
//      item_json["start_time"] = item.second.ast;
//      item_json["end_time"] = item.second.aft;
//      item_json["host"] = item.second.host;
//      result_json.push_back(item_json);
//    }


//    std::ostringstream json_file2;
//    json_file2 << "result-fitness-" << prueba << ".json";
//    std::ofstream ofs2(json_file2.str());
//    ofs2 << std::setw(4) << result_json << std::endl;
//    ofs2.close();


  }

  fsols.close();

  ofstream fmax("max.txt", ios_base::out);
  ofstream fmed("med.txt", ios_base::out);
  escribirTablaFitnessMejor(fmax);
  escribirTablaFitnessMedia(fmed);
}

template <class FitT, class PobT, class CroT, class ProT>
void traza<FitT, PobT, CroT, ProT>::muestraPrueba(unsigned int& p,
                                                  ostream& out) {
  out << p << "  " << (double)tiempoPrueba[p] / (double)CLOCKS_PER_SEC << "   ";
  out << totalEvaluados[p] << "   " << numSols[p] << "   "
      << mejorSol[p].fitness() << endl;

  // Mostrar individuo
  out << mejorSol[p] << endl;
}

template <class FitT, class PobT, class CroT, class ProT>
void traza<FitT, PobT, CroT, ProT>::escribirTablaFitness(ostream& out) const {
  out << "**** MAKESPAN *****" << endl;
  escribirTablaFitnessMejor(out);

  out << "*** MEDIA ****" << endl;
  escribirTablaFitnessMedia(out);
}

template <class FitT, class PobT, class CroT, class ProT>
void traza<FitT, PobT, CroT, ProT>::escribirTablaFitnessMejor(
    ostream& out) const {
  // Fitness es mejor y medio respectivamente por generacion y prueba
  FitT acum;
  unsigned int n;

  for (unsigned int gen = 0; gen < nG; ++gen) {
    bool nulo = true;
    n = 0;  // num pruebas que ejecutaron esta generacion

    for (unsigned int prueba = 0; prueba < nP; ++prueba) {
      if (ultGen[prueba] >= gen) {
        if (nulo) {
          acum = mejorFitness[prueba][gen];
          nulo = false;
        } else
          acum = acum + mejorFitness[prueba][gen];
        n++;
      }
      out << mejorFitness[prueba][gen] << "  ";
    }
    // Promedio de los mejores fitness
    if (n > 0)
      out << acum / n << endl;
    else
      out << TGen() << endl;
  }
}

template <class FitT, class PobT, class CroT, class ProT>
void traza<FitT, PobT, CroT, ProT>::escribirTablaFitnessMedia(
    ostream& out) const {
  // Fitness es mejor y medio respectivamente por generacion y prueba
  FitT acum;
  unsigned int n;
  for (unsigned int gen = 0; gen < nG; ++gen) {
    bool nulo = true;

    n = 0;  // num pruebas que ejecutaron esta generacion

    for (unsigned int prueba = 0; prueba < nP; ++prueba) {
      if (ultGen[prueba] >= gen) {
        if (nulo) {
          acum = mediaFitness[prueba][gen];
          nulo = false;
        } else
          acum = acum + mediaFitness[prueba][gen];
        n++;
      }
      out << mediaFitness[prueba][gen] << "  ";
    }
    // Promedio de las medias de fitness
    if (n > 0)
      out << acum / n << endl;
    else
      out << TGen() << endl;
  }
}

#endif
