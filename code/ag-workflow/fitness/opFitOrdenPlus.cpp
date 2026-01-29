#include "opFitOrdenPlus.h"
#include "heft_service.h"
#include <assert.h>

/******************************************************************/
/*                                                                */
/*          implementacion de la clase opFitOrden                   */
/*                                                                */
/******************************************************************/

opFitOrdenPlus::opFitOrdenPlus(const problema& prob)
    : opFitness<crPermuta, problema>(prob) {}

void opFitOrdenPlus::evaluaCromosoma(crPermuta& cr) {

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

  const auto& task_bits_output = pro_pr.getTaskBitsOutput();

  // The schedule contains the est on the first item and the machine on the
  // second
  auto schedule = vector<Schedule>(workflow.size());

  for (unsigned int gen = 0; gen < cr.numGenes(); ++gen) {
    int id_task = cr[gen].first;
    int id_host = cr[gen].second;

    // We need to avoid using the name and only use the task id

    // const auto& task_name = task_ids[id_task];
    // const auto& task = workflow.at(task_name);
    // const auto& host_name = host_ids[id_host];
    double current_host_network_speed = hosts[id_host].first;

    // flag to choose heft or heft plus
    // first do normal heft

    // calculate coms from parents
    double max_est = 0;

    // Calculate coms for all hosts
    std::vector<double> host_coms(hosts.size(),0);
    int host_id = 0;
    for (const auto& host : hosts) {
      for (const auto& parent : workflow[id_task]) {
        // find the name of the host checking the id of the chromosome
        // std::string parent_host_name = schedule[parent].host;

        const auto& parent_host = schedule[parent].host_id;

        // calculate transfer cost from parent, if is the same vm the cost is 0
        double coms_time = 0;

        // unsigned int parent_id = task_to_id.at(parent);

        // Check if the hosts are the same or not
        double slowest_speed;
        if (host_id != parent_host) {
          double parent_network_speed = hosts[parent_host].first;

          double bandwidth;
          // Choose the slowest speed
          if (parent_network_speed < current_host_network_speed) {
            bandwidth = parent_network_speed;
          } else {
            bandwidth = current_host_network_speed;
          }
          // We need to do the minimum between bandwidth and parent disk

          double parent_disk_speed = hosts[parent_host].second;
          if (bandwidth < parent_disk_speed) {
            slowest_speed = bandwidth;
          } else {
            slowest_speed = parent_disk_speed;
          }

        } else {
          slowest_speed = host.second;
        }

        // host_coms[host] += network_map.at({parent, task_name}) /
        // slowest_speed;
        host_coms[host_id] += network_matrix[parent][id_task] / slowest_speed;
        double est = schedule[parent].eft;
        max_est = std::max(est, max_est);
      }
      host_id++;
    }

    double disk_read_staging{network_matrix[id_task][id_task] /
                             hosts[id_host].second};

    //    disk_read_staging =
    //        heftService_.CalculateComs(network_matrix[id_task][id_task],
    //                                   hosts[host_id].second);
    //
    //    double disk_write_time = heftService_.CalculateDiskComs(
    //        task_bits_output[id_task], hosts[host_id].second);
    double disk_write_time{task_bits_output[id_task] / hosts[id_host].second};

    double eft = disk_read_staging + disk_write_time +
                 computation_matrix[id_task][id_host] +
                 std::max(available[id_host], max_est) + host_coms[id_host];
    // Write when tha host is available
    available[id_host] = eft;
    auto ast = available[id_host] -
               computation_matrix[id_task][id_host] - disk_write_time -
                       host_coms[id_host] - disk_read_staging;  // AST
    // Fill the schedule
    //    schedule[task_name].task_name = task_name;
    //    schedule[task_name].ast =
    //
    schedule[id_task] = {id_task,ast,eft ,id_host};  // AFT and Host

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
