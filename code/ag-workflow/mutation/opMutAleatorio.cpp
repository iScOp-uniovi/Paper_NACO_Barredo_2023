#include "opMutAleatorio.h"
#include "problem/proPermuta.h"

/******************************************************************/
/*                                                                */
/*          implementacion de la clase opMutAleatorio             */
/*                                                                */
/******************************************************************/

opMutAleatorio::opMutAleatorio(const problema& _pr, const double& prMut)
    : opMutacion<poblacion<crPermuta>, crPermuta>(prMut), pr(_pr) {}

void opMutAleatorio::mutaIndividuo(crPermuta& cr) {
  const auto& pro_pr = dynamic_cast<const proPermuta&>(pr);
  const auto& workflow_json = pro_pr.getWorkflowJson();
  const auto& task_ids = pro_pr.getTaskIds();

  // Choose random cut
  unsigned int pos = r.rnd(0, cr.numGenes() - 1);
  //  std::cout << "Choose: " << pos << " ";

  // Avoid max int value
  int pos_left = pos - 1;
  unsigned int pos_right = pos + 1;
  bool left_not_found = true;
  bool right_not_found = true;
  auto task_name_to_mutate = task_ids[cr[pos].first];
  auto task_to_mutate = workflow_json.at(task_name_to_mutate);

  // Check left side
  while (pos_left >= 0 && left_not_found) {
    auto task_to_check = task_ids[cr[pos_left].first];
    auto found = std::find(task_to_mutate.parents.begin(),
                           task_to_mutate.parents.end(), task_to_check);
    // Check if the new task is a parent
    if (found != task_to_mutate.parents.end()) {
      // Stop searching
      left_not_found = false;
    } else {
      // Continue search
      pos_left--;
    }
  }

  //  std::cout << "Choose left: " << pos_left << " ";
  // Check Right side
  while (pos_right < cr.numGenes() - 1 && right_not_found) {
    auto task_to_check = task_ids[cr[pos_right].first];
    auto found = std::find(task_to_mutate.children.begin(),
                           task_to_mutate.children.end(), task_to_check);
    // Check if the new task is a parent
    if (found != task_to_mutate.children.end()) {
      // Stop searching
      right_not_found = false;
    } else {
      // Continue search
      pos_right++;
    }
  }
  //  std::cout << "Choose Right: " << pos_right << " ";

  // get new position
  unsigned int new_pos = r.rnd(pos_left + 1, pos_right - 1);
  //  std::cout << "Choose newPos: " << new_pos << " ";

  // Now we need to find if we have to go right or left
  auto aux_gen = cr[pos];
  if (new_pos < pos) {
    // Go left
    for (int i = pos - 1; i >= new_pos && i >=0; i--) {
      // swap to the left
      cr[i + 1] = cr[i];
    }
  } else if (new_pos > pos) {
    for (unsigned int i = pos + 1; i <= new_pos; i++) {
      // swap to the left
      cr[i - 1] = cr[i];
    }
  }
  cr[new_pos] = aux_gen;
  // Now mutate new pos

  cr[new_pos].second = r.rnd(0, pro_pr.getHosts().size() - 1);
  //  std::cout << "Vm before: " << aux_gen.second << " "
  //            << "vm after: " << cr[new_pos].second << std::endl;
}
