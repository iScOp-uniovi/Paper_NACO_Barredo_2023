/*
 * proPermuta.h
 *
 *  Created on: 03/03/2012
 *      Author: puente
 */

#ifndef PROPERMUTA_H_
#define PROPERMUTA_H_

#define _strdup strdup

#include "fitness/heft_service.h"
#include "host_parser.h"
#include "problema.h"
#include "workflow_parser.h"
#include <cstring>
#include <fstream>
#include <map>
class proPermuta : public problema {
 public:
  proPermuta(char* fichero, char* fichero2)
      : problema(fichero), fichHosts(_strdup(fichero2)) {
    // Read from workflow file and call parse workflow
    heftmatic::UnitParser unit_parser;
    std::ifstream workflow_stream(fichero);
    nlohmann::json json;
    workflow_stream >> json;
    workflow_json = heftmatic::ParseWorkflow(json);
    // Fix workflow
    // Fix missing children in the tasks
    // first: task_name second: task
    // std::map<std::string,unsigned int> task_to_id;
    int task_index = 0;
    for (const auto& task : workflow_json) {
      // We need to know the position of each task in the workflow vector
      task_to_id[task.first] = task_index;

      for (const auto& parent : task.second.parents)
        // Fix missing children
        if (std::find(workflow_json[parent].children.begin(),
                      workflow_json[parent].children.end(), task.second.name) ==
            workflow_json[parent].children.end()) {
          workflow_json[parent].children.push_back(task.second.name);
        }
      task_index++;
    }

    // Pre calculate coms
    // first: task_name second: task
    workflow =
        std::vector<std::vector<int>>(workflow_json.size(), vector<int>(0, 0));
    network_matrix = std::vector<std::vector<double>>(
        workflow_json.size(), vector<double>(workflow_json.size(), 0));
    task_bits_output = std::vector<double>(workflow_json.size(), 0);
    for (auto& task : workflow_json) {
      task_ids.push_back(task.first);
      double coms_inter_tasks = 0;
      task_bits_output[task_to_id[task.first]] =
          unit_parser.to_bits(task.second.files_output_size);

      for (auto& parent : task.second.parents) {
        workflow[task_to_id[task.first]].push_back(task_to_id[parent]);

        std::vector<heftmatic::TaskFile> files_in_common =
            heftmatic::HeftService::intersectionFiles(
                workflow_json[parent].files_output, task.second.files_input);
        double total_size = 0;
        for (auto& file : files_in_common) {
          total_size += file.size;
        }
        coms_inter_tasks += unit_parser.to_bits(total_size);

        network_matrix[task_to_id[parent]][task_to_id[task.first]] =
            unit_parser.to_bits(total_size);
      }

      // Add Stage in the same position as the task to be selected
      network_matrix[task_to_id[task.first]][task_to_id[task.first]] =
          unit_parser.to_bits(task.second.files_input_size) - coms_inter_tasks;
    }

    hosts_json = heftmatic::ParseHost(fichero2);
    // std::map<std::string,unsigned int> task_to_id;
    int host_index = 0;
    // hosts_ids.reserve(hosts_json.size());
    //  first: host_name second: host
    for (auto& host : hosts_json) {
      host_to_id[host.first] = host_index;
      hosts.emplace_back(host.second.network_speed_value, host.second.disk_speed_value);
      hosts_ids.push_back(host.first);
      host_index++;
    }

    computation_matrix = heftService.CreateComputationMatrix(
        workflow_json, hosts_json, "441Gf", task_to_id, host_to_id);
  }

  ~proPermuta() {
    if (fichHosts) delete[] fichHosts;
  }
  virtual int getSol() const { return -1; }

  int getTotalItems() const;
  /* Produce: el total de genes que tendria un cromosoma del problema
   */

 protected:
  char* fichHosts;

  // The workflow is defined as a vector of vector to get a list of parents
  // If we do a workflow[i] we can get the list of parents
  // We can't search for a specific parent, so we need to iterate
  // What we can find in the workflow[i][j] position is the id of the task
  vector<vector<int>> workflow;
  // The host is represented with a vector of pair of integers.
  // The first element is the network speed and the second is the disk speed.
  vector<std::pair<int, int>> hosts;

  // Time need it to execute task i in host j
  vector<vector<double>> computation_matrix;

  // Bytes transfer between task i and task j
  vector<vector<double>> network_matrix;

  vector<double> task_bits_output;

  std::map<std::string, unsigned int> task_to_id;
  std::map<std::string, unsigned int> host_to_id;

  vector<std::string> hosts_ids;
  vector<std::string> task_ids;

  std::map<std::string, heftmatic::Task> workflow_json;
  std::map<std::string, heftmatic::Host> hosts_json;

 public:
  const vector<std::pair<int, int>>& getHosts() const;
  const vector<vector<int>>& getWorkflow() const;
  const vector<std::string>& getHostsIds() const;
  const vector<std::string>& getTaskIds() const;
  const map<std::string, unsigned int>& getTaskToId() const;
  const map<std::string, unsigned int>& getHostToId() const;
  const vector<vector<double>>& getComputationMatrix() const;
  const vector<vector<double>>& getNetworkMatrix() const;
  const vector<double>& getTaskBitsOutput() const;
  const map<std::string, heftmatic::Task>& getWorkflowJson() const;
  const map<std::string, heftmatic::Host>& getHostsJson() const;

 private:
  heftmatic::HeftService heftService;
};

#endif /* PROPERMUTA_H_ */
