#ifndef HEFTMATIC_INCLUDE_HEFTMATIC_WORKFLOW_PARSER_PREFIX_H
#define HEFTMATIC_INCLUDE_HEFTMATIC_WORKFLOW_PARSER_PREFIX_H
#include <nlohmann/json.hpp>

#include <cstdint>
#include <string> //for std::string
#include <utility>
#include <vector> //for std::vector

namespace heftmatic {

struct TaskFile {
  std::string name;
  std::string link; // direction, can be input or output
  float size;
  TaskFile(std::string aName, std::string aLink, float aSize)
      : name(std::move(aName)), link(std::move(aLink)), size(aSize) {}
};

auto operator==(const TaskFile &taskFile1, const TaskFile &taskFile2) -> bool;
auto operator<(const TaskFile &taskFile1, const TaskFile &taskFile2) -> bool;


struct Task {

  std::string name;
  double_t runtime;
  int64_t files_input_size = 0;      // Total KB to transfer in
  int64_t files_output_size = 0;     // Total KB to transfer out
  std::vector<std::string> parents;  // Save they key for each child
  std::vector<std::string> children; // Save they key for each child
  std::vector<heftmatic::TaskFile>
      files_input; // List of input files (from parents)
  std::vector<heftmatic::TaskFile>
      files_output; // List of output files (to childs)

};

// Parse json and creates a map of tasks.
// Map enables to easily find a child.
auto ParseWorkflow(nlohmann::json json) -> std::map<std::string, Task>;


} // namespace heftmatic

#endif // HEFTMATIC_INCLUDE_HEFTMATIC_WORKFLOW_PARSER_PREFIX_H
