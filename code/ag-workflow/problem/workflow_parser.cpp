#include "workflow_parser.h"
#include <iostream>

namespace heftmatic {


  auto operator==(const TaskFile &taskFile1, const TaskFile &taskFile2) -> bool {
    return taskFile1.name == taskFile2.name;
  }



  //Order by name
  auto
  operator<(const TaskFile &taskFile1, const TaskFile &taskFile2) -> bool {
    return taskFile1.name < taskFile2.name;
  }


  auto ParseWorkflow(nlohmann::json json) -> std::map<std::string, Task> {

    std::map<std::string, heftmatic::Task> tasks;
    for (auto &element : json["workflow"]["jobs"]) {
      Task task = Task();
      task.name = element["name"];
      task.runtime = element["runtime"];
      // Calculate total size to tranfer
      for (auto &file : element["files"]) {
        // Check if is input or output
        if (file["link"] == "input") {
          task.files_input_size += __int64_t(file["size"]);
          task.files_input.push_back(
                  *new TaskFile(file["name"], file["link"],
                                file["size"]));
        } else if (file["link"] == "output") {
          task.files_output_size += __int64_t(file["size"]);


          task.files_output.push_back(
                  *new TaskFile(file["name"], file["link"],
                                file["size"]));
        }
      }

      // Order the files
      std::sort(task.files_input.begin(), task.files_input.end());
      std::sort(task.files_output.begin(), task.files_output.end());

      for (auto &child : element["children"]) {
        task.children.push_back(child);
      }


      for (auto &parent : element["parents"]) {
        task.parents.push_back(parent);
      }

      tasks[task.name] = task;



    }

    return tasks;
  }

}// namespace heftmatic
