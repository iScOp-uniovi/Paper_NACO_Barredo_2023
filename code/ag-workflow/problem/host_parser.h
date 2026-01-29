//
// Created by Pablo Barredo on 29/4/21.
//

#ifndef HEFTMATIC_HOST_PARSER_H
#define HEFTMATIC_HOST_PARSER_H
#include <map>
#include <string>
#include <vector>
#include "tools/unit_parser.h"
namespace heftmatic {

struct Host {
  std::string name;
  std::string flops;
  int cores;
  std::string disk_speed;
  std::string network_speed;
  double network_speed_value;
  double disk_speed_value;

  auto operator==(const Host& rhs) const -> bool;
  auto operator<(const Host& rhs) const -> bool;
};

auto ParseHost(const std::string& hostJson)
    -> std::map<std::string, heftmatic::Host>;


}  // namespace heftmatic

//heftmatic::UnitParser unit_parser;

#endif  // HEFTMATIC_HOST_PARSER_H
