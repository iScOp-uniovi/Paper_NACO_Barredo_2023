//
// Created by pablo on 11/04/2022.
//
#include "cromosoma.h"
bool operator<(const Schedule& schedule1, const Schedule& schedule2) {
  return schedule1.ast < schedule2.ast;
}
