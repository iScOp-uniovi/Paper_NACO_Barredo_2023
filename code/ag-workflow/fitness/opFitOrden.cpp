#include "opFitOrden.h"
#include "heft_service.h"
#include <assert.h>

/******************************************************************/
/*                                                                */
/*          implementacion de la clase opFitOrden                   */
/*                                                                */
/******************************************************************/

opFitOrden::opFitOrden(const problema& prob)
    : opFitness<crPermuta, problema>(prob) {}

void opFitOrden::evaluaCromosoma(crPermuta& cr) {
  TFit makespan = 0;
  const auto& pro_pr = dynamic_cast<const proPermuta&>(p);
  const auto& workflow = pro_pr.getWorkflow();
  // const auto& task_ids = pro_pr.getTaskIds();
  const auto& task_to_id = pro_pr.getTaskToId();
  const auto& hosts = pro_pr.getHosts();
  auto available = std::vector<double>(hosts.size());
  // const auto& host_ids = pro_pr.getHostsIds();
  const auto& host_to_ids = pro_pr.getHostToId();
  const auto& network_matrix = pro_pr.getNetworkMatrix();

  const auto& computation_matrix = pro_pr.getComputationMatrix();
  // The schedule contains the est on the first item and the machine on the
  // second
  auto schedule = vector<Schedule>(workflow.size(), {0,0});

  for (unsigned int gen = 0; gen < cr.numGenes(); ++gen) {
    int id_task = cr[gen].first;
    int id_host = cr[gen].second;
    // const auto& task_name = task_ids[id_task];
    // const auto& task = workflow.at(task_name);
    // const auto& host_name = host_ids[id_host];
    double current_host_network_speed = hosts[id_host].first;

    // flag to choose heft or heft plus
    // first do normal heft

    // calculate coms from parents
    double max_est = 0;

    for (const auto& parent : workflow[id_task]) {
      // calculate transfer cost from parent, if is the same vm the cost is 0
      double coms_time = 0;

      // unsigned int parent_id = task_to_id.at(parent);
      //  find the name of the host checking the id of the chromosome
      auto parent_host = schedule[parent].host_id;

      // Check if the hosts are the same or not

      if (id_host != parent_host) {
        //        double parent_network_speed = unitParser.parse_network_speed(
        //            hosts.at(parent_host_name).network_speed);
        double parent_network_speed = hosts[parent_host].first;

        double bandwidth;
        // Choose the slowest speed
        if (parent_network_speed < current_host_network_speed) {
          bandwidth = parent_network_speed;
        } else {
          bandwidth = current_host_network_speed;
        }
        coms_time =  network_matrix[parent][id_task] / bandwidth;
      }
      // Calculate the max est of each parent
      double est = schedule[parent].eft + coms_time;
      max_est = std::max(est, max_est);
    }

    double eft = computation_matrix[id_task][id_host] +
                 std::max(available[id_host], max_est);
    // Write when tha host is available
    available[id_host] = eft;
    auto ast = available[id_host] - computation_matrix[id_task][id_host];
    // Fill the schedule
//    schedule[task_name].task_name = task_name;
//    schedule[task_name].ast =
//        available[host_name] -
//        computation_matrix.at(task_name).at(host_name);  // AST
    schedule[id_task] = {id_task,ast,eft, id_host};  // AFT and Host

    if (eft > makespan) {
      makespan = eft;
    }
  }

  // TODO: Reorder this array with AST
  auto aux_schedule = schedule;
  std::sort(aux_schedule.begin(), aux_schedule.end());

  // Reorder the chromosome
  for(int i=0; i<aux_schedule.size(); i++){
    cr[i].first=aux_schedule[i].task_id;
    cr[i].second=aux_schedule[i].host_id;
  }
  cr.setSchedule(schedule);

  cr.fijaFitness(makespan);
}
