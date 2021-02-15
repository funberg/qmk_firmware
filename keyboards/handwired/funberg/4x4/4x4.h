#pragma once
#include "quantum.h"

#define LAYOUT( \
  K11, K12, K13, K14, \
  K21, K22, K23, K24, \
  K31, K32, K33, K34, \
  K41, K42, K43, K44 \
) { \
  {  K11, K12, K13, K14  }, \
  {  K21, K22, K23, K24  }, \
  {  K31, K32, K33, K34  }, \
  {  K41, K42, K43, K44  } \
}
