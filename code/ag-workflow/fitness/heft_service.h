//
// Created by pablo on 18/01/2022.
//

#ifndef AG_WORKFLOW_HEFT_SERVICE_H
#define AG_WORKFLOW_HEFT_SERVICE_H

#include "problem/host_parser.h"
#include "problem/workflow_parser.h"
#include "tools/unit_parser.h"
#include <unordered_set>
namespace heftmatic {

struct Solution {
  bool operator==(const Solution& rhs) const;
  bool operator<(const Solution& rhs) const;
  bool operator()(const Solution& rhs) const;
  std::string task_name;
  double ast;
  double aft;
  std::string host;
};

class HeftService {
 public:
  auto CreateComputationMatrix(
      const std::map<std::string, Task>& tasks,
      const std::map<std::string, heftmatic::Host>& hosts,
      const std::string& reference_flops,
      std::map<std::string, unsigned int> task_to_id,
      std::map<std::string, unsigned int> host_to_id) -> const std::vector<std::vector<double>>;
  static auto intersectionFiles(const std::vector<TaskFile>& vector1,
                         const std::vector<TaskFile>& vector2)
      -> std::vector<TaskFile>;

  auto CalculateComs(double bitsToTransfer, double referenceNetworkSpeed)
      -> double;

  auto CalculateDiskComs(double bitsToTransfer,
                         double diskSpeed) -> double;
 private:
  heftmatic::UnitParser unitParser_;
};

}  // namespace heftmatic

#endif  // AG_WORKFLOW_HEFT_SERVICE_H
