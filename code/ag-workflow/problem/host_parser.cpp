//
// Created by Pablo Barredo on 29/4/21.
//
#include "host_parser.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

namespace heftmatic {

auto ParseHost(const std::string& hostJson)
    -> std::map<std::string, heftmatic::Host> {

  heftmatic::UnitParser unit_parser;
  // Load json from file
  std::ifstream host_stream(hostJson.c_str());
  std::map<std::string, heftmatic::Host> hosts;
  nlohmann::json host_json;
  host_stream >> host_json;

  // loop over hosts
  for (auto machine : host_json.at("machines")) {
    heftmatic::Host host;
    host.name = machine["name"];
    host.flops = machine["cpu_speed"];
    std::string cores_str = machine["cores"];
    host.cores = std::stoi(cores_str);
    host.disk_speed = machine["disk_speed"];
    host.network_speed = machine["network_speed"];
    // Calculate network speed
    host.network_speed_value =
        unit_parser.parse_network_speed(host.network_speed);
    host.disk_speed_value =
        unit_parser.parse_network_speed(host.disk_speed);


    // Add to map
    hosts[host.name] = host;
  }

  return hosts;
}

bool Host::operator==(const Host& rhs) const {
  return name == rhs.name && flops == rhs.flops && cores == rhs.cores &&
         disk_speed == rhs.disk_speed && network_speed == rhs.network_speed;
}
bool Host::operator<(const Host& rhs) const {
  if (name < rhs.name) return true;
  if (rhs.name < name) return false;
  if (flops < rhs.flops) return true;
  if (rhs.flops < flops) return false;
  if (cores < rhs.cores) return true;
  if (rhs.cores < cores) return false;
  if (disk_speed < rhs.disk_speed) return true;
  if (rhs.disk_speed < disk_speed) return false;
  return network_speed < rhs.network_speed;
}

}  // namespace heftmatic
