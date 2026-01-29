/*
 * proPermuta.cpp
 *
 *  Created on: 03/03/2012
 *      Author: puente
 */

#include "proPermuta.h"
#include <cstdlib>

int proPermuta::getTotalItems() const {
  /* Produce: el total de genes que tendria un cromosoma del problema
   */
  //  a modo de prueba transformamos el nombre en un numero "20" -> 20
  return atoi(this->nombreProblema());
}
const vector<std::pair<int, int>>& proPermuta::getHosts() const {
  return this->hosts;
}

const vector<vector<int>>& proPermuta::getWorkflow() const {
  return this->workflow;
}
const vector<std::string>& proPermuta::getHostsIds() const { return this->hosts_ids; }

const vector<std::string>& proPermuta::getTaskIds() const { return this->task_ids; }
const map<std::string, unsigned int>& proPermuta::getTaskToId() const {
  return task_to_id;
}
const map<std::string, unsigned int>& proPermuta::getHostToId() const {
  return host_to_id;
}

const vector<vector<double>>& proPermuta::getComputationMatrix() const {
  return computation_matrix;
}
const vector<vector<double>>& proPermuta::getNetworkMatrix() const {
  return network_matrix;
}
const vector<double>& proPermuta::getTaskBitsOutput() const {
  return task_bits_output;
}
const map<std::string, heftmatic::Task>& proPermuta::getWorkflowJson()
    const {
  return workflow_json;
}
const map<std::string, heftmatic::Host>& proPermuta::getHostsJson() const {
  return hosts_json;
}
