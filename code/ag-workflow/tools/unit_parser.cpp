//
// Created by Pablo Barredo on 10/5/21.
//

#include "unit_parser.h"
#include <iostream>
#include <cmath>
#include <regex>
#include <cstdlib>

namespace heftmatic {
  auto UnitParser::parse_compute_speed(const std::string & string) -> double {
    std::regex rgx("([0-9]+\\.*[0-9]*)([A-z]+)f");
    std::smatch matches;
    double flops = -1;
    if (std::regex_search(string, matches, rgx)) {
      // Match found
      // Find exp and multiply by base Eg. 1000^3
      flops = std::atof(matches[1].str().c_str()) * pow(BASE_10, BASE10_PREFIXES[matches[2].str()]);

    } else {
      std::cout << "Match not found in compute speed\n";
      flops = -1;
    }
    return flops;
  }
  auto UnitParser::parse_network_speed(const std::string& string ) -> double {
    std::regex rgx("([0-9]+\\.*[0-9]*)([A-z]+)([Bb])ps");
    std::smatch matches;
    double speed = -1;
    if (std::regex_search(string, matches, rgx)){
      // Find exp and multiply by base
      speed = std::atof(matches[1].str().c_str()) * pow(BASE_10, BASE10_PREFIXES[matches[2].str()]);
      speed = speed * BIT_OR_BYTE[matches[3].str()];
    } else {
      std::cout << "Match not found in network speed" << string << "\n";
      speed = -1;
    }
    // in bits
    return speed;
    //return speed*8;
  }
  auto UnitParser::parse_file_size(std::string string) -> double {
    std::regex rgx("([0-9]+\\.*[0-9]*)([A-z]+)B");
    std::smatch matches;
    double size = -1;
    if (std::regex_search(string, matches, rgx)){
      // Find exp and multiply to get bytes
      size = std::atof(matches[1].str().c_str()) * pow(BASE_10, BASE10_PREFIXES[matches[2].str()]);
    } else {
      std::cout << "Match not found in file size";
      size=-1;
    }
    // in Bytes
    return size;
  }
  auto UnitParser::to_bits(double bytes) -> double {
    const double bits = 8;
    return bytes * bits;
  }
};// namespace heftmatic
