//
// Created by Pablo Barredo on 10/5/21.
//

#ifndef HEFTMATIC_UNIT_PARSER_H
#define HEFTMATIC_UNIT_PARSER_H
#include <map>
#include <string>
#include <vector>
namespace heftmatic {
class UnitParser {
 public:
  auto parse_compute_speed(const std::string & string) -> double;
  auto parse_network_speed(const std::string& string) -> double;
  auto parse_file_size(std::string string) -> double;
  auto to_bits(double bytes) -> double;

 private:
  std::map<std::string, int64_t> BASE2_PREFIXES = {
      {"Ki", 1}, {"Mi", 2}, {"Gi", 3}, {"Ti", 4},
      {"Pi", 5}, {"E", 6},  {"Z", 7},  {"Y", 8}};
  std::map<std::string, int64_t> BASE10_PREFIXES = {
      {"K", 1}, {"M", 2}, {"G", 3}, {"T", 4},
      {"P", 5}, {"E", 6}, {"Z", 7}, {"Y", 8}};
  std::map<std::string, int64_t> BIT_OR_BYTE = {{"B", 8}, {"b", 1}};
  const double BASE_10 = 1000;
  const double BASE_2 = 1024;
};

}  // namespace heftmatic

#endif  // HEFTMATIC_UNIT_PARSER_H
