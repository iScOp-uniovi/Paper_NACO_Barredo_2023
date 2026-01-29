
#include "opGenPermuta.h"

/******************************************************************/
/*                                                                */
/*             implementacion de la clase opGenPermuta                */
/*                                                                */
/******************************************************************/

OpGenPermuta::OpGenPermuta(const proPermuta& prob, char* nombre)
    : opGenesis<poblacion<crPermuta>, proPermuta, crPermuta>(prob, nombre),
      r(*genRandomSingleton::getInstance()) {}

void OpGenPermuta::generaIndividuo(crPermuta& cr) {
  // Invalidar cromosoma (por si se esta reutilizando, ej: experimento con
  // varias pruebas)
  cr.invalida();
  // Crear un cromosoma valido


  auto tasks_ids = pr.getTaskIds();
  auto hosts_ids = pr.getHostsIds();
  auto workflow = pr.getWorkflowJson();


  // Create map task to ids
  auto task_to_id = pr.getTaskToId();

  cr.fijaNumGenes(tasks_ids.size());


  vector<int> tasks_ordered;
  tasks_ordered.reserve(tasks_ids.size());
  std::map<std::string, int> number_of_parents;

  std::vector<const heftmatic::Task*> tasks_ids_to_explore;
  for (const auto& task_name : tasks_ids) {
    number_of_parents[task_name] = workflow[task_name].parents.size();
    if (workflow[task_name].parents.empty()) {
      tasks_ids_to_explore.push_back(&workflow[task_name]);
    }
  }


  for (unsigned int i = 0; i < tasks_ids.size(); i++) {

    // Get random first element
    int pos = r.rnd(0,tasks_ids_to_explore.size()-1);
    swap(tasks_ids_to_explore[0],tasks_ids_to_explore[pos]);
    const auto* task_to_explore = tasks_ids_to_explore[0];
    // Remove element from pool
    tasks_ids_to_explore.erase(tasks_ids_to_explore.begin());



    tasks_ordered.push_back(task_to_id[task_to_explore->name]);

    auto children = task_to_explore->children;


    // add shuffle children
    for (const auto& child : children) {
      number_of_parents[child]--;
      if (number_of_parents[child] == 0) {
        tasks_ids_to_explore.push_back(&workflow[child]);
      }
    }
  }



  for (unsigned int gen = 0; gen < cr.numGenes(); ++gen) {
    // <?> A RELLENAR EN FUNCION DEL PROBLEMA
    cr[gen] = TGen(tasks_ordered[gen], r.rnd(0, hosts_ids.size() - 1));
  }
}

