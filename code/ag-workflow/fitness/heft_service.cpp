//
// Created by pablo on 18/01/2022.
//

#include "heft_service.h"

namespace heftmatic {

bool Solution::operator==(const Solution& rhs) const {
  return task_name == rhs.task_name && ast == rhs.ast && aft == rhs.aft &&
         host == rhs.host;
}

bool Solution::operator<(const Solution& rhs) const { return ast < rhs.ast; }
bool Solution::operator()(const Solution& rhs) const { return ast < rhs.ast; }

// Returns intersection vector
auto HeftService::intersectionFiles(const std::vector<TaskFile>& vector1,
                                    const std::vector<TaskFile>& vector2)
    -> std::vector<TaskFile> {
  std::vector<TaskFile> vector3;
  std::set_intersection(vector1.begin(), vector1.end(), vector2.begin(),
                        vector2.end(), back_inserter(vector3));
  return vector3;
}

auto HeftService::CreateComputationMatrix(
    const std::map<std::string, Task>& tasks,
    const std::map<std::string, heftmatic::Host>& hosts,
    const std::string& reference_flops,
    std::map<std::string, unsigned int> task_to_id,
    std::map<std::string, unsigned int> host_to_id) -> const std::vector<std::vector<double>> {
    std::vector<std::vector<double>> computation_matrix(
      task_to_id.size(), std::vector<double>(host_to_id.size()));

  // first: task_name second: task
  for (const auto& task : tasks) {
    auto cost_map = std::map<std::string, double>();
    // first: host_name second: host
    for (const auto& host : hosts) {
      // Parse the CPU speed to double and then divide to get the multiplication
      // factor
      double flops_factor =
          unitParser_.parse_compute_speed(reference_flops) /
          (unitParser_.parse_compute_speed(host.second.flops) *
           host.second.cores);

      // Multiply the runtime by the factor to know the expected runtime with
      // the new hardware
      computation_matrix[task_to_id[task.first]][host_to_id[host.first]] =
          task.second.runtime * flops_factor;
    }
  }

  return computation_matrix;
}

auto HeftService::CalculateComs(double bitsToTransfer,
                                double referenceNetworkSpeed) -> double {
  auto coms_time = (bitsToTransfer) / referenceNetworkSpeed;
  return coms_time;
}

auto HeftService::CalculateDiskComs(double bitsToTransfer,
                                    double diskSpeed) -> double {



  auto coms_time = bitsToTransfer / diskSpeed;
  return coms_time;
}

}  // namespace heftmatic
