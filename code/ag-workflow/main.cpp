

#include "chromosome/crPermuta.h"
#include "fitness/opFitOrden.h"
#include "fitness/opFitOrdenPlus.h"
#include "ga/genPermuta.h"
#include "generation/opGenPermuta.h"
#include "poblacion.h"
#include "problem/proPermuta.h"
//#include <cstring>
#include <iostream>
//#include <stdexcept>

// int main3(int argc, char* argv[]) {
//   crPermuta cr(100);
//   std::cout << "Genotipo:";
//   cr.genotipo(std::cout);
//   std::cout << std::endl;
//   std::cout << "Fenotipo:";
//   cr.fenotipo(std::cout);
//   std::cout << std::endl;
//   std::cout << "Cr:" << cr << std::endl;
//
//   return 0;
// }

int mainTest() {
  // Generador de numeros aleatorios (por defecto generador por secuencia)
  genRandomSingleton::init(fija, secuencia);

  proPermuta problem("../data/heftmatic-workflow.json", "../data/hosts.json");
  //
  crPermuta chromosome(0);
  OpGenPermuta permute_gen(problem);
  opFitOrdenPlus fit(problem);
  opCruGPX opCr(problem, 1.0);
  opMutAleatorio opMut(problem, 1.0);

  // for(int i = 0; i < 3000 ; i++) {
  std::cout << "Genera" << std::endl;
  poblacion<crPermuta> pob(100);
  auto *esc = new escCte<crPermuta, TFit>(0);
  auto *sel = new opSelTorneo<crPermuta, TFit>(*esc, pob.totalIndividuos(), 2);
  permute_gen.iniciaPoblacion(pob);

  fit.aplica(pob);
  std::cout << pob << std::endl;
  std::cout << pob[pob.mejorIndividuo()].fitness() << std::endl;
  std::cout << std::endl;
  // sel->aplica(pob);
  std::cout << "Curuzaiton't" << std::endl;
  // opCr.aplica(pob);
  opMut.aplica(pob);
  std::cout << "Curuzaito" << std::endl;
  fit.aplica(pob);
  std::cout << pob << std::endl;
  std::cout << pob[pob.mejorIndividuo()].fitness() << std::endl;
  // sel->aplica2(pob);
  // std::cout << pob[pob.mejorIndividuo()].fitness() << std::endl;

  // False chromosome
  // std::stringstream test_cr;
  // 2 hosts
  // test_cr.str("0 0 1 0 3 1 4 1 2 0 5 1 8 0 6 1 7 0 9 0");
  // 3 hosts heft
  //  test_cr.str(
  //      "0 0"
  //      " 3 0"
  //      " 4 2"
  //      " 2 1"
  //      " 1 0"
  //      " 5 2"
  //      " 6 1"
  //      " 8 0"
  //      " 7 2"
  //      " 9 2");

  // 3 hosts heftplus
  //  test_cr.str(
  //      "0 0"
  //      " 3 0"
  //      " 2 1"
  //      " 1 2"
  //      " 4 0"
  //      " 5 1"
  //      " 6 2"
  //      " 8 0"
  //      " 7 1"
  //      " 9 2");

  // test_cr >> chromosome;

  //    std::cout << chromosome << endl;
  //  std::cout << "Evalua" << std::endl;
  //  fit.evaluaCromosoma(chromosome);
  //  std::cout << "Evaluado" << std::endl;
  //  std::cout << "Fitness:" << chromosome.fitness() << std::endl;
  //   }

  // Create schedule json

  return 0;
}

//---------------------------------------------------------------------------
// Sin implementar la opcion de flujo de salida
int main(int argc, char* argv[]) {
  // Nombre del fichero de configuracion
  string fconfig;
  ofstream out(".errores");

  // Seleccionar accion a ejecutar
  switch (argc) {
    case 1:
      // Por defecto el fichero de configuracion es entrada_gen.txt
      // -----Provisional-----------
      fconfig = "entrada_gen.txt";
      break;

    case 2:
      // Mostrar la ayuda
      if (!strcmp("-?", argv[1])) {
        cout << endl
             << "\t" << argv[0] << "  [-?][-v] archivo1 [archivo2]" << endl
             << endl;
        cout << "\t-v         - Genera unicamente una cadena de texto "
                "descriptiva de la version del Genetico asociado y finaliza."
             << endl;
        cout << "\tarchivo1   - Archivo conteniendo la configuraci�n del "
                "genetico."
             << endl;
        cout
            << "\t[archivo2] - Si se especifica dirige la salida de la " <<
               "ejecucion a dicho archivo, por defecto sera la salida estandar."
            << endl;

        cout << "\t-?         - Muestra la presente ayuda de pantalla y "
                "finaliza."
             << endl
             << endl;
        out << "AYUDA";
        return 0;
      }
      // Mostrar la version
      else if (!strcmp("-v", argv[1])) {
        cout << "Genetico version 1.0" << endl;
        out << "VERSION";
        return 0;
      }
      // Fichero de configuracion
      else {
        fconfig = argv[1];
        break;
      }
    case 3:
      fconfig = argv[1];
      break;
    default:
      out << "DEFAULT" << endl;
      return -1;
  }

  // Ejecucion del genetico
  genPermuta gen;
  try {
    gen.ejecuta(fconfig.c_str());
  } catch (fichExc& ex) {
    cout << ex.que() << endl << ex.donde() << endl;
    out << "-2";
    return -2;
  } catch (valExc& ex) {
    cout << ex.que() << endl << ex.donde() << endl;
    out << "-3";
    return -3;
  } catch (probExc& ex) {
    cout << ex.que() << endl << ex.donde() << endl;
    out << "-4";
    return -4;
  } catch (exception& ex) {
    cout << ex.what() << endl;
    return -5;
  }
  out << "NORMAL";
  return 0;
}
