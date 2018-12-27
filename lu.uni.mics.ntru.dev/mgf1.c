//
// Created by Thibault Simonetto on 27/12/2018.
//

#include "mgf1.h"

static int8_t HASH_OUTPUT_SIZE = 32;
static int8_t MIN_CALLS_MASK_SIZE = 4;

void choose(uint8_t octet, uint8_t *c) {

    for (int i = 0; i < 5; ++i) {
        c[i] = (uint8_t) (octet % 3);
        octet = (uint8_t) ((octet - c[i]) / 3);
    }

}

uint8_t mgf1(uint8_t seed[], uint8_t seed_len, uint8_t min_calls_mask, uint8_t N, uint8_t *mask){

    uint8_t Z[36];

    sha256_hash(Z, seed, seed_len);

    uint8_t bufferSize = (uint8_t) (min_calls_mask * HASH_OUTPUT_SIZE);
    uint8_t *buffer = malloc(min_calls_mask * sizeof(uint8_t));


    uint8_t *ctr = Z +32;

    // Set counter to 0
    memset(ctr, 0, 4);

    for (uint8_t i = 0; i < min_calls_mask; ++i) {

        // Generate hash and add it to buffer
        sha256_hash((buffer + i*HASH_OUTPUT_SIZE), Z, (size_t) (HASH_OUTPUT_SIZE + MIN_CALLS_MASK_SIZE));

        // Increment ctr
        if (++ctr[3] == 0) {
            if (++ctr[2] == 0) {
                if (++ctr[1] == 0) {
                    ++ctr[0];
                }
            }
        }
    }

    uint8_t octet_available = bufferSize;
    uint8_t *octet = buffer;

    while (N >=5 ){

        if (octet_available == 0){
            return 1;
        }

        if (*octet < 243){
            choose(*octet, mask);
            mask +=5;
            N -= 5;
        }
        octet++;
        octet_available--;

    }

    while (N) {

        uint8_t trits [5];
        if (octet_available == 0){
            return 1;
        }

        if (*octet < 243){
            choose(*octet, trits);
            memcpy(mask, trits, N);
            N = 0;
        } else {
            octet++;
            --octet_available;
        }

    }

    free(buffer);

    return 0;

}
