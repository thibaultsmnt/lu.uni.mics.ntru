//
// Created by Thibault Simonetto on 27/12/2018.
//

#ifndef NTRUE_MGF1_H
#define NTRUE_MGF1_H

#include <stdint.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include "sha256.h"

void choose(uint8_t octet, uint8_t *c);
uint8_t mgf1(uint8_t seed[], uint8_t seed_len, uint8_t min_calls_mask, uint8_t N, uint8_t *mask);


#endif //NTRUE_MGF1_H
